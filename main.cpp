#include <algorithm>
#include <iostream>
#include <vector>

#include "Vector.h"
#include "VectorIterator.h"

int main()
{
	std::vector<int> v;
	v.reserve(100);
	v.reserve(5);
	std::cout << v.capacity() << std::endl;
	std::cout << sizeof(v) << std::endl;
	v.insert(v.end(), 1);
	auto it = v.insert(v.begin(), 1000);
	for (int i : v)
		std::cout << i;
	std::cout << std::endl << *it;

	int* a = new int[6];
	
	for (int i = 0; i < 6; ++i)
		a[i] = i;

	Vector vec(a, 6);

	std::cout << "Fifth element is " << vec.at(5) << std::endl;
	vec.at(5) = 100;
	std::cout << "Fifth element is " << vec.at(5) << std::endl;

	std::cout << "Fifth element is " << vec[5] << std::endl;
	vec[5] = 10000;
	std::cout << "Fifth element is " << vec[5] << std::endl;

	for (int i : vec)
		std::cout << i << ' ';
	std::cout << std::endl;

    //std::cout << *std::find(vec.begin(), vec.end(), 3) << std::endl;

	std::cout << "First element of container is " << vec.front() << std::endl;
	std::cout << "Last element of container is " << vec.back() << std::endl;
	std::cout << "Adress of container: " << vec.data() << std::endl;
	std::cout << "Is container empty? - " << vec.empty() << std::endl;
	std::cout << "The size of container is " << vec.size() << std::endl;

	std::cout << "Capacity: " << vec.capacity() << std::endl;
	vec.reserve(1000);
	std::cout << "Capacity: " << vec.capacity() << std::endl;

	for (int i : vec)
		std::cout << i << ' ';
	std::cout << std::endl;

	vec.insert(vec.begin(), 1);
	vec.insert(vec.begin() + 3, 999);
	vec.clear();
	vec.insert(vec.begin(), 876);

	for (int i : vec)
		std::cout << i << ' ';

	return 0;
}