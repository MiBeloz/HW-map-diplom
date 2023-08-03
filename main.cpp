#include <iostream>
#include <chrono>

#include "thread_pool.h"
#include "my_functions.h"

using namespace std::chrono_literals;


int main() {
	setlocale(LC_ALL, "ru");
	std::cout << "\tПотокобезопасная очередь\n\n" << std::endl;

	const short threads = std::thread::hardware_concurrency();
	std::cout << "Количество аппаратных ядер: " << threads << std::endl << std::endl;

	thread_pool th_pool(threads);

	while (!th_pool.is_full()) {
		th_pool.submit(std::function<void()>(print_name));
		th_pool.submit(std::function<void()>(print_surname));
		th_pool.work_all();
		std::this_thread::sleep_for(1000ms);

	} 

	std::cout << "\n------------------------------------" << std::endl;
	std::cout << "Все процессы завершены" << std::endl;

	system("pause > nul");
	return 0;
}
