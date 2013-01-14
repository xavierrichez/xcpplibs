#ifndef MESSAGECHANNEL_H_
#define MESSAGECHANNEL_H_

#include <xcpplibs/logger.h>
#include <lcm/lcm-cpp.hpp>
#include "MessageHandler.h"
#include "MessageException.h"
#include "stringcollections.h"

template <class T> class MessageChannel {

public:
	MessageChannel(const char *channelName, MessageHandler<T> *handler=NULL);
	virtual ~MessageChannel();

	const std::string & getChannelName() const;

	const MessageHandler<T> *getMessageHandler() const;
	void setMessageHandler(MessageHandler<T> *handler);

	bool sendMessage(const T &message);
	void waitForMessage();

protected:
	void handleMessage(const lcm::ReceiveBuffer* rbuf, const std::string& channelName, const T* messageData);

	std::string		m_channelName;
	lcm::LCM		m_lcm;
	lcm::Subscription *m_lcmSubscription;
	MessageHandler<T> *m_handler;

};

template <class T> MessageChannel<T>::MessageChannel(const char *channelName, MessageHandler<T> *handler):
	m_channelName(channelName),
	m_lcm(),
	m_lcmSubscription(NULL),
	m_handler(handler)
{
	xlog::trace("MessageChannel", "constructor");

	if (!m_lcm.good())
	    xlog::fatal("Communication layer is not ready. Any firewall or network issue ?");

	if (m_handler)
	{
		// if the user provided a message handler, we shoud subscribe the channel to receive the messages
		xlog::debug("MessageChannel", "constructor", (std::string("subscribe to channel ")+channelName).c_str());
		m_lcmSubscription = m_lcm.subscribe(m_channelName.c_str(), &MessageChannel<T>::handleMessage, this);
	}
}

template <class T> MessageChannel<T>::~MessageChannel()
{
	xlog::trace("MessageChannel", "destructor");

	if (m_handler)
	{
		// we should NOT delete the message handler
		m_handler=NULL;
	}

	if (m_lcmSubscription)
	{
		m_lcm.unsubscribe(m_lcmSubscription);
		m_lcmSubscription=NULL;
	}
}

template <class T> const std::string & MessageChannel<T>::getChannelName() const
{ return m_channelName; }

template <class T> const MessageHandler<T> *MessageChannel<T>::getMessageHandler() const
{ return m_handler; }

template <class T> void MessageChannel<T>::setMessageHandler(MessageHandler<T> *handler)
{ m_handler = handler; }


template <class T> void MessageChannel<T>::waitForMessage()
{
	xlog::trace("MessageChannel", "waitForMessage", m_channelName.c_str());

	if (!m_handler)
	{
		xlog::error("MessageChannel", "waitForMessage", "Message handler not defined");
		throw MessageException("Message handler not defined");
	}

	try {
		if (m_lcm.handle() != 0)
		{
			if (! m_lcm.good())
			{
				xlog::fatal("Communication error !");
			}
			xlog::debug("MessageChannel", "waitForMessage", "lcm good");
		}
	} catch (std::exception &e) {
		xlog::syserr(e.what());
	}
}

template <class T> void MessageChannel<T>::handleMessage(const lcm::ReceiveBuffer* rbuf, const std::string& channelName, const T* messageData)
{
	xlog::trace("MessageChannel", "handleMessage", channelName.c_str());

	m_handler->notifyMessage(messageData);
}

template <class T> bool MessageChannel<T>::sendMessage(const T &message)
{
	xlog::trace("MessageChannel", "sendMessage", (std::string("on ")+m_channelName).c_str());

	m_lcm.publish(m_channelName, &message);
	
	return true;
}

#endif /* MESSAGECHANNEL_H_ */
