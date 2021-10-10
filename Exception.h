#ifndef _EXCEPTION_H
#define _EXCEPTION_H
#include<exception>
#include<iostream>
using namespace std;

class VarNotAvailableException : public exception
{
public:
	VarNotAvailableException(const char* msg) :exception(msg) { };
};
class TokenNotReady: public exception
{
public:
	TokenNotReady(const char* msg) :exception(msg) { };
};
#endif