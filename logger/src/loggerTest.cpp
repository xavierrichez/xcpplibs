#include "Logger.h"
#include <iostream>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cerr<<"log::verbosity must be set"<<std::endl;
		exit(0);
	}
	int level = atoi(argv[1]);
	log::setup((log::LogLevel)level);
	log::error("loggerTest", "main", "test error");
	log::warn("loggerTest",  "main", "test warn");
	log::info("loggerTest",  "main", "test info");
	log::debug("loggerTest", "main", "test debug");
	log::trace("loggerTest", "main", "test trace");
}


