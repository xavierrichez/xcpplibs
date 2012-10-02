/**********************************************************************************
 * Autorestart.c : autorestart process
 *//*******************************************************************************
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
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 **********************************************************************************/

/// see http://www.highscore.de/boost/process0.5/boost_process/tutorial.html#boost_process.tutorial.starting_a_program

#include <iostream>
#include <unistd.h>
#include <boost/process.hpp>

using namespace boost::process;
using namespace boost::process::initializers;

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cerr<<"Please indicated a command line to execute"<<std::endl;
		std::cout<<"Example : autorestart my_process -my_param1 -my_param2 my_argument"<<std::endl;
	}

	std::string cmdLine = argv[1];
	for(int i=2; i<argc; i++)
		cmdLine.append(argv[i]).append(" ");

	boost::iostreams::file_descriptor_sink cmdLog(std::string(argv[1]).append(".log"), BOOST_IOS::out);		
	while (true)
	{
#if defined(BOOST_POSIX_API)
		signal(SIGCHLD, SIG_IGN);
#endif
		child c = execute(
			run_exe(argv[1]),
			set_cmd_line(cmdLine),
			start_in_dir("."),
			bind_stdout(cmdLog),
			bind_stderr(cmdLog),
			inherit_env()
		);
#if defined(BOOST_WINDOWS_API)
		c.discard();
#endif
		std::clog<<"Program stopped, restart"<<std::endl;
	}

	std::cout<<"Autorestart killed"<<std::endl;
}
