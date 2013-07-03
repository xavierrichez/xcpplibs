#ifndef MESSAGEEXCEPTION_H_
#define MESSAGEEXCEPTION_H_

/**********************************************************************************
 * MessageException : Thrown on communication error.
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
 **********************************************************************************/

#include <exception>
#include <string>

class MessageException: public std::exception {
public:
   inline MessageException(const std::string &s) : message(s) {}
   inline ~MessageException() throw() {}
   inline const char* what() const throw() { return message.c_str(); }
private:
   std::string message;
};

#endif /* MESSAGEEXCEPTION_H_ */
