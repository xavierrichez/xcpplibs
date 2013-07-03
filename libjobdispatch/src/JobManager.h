#ifndef JOBMANAGER_H_
#define JOBMANAGER_H_

/**********************************************************************************
 * JobManager : abstract class used by the JobDispatcher to get the job content.
 *
 **********************************************************************************
 * Copyright (C) 2012 by Xavier Richez
 * xavier[.]richez[@]laposte.net
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 **********************************************************************************/

#include <string>
#include "JobInfo.hpp"

class JobManager {
public:
	JobManager() {};
	virtual ~JobManager() {};

	virtual bool getJobInfo(const std::string &jobID, JobInfo &job)=0;
};

#endif /* JOBMANAGER_H_ */
