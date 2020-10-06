#include <iostream>
#include "Containers/Vector.hpp"

void Print(const nstd::Vector<int>& vec) {
	for (size_t i = 0; i < vec.size(); ++i)
		std::cout << vec[i] << " ";

	std::cout << std::endl;
}

int main() {
	nstd::Vector<int> vec1{ -3, -460, -22, 46, 100 };
	nstd::Vector<int> vec2;
	
	Print(vec1);
	Print(vec2);

	std::cin.get();

	return 0;
}