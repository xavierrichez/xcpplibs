/**********************************************************************************
 * Logger.h : some useful (abstract) functions for debug
 *//*******************************************************************************
 * Copyright (C) 2006 by Xavier Richez
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
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 **********************************************************************************/
#ifndef _Logger_H
#define _Logger_H

#include <string>

namespace log
{
	typedef enum { UNDEFINED=-1, TRACE, DEBUG, INFO, WARN, ERROR, NO_LOG } LogLevel;
	extern LogLevel verbosity;
	
	void setup(const char *filename);
	void setup(LogLevel verbosity);
	
	/// error message if log::verbosity is lower or equal to ERROR
	void error(const char *class_name, const char *operation, const char *message=NULL);
	void error(const char *message);
	
	/// warn message if log::verbosity is lower or equal to WARN
	void warn(const char *class_name, const char *operation, const char *message=NULL);
	void warn(const char *message);
	
	/// info message if log::verbosity is lower or equal to INFO
	void info(const char *class_name, const char *operation, const char *message=NULL);
	void info(const char *message);
	
	/// debug message if log::verbosity is lower or equal to DEBUG
	void debug(const char *class_name, const char *operation, const char *message=NULL);
	void debug(const char *message);

	/// trace message if log::verbosity is lower or equal to TRACE
	void trace(const char *class_name, const char *operation, const char *message=NULL);
	void trace(const char *message);
	
	/// message.
	void msg(const char *class_name, const char *operation, const char *message=NULL);
	void msg(const char *message);

	/// system error !.
	void syserr(const char *message);

	/// fatal error !.
	void fatal(const char *message);
};

#endif
