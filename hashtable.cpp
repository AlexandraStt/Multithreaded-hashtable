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
	//std::cout << new_key << " " << hash << std::endl << std::endl;
	
	while (true)
	{
		if(!this -> hashes[hash] -> get_head())
		{
			//std::cout << "111" << std::endl;
			if ((this -> hashes[hash] -> m).try_lock())
			{
				//std::cout << "111" << std::endl;
				node *new_node = new node(this -> hashes[hash] -> get_head(), new_value);
 				this -> hashes[hash] -> set_head(new_node);
 				(this -> hashes[hash] -> m).unlock();
 				//std::cout << *this;	
				break;
				
			}
		}
		else
		{
			if ((this -> hashes[hash] -> get_head() ->  m).try_lock())
			{
				//std::cout << "222" << std::endl;
				//std::lock_guard<std::mutex> lg(this -> hashes[hash] -> get_head() -> m);
				//(this -> hashes[hash] -> get_head() -> m).lock();
				node *new_node = new node(this -> hashes[hash] -> get_head(), new_value);
				new_node -> m.lock();
				
		 		this -> hashes[hash] -> set_head(new_node);
		 		//после этой команды может другой оператор начать выполнять цикл
		 		(new_node -> get_next() ->  m).unlock();
		 		new_node -> m.unlock();
		 		//std::cout << *this;	
		 		break;
		 	}
		}
		
			
	}
	//std::cout << *this;		
	
	/*
	if (!this -> hashes[hash])
	{
		std::lock_guard<std::mutex> lg(this -> hashes[hash] -> get_head() -> get_mutex());
		node *new_node = new node(this -> hashes[hash] -> get_head(), new_value);
 		this -> hashes[hash] -> set_head(new_node);
	}
	else
	{
		
		list *new_list = new list(new node(nullptr, new_value));
		this -> hashes[hash] = new_list;
	}
	*/	
}

void threadsafe_hashtable::add_many_randoms()
{
	for (int i = 0; i < 100; i++)
	{
		char* new_str = nullptr;
		value *v = new value(new_str, i);
		this -> add(v -> get_int(), v);
	}
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
		os << i << ": " << std::endl;
		if (ht.hashes[i] -> get_head())
		{
			node *nd = ht.hashes[i] -> get_head();
			while (nd)
			{
				os << nd -> get_data() -> get_int() << " ";
				//os << nd -> get_data() -> get_str() << " " << std::endl;
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







