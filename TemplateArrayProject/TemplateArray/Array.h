#ifndef ARRAY_H
#define ARRAY_H

#include <string> 
#include <iostream>
#include <stdexcept>

using std::cout;
using std::cin;
using std::endl;
using std::string;

template <typename T>
class Array
{
private:
	T* my_array;
	int	starting_index;
	int	size;

public:
	Array() : my_array(new T[0]), size(0) {};
	Array(int length, int start_index = 0);
	Array(const Array<T>& copy);
	Array(Array<T>&& copy);
	~Array();

	Array& operator =(const Array<T>& rhs);
	Array& operator =(Array<T>&& rhs);
	T& operator [] (int index);

	bool    IsEmpty();
	int		GetStartingIndex();
	int		GetSize();
	void	SetStartIndex(int start_index);
	void	SetSize(int length);
	T       GetFront();
	T		GetBack();
	
};

//----------------------------------------------------------------
//Constructors----------------------------------------------------
//----------------------------------------------------------------

// NOTE: This is Array's 2 argument constructor
template <typename T>
Array<T>::Array(int length, int start_index)
{
	this->size = length;
	this->my_array = new T[this->size];
	this->SetStartIndex(start_index);
}


// NOTE: This is Array's copy constructor
template <typename T>
Array<T>::Array(const Array<T>& copy)
{
	*this = copy;
}


// NOTE: This is Array's move constructor
template<typename T>
inline Array<T>::Array(Array<T>&& copy)
{
	*this = std::move(copy);
}

// NOTE: This is Array's destructor
template<typename T>
inline Array<T>::~Array()
{
	delete[] my_array;
}

//----------------------------------------------------------------
//Setters---------------------------------------------------------
//----------------------------------------------------------------

// NOTE: This sets Array's starting index
template <typename T>
void Array<T>::SetStartIndex(int start_index)
{
	this->starting_index = start_index;
}

// NOTE: This sets Array's size
template <typename T>
void Array<T>::SetSize(int length)
{
	if (length < 0)
	{
		throw std::invalid_argument("Array cannot have length less than zero");
	}
	else if (length > size)
	{
		T* temporary_array = new T[length];

		for (int i = 0; i < size; i++)
		{
			temporary_array[i] = this->my_array[i];
		}

		delete[] this->my_array;
		this->my_array = nullptr;
		this->my_array = temporary_array;

		for (int i = size; i < length; i++)
		{
			this->my_array[i] = T();
		}

		this->size = length;
	}
	else
	{	
		this->size = length;
	}
}

//----------------------------------------------------------------
//Array Getters---------------------------------------------------
//----------------------------------------------------------------

// NOTE: This returns Array's size
template <typename T>
int Array<T>::GetSize()
{
	return this->size;
}

// NOTE: This returns Array's starting index
template <typename T>
int Array<T>::GetStartingIndex()
{
	return this->starting_index;
}

// NOTE: This returns the element at the front of Array
template <typename T>
T Array<T>::GetFront()
{
	return this->my_array[this->GetStartingIndex()];
}

// NOTE: This returns the last element in Array
template <typename T>
T Array<T>::GetBack()
{
	return this->my_array[this->GetSize() - 1];
}

//----------------------------------------------------------------
//Operator Overloads----------------------------------------------
//----------------------------------------------------------------

// NOTE: This is the overloaded equals operator for Array
template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& rhs)
{
	if (this != &rhs)
	{
		delete[] this->my_array;
		this->my_array = nullptr;

		if (rhs.my_array != nullptr)
		{
			this->my_array = new T[rhs.size];
			this->size = rhs.size;

			for (int i = 0; i < rhs.size; i++)
			{
				this->my_array[i] = rhs.my_array[i];
			}
		}
	}

	this->SetStartIndex(rhs.starting_index);
	this->SetSize(rhs.size);

	return *this;
}

// NOTE: This is an overloaded move assignment operator for Array
template<typename T>
Array<T>& Array<T>::operator=(Array<T>&& rhs)
{
	if (this != rhs)
	{
		delete[] this->my_array;
		this->my_array = nullptr;

		if (rhs.my_array != nullptr)
		{
			this->my_array = new T[rhs.size];
			this.size = rhs.size;

			for (int i = 0; i < rhs.size; i++)
			{
				this->my_array[i] = rhs.my_array[i];
			}
		}
	}

	this->SetStartIndex(rhs.starting_index);
	this->SetSize(rhs.size);

	return *this;
}

// NOTE: This is an overloaded array index operator for Array
template<typename T>
T& Array<T>::operator [] (int index)
{
	int upperBound;
	int lowerBound = this->GetStartingIndex();

	if (this->GetSize() == 1)
	{
		upperBound = 0;
	}
	else 
	{
		upperBound = this->GetSize() + lowerBound - 1;
	}

	if (index < lowerBound)
	{
		throw std::domain_error("Index must be greater than the array's lower bounds");
	}
	else if (index > upperBound)
	{
		throw std::domain_error("Index must be less than the array's upper bounds");
	}
	else
	{
		return this->my_array[index - lowerBound];
	}
}

//----------------------------------------------------------------
//Other-----------------------------------------------------------
//----------------------------------------------------------------

// NOTE: Checks if the array is empty;
template<typename T>
bool Array<T>::IsEmpty()
{
	if (this->size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

#endif
