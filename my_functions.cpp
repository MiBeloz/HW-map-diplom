#include "my_functions.h"


std::mutex mtx_cout;

void print_name() noexcept {
	std::lock_guard<std::mutex> lg(mtx_cout);
	std::cout << "Михаил" << std::endl;
}

void print_surname() noexcept {
	std::lock_guard<std::mutex> lg(mtx_cout);
	std::cout << "Белозеров" << std::endl;
}
