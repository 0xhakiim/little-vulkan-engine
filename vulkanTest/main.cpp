
#include "first_app.hpp"

#include <iostream>
int main() {

	lve::FirstApp app{}; //rotating triangle app
	//lve::two_bodies app{}; //two bodies simulation app
	try {
		app.run();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return 0;
}