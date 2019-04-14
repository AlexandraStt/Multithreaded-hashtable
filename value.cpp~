#include <vector>
#include <iostream>    
#include <cstring> 
#include <memory>
#include <mutex>
//#include <condition_variable>
#include "value.h"


value::value(value const &other)
{
	this -> str = new char[20];
	strcpy(this -> str, other.str);
	this -> some_int = other.some_int;
}

value::value(char* other_str, int other_int)
{
	this -> str = other_str;
	this -> some_int = other_int;
}

char* value::get_str() {return this -> str;};

int value::get_int() {return this -> some_int;};

value::~value()
{
	if (this -> str)
		delete [] this -> str;
}
	
