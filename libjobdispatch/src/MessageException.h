#ifndef MESSAGEEXCEPTION_H_
#define MESSAGEEXCEPTION_H_

#include <exception>
#include "stringcollections.h"

class MessageException: public std::exception {
public:
   inline MessageException(const std::string &s) : message(s) {}
   inline ~MessageException() throw() {}
   inline const char* what() const throw() { return message.c_str(); }
private:
   std::string message;
};

#endif /* PROCESSEXCEPTION_H_ */
