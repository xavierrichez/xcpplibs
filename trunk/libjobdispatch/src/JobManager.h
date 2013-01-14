#ifndef JOBMANAGER_H_
#define JOBMANAGER_H_

#include <string>
#include "JobInfo.hpp"

class JobManager {
public:
	JobManager() {};
	virtual ~JobManager() {};

	virtual void jobCompleted(const std::string &jobID)=0;
	virtual void batchCompleted()=0;

	virtual JobInfo getJobInfo(const std::string &jobID)=0;
};

#endif /* JOBMANAGER_H_ */
