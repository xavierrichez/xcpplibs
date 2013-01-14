#include "PingChannel.h"
#include <xcpplibs/logger.h>

static const char *className = "PingChannel";

PingChannel::PingChannel(const char *channelName, MessageHandler<Ping> *handler):
MessageChannel<Ping>(channelName, handler)
{
	xlog::trace(className, "constructor");
}

PingChannel::~PingChannel()
{
	xlog::trace(className, "destructor");
}
