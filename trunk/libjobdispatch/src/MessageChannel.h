#ifndef MESSAGECHANNEL_H_
#define MESSAGECHANNEL_H_

/**********************************************************************************
 * MessageChannel : Generic communication channel.
 *
 **********************************************************************************
 * Copyright (C) 2012 by Xavier Richez
 * xavier[.]richez[@]laposte.net
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 **********************************************************************************/

#include <xcpplibs/logger.h>
#include <lcm/lcm-cpp.hpp>
#include <boost/thread.hpp>
#include "stringcollections.h"
#include "MessageHandler.h"
#include "MessageException.h"
#ifdef _WIN32
#include <lcm/windows/WinPorting.h>
#else
#include <sys/time.h>
#include <sys/select.h>
#endif

template <class T> class MessageChannel {

public:
	MessageChannel(const char *channelName, MessageHandler<T> *handler=NULL);
	virtual ~MessageChannel();

	const std::string & getChannelName() const;

	const std::vector< MessageHandler<T> *> &getMessageHandlers() const;
	void addMessageHandler(MessageHandler<T> *handler);

	bool sendMessage(const T &message);
	void handleMessages();
	bool waitForMessageWithTimeout(int secondsToWait);

protected:

	std::string		m_channelName;
	lcm::LCM		m_lcm;
	std::vector< MessageHandler<T> *> m_handlers;

};

template <class T> MessageChannel<T>::MessageChannel(const char *channelName, MessageHandler<T> *handler):
	m_channelName(channelName),
	m_lcm(),
	m_handlers()
{
	xlog::trace("MessageChannel", "constructor");

	if (!m_lcm.good())
	    xlog::fatal("Communication layer is not ready. Any firewall or network issue ?");

	if (handler)
	{
		addMessageHandler(handler);
	}
}

template <class T> MessageChannel<T>::~MessageChannel()
{
	xlog::trace("MessageChannel", "destructor");

	m_handlers.clear();
}

template <class T> const std::string & MessageChannel<T>::getChannelName() const
{ return m_channelName; }

template <class T> const std::vector< MessageHandler<T> *> &MessageChannel<T>::getMessageHandlers() const
{ return m_handlers; }

template <class T> void MessageChannel<T>::addMessageHandler(MessageHandler<T> *handler)
{
	xlog::trace("MessageChannel", "addMessageHandler");

	m_handlers.push_back(handler);

	// we shoud subscribe the channel to receive the messages
	xlog::debug("MessageChannel", "addMessageHandler", ("subscribe to channel "+m_channelName).c_str());
	lcm::Subscription *subscription = m_lcm.subscribe(m_channelName.c_str(), &MessageHandler<T>::handleMessage, handler);
	if (subscription != NULL)
		subscription->setQueueCapacity(100);
}


template <class T> void MessageChannel<T>::handleMessages()
{
	xlog::trace("MessageChannel", "handleMessages", m_channelName.c_str());

	if (m_handlers.empty())
	{
		xlog::error("MessageChannel", "handleMessages", "No message handler defined");
		throw MessageException("No message handler defined");
	}

	try {
		if (m_lcm.handle() != 0)
		{
			if (! m_lcm.good())
			{
				xlog::fatal("Communication error !");
			}
			else
				xlog::debug("MessageChannel", "handleMessages", "communication ok");
		}
	} catch (std::exception &e) {
		xlog::error("MessageChannel", "handleMessages", (std::string("exception : ")+e.what()).c_str());
	}
}

template <class T> bool MessageChannel<T>::waitForMessageWithTimeout(int secondsToWait)
{
	xlog::trace("MessageChannel", "waitForMessageWithTimeout", m_channelName.c_str());
	//@see lcm/examples/c/listener-async.c

	int internalLcmPipe = m_lcm.getFileno();
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(internalLcmPipe, &fds);

	// wait a limited amount of time for an incoming message
	struct timeval timeout = {
		1,  // seconds
		0   // microseconds
	};
	int waitStatus = select(internalLcmPipe + 1, &fds, 0, 0, &timeout);

	if (waitStatus == 0)
	{
		xlog::trace("MessageChannel", "waitForMessageWithTimeout", "timeout expired, no message");
		return false;
	}
	else if (waitStatus < 0)
	{
		xlog::warn("MessageChannel" "waitForMessageWithTimeout", "socket error !!");
		return false;
	}
	else
	{
		if (FD_ISSET(internalLcmPipe, &fds))
		{
			// LCM has events ready to be processed.
			xlog::trace("MessageChannel", "waitForMessageWithTimeout", "messages available");
			return true;
		}
		else
		{
			xlog::debug("MessageChannel", "waitForMessageWithTimeout", "no more message available");
			return false;
		}
    }
}

template <class T> bool MessageChannel<T>::sendMessage(const T &message)
{
	xlog::trace("MessageChannel", "sendMessage", (std::string("on ")+m_channelName).c_str());

	m_lcm.publish(m_channelName, &message);
	
	return true;
}

#endif /* MESSAGECHANNEL_H_ */
