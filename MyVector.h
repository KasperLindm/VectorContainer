template <typename T>
class MyVector
{
public:
	T* Data;
	int v_size;
	int v_capacity;

	//if nothing is defined set everything to null
	MyVector();

	//overload constructor If size is defined
	MyVector(const T& _vector);

	//Destructor
	~MyVector();

	void PushBack(const T& _value);

	void Insert(const T& _value, const int& _index);

	void Remove(const T& _value);

	void Erase();

	int GetSize();

};

template<typename T>
MyVector<T>::MyVector()
{

}

template<typename T>
MyVector<T>::MyVector(const T& _vector)
{
	v_size = _vector.size;
	v_capacity = _vector.capacity;
	Data = new T[v_capacity];
	for (unsigned int i = 0; i < v_size; ++i)
	{
		Data[i] = _vector.Data[i];
	}
}

template<typename T>
MyVector<T>::~MyVector()
{
	delete[] Data;
}

//Place it as far back as possible

template <typename T>
void MyVector<T>::PushBack(const T& _value)
{
	if (v_size >= v_capacity)
	{
		int newCapacity = 1 << v_capacity;
		T* newDataForVector = new T[newCapacity];

		for (unsigned int i = 0; i < v_size; ++i)
		{
			newDataForVector[i] = Data[i];
		}
		v_capacity = newCapacity;
		delete[] Data;
		Data = newDataForVector;
	}
	Data[v_size] = _value;
	v_size++;
}


//Insert on the first place it finds or expands vector
template<typename T>
inline void MyVector<T>::Insert(const T& _value, const int& _index)
{
	v_size++;
	T* TempVector = new T[v_size];
	TempVector = Data;

	for (int i = _index + 1; i < v_size; i++)
	{
		TempVector[i] = Data[i - 1];
	}
	TempVector[_index] = _value;
	Data = TempVector;
}

//remove specific value and shift all values after back
template<typename T>
inline void MyVector<T>::Remove(const T& _value)
{
	T* TempVector = new T[v_size];
	int AmountToAdd = 0;
	//Iterate from the removed index and swap the ones behind it
	for (int i = 0; i < v_size; i++)
	{
		if (Data[i] != _value)
		{
			TempVector[AmountToAdd] = Data[i];
			AmountToAdd++;
		}
	}
	v_size = AmountToAdd;
	Data = TempVector;
}

//erase entire Vector
template<typename T>
inline void MyVector<T>::Erase()
{
	delete Data;
	Data = nullptr;
	v_size = 0;

}

//Return the size of the vector
template<typename T>
int MyVector<T>::GetSize()
{
	return v_size;
}

