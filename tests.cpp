#include <valgrind/drd.h>
#define _GLIBCXX_SYNCHRONIZATION_HAPPENS_BEFORE(addr) ANNOTATE_HAPPENS_BEFORE(addr)
#define _GLIBCXX_SYNCHRONIZATION_HAPPENS_AFTER(addr)  ANNOTATE_HAPPENS_AFTER(addr)

#include <gtest/gtest.h>
#include <functional>
#include "hashtable.h"
#include <ctime>
#include <chrono>
#include <thread>

typedef std::chrono::high_resolution_clock Clock;

//using namespace std;

TEST(TestHashTable, Test1)
{
	int n = 2;
	std::thread threads[n];
	int prime = 100;
	threadsafe_hashtable *ht = new threadsafe_hashtable(prime);
	for (int i = 0; i < n; i++)
	{
		//char* new_str = nullptr;
		//value *v = new value(new_str, rand()% 20000);
		threads[i] = std::thread(&threadsafe_hashtable::add_many_randoms, &(*ht));
	}
	
	for (int i = 0; i < n; i++)
		threads[i].join();
	std::cout << *ht << std::endl;
	delete ht;
	ASSERT_TRUE(true);
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	
}
