#include "JobDispatcher.h"
#include <string>
#include <iostream>
#include <boost/thread.hpp>
#include <xcpplibs/logger.h>
#include "JobHandler.h"
#include "JobManager.h"

short JobDispatcher::defaultWaitTime = 1 ;
static const char *	className="JobDispatcher";

JobDispatcher::JobDispatcher(const char *channelName, JobManager *jobMgr):
	m_waitTime(defaultWaitTime),
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
	xlog::trace(className, "addNewJob", (m_dispatchChannel.getChannelName()+" <<-- "+jobID).c_str());

	m_jobList.push_back(jobID);
}

void JobDispatcher::dispatchJobs()
{
	xlog::trace(className, "dispatchJobs", m_dispatchChannel.getChannelName().c_str());

	bool firstLaunch = true;
	if (m_jobList.size() > 0)
		while (! m_jobsDone)
	{
		/* until all jobs are completed, we keep waiting for a ping.
		 * but we wait with a timeout : provided this timeout expires, the dispatcher broadcasts the services
		 */

		if (m_pingChannel.waitForMessageWithTimeout(m_waitTime))
		{	// a service answered
			m_pingChannel.handleMessages();
		}
		else
		{	// the timeout expired without message
			if (m_jobList.empty())
			{
				if (m_jobsInProgress.empty())
				{
					m_jobsDone = true;
					xlog::debug(className, "dispatchJobs", "completed batch");
					continue;
				}
				else
					xlog::info(className, "dispatchJobs", ("waiting for "+m_jobsInProgress.begin()->first+" to complete its job on "+ m_dispatchChannel.getChannelName()).c_str());
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
		}
	}
}


/**
 * Callback function, triggered when a ping is received from a service
 **/
void JobDispatcher::notifyMessage(const Ping *serviceInfo)
{
	xlog::trace(className, "notifyMessage", ("ping from "+serviceInfo->processId).c_str());

	if (! serviceInfo)
	{
		xlog::warn(className, "notifyMessage", "empty message");
		return;
	}

	std::string pID = serviceInfo->serviceId;

	if (m_jobsInProgress.count(pID))
	{	// the service sent a ping, so it has completed its previous job
		xlog::debug(className, "notifyMessage", (pID+" completed "+m_jobsInProgress[pID]).c_str());
		m_jobsInProgress.erase(pID);
	}

	if (! m_jobList.empty())
	{	// new job to assign
		xlog::debug(className, "notifyMessage", ("service '"+pID+"' is available").c_str());
		m_waitTime = 10;

		JobInfo job;
		std::string jobID;
		bool foundJob=false;
		do
		{
			jobID = *(m_jobList.begin());
			m_jobList.erase(m_jobList.begin());
			if (! m_jobManager->getJobInfo(jobID, job))
			{
				xlog::warn(className, "notifyMessage", ("document skipped : '"+jobID+"' ("+job.fileToProcess+")").c_str());
			}
			else
			{
				foundJob=true;
				xlog::info(className, "notifyMessage", ("new doc to process by "+pID+" : "+job.fileToProcess).c_str());
			}
		} while ((! foundJob) && (! m_jobList.empty()));

		if (foundJob)
		{
			// the new job gets the "being processed" status
			m_jobsInProgress[pID]=jobID;

			// shipping the message
			job.serviceId=pID;
			m_dispatchChannel.sendMessage(job);
		}
		else 
		{
			m_jobsDone = m_jobsInProgress.empty();
		}
	}
	else
	{
		xlog::debug(className, "notifyMessage", ("all jobs completed by "+serviceInfo->serviceId).c_str());
		m_jobsDone = m_jobsInProgress.empty();
	}
}

