#include <vector>
#include <iostream>    
#include <cstring> 
#include <memory>
#include <mutex>
#include <condition_variable>
#include "list.h"



node::node(node *new_next, value *new_data):next(new_next), data(new_data){};
node* node::get_next() {return this -> next;};
value* node::get_data() {return this -> data;};
node::~node() {delete this -> data;};

list::list(){this -> head = nullptr;};
list::list(node* new_head): head(new_head){};
node* list::get_head() {return this -> head;};
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
		
	
