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
		digits = new int[_capacity];
		for (size_t i = 0; i < _size; ++i)
			digits[i] = temp[i];

		delete[] temp;
	}

}

VectorIterator Vector::insert(const VectorIterator& it, int&& element)
{
	_size++;

	if (_capacity >= _size)
	{
		size_t pos1 = std::distance(it, this->end()) + 1;
		int* temp = new int[std::distance(it, this->end()) + 1];
		size_t t_count = 0;
		for (auto iter = it; iter != this->end() - 1; iter++)  /*копирование второй части массива во временный массив*/
		{
			temp[t_count] = *iter;
			t_count++;
		}

		size_t pos2 = std::distance(this->begin(), it + 1) - 1;
		digits[std::distance(this->begin(), it + 1) - 1] = element; 

		for (size_t i = 0; i < t_count; i++)
			digits[std::distance(this->begin(), it + 1) + i] = temp[i];

		delete[] temp;

		return it - 1;
	}
	else
	{
		size_t pos = 0;     /* ищу индекс, где массив разделится (адрес итератора не будет актуальным при расширении вместимости вектора) */
		for (auto iter = this->begin(); iter != it; iter++)
			pos++;

		int* temp = new int[std::distance(it, this->end())];
		size_t t_count = 0;

		for (auto iter = it; iter != this->end(); iter++)  /*копирование второй части массива во временный массив*/
		{
			temp[t_count] = *iter;
			t_count++;
		}

		this->reserve(1.5 * _capacity);

		digits[pos] = element;
		int* res = new int(digits[pos]);
		VectorIterator result(res);
		pos++;

		for (size_t i = 0; i < t_count; i++)
			digits[pos + i] = temp[i];
		delete[] temp;

		return result;
	}
}

VectorIterator Vector::insert(const VectorIterator& it, size_t count, int&& element)
{
	_size += count;

	if (_capacity >= _size)
	{
		int* temp = new int[std::distance(it, this->end() - count)];
		size_t t_count = 0;
		for (auto iter = it; iter != this->end() - 1; iter++)  /*копирование второй части массива во временный массив*/
		{
			temp[t_count] = *iter;
			t_count++;
		}

		for (size_t i = 0; i < count; i++)
			digits[std::distance(this->begin(), it + 1) - 1 + i] = element; 

		for (size_t i = 0; i < t_count; i++)
			digits[std::distance(this->begin(), it + 1) + count + i - 1] = temp[i];
		delete[] temp;

		return it - 1;
	}
	else
	{
		size_t pos = 0;
		for (auto iter = this->begin(); iter != it; iter++)
			pos++;

		int* temp = new int[std::distance(it, this->end()) - count];
		size_t t_count = 0;

		for (auto iter = it; iter != this->end(); iter++)  /*копирование второй части массива во временный массив*/
		{
			temp[t_count] = *iter;
			t_count++;
		}

		while (_capacity < _size)
			this->reserve(1.5 * _capacity);

		for (size_t i = 0; i < count; i++)
		{
			digits[pos] = element;
			pos++;
		}

		int* res = new int(digits[pos]);
		VectorIterator result(res);
		pos++;

		for (size_t i = 0; i < t_count; i++)
			digits[pos + i] = temp[i];
		delete[] temp;

		return result;
	}
}

VectorIterator Vector::insert(const VectorIterator& _where, const VectorIterator& l_it, const VectorIterator& r_it)
{

	if (_size + std::distance(l_it, r_it) <= _capacity)
	{
		size_t cur_size = std::distance(l_it, r_it);
		size_t a = std::distance(_where, this->end()); 
		int* temp = new int[std::distance(_where, this->end())];
		size_t t_count = 0;

		for (auto iter = _where; iter != this->end(); iter++) /*копирование второй части во вр. массив*/
		{
			temp[t_count] = *iter;
			t_count++;
		}

		VectorIterator it = l_it;
		for (size_t i = 0; i < cur_size; i++) /*заполняем промежуток нужными элементами*/
		{
			digits[std::distance(this->begin(), _where + 1) - 1 + i] = *it;
			it++;
		}

		for (size_t i = 0; i < t_count; i++)  /*вставляем то что держали во вр. массиве*/
			digits[std::distance(this->begin(), _where + 1) + cur_size + i - 1] = temp[i];

		_size += cur_size;
		delete[] temp;
		return VectorIterator(this->begin() + std::distance(this->begin(), _where) + cur_size - 1);
	}
	else
	{
		size_t cur_size = std::distance(l_it, r_it);
		size_t pos = 0;
		for (auto iter = this->begin(); iter != _where; iter++)
			pos++;

		size_t tt = std::distance(_where, this->end());
		int* temp = new int[std::distance(_where, this->end())];
		size_t t_count = 0;

		for (auto iter = _where; iter != this->end(); iter++)  /*копирование второй части массива во временный массив*/
		{
			temp[t_count] = *iter;
			t_count++;
		}

		while (_capacity < _size + cur_size)    /*пока места не будет достаточно, выделяем память*/
			this->reserve(1.5 * _capacity);

		for (auto iter = l_it; iter != r_it; iter++)      /*копируем что требуется */
		{
			digits[pos] = *iter;
			pos++;
		}

		int* res = new int(*(r_it - 1));

		for (size_t i = 0; i < t_count; i++)  /*вставляем то что запоминали*/
		{
			digits[pos] = temp[i];
			pos++;
		}

		_size += cur_size;
		delete[] temp;
		return VectorIterator(res);
	}
}

VectorIterator Vector::erase(const VectorIterator& it)
{
	int* temp = new int[std::distance(it + 1, this->end())];
	size_t count = 0;

	for (auto iter = it + 1; iter != this->end(); iter++)
	{
		temp[count] = *iter;
		count++;
	}

	size_t pos = 0;
	for (size_t i = std::distance(this->begin(), it); i < std::distance(this->begin(), this->end()); i++)
	{
		digits[i] = temp[pos];
		pos++;
	}

	delete[] temp;
	_size--;
	return it;
}

VectorIterator Vector::erase(const VectorIterator& l_it, const VectorIterator& r_it)
{
	size_t distance = std::distance(l_it, r_it);
	size_t count = 0;
	int* temp = new int[std::distance(r_it, this->end())];

	for (auto iter = r_it; iter != this->end(); iter++)
	{
		temp[count] = *iter;
		count++;
	}

	size_t pos = 0;
	for (size_t i = std::distance(this->begin(), l_it); i < std::distance(this->begin(), r_it); i++)
	{
		digits[i] = temp[pos];
		pos++;
	}
	
	delete[] temp;
	_size -= distance;
	return l_it;
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
