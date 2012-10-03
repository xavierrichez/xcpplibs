#include <iostream>
#include <string>
#include "logger.h"

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
	std::string strLevel = l;
	if ((strLevel == "TRACE") || (strLevel == "Trace") || (strLevel == "trace"))
		xlog::level = xlog::level_TRACE;
	else if ((strLevel == "DEBUG") || (strLevel == "Debug") || (strLevel == "debug"))
		xlog::level = xlog::level_DEBUG;
	else if ((strLevel == "INFO") || (strLevel == "Info") || (strLevel == "info"))
		xlog::level = xlog::level_INFO;
	else if ((strLevel == "WARN") || (strLevel == "Warn") || (strLevel == "warn"))
		xlog::level = xlog::level_WARN;
	else if ((strLevel == "ERROR") || (strLevel == "Error") || (strLevel == "error"))
		xlog::level = xlog::level_ERROR;
	else if ((strLevel == "NO_LOG") || (strLevel == "No_log") || (strLevel == "no_log"))
		xlog::level = xlog::level_NO_LOG;
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
		std::string msg = "!! ERROR -->> ";
		
		if (class_name)
			msg = msg + class_name;
		if (operation)
			msg = msg + "::" + operation + "  ";
		if (message)
			msg = msg + message;		
			
		if (! msg.empty())			
		{
			std::clog<<msg<<std::endl;
		}
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
		std::string msg = "- WARN - ";
		
		if (class_name)
			msg = msg + class_name;
		if (operation)
			msg = msg + "::" + operation + "  ";
		if (message)
			msg = msg + message;		
			
		if (! msg.empty())			
		{
			std::clog<<msg<<std::endl;
		}
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
		std::string msg = " (INFO) ";
		
		if (class_name)
			msg = msg + class_name;
		if (operation)
			msg = msg + "::" + operation + "  ";
		if (message)
			msg = msg + message;	
		if (! msg.empty())			
		{
			std::clog<<msg<<std::endl;
		}
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
		std::string msg = "  DEBUG  ";
		if (class_name)
			msg = msg + class_name;
		if (operation)
			msg = msg + "::" + operation + "  ";
		if (message)
			msg = msg + message;	
		if (! msg.empty())			
		{
			std::clog<<msg<<std::endl;
		}
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
		std::string msg = "  TRACE  ";
		if (class_name)
			msg = msg + class_name;
		if (operation)
			msg = msg + "::" + operation + "  ";
		if (message)
			msg = msg + message;	
		if (! msg.empty())			
		{
			std::clog<<msg<<std::endl;
		}
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
	if (class_name)
		msg = msg + class_name;
	if (operation)
		msg = msg + "::" + operation + "  ";
	if (message)
		msg = msg + message;
		
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
		std::string msg = std::string("System error : ") + message;
		std::cerr<<msg<<std::endl;
	}
}


//===============================================
void xlog::fatal(const char *message)
//===============================================
{
	if (message)
	{
		std::string msg = std::string("Fatal error ! The program will exit. Message is :\n") + message;
		std::cerr<<msg<<std::endl;
	}
}

