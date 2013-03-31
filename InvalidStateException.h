/* 
 * File:   InvalidStateException.h
 * Author: dcostinett
 * mailto:danco@uw.edu
 *
 * Created on March 31, 2013, 5:50 AM
 */
#if !defined INVALIDSTATEEXCEPTION_H_ALREADY_DEFINED
#define INVALIDSTATEEXCEPTION_H_ALREADY_DEFINED

#include "Assignment01.h"

class InvalidStateException : public std::exception
{
public:
	InvalidStateException(std::string msg);
};


#endif	/* INVALIDSTATEEXCEPTION_H */

