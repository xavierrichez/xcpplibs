#ifndef JOBDISPATCHCHANNEL_H_
#define JOBDISPATCHCHANNEL_H_

/**********************************************************************************
 * JobDispatchChannel : this channel targets the services.
 * The master sends the jobs on this channel.
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
#include "JobInfo.hpp"

class JobDispatchChannel : public MessageChannel<JobInfo> {
public:
	JobDispatchChannel(const char *channelName, MessageHandler<JobInfo> *handler=NULL);
	virtual ~JobDispatchChannel();
	std::string getPingChannelName() const;
};

#endif /* JOBDISPATCHCHANNEL_H_ */
