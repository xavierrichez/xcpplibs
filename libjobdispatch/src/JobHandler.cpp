#include "JobHandler.h"
#include <string>
#include <fstream>
#include <iostream>
#include <boost/thread.hpp>
#include <xcpplibs/logger.h>

static const char *className="JobHandler";
short 		JobHandler::MaxBroadcastNumber	= 20;
const char *JobHandler::BroadcastStartupID	="MasterJustStarted";
const char *JobHandler::BroadcastID		="MasterBroadcast";
int 		JobHandler::ReadRetryInterval	= 8;
int			JobHandler::ReadRetryNumber		= 8;

JobHandler::JobHandler(const std::string &serviceId, const char *channelName):
	m_serviceId(serviceId),
	m_dispatchChannel(channelName, this),
	m_pingChannel(m_dispatchChannel.getPingChannelName().c_str()),
	m_available(true),
	m_ignoreBroadcast(false),
	m_broadcastCounter(0)
{
	xlog::trace(className, "constructor");
}

JobHandler::~JobHandler()
{
	xlog::trace(className, "destructor");
}

void JobHandler::plug()
{
	xlog::trace(className, "plug");

	sendPing();
	while (true)
	{
		m_dispatchChannel.waitForMessage();
	}
}

/**
 * Fonction qui envoie un simple ping au master
 */
void JobHandler::sendPing()
{
	xlog::trace(className, "sendPing");

	Ping ping;
	ping.serviceId=m_serviceId;
	ping.available=m_available;
	m_pingChannel.sendMessage(ping);
}


/**
 * fonction (callback) declenchee quand le service recoit une commande
 * la commande peut etre destinee a ce service, mais aussi a un autre service
 */
void JobHandler::notifyMessage(const JobInfo *job)
{
	xlog::trace(className, "notifyMessage");

	if (! job)
	{
		xlog::warn(className, "notifyMessage", "empty message");
		return;
	}

	if (job->serviceId == BroadcastStartupID)
	{ 	// sent on master start
		xlog::debug(className, "notifyMessage", "master started");
		sendPing();
		m_ignoreBroadcast = false;
	}
	else if (job->serviceId == BroadcastID)
	{ 	// broadcast from the master
		if (! m_ignoreBroadcast)
		{
			sendPing();
			xlog::debug(className, "notifyMessage", "replied to broadcast");
			m_ignoreBroadcast = true;
		}
		else
		{
			xlog::debug(className, "notifyMessage", "broadcast ignored");
			m_broadcastCounter++;
			if (m_broadcastCounter > MaxBroadcastNumber)
			{
				m_ignoreBroadcast = false;
				m_broadcastCounter= 0;
			}
		}
	}
	else if (m_serviceId == job->serviceId)
	{ 	// if the current instructions are for this processor, launch the process
		m_available = false;
		handle(job);
		m_available = true;
		m_ignoreBroadcast = false;
	}
	else
	{	// job for another service
		xlog::debug(className, "notifyMessage", ("message to "+job->serviceId).c_str());
	}
}

#ifdef TESTING
#include <iostream>
class BasicJobHandler : public JobHandler
{
public:
	BasicJobHandler(const std::string &serviceId, const char *channelName);
	void process(const JobInfo *job);
};

BasicJobHandler::BasicJobHandler(const std::string &serviceId, const char *channelName):
	JobHandler(serviceId, channelName)
{;}

void BasicJobHandler::process(const JobInfo *job)
{
	std::cout<<"new job !\n";
	if (job != NULL)
	{
		std::cout<<job->sourceDocument<<" as "<<job->fileParameters<<std::endl;
	}
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cerr<<"usage : "<<argv[0]<<" lang [logLevel]"<<std::endl;
		exit(EXIT_FAILURE);
	}

	xlog::setLogLevel(xlog::level_WARN);
	const char * lang = argv[1];
	if (argc > 2)
		xlog::setLogLevel(argv[2]);

	BasicJobHandler langProcess(lang, ProcessingChannel::ChannelDocumentEtiq(lang).c_str());
	langProcess.plug();
}

#endif
