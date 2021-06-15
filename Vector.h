#include "VectorIterator.h"
#include <stdexcept>
#include <iostream>

#pragma once

class Vector
{
	int* digits;
	size_t _size;
	size_t _capacity;

public:
	Vector() : _size(0), _capacity(0) 
	{
		digits = new int[1];
	};

	Vector(const Vector& vec);
	Vector(const int* vec, size_t num);

	void print()
	{
		for (int i : *this)
			std::cout << i << ' ';
		std::cout << std::endl;
	}

	size_t size() const { return _size; };
	size_t length() const { return _size; };
	size_t capacity() const { return _capacity - 1; };

	~Vector() 
	{
		if (digits != nullptr)
			delete[] digits; 
	};

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

	int& front() { return *begin(); };
	int& back() { return *(end() - 1); };

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

		digits = new int[1];
	}

	VectorIterator insert(const VectorIterator& it, int&& element);
	VectorIterator insert(const VectorIterator& it, size_t count, int&& element);
	VectorIterator insert(const VectorIterator& _where, const VectorIterator& l_it, const VectorIterator& r_it);

	VectorIterator erase(const VectorIterator& it);
	VectorIterator erase(const VectorIterator& l_it, const VectorIterator& r_it);

	void push_back(int&& element);
	void pop_back() { _size--; };

	void resize(size_t actual_size);
	void swap(Vector& other);
};
