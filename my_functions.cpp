#include "my_functions.h"


void print_name() {
	std::this_thread::sleep_for(2000ms);
	std::cout << "Михаил" << std::endl;
}

void print_surname() {
	std::this_thread::sleep_for(1000ms);
	std::cout << "Белозеров" << std::endl;
}
