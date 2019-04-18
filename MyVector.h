#pragma once
#include <cassert>

template <typename T>
class MyVector
{
private:
	T* data;
	int size = 0;
	int capacity = 1;

public:
	//If nothing is defined set everything to null
	MyVector();

	//Copy constructor
	MyVector(const T& vectorData);

	//Destructor
	~MyVector();

	void PushBack(const T value); //Would use small letter for all functions as begin and end has that

	void Insert(const T value, int index);

	void Swap(int firstIndex, int secondIndex);

	void RemoveAt(int index);

	void Remove(const T value);

	void Erase();

	void Sort();

	int Search(T ValueToFind, T Left, T Right);

	void IncreaseCap();

	const int Size();

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
};

template<typename T>
MyVector<T>::MyVector()
	: data(new T[capacity]())
{}

template<typename T>
MyVector<T>::MyVector(const T& vectorData)
	: size(vectorData.size), capacity(vectorData.capacity)
{
	data = vectorData;
}

//Need copy constructor
template<typename T>
MyVector<T>::~MyVector()
{
	//delete[] data;
}

//Place value as far back as possible, Try to not reallocate new memory
template <typename T>
inline void MyVector<T>::PushBack(const T value)
{
	IncreaseCap();
	T* newDataForVector = new T[capacity];

	for (int i = 0; i < size; ++i)
	{
		newDataForVector[i] = data[i];
	}

	delete[] data;
	data = newDataForVector;
	data[size] = value;

	size++;
	//data[size] = value;
	//size++;
}

//Insert value on the first place it finds or expands vector
template<typename T>
inline void MyVector<T>::Insert(const T value, int index)
{
	//dont create a temp
	assert(index <= size && "index out of range in insert");
	if (size >= capacity)
	{
		int newCapacity = capacity + 1;
		T* TempVector = new T[newCapacity];

		for (int i = 0; i < index; i++)
		{
			TempVector[i] = data[i];

		}
		TempVector[index] = value;
		for (int i = index; i < size; i++)
		{
			TempVector[i + 1] = data[i];
		}
		data = TempVector;
		size++;
	}
}

//remove specific value's and shift all values after back
template<typename T>
inline void MyVector<T>::Remove(const T value)
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
inline void MyVector<T>::Swap(int firstIndex, int secondIndex)
{
	assert(firstIndex <= size && secondIndex <= size && "index out of range in Swap");
	T temp = data[firstIndex];
	data[firstIndex] = data[secondIndex];
	data[secondIndex] = temp;
}

template <typename T>
inline void MyVector<T>::RemoveAt(int index) //Should be called swapToRemoveAt
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
inline void MyVector<T>::Sort()
{
	for (int i = 0; i < (size); i++)
	{
		for (int x = 0; x < size; x++)
		{
			if (data[i] < data[x])
			{
				Swap(i, x);
			}
		}
	}
}

template<typename T>
inline int MyVector<T>::Search(T ValueToFind, T Left, T Right)
{
	if (Left < Right)
	{
		T Mid = (Left + Right) / 2;

		if (data[Mid] == ValueToFind)
			return Mid;

		if (ValueToFind < data[Mid])
			return Search(ValueToFind, Left, Mid);

		if (Left + 1 == Right)
			return -1;

		return Search(ValueToFind, Mid, Right);
	}
	return -1;
}

//Should reallocate memory if cap is reached
template<typename T>
inline void MyVector<T>::IncreaseCap()
{
	if (size >= capacity)
	{
		capacity *= 2;

		T* tempVector = new T[capacity];

		int i = 0;
		for (T* itr = begin(); itr < end(); itr++)
		{
			tempVector[i] = *itr;
			i++;
		}

		delete[] data;
		data = tempVector;
	}
}

template<typename T>
inline const int MyVector<T>::Size()
{
	return size;
}
