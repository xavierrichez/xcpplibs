#ifndef MESSAGEHANDLER_H_
#define MESSAGEHANDLER_H_

/**********************************************************************************
 * MessageHandler : abstract class used by the MessageChannel.
 * Any message subscriber should extend MessageHandler.
 * @see JobHandler
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

#include <lcm/lcm-cpp.hpp>

template <class T> class MessageHandler
{
public:
	virtual ~MessageHandler() {;}

	void handleMessage(const lcm::ReceiveBuffer* rbuf, const std::string& channelName, const T* messageData);
	virtual void notifyMessage(const T *messageData)=0;
};

template <class T> void MessageHandler<T>::handleMessage(const lcm::ReceiveBuffer* rbuf, const std::string& channelName, const T* messageData)
{
	notifyMessage(messageData);
}

#endif /* MESSAGEHANDLER_H_ */
