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
	MyVector(const int VecSize);

	//Destructor
	~MyVector();

	void PushBack(const T& _value);

	void Insert(const T& _value, const int& _index);

	void Remove(const T& _value);

	void Erase();

	int GetSize();

	typedef T* iterator;
	iterator begin() { return &Data[0]; }
	iterator end() { return &Data[v_size]; }

	T& operator[](int index)
	{
		if (index > v_capacity)
		{
			throw std::out_of_range("index is out");
		}
		return Data[index];
	}

	T operator[](int index) const
	{
		if (index > v_capacity)
		{
			throw std::out_of_range("index is out");
		}
		return Data[index];
	}
};

template<typename T>
MyVector<T>::MyVector()
{
	v_size = 0;
	v_capacity = 0;
	Data = new T[v_capacity];
}

template<typename T>
MyVector<T>::MyVector(const int VecSize)
{
	v_size = _vector;
	v_capacity = _vector;
	Data = new T[v_capacity];
	for (unsigned int i = 0; i < v_size; ++i)
	{
		Data[i] = 0;
	}
}

template<typename T>
MyVector<T>::~MyVector()
{
	delete[] Data;
	Data = nullptr;
}

//Place _value as far back as possible
template <typename T>
void MyVector<T>::PushBack(const T& _value)
{
	if (v_size >= v_capacity)
	{
		int newCapacity = v_capacity + 1;
		T* newDataForVector = new T[newCapacity];
		for (int i = 0; i < v_size; ++i)
		{
			newDataForVector[i] = Data[i];
		}
		v_capacity = newCapacity;
		delete[] Data;
		Data = newDataForVector;
		Data[v_size] = _value;
		v_size++;
	}
}

//Insert _value on the first place it finds or expands vector
template<typename T>
inline void MyVector<T>::Insert(const T& _value, const int& _index)
{
	if (v_size >= v_capacity)
	{
		int newCapacity = v_capacity + 1;
		T* TempVector = new T[newCapacity];
		for (int i = 0; i < _index; i++)
		{
			TempVector[i] = Data[i];
		}
		TempVector[_index] = _value;
		for (int i = _index; i < v_size; i++)
		{
			TempVector[i + 1] = Data[i];
		}
		Data = TempVector;
		v_size++;
	}
}

//remove specific _value's and shift all values after back
template<typename T>
inline void MyVector<T>::Remove(const T& _value)
{
	if (v_size >= v_capacity)
	{
		T* TempVector = new T[v_capacity - 1];
		int AmountToAdd = 0;
		for (int i = 0; i < v_size; i++)
		{
			if (Data[i] != _value)
			{
				TempVector[AmountToAdd] = Data[i];
				AmountToAdd++;
			}
		}
		Data = TempVector;
		v_size = AmountToAdd;
	}
}

//erase entire vector
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
