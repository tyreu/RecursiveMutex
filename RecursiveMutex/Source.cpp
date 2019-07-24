#include <iostream>
#include <shared_mutex>
#include <atomic>
using namespace std;

class shared_recursive_mutex : public mutex
{
public:
	void lock(void) {
		std::thread::id this_id = std::this_thread::get_id();
		if (owner == this_id) 
			// recursive locking
			count++;
		else {
			// normal locking
			mutex::lock();
			owner = this_id;
			count = 1;
		}
	}
	void unlock(void) 
	{
		if (count > 1) 
			// recursive unlocking
			count--;
		else {
			// normal unlocking
			owner = std::thread::id();
			count = 0;
			mutex::unlock();
		}
	}

private:
	std::atomic<std::thread::id> owner;
	int count;
}; 

int main()
{
	return 0;
}