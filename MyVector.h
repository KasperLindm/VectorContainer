#pragma once
#include <cassert>

template <typename T>
class MyVector
{
public:

	//If nothing is defined set everything to null
	MyVector();

	//Copy constructor
	MyVector(const T& _vector);

	//Destructor
	~MyVector();

	void PushBack(const T& value); //Would use small letter for all functions as begin and end has that

	void Insert(const T& value, int index);

	void Swap(int firstIndex, int secondIndex);

	void RemoveAt(int index);

	void Remove(const T& value);

	void Erase();

	void CheckCap();

	const int GetSize(); //can be const and called just size()

	typedef T* iterator;
	iterator begin() { return &data[0]; }
	iterator end() { return &data[size]; }

	T& operator[](int index)
	{
		assert(index <= size && "index out of range []");
		return data[index];
	}

	T operator[](int index) const
	{
		assert(index <= size && "index out of range In [] const");
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

template<typename T>
MyVector<T>::MyVector(const T& vectorData)
	: size(vectorData.size), capacity(vectorData.capacity)
{
	data = vectorData;
}

//Need copy constructor
template<typename T>
MyVector<T>::~MyVector() //needs to delete your data or you get a mem leak
{
	delete[] data;
}

//Place value as far back as possible
template <typename T>
void MyVector<T>::PushBack(const T& value)
{
	CheckCap();
	data[size] = value;
	size++;
}

//Insert value on the first place it finds or expands vector
template<typename T>
inline void MyVector<T>::Insert(const T& value, int index)
{
	assert(index <= size && "index out of range in insert");
	PushBack(value);
	Swap(data[index], size - 1); //Insert shouldn't typically swap, would make diff function for that
}

//remove specific value's and shift all values after back
template<typename T>
inline void MyVector<T>::Remove(const T& value)
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
	assert(firstIndex <= size && secondIndex <= size && "index out of range in Swap");
	T temp = data[firstIndex];
	data[firstIndex] = data[secondIndex];
	data[secondIndex] = temp;
}

template <typename T>
void MyVector<T>::RemoveAt(int index) //Should be called swapToRemoveAt
{
	assert(index <= size && "index out of range in RemoveAt");
	Swap(index, --size);
}

template<typename T>
inline void MyVector<T>::Erase()
{
	delete[] data;
}

template<typename T>
void MyVector<T>::CheckCap() //Functions should only do one thing, so should have one function for checking cap and one for increasing cap, or just check cap in the function where you call increaseSize
{
	if (size >= capacity)
	{
		capacity *= 2;
	}
}

template<typename T>
const int MyVector<T>::GetSize()
{
	return size;
}
