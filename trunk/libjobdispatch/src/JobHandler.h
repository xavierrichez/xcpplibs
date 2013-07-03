#ifndef JOBHANDLER_H_
#define JOBHANDLER_H_

/**********************************************************************************
 * JobHandler : client service prototype.
 * A service implementation only has to extend this class and to implement the handle(job) function.
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

#include <string>
#include "MessageHandler.h"
#include "JobInfo.hpp"
#include "JobDispatchChannel.h"
#include "PingChannel.h"

class JobHandler : public MessageHandler<JobInfo>
{
public:
	JobHandler(const std::string &serviceId, const char *channelName);
	virtual ~JobHandler();

	void plug();

public:
	static const char *BroadcastStartupID;
	static const char *BroadcastID;
	static short MaxBroadcastNumber;
	static int ReadRetryInterval;

protected:
	void sendPing();
	void notifyMessage(const JobInfo *command);
	virtual void handle(const JobInfo *job)=0;

	std::string 		m_serviceId;
	JobDispatchChannel	m_dispatchChannel;
	PingChannel			m_pingChannel;
	bool				m_available;
	bool				m_ignoreBroadcast;
	int					m_broadcastCounter;
};

#endif /* JOBHANDLER_H_ */
