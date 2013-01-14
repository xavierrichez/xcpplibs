#include "JobDispatchChannel.h"
#include <xcpplibs/logger.h>
#include <iostream>

static const char *className = "ProcessingChannel";

JobDispatchChannel::JobDispatchChannel(const char *channelName, MessageHandler<JobInfo> *handler):
	MessageChannel<JobInfo>(channelName, handler)
{
	xlog::trace(className, "constructor");
}

JobDispatchChannel::~JobDispatchChannel()
{
	xlog::trace(className, "destructor");
}

std::string JobDispatchChannel::getPingChannelName() const
{
	xlog::trace(className, "getPingChannelName");

	return this->m_channelName + "_PING";
}
