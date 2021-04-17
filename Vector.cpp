#include "Vector.h"

Vector::Vector(const int* vec, size_t num) : _size(num), _capacity(_size + 1)
{
	digits = new int[_capacity];

	for (int i = 0; i < _size; ++i)
		digits[i] = vec[i];
}

Vector::Vector(const Vector& vec) : _size(vec._size), _capacity(vec._capacity)
{
	if (_capacity == 1)
		digits = new int[1];
	else
	{
		digits = new int[_capacity];

		for (int i = 0; i < _size; ++i)
			digits[i] = vec.digits[i];
	}
}

Vector& Vector::operator=(const Vector& other)
{
	if (this != &other)
	{
		if (_capacity != other._capacity)
		{
			delete[] digits;
			_capacity = other._capacity;
			_size = other._size;
			digits = new int[_capacity];
		}

		for (int i = 0; i < _size; ++i)
			digits[i] = other.digits[i];
	}

	return *this;
}

void Vector::reserve(size_t num)
{
	if (num > _capacity)
	{

	}
}

VectorIterator Vector::insert(const VectorIterator& it, int element)
{
	if (_size != 0)
	{
		int* temp = new int[_size + 1];

		for (size_t i = 0; i < *it; ++i)
			temp[i] = digits[i];
		temp[*it] = element;

		for (size_t i = *it + 1; i < _size + 1; ++i)
			temp[i] = digits[i - 1];

		delete[] digits;
		if (_capacity == _size)
			_capacity++;
		_size++;
		digits = new int[_size];

		for (int i = 0; i < _size; ++i)
			digits[i] = temp[i];
		delete[] temp;

	}
	else
	{
		digits = new int[1];
		digits[*it] = element;
	}
	return it - 1;
}