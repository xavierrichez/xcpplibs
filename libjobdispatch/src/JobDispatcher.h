#ifndef JOBDISPATCHER_H_
#define JOBDISPATCHER_H_

/**********************************************************************************
 * JobDispatcher : dispatches jobs to the clients, using a JobDispatchChannel.
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
#include "Ping.hpp"
#include "PingChannel.h"
#include "JobDispatchChannel.h"
#include "JobManager.h"

class JobDispatcher : public MessageHandler<Ping> {
public:
	JobDispatcher(const char *channelName, JobManager *jobMgr);
	virtual ~JobDispatcher();

	void addNewJob(const std::string &jobID);
	void dispatchJobs();

public:
	static short defaultWaitTime;

private:
	void notifyMessage(const Ping *messageData);

protected:
	int					m_waitTime;
	stringvector		m_jobList;
	bool				m_jobsDone;
	JobManager *		m_jobManager;
	stringmap			m_jobsInProgress;
	JobDispatchChannel	m_dispatchChannel;
	PingChannel			m_pingChannel;
};

#endif /* JOBDISPATCHER_H_ */
