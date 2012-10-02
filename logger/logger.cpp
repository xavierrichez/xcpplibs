#include <iostream>
#include <string>
#include "Logger.h"

log::LogLevel log::verbosity = UNDEFINED;

/// Setup the logger.
//===============================================
void log::setup(const char *filename)
//===============================================
{
	// TODO : parse config file
}

/// Setup the logger.
//===============================================
void log::setup(LogLevel level)
//===============================================
{
	log::verbosity = level;
}


/// Error message.
//===============================================
void log::error(const char *class_name, const char *operation, const char *message)
//===============================================
{
	if (log::verbosity == UNDEFINED)
		msg("log", "error", "No value for log::verbosity !");
	else if (log::verbosity <= ERROR)
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
void log::error(const char *message)
//===============================================
{
	error(NULL, NULL, message);
}


/// Warn message.
//===============================================
void log::warn(const char *class_name, const char *operation, const char *message)
//===============================================
{
	if (log::verbosity == UNDEFINED)
		msg("log", "warn", "No value for log::verbosity !");
	else if (log::verbosity <= WARN)
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
void log::warn(const char *message)
//===============================================
{
	warn(NULL, NULL, message);
}


/// Info message.
//===============================================
void log::info(const char *class_name, const char *operation, const char *message)
//===============================================
{
	if (log::verbosity == UNDEFINED)
		msg("log", "info", "No value for log::verbosity !");
	else if (log::verbosity <= INFO)
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
void log::info(const char *message)
//===============================================
{
	info(NULL, NULL, message);
}


/// Debug message.
//===============================================
void log::debug(const char *class_name, const char *operation, const char *message)
//===============================================
{
	if (log::verbosity == UNDEFINED)
		msg("log", "debug", "No value for log::verbosity !");
	else if (log::verbosity <= DEBUG)
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
void log::debug(const char *message)
//===============================================
{
	debug(NULL, NULL, message);
}


/// Trace message.
//===============================================
void log::trace(const char *class_name, const char *operation, const char *message)
//===============================================
{
	if (log::verbosity == UNDEFINED)
		msg("log", "trace", "No value for log::verbosity !");
	else if (log::verbosity <= TRACE)
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
void log::trace(const char *message)
//===============================================
{
	trace(NULL, NULL, message);
}


/// Message.
//===============================================
void log::msg(const char *class_name, const char *operation, const char *message)
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
void log::msg(const char *message)
//===============================================
{
	msg(NULL, NULL, message);
}


//===============================================
void log::syserr(const char *message)
//===============================================
{
	if (message)
	{
		std::string msg = std::string("System error : ") + message;
		std::cerr<<msg<<std::endl;
	}
}


//===============================================
void log::fatal(const char *message)
//===============================================
{
	if (message)
	{
		std::string msg = std::string("Fatal error ! The program will exit. Message is :\n") + message;
		std::cerr<<msg<<std::endl;
	}
}

