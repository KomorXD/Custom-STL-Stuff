#include <iostream>
#include "Containers/Vector.hpp"

void Print(const nstd::Vector<int>& vec) {
	for (size_t i = 0; i < vec.size(); ++i)
		std::cout << vec[i] << " ";

	std::cout << std::endl;
}

int main() {
	nstd::Vector<int> vec1{ 1, 2, 3, 4, 5 };

	vec1.emplace(vec1.begin() + 3, 70);

	Print(vec1);

	vec1.clear();
	
	std::cin.get();

	return 0;
}