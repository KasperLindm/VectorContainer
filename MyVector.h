#pragma once
#include <cassert>

template <typename T>
class MyVector
{
public:

	//if nothing is defined set everything to null
	MyVector();

	//Destructor
	~MyVector();

	void PushBack(const T& value); //Would use small letter for all functions as begin and end has that

	void Insert(const T& value, const int& index); //no const ref needed

	void Swap(int firstIndex, int secondIndex);

	void RemoveAt(int index);

	void RemoveValue(const T& value); //Just remove is fine and standard

	void Erase();

	void CheckCap(); //can be const if it only does what it says it does

	const int GetSize(); //can be const and called just size()

	typedef T* iterator;
	iterator begin() { return &data[0]; }
	iterator end() { return &data[size]; }

	T& operator[](int index)
	{
		assert(index && "index out of range");
		return data[index];
	}

	T operator[](int index) const
	{
		assert(index && "index out of range");
		return data[index];
	}

private:
	T* data;
	int size = 0;
	int capacity = 1;
};

template<typename T>
MyVector<T>::MyVector()
	: data(new T[capacity])
{}

//Need copy constructor 

template<typename T>
MyVector<T>::~MyVector() //needs to delete your data or you get a mem leak
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
	assert(index && "index out of range");
	PushBack(value);
	Swap(data[index], size - 1); //Insert shouldn't typically swap, would make diff function for that
}

//remove specific _value's and shift all values after back
template<typename T>
inline void MyVector<T>::RemoveValue(const T& value)
{
	T* tempVector = new T[capacity]; //Shouldn't allocate new memory when removing something, never need to increase size for that
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
	assert(firstIndex && secondIndex && "index out of range");
	T temp = data[firstIndex];
	data[firstIndex] = data[secondIndex];
	data[secondIndex] = temp;
}

template <typename T>
void MyVector<T>::RemoveAt(int index) //Should be called swapToRemoveAt
{
	assert(index && "index out of range");
	Swap(index, --size);
}

//erase entire vector
template<typename T>
inline void MyVector<T>::Erase()
{
	delete[] data;
}

//doubles capacity if size exceeds capacity
template<typename T>
void MyVector<T>::CheckCap() //Functions should only do one thing, so should have one function for checking cap and one for increasing cap, or just check cap in the function where you call increaseSize
{
	if (size >= capacity)
	{
		capacity *= 2;
	}
}

//Return the size of the vector
template<typename T>
const int MyVector<T>::GetSize()
{
	return size;
}
