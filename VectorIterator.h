#include <iterator>

#pragma once

class VectorIterator
{
	int* pos;

public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = int;                                     /*Тип значения  */
	using difference_type = int;                                /*Тип расстояния*/
	using pointer = int*;                                       /*Тип указателя */
	using reference = int&;                                     /*Тип ссылки    */

	VectorIterator(int* position) : pos(position) { };

	bool operator==(const VectorIterator& other) const { return pos == other.pos; };
	bool operator!=(const VectorIterator& other) const { return pos != other.pos; };
	bool operator>(const VectorIterator& other) const { return pos > other.pos; };
	bool operator<(const VectorIterator& other) const { return pos < other.pos; };
	bool operator>=(const VectorIterator& other) const { return pos >= other.pos; };
	bool operator<=(const VectorIterator& other) const { return pos <= other.pos; };

	reference operator*() const { return *pos; };
	pointer operator->() const { return pos; };

	VectorIterator& operator++()
	{
		++pos;
		return *this;
	};

	VectorIterator& operator++(int)
	{
		VectorIterator temp = *this;
		++pos;
		return temp;
	};

	VectorIterator& operator--()
	{
		--pos;
		return *this;
	};

	VectorIterator& operator--(int)
	{
		VectorIterator temp = *this;
		--pos;
		return temp;
	};

	reference operator[](size_t index) const { return pos[index]; };

	VectorIterator operator+(const difference_type& diff) const { return VectorIterator(pos + diff); };
	friend inline VectorIterator operator+(const difference_type& diff, const VectorIterator& other) 
	{
		return VectorIterator(other.pos + diff);
	};

	VectorIterator operator-(const difference_type& diff) const { return VectorIterator(pos - diff); };
	difference_type operator-(const VectorIterator& other) const { return std::distance(other.pos, pos); };

	VectorIterator operator+=(const difference_type& diff)
	{
		pos += diff;
		return *this;
	};

	VectorIterator operator-=(const difference_type& diff)
	{
		pos -= diff;
		return *this;
	};
};