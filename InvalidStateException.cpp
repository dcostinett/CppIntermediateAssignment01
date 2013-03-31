/*
InvalidStateException.cpp
Dan Costinett
danco@uw.edu

*/
#include "InvalidStateException.h"

InvalidStateException::InvalidStateException(std::string msg) : std::exception(msg.c_str())
{
	std::cout << msg.c_str() << std::endl;
}

