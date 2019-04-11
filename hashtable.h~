#pragma once

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "list.h"

class threadsafe_hashtable
{
	private:
		std::vector<list*> hashes;
		int prime;
		int get_hash(int key);
	public:
		threadsafe_hashtable(int prime_int);
		void add(int new_key, value *new_value);
		void add_many_randoms();
		~threadsafe_hashtable();
		
		friend std::ostream& operator<<(std::ostream& os, const threadsafe_hashtable& v);
	
};

std::ostream& operator<<(std::ostream& os, const threadsafe_hashtable& v);






#endif
