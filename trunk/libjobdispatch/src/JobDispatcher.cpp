#include "JobDispatcher.h"
#include <string>
#include <iostream>
#include <boost/thread.hpp>
#include <xcpplibs/logger.h>
#include "JobHandler.h"
#include "JobManager.h"

short JobDispatcher::defaultWaitTime = 2000 ;
static const char *	className="JobDispatcher";

JobDispatcher::JobDispatcher(const char *channelName, JobManager *jobMgr):
	m_waitTime(defaultWaitTime),
	m_broadcastCounter(0),
	m_jobList(),
	m_jobsDone(false),
	m_jobManager(jobMgr),
	m_jobsInProgress(),
	m_dispatchChannel(channelName),
	m_pingChannel(m_dispatchChannel.getPingChannelName().c_str(), this)
{
	xlog::trace(className, "constructor");
}


JobDispatcher::~JobDispatcher()
{
	xlog::trace(className, "destructor");
}

void JobDispatcher::addNewJob(const std::string &jobID)
{
	xlog::trace(className, "addNewJob", m_dispatchChannel.getChannelName().c_str());

	m_jobList.push_back(jobID);
}

void JobDispatcher::dispatchJobs()
{
	xlog::trace(className, "dispatchJobs", m_dispatchChannel.getChannelName().c_str());

	bool firstLaunch = true;
	boost::thread *timeoutCall=NULL;
	bool serviceAvailable = false;
	while (! m_jobsDone)
	{
		/* until all jobs are completed, we keep waiting for a ping.
		 * but we wait with a timeout : provided this timeout expires, the dispatcher broadcasts the services
		 * the boos::thread::timed_join returns :
		 * - true if the thread completed normally
		 * - false if the timeout expired before the thread completion
		 * but however the timeout expires, the thread remains still active !
		 */

		if (serviceAvailable || firstLaunch)
		{   // if a service answered, the thread is done. Renew it to wait for another service
			timeoutCall = new boost::thread(&JobDispatcher::waitForServices, this);
			serviceAvailable = false;
		}

		if (! timeoutCall->timed_join(boost::posix_time::milliseconds(m_waitTime)))
		{
			if (m_jobList.empty())
			{
				xlog::info(className, "dispatchJobs", ("waiting for services to complete on "+ m_dispatchChannel.getChannelName()).c_str());
			}
			else
			{
				xlog::info(className, "dispatchJobs", ("no service available on "+ m_dispatchChannel.getChannelName()+", sending broadcast").c_str());
			}

			JobInfo broadcast;
			if (firstLaunch)
			{
				broadcast.serviceId = JobHandler::BroadcastStartupID;
				firstLaunch = false;
			}
			else
				broadcast.serviceId = JobHandler::BroadcastID;

			m_dispatchChannel.sendMessage(broadcast);

			m_broadcastCounter++;
			if (m_broadcastCounter > 5)
			{
				m_waitTime = defaultWaitTime;
				if (m_broadcastCounter > JobHandler::MaxBroadcastNumber)
					m_waitTime = 10*defaultWaitTime;
			}
		}
		else
		{	// the thread completed before the timeout expiration
			serviceAvailable = true;
			delete timeoutCall;
		}
	}

	// tell the job manager that the batch is complete
	m_jobManager->batchCompleted();
}


void JobDispatcher::waitForServices()
{
	xlog::trace(className, "waitForServices");

	boost::this_thread::interruption_point();
	m_pingChannel.waitForMessage();
	boost::this_thread::interruption_point();
}


/**
 * Callback function, triggered when a ping is received from a service
 **/
void JobDispatcher::notifyMessage(const Ping *serviceInfo)
{
	xlog::trace(className, "notifyMessage", "ping");

	if (! serviceInfo)
	{
		xlog::warn(className, "notifyMessage", "empty message");
		return;
	}

	if (! serviceInfo->available)
	{
		xlog::info(className, "notifyMessage", ("service '"+serviceInfo->serviceId+"' is not available").c_str());
		return;
	}

	std::string pID = serviceInfo->serviceId;

	if (m_jobsInProgress.count(pID))
	{	// the service sent a ping, so it's completed its previous job
		m_jobManager->jobCompleted(m_jobsInProgress[pID]);
	}

	if (! m_jobList.empty())
	{	// new job to assign
		xlog::debug(className, "notifyMessage", ("service '"+pID+"' is available").c_str());
		m_waitTime = 10;
		m_broadcastCounter = 0;

		std::string jobID = m_jobList.front();
		JobInfo job = m_jobManager->getJobInfo(jobID);
		m_jobList.pop_front();
		xlog::info(className, "notifyMessage", ("new doc to process by "+pID+" : "+job.fileToProcess).c_str());

		// the new job gets the "being processed" status
		m_jobsInProgress[pID]=jobID;

		// shipping the message
		job.serviceId=pID;
		m_dispatchChannel.sendMessage(job);
	}
	else
	{
		xlog::debug(className, "notifyMessage", ("all jobs completed by "+serviceInfo->serviceId).c_str());
		m_jobsInProgress.erase(pID);
		m_jobsDone = m_jobsInProgress.empty();
	}
}

