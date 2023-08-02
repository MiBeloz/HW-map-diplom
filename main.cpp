#include <iostream>
#include <chrono>

#include "thread_pool.h"
#include "my_functions.h"

using namespace std::chrono_literals;


int main() {
	setlocale(LC_ALL, "ru");
	std::cout << "\tПотокобезопасная очередь\n\n" << std::endl;

	int threads = std::thread::hardware_concurrency();
	thread_pool th_pool;

	for (size_t i = 0; i < threads / 2; ++i){
		th_pool.submit(std::function<void()>(print_name));
		th_pool.submit(std::function<void()>(print_surname));
		th_pool.work();
		th_pool.work();
		std::this_thread::sleep_for(1000ms);
	}

	system("pause > nul");
	return 0;
}
