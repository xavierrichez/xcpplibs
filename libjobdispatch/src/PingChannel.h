#ifndef PINGCHANNEL_H_
#define PINGCHANNEL_H_

#include "MessageChannel.h"
#include "MessageHandler.h"
#include "Ping.hpp"

/**
 * Canal de ping pour la sollicitation du master par les services clients
 */
class PingChannel : public MessageChannel<Ping> {
public:
	PingChannel(const char *channelName, MessageHandler<Ping> *handler=NULL);
	virtual ~PingChannel();
};

#endif /* PINGCHANNEL_H_ */
