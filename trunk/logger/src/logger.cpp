#include <iostream>
#include <string>
#include "logger.h"

xlog::LogLevel xlog::verbosity = UNDEFINED;

/// Error message.
//===============================================
void xlog::error(const char *class_name, const char *operation, const char *message)
//===============================================
{
	if (xlog::verbosity == UNDEFINED)
		msg("log", "error", "No value for xlog::verbosity !");
	else if (xlog::verbosity <= ERROR)
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
	if (xlog::verbosity == UNDEFINED)
		msg("log", "warn", "No value for xlog::verbosity !");
	else if (xlog::verbosity <= WARN)
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
	if (xlog::verbosity == UNDEFINED)
		msg("log", "info", "No value for xlog::verbosity !");
	else if (xlog::verbosity <= INFO)
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
	if (xlog::verbosity == UNDEFINED)
		msg("log", "debug", "No value for xlog::verbosity !");
	else if (xlog::verbosity <= DEBUG)
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
	if (xlog::verbosity == UNDEFINED)
		msg("log", "trace", "No value for xlog::verbosity !");
	else if (xlog::verbosity <= TRACE)
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

