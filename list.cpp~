#include <vector>
#include <iostream>    
#include <cstring> 
#include <memory>
#include <mutex>
//#include <condition_variable>
#include "list.h"



node::node(node *new_next, value *new_data):next(new_next), data(new_data){};
node::node():next(nullptr), data(nullptr){};
node* node::get_next() {return this -> next;};
value* node::get_value() {return this -> data;};
void node::lock(){this -> m.lock();};
void node::unlock(){this -> m.unlock();};
void node::set_value(value *new_data) {this -> data = new_data;};
void node::set_next(node *nd) {this -> next = nd;};
node::~node() {if (this -> data) delete this -> data;};





list::list(){this -> head = new node();};
list::list(node* new_head): head(new_head){};
node* list::get_head() {return this -> head;};

bool list::check_key(int key)
{
	node *prev, *curr;
	prev = head;
	prev -> lock();
	curr = head -> get_next();
	while (curr)
	{
		curr -> lock();
		if (curr -> get_value() -> get_int() == key)
		{
			prev -> unlock();
			curr -> unlock();
			return true;
		}
		  	
		prev -> unlock();
		prev = curr;
		curr = curr -> get_next();
	}
	
	prev -> unlock();
	return false;
};


std::vector<char*>* list::delete_key(int key)
{
	std::vector<char*> ans;

	node *prev, *curr;
	prev = head;
	prev -> lock();
	curr = head -> get_next();
	while (curr)
	{
		curr -> lock();
		if (curr -> get_value() -> get_int() == key)
		{
			ans.push_back(curr -> get_value() -> get_str());
			prev -> set_next(curr -> get_next());
			node *for_delete = curr;
			//curr -> get_next() -> lock();
			curr = curr -> get_next();
			for_delete -> unlock();
			delete for_delete;
			continue;
		}
		prev -> unlock();
		prev = curr;
		curr = curr -> get_next();
	}
		
	prev -> unlock();
	
	if (ans.size() == 0)
		return nullptr;
	else
		return &ans;
	
}




void list::push(int key, value *new_value)
{
	//std::cout << key << std::endl;
	node *new_nd = new node(nullptr, new_value);
	//this -> head -> lock();
	node *prev, *curr;
	prev = head;
	prev -> lock();
	curr = head -> get_next();
	while (curr)
	{
		curr -> lock();
		prev -> unlock();
		prev = curr;
		curr = curr -> get_next();
	}
	
	prev -> set_next(new_nd);
	prev -> unlock();	
}

void list::set_head(node* new_head) {this -> head = new_head;};

list::~list()
{	
	node *for_delete, *curr = this -> head;
	while (curr)
	{
		for_delete = curr;
		curr = curr -> get_next();
		delete for_delete;
	}
}
		
	
