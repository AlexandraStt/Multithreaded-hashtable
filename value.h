#pragma once

#ifndef VALUE_H
#define VALUE_H
	
#include <vector>
#include <iostream>    
#include <cstring> 
#include <memory>
#include <mutex>
//#include <condition_variable>

class value 
{
	private:
		char* str;
		int some_int;
	public:
		value() {};
		value(char* other_str, int other_int);
		value(value const &other);
		char* get_str();
		int get_int();
		~value();
};

#endif
