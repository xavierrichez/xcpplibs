/**********************************************************************************
 * Dummy.cpp : entry point of the application
 *//*******************************************************************************
 * Copyright (C) 2005 by Xavier Richez
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
 
#include "Bases.h"
#include <signal.h>
#include <fstream>
//
// functions
//===============================================
/// manage CTRL+C shortcut.
void quit(int value=0);
/// show the possible options.
void usage();
/// manage console args.
int process_args(int argc, char *argv[]);
//===============================================

//
// globals
//===============================================
/// output buffer
std::ofstream buffer;
/// filesize params
int destsize=0, actualsize=0;
/// size unit param
char unit=' ';
long int bytes=1;
//===============================================


/// Application entry point.
//===============================================
int main(int argc, char *argv[])
//===============================================
{
///>> CTRL+C management to properly exit (we never know !).
	signal(1, &quit);
	signal(SIGINT, &quit);

///>> Initialize random generator
	rdminit();

///>> Command-line option analysis.
	process_args(argc, argv);

///>> Feed random data into the file
	int i, max=destsize*bytes;
	char c;
	for(i=0; i<max; i++)
	{
		do
		{
			c=(rdm(256));
		}
		while (c=='\n');
		try 
        {
            buffer<<c;
        }
		catch (char *str)
        {
              std::cout<<"Error while writing : "<<str<<std::endl;
        }
		actualsize++;
	}

///>> Normal exit.
	//system("pause");
	std::cout<<"Finished\n";
	return 0;
}

/// Properly exit the program.
//===============================================
void quit(int value)
//===============================================
{
	buffer.close();
	if (value >= 0)
		std::cout<<"Filesize is ~"<<(int)(actualsize/bytes)<<" "<<unit<<"bytes"<<std::endl;
	exit(value);
}

/// Command arguments.
//===============================================
void usage()
//===============================================
{
	std::cout << "\nUsage :\n"
		"    dummy size [data_unit output_filename]\n\n"
    	"Generates a random file which fits to size.\n"
		"The data_unit parameter could be \"K\" for kilobyte,\n"
		"\"M\" for megabyte or \"G\" for gigabyte.\n"
		"Default is byte."
		<< std::endl;
		
	std::cout << "\nExample :\n"
		"    dummy 256 M usbkey.testfile\n";
}

/// Do what has to be done with the args.
//===============================================
int process_args(int argc, char *argv[])
//===============================================
{
	// there must be at least one param
	if (argc <= 1)
	{
		std::cerr<<"Not enough parameters !\n";
		usage();
		quit(-1);
 	}
	else
	{
		// the first parameter is the length
		destsize=atoi(argv[1]);
		
		// the second (optional) parameter is the unit
		if (argc > 2)
		{
		    unit=argv[2][0];
		    
		    // uppercase if needed to
		    if ((unit >= 'a') && (unit <='z'))
		    {
				unit = unit + 'A' - 'a';
			}
			
			// error case
			if ((
				 (unit != ' ') && (unit != 'B') && (unit != 'O') &&
				 (unit != 'K') && (unit != 'M') && (unit != 'G')
				 )
				|| (unit <='A') || (unit >='Z'))
			{
				std::cerr<<"Invalid data unit !\n";
				usage();
				quit(-2);
			}
			// else process
			else
			{
				switch (unit) {
					case ' ' : bytes=1; break;
					case 'B' : unit=' '; bytes=1; break;
					case 'O' : unit=' '; bytes=1; break;
					case 'K' : bytes=1024; break;
					case 'M' : bytes=1024*1024; break;
					case 'G' : bytes=1024*1024*1024; break;
					default : bytes=1; break;
				}
			}
			
			std::cout<<"Data unit is "<<unit<<"byte\n";
		}
		
		// the third (optional) parameter is the output filename
	    if (argc > 3)
	    {
			std::string output(argv[3]);
			char last=output[output.length()-1];
			// if the path is a directory			
			if (last == ':')
			{
				output += '\\';
				last='\\';
			}				
		    if ((last == '\\') || (last == '/'))
				output += "dummy.file";
   			try
   			{
				buffer.open(output.c_str());
				buffer.clear();
            }
            catch (char * str)
            {
				std::cout<<"Some error happened while opening file for writing : "
                           <<str<<std::endl;
				quit(-3);
            }
			std::cout<<"Outputting into "<<output<<std::endl;            
		}
		else
		{
			try
			{
				buffer.open("dummy.file");
				buffer.clear();
            }
			catch (char * str)
            {
                std::cout<<"Some error happened while opening file for writing : "
                           <<str<<std::endl;
				quit(-3);
            }
			std::cout<<"Ouputting into dummy.file\n";                  
		}
	}
	return 0;
}
