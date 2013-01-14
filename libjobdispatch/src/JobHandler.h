#ifndef JOBHANDLER_H_
#define JOBHANDLER_H_

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
	static int ReadRetryNumber;

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
