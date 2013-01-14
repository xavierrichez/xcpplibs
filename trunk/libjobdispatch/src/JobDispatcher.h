#ifndef JOBDISPATCHER_H_
#define JOBDISPATCHER_H_

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
	void waitForServices();

protected:
	int					m_waitTime;
	int					m_broadcastCounter;
	stringdeque			m_jobList;
	bool				m_jobsDone;
	JobManager *		m_jobManager;
	stringmap			m_jobsInProgress;
	JobDispatchChannel	m_dispatchChannel;
	PingChannel			m_pingChannel;
};

#endif /* JOBDISPATCHER_H_ */
