#include <valgrind/drd.h>
#define _GLIBCXX_SYNCHRONIZATION_HAPPENS_BEFORE(addr) ANNOTATE_HAPPENS_BEFORE(addr)
#define _GLIBCXX_SYNCHRONIZATION_HAPPENS_AFTER(addr)  ANNOTATE_HAPPENS_AFTER(addr)

#include <gtest/gtest.h>
#include <functional>
#include "hashtable.h"
#include <ctime>
#include <chrono>
#include <thread>

TEST(TestHashTable, TestAddRandoms)
{
	int n = 5;
	std::thread threads[n];
	int prime = 100;
	threadsafe_hashtable *ht = new threadsafe_hashtable(prime);
	for (int i = 0; i < n; i++)
	{
		threads[i] = std::thread(&threadsafe_hashtable::add_many_randoms, &(*ht));
	}
	
	for (int i = 0; i < n; i++)
		threads[i].join();
		
	std::cout << ht -> size() << std::endl;
	std::cout << *ht << std::endl;
	delete ht;
}

TEST(TestHashTable, TestAddThousand)
{
	int n = 5;
	std::thread threads[n];
	int prime = 199;
	threadsafe_hashtable *ht = new threadsafe_hashtable(prime);
	std::vector<std::vector<int>> a(n);
	for (int i = 0; i < 1000; i++)
	{
		a[i % n].push_back(i);
	}
	for (int i = 0; i < n; i++)
	{
		threads[i] = std::thread(&threadsafe_hashtable::add_vector, &(*ht), cref(a[i]));
	}
	
	for (int i = 0; i < n; i++)
		threads[i].join();
		
	std::cout << *ht << std::endl;
	delete ht;
}

TEST(TestHashTable, DeleteRandoms)
{
	int n = 5;
	std::thread threads[n];
	int prime = 200;
	threadsafe_hashtable *ht = new threadsafe_hashtable(prime);
	std::vector<std::vector<int>> a(n);
	for (int i = 0; i < 1000; i++)
	{
		a[i % n].push_back(i);
	}
	
	
	for (int i = 0; i < n; i++)
	{
		threads[i] = std::thread(&threadsafe_hashtable::add_vector, &(*ht), cref(a[i]));
	}
	
	for (int i = 0; i < n; i++)
		threads[i].join();
		
	std::cout << ht -> size() << std::endl;	
	std::cout << *ht << std::endl;
	
	for (int i = 0; i < n; i++)
	{
		threads[i] = std::thread(&threadsafe_hashtable::delete_many_randoms, &(*ht));
	}
	 
	for (int i = 0; i < n; i++)
		threads[i].join();
		
	std::cout << ht -> size() << std::endl;
	std::cout << *ht << std::endl;
	delete ht;
}


TEST(TestHashTable2, DeleteCertainKeys)
{
	int n = 5;
	std::thread threads[n];
	int prime = 200;
	threadsafe_hashtable *ht = new threadsafe_hashtable(prime);
	
	std::vector<std::vector<int>> a(n);
	for (int i = 0; i < 1000; i++)
		a[i % n].push_back(i);
	for (int i = 0; i < n; i++)
		threads[i] = std::thread(&threadsafe_hashtable::add_vector, &(*ht), cref(a[i]));
	for (int i = 0; i < n; i++)
		threads[i].join();
		
	std::cout << ht -> size() << std::endl;	
	std::cout << *ht << std::endl;
	
	std::vector<std::vector<int>> for_delete(n);
	for (int i = 0; i < 500; i++)
		for_delete[i % n].push_back(i);
	for (int i = 0; i < n; i++)
		threads[i] = std::thread(&threadsafe_hashtable::delete_vector, &(*ht), cref(for_delete[i])); 
	for (int i = 0; i < n; i++)
		threads[i].join();
		
	std::cout << ht -> size() << std::endl;
	std::cout << *ht << std::endl;
	delete ht;
}


TEST(TestHashTable, TestCheckRandoms)
{
	int n = 4;
	std::thread threads[n];
	int prime = 100;
	threadsafe_hashtable *ht = new threadsafe_hashtable(prime);
	
	for (int i = 0; i < n; i++)
		threads[i] = std::thread(&threadsafe_hashtable::add_many_randoms, &(*ht));
	
	for (int i = 0; i < n; i++)
		threads[i].join();
		
	std::cout << *ht << std::endl;
	
	for (int i = 0; i < n; i++)
		threads[i] = std::thread(&threadsafe_hashtable::check_random_keys, &(*ht));
	
	for (int i = 0; i < n; i++)
		threads[i].join();
			
	delete ht;
}


int main(int argc, char **argv)
{
	std::freopen("check_keys.txt", "w", stdout);
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	std::fclose(stdout);
	
}
