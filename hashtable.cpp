#include <vector>
#include <iostream>    
#include <cstring> 
#include <memory>
#include <mutex>
#include <condition_variable>
#include "hashtable.h"

int threadsafe_hashtable::get_hash(int key)
{
	return key % this -> prime;
}


threadsafe_hashtable::threadsafe_hashtable(int new_prime)
{
	this -> prime = new_prime;
	(this -> hashes).resize(new_prime);
	for (int i = 0; i < new_prime; i++)
		this -> hashes[i] = new list();
}

void threadsafe_hashtable::add(int new_key, value *new_value)
{	
	int hash = get_hash(new_key);
	
	this -> hashes[hash] -> push(new_key, new_value);
}


bool threadsafe_hashtable::check_key(int key)
{
	int hash = get_hash(key);
	return this -> hashes[hash] -> check_key(key);
	
}

std::vector<char*>* threadsafe_hashtable::delete_key(int key)
{
	std::vector<char*> ans;
	int hash = get_hash(key);	
	//if (this -> check_key(key))
		return this -> hashes[hash] -> delete_key(key);
	//else
		//return ans;
} 

void threadsafe_hashtable::add_many_randoms()
{
	for (int i = 0; i < 100; i++)
	{
		//char* new_str = new char[2];
		//new_str[0] = char(rand() % 23 + 48);
		char* new_str = nullptr;
		//new_str[1] = '\0';
		value *v = new value(new_str, rand() % 20000);
		this -> add(v -> get_int(), v);
	}
}


void threadsafe_hashtable::add_many(std::vector<int> const &a)
{
	 for (int i = 0; i < a.size(); i++)
	 {
	 	add(a[i], new value(nullptr, a[i]));
	 }
}

void threadsafe_hashtable::delete_many_randoms()
{
	 for (int i = 0; i < 100; i++)
	 {
	 	this -> delete_key(rand() % 1000);
	 }
}


void threadsafe_hashtable::check_random_keys()
{
	std::freopen("check_keys.txt", "a", stdout);
		
	for (int i = 0; i < 100; i++)
	{
		int for_check = rand() % 20000;
		if (this -> check_key(for_check))
		{
			std::printf("%d%s\n", for_check, " - yes");
		}
		else
		{
			std::printf("%d%s\n", for_check, " - no");
		}
	}	
	
	std::fclose(stdout);
		
}

threadsafe_hashtable::~threadsafe_hashtable()
{
	for (int i = 0; i < this -> prime; i++)
	{
		delete this -> hashes[i];
	}
}

std::ostream& operator<<(std::ostream& os, const threadsafe_hashtable& ht)
{
	for (int i = 0; i < ht.prime; i++)
	{
		os << i << ": ";
		if (ht.hashes[i] -> get_head() -> get_next())
		{
			node *nd = ht.hashes[i] -> get_head() -> get_next();
			while (nd)
			{
				os << nd -> get_value() -> get_int() << " ";
				//os << nd -> get_value() -> get_str() << " ;";
				nd = nd -> get_next();
			}
			std::cout << std::endl;
		}
		else
		{
			os << " --- " << std::endl;
		}
	}
	return os;

}







