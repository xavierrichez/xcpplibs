#ifndef PINGCHANNEL_H_
#define PINGCHANNEL_H_

/**********************************************************************************
 * PingChannel : this channel targets the master.
 * The client services use this channel to say "hi, I'm there!" to the master, so that they get some work to do.
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

#include "MessageChannel.h"
#include "MessageHandler.h"
#include "Ping.hpp"

class PingChannel : public MessageChannel<Ping> {
public:
	PingChannel(const char *channelName, MessageHandler<Ping> *handler=NULL);
	virtual ~PingChannel();
};

#endif /* PINGCHANNEL_H_ */
