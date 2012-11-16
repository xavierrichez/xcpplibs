#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "logger.h"

bool		   xlog::printDate = false;
static time_t  dateTime_t;
static char    dateTimeStr[40];
xlog::LogLevel xlog::level = level_UNDEFINED;

void xlog::setLogLevel(LogLevel l)
{
	xlog::level = l;
}

void xlog::setLogLevel(int l)
{
	xlog::level = (LogLevel)l;
}

void xlog::setLogLevel(const char *l)
{
	std::string strLevel(l);
	for(int i=0; i<strLevel.size(); i++)
		strLevel[i] = toupper(strLevel[i]);

	if (strLevel == "TRACE")
		xlog::level = xlog::level_TRACE;
	else if (strLevel == "DEBUG")
		xlog::level = xlog::level_DEBUG;
	else if (strLevel == "INFO")
		xlog::level = xlog::level_INFO;
	else if (strLevel == "WARN")
		xlog::level = xlog::level_WARN;
	else if (strLevel == "ERROR")
		xlog::level = xlog::level_ERROR;
	else if (strLevel == "NO_LOG")
		xlog::level = xlog::level_NO_LOG;
}

void xlog::enableDateTimeLog(bool enabled)
{
	xlog::printDate = enabled;
}

const char *xlog::dateTime()
{
	time (&dateTime_t);

	struct tm * timeinfo = localtime ( &dateTime_t );
	strftime(dateTimeStr, 40, "%Y-%m-%d %H:%M::%S", timeinfo);

	return dateTimeStr;
}

void formatMessage(std::string &result, const char *class_name, const char *operation, const char *message)
{
	if (xlog::printDate)
		result.append(xlog::dateTime()).append(" ");
	if (class_name)
		result.append(class_name);
	if (operation)
		result.append("::").append(operation);
	if (message)
		result.append(" - ").append(message);
}

/// Error message.
//===============================================
void xlog::error(const char *class_name, const char *operation, const char *message)
//===============================================
{
	if (xlog::level == level_UNDEFINED)
		msg("log", "error", "No value set for xlog::level !");
	else if (xlog::level <= level_ERROR)
	{
		std::string msg = "!!ERROR -->> ";
		formatMessage(msg, class_name, operation, message);
		std::cout<<msg<<std::endl;
	}
}

//===============================================
void xlog::error(const char *message)
//===============================================
{
	error(NULL, NULL, message);
}


/// Warn message.
//===============================================
void xlog::warn(const char *class_name, const char *operation, const char *message)
//===============================================
{
	if (xlog::level == level_UNDEFINED)
		msg("log", "warn", "No value set for xlog::level !");
	else if (xlog::level <= level_WARN)
	{
		std::string msg = "--WARN-- ";
		formatMessage(msg, class_name, operation, message);
		std::cout<<msg<<std::endl;
	}
}

//===============================================
void xlog::warn(const char *message)
//===============================================
{
	warn(NULL, NULL, message);
}


/// Info message.
//===============================================
void xlog::info(const char *class_name, const char *operation, const char *message)
//===============================================
{
	if (xlog::level == level_UNDEFINED)
		msg("log", "info", "No value set for xlog::level !");
	else if (xlog::level <= level_INFO)
	{
		std::string msg = "- INFO - ";
		formatMessage(msg, class_name, operation, message);
		std::cout<<msg<<std::endl;
	}
}

//===============================================
void xlog::info(const char *message)
//===============================================
{
	info(NULL, NULL, message);
}


/// Debug message.
//===============================================
void xlog::debug(const char *class_name, const char *operation, const char *message)
//===============================================
{
	if (xlog::level == level_UNDEFINED)
		msg("log", "debug", "No value set for xlog::level !");
	else if (xlog::level <= level_DEBUG)
	{
		std::string msg = "( DEBUG )";
		formatMessage(msg, class_name, operation, message);
		std::cout<<msg<<std::endl;
	}
}

//===============================================
void xlog::debug(const char *message)
//===============================================
{
	debug(NULL, NULL, message);
}


/// Trace message.
//===============================================
void xlog::trace(const char *class_name, const char *operation, const char *message)
//===============================================
{
	if (xlog::level == level_UNDEFINED)
		msg("log", "trace", "No value set for xlog::level !");
	else if (xlog::level <= level_TRACE)
	{
		std::string msg = "((TRACE))";
		formatMessage(msg, class_name, operation, message);
		std::cout<<msg<<std::endl;
	}
}

//===============================================
void xlog::trace(const char *message)
//===============================================
{
	trace(NULL, NULL, message);
}


/// Message.
//===============================================
void xlog::msg(const char *class_name, const char *operation, const char *message)
//===============================================
{
	std::string msg;
	formatMessage(msg, class_name, operation, message);
	if (! msg.empty())
	{
		std::cout<<msg<<std::endl;
	}	
}

//===============================================
void xlog::msg(const char *message)
//===============================================
{
	msg(NULL, NULL, message);
}


//===============================================
void xlog::syserr(const char *message)
//===============================================
{
	if (message)
	{
		std::string msg;
		if (printDate)
			msg.append(dateTime()).append(" ");
		msg.append("System error : ").append(message);
		std::cerr<<msg<<std::endl;
	}
}


//===============================================
void xlog::fatal(const char *message)
//===============================================
{
	if (message)
	{
		std::string msg;
		if (printDate)
			msg.append(dateTime()).append(" ");
		msg.append("Fatal error ! The program will exit. Message is :\n").append(message);
		std::cerr<<msg<<std::endl;
	}
	exit(EXIT_FAILURE);
}


/// Trace message.
//===============================================
void xlog::fatal(const char *class_name, const char *operation, const char *message)
//===============================================
{
	if ((! class_name) && (! operation))
		xlog::fatal(message);

	else
	{
		std::string msg;
		if (printDate)
		{
			msg.append(dateTime()).append(" ");
			xlog::printDate = false;
		}
		msg.append("Fatal error ! The program will exit. Message is :\n");
		formatMessage(msg, class_name, operation, message);
		std::cerr<<msg<<std::endl;
	}
	exit(EXIT_FAILURE);
}
