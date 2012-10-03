#include "Logger.h"
#include <iostream>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cerr<<"xlog::verbosity must be set"<<std::endl;
		exit(0);
	}
	int level = atoi(argv[1]);
	xlog::setup((xlog::LogLevel)level);
	xlog::error("loggerTest", "main", "test error");
	xlog::warn("loggerTest",  "main", "test warn");
	xlog::info("loggerTest",  "main", "test info");
	xlog::debug("loggerTest", "main", "test debug");
	xlog::trace("loggerTest", "main", "test trace");
}


