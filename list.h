#pragma once

#ifndef LIST_H
#define LIST_H

#include "value.h"

class threadsafe_hashtable;

class node
{
	private:
		node* next;
		value* data;
		mutable std::mutex m;
	public:	
		node(node *new_next, value *new_data);
		node();
		node* get_next();
		value* get_value();
		void lock();
		void unlock();
		void set_value(value *new_data);
		void set_next(node *next);
		~node();
};



class list
{
	private:
		node* head;		
	public:
		mutable std::mutex m;
		list(node* new_node);
		list();
		node* get_head();
		bool check_key(int key);
		void delete_key(int key);
		void delete_and_get_key(int key, std::vector<char*>* ans);
		void push(int new_key, value *new_value);
		void set_head(node* new_head);
		~list();	
};

#endif
