#include <thread>
#include <atomic>
#include <vector>
#include <climits>

void busy_thread()
{
    while(true)
	{

	}
}

void slow_algorithm()
{
    for(long i =0;i<LONG_MAX;i++)
	{
            for(long j=0;j<LONG_MAX;j++)
		{
 		    volatile long x = i*j;
		}
	}
}

int main()
{
    std::vector<std::thread> threads;
    threads.emplace_back(busy_thread);
    threads.emplace_back(slow_algorithm);
    for (auto& t : threads)
	    t.join();
    return 0;
}

