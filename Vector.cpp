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
		_capacity = num;

		int* temp = new int[_size];
		for (size_t i = 0; i < _size; ++i)
			temp[i] = digits[i];

		delete[] digits;
		digits = temp;
	}

}

VectorIterator Vector::insert(const VectorIterator& it, int&& element)
{
	_size++;

	if (_capacity >= _size)  // если максимальная величина не превышает текущий размер
	{
	    int dif = std::distance(begin(), it);

	    for (size_t i = _size; i > dif; i--)
	        digits[i] = digits[i - 1];

	    *it = element;

	    return it;
	}
	else
	{
	    int dif = std::distance(begin(), it);

		reserve(1.5 * _capacity);

        for (size_t i = _size; i > dif; i--)
            digits[i] = digits[i - 1];

        *(begin() + dif) = element;

        return begin() + dif + 1;
	}
}

VectorIterator Vector::insert(const VectorIterator& it, size_t count, int&& element)
{
	_size += count;
    int dif = std::distance(begin(), it);

	if (_capacity < _size)
        while (_capacity < _size)
            reserve(1.5 * _capacity);

    for (size_t i = _size + count - 1; i > dif - 1; i--)
        digits[i] = digits[i - count];

    for (int i = dif; i < dif + count; i++)
        digits[i] = element;

    return begin() + dif + count;
}

VectorIterator Vector::insert(const VectorIterator& _where, const VectorIterator& l_it, const VectorIterator& r_it)
{
    int dif = std::distance(l_it, r_it);
    int beg_dif = std::distance(begin(), _where);
    VectorIterator temp_it = l_it;
    _size += dif;

    if (_size > _capacity)
        while (_size + dif > _capacity)
            reserve(1.5 * _capacity);

    for (int i = _size + dif - 1; i > beg_dif - 1; i--)
        digits[i] = digits[i - dif];

    for (int i = beg_dif; i < beg_dif + dif; i++)
    {
        digits[i] = *l_it;
        l_it;
    }

    return begin() + beg_dif;
}

VectorIterator Vector::erase(const VectorIterator& it)
{
	size_t dif = std::distance(begin(), it);
	for (int i = dif; i < _size - 1; i++)
	    digits[i] = digits[i + 1];
	_size--;
	return begin() + dif;
}

VectorIterator Vector::erase(const VectorIterator& l_it, const VectorIterator& r_it)
{
	size_t dif = std::distance(l_it, r_it);
	size_t beg_dif = std::distance(begin(), l_it);
	size_t end_dif = std::distance(begin(), r_it);
	for (int i = beg_dif; i < end_dif; i++)
	    digits[i] = digits[i + dif];
	_size -= dif;
	return begin() + dif;
}

void Vector::push_back(int&& element)
{
	if (_capacity >= _size)
	{
		_size++;
		digits[_size - 1] = element;
	}
	else
	{
		reserve(1.5 * _capacity);
		_size++;
		digits[_size - 1] = element;
	}
}

void Vector::resize(size_t actual_size)
{
	int* temp = new int[_size];

	for (size_t i = 0; i < _size; i++)
		temp[i] = digits[i];

	delete[] digits;
	digits = new int[actual_size];

	if (actual_size < _size)
		for (size_t i = 0; i < actual_size; i++)
			digits[i] = temp[i];
	else
	{
		for (size_t i = 0; i < _size; i++)
			digits[i] = temp[i];

		for (size_t i = _size; i < actual_size; i++)
			digits[i] = 0;
	}

	delete[] temp;
	_size = actual_size;
	if (_capacity < _size)
		_capacity = _size;
}

void Vector::swap(Vector& other)
{
	Vector temp = *this;
	*this = other;
	other = temp;
}
