#pragma once
#include <cassert>

template <typename T>
class MyVector
{
public:
	T* data;
	int size = 0;
	int capacity = 1;

	//if nothing is defined set everything to null
	MyVector();

	//Destructor
	~MyVector();

	void PushBack(const T& value);

	void Insert(const T& value, const int& index);

	void Swap(int firstIndex, int secondIndex);

	void RemoveAt(int index);

	void RemoveValue(const T& value);

	void Erase();

	void CheckCap();

	int GetSize();

	typedef T* iterator;
	iterator begin() { return &data[0]; }
	iterator end() { return &data[size]; }

	T& operator[](int index)
	{
		if (index > capacity)
		{
			throw std::out_of_range("index is out of range");
		}
		return data[index];
	}

	T operator[](int index) const
	{
		if (index > capacity)
		{
			throw std::out_of_range("index is out of range");
		}
		return data[index];
	}
};

template<typename T>
MyVector<T>::MyVector()
	: data(new T[capacity])
{}

template<typename T>
MyVector<T>::~MyVector()
{}

//Place _value as far back as possible
template <typename T>
void MyVector<T>::PushBack(const T& value)
{
	CheckCap();
	data[size] = value;
	size++;
}

//Insert _value on the first place it finds or expands vector
template<typename T>
inline void MyVector<T>::Insert(const T& value, const int& index)
{
	assert(index < capacity);
	CheckCap();
	PushBack(value);
	Swap(data[index], size - 1);
}

//remove specific _value's and shift all values after back
template<typename T>
inline void MyVector<T>::RemoveValue(const T& value)
{
	T* tempVector = new T[capacity];
	int amountToAdd = 0;
	for (int i = 0; i < size; i++)
	{
		if (data[i] != value)
		{
			tempVector[amountToAdd] = data[i];
			amountToAdd++;
		}
	}
	size = amountToAdd;
	data = tempVector;
}

template <typename T>
void MyVector<T>::Swap(int firstIndex, int secondIndex)
{
	//assert(firstIndex && secondIndex && "First or second index out of range");
	T temp = data[firstIndex];
	data[firstIndex] = data[secondIndex];
	data[secondIndex] = temp;
}

template <typename T>
void MyVector<T>::RemoveAt(int index)
{
	//assert(index && "index out of range");
	Swap(index, size - 1);
	size--;
}

//erase entire vector
template<typename T>
inline void MyVector<T>::Erase()
{
	~MyVector();
}

//doubles capacity if size exceeds capacity
template<typename T>
void MyVector<T>::CheckCap()
{
	if (size >= capacity)
	{
		capacity *= 2;
	}
}

//Return the size of the vector
template<typename T>
int MyVector<T>::GetSize()
{
	return size;
}
