#pragma once

#ifndef LIST_H
#define LIST_H

#include "value.h"

class node
{
	private:
		node* next;
		value* data;
	public:
		mutable std::mutex m;
		node(node *new_next, value *new_data);
		node* get_next();
		value* get_data();
		~node();
};

class list
{
	private:
		node* head;
		std::condition_variable cond;
		
	public:
		mutable std::mutex m;
		list(node* new_node);
		list();
		node* get_head();
		void set_head(node* new_head);
		~list();
		
		
		
};

#endif
