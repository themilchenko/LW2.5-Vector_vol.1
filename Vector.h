#include "VectorIterator.h"
#include <stdexcept>

#pragma once

class Vector
{
	int* digits;
	size_t _size;
	size_t _capacity;

public:
	Vector() : digits(nullptr), _size(0), _capacity(0) { };
	Vector(const Vector& vec);
	Vector(const int* vec, size_t num);

	size_t size() const { return _size; };
	size_t length() const { return _size; };
	size_t capacity() const { return _capacity - 1; };

	~Vector() { delete[] digits; };

	Vector& operator=(const Vector& other);
	VectorIterator begin() const { return VectorIterator(&digits[0]); };
	VectorIterator end() const { return VectorIterator(&digits[_size]); };

	int& at(size_t index)
	{
		if ((index < _size) && (index >= 0))
			return digits[index];
		else
			throw std::out_of_range("Out of range");
	}

	int& operator[](size_t index) { return digits[index]; };

	int& front() { return *this->begin(); };
	int& back() { return *(this->end() - 1); };

	int* data() { return digits; };

	bool empty() const 
	{
		if (_size == 0)
			return true;
		else
			return false;
	}

	void reserve(size_t num);

	void clear() 
	{
		delete[] digits;
		_size = 0;
	}

	VectorIterator insert(const VectorIterator& it, int element);
};