#ifndef JOBDISPATCHCHANNEL_H_
#define JOBDISPATCHCHANNEL_H_

#include "MessageChannel.h"
#include "MessageHandler.h"
#include "JobInfo.hpp"

/**
 * Canal de messages pour l'envoi de commandes par le master
 */
class JobDispatchChannel : public MessageChannel<JobInfo> {
public:
	JobDispatchChannel(const char *channelName, MessageHandler<JobInfo> *handler=NULL);
	virtual ~JobDispatchChannel();
	std::string getPingChannelName() const;
};

#endif /* JOBDISPATCHCHANNEL_H_ */
