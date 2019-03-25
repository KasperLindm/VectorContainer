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

	void CheckCap();

	int GetSize();

	typedef T* iterator;
	iterator begin() { return &Data[0]; }
	iterator end() { return &Data[v_size]; }

	T& operator[](int index)
	{
		if (index > v_capacity)
		{
			throw std::out_of_range("index is out of range");
		}
		return Data[index];
	}

	T operator[](int index) const
	{
		if (index > v_capacity)
		{
			throw std::out_of_range("index is out of range");
		}
		return Data[index];
	}
};

template<typename T>
MyVector<T>::MyVector()
{
	v_size = 0;
	v_capacity = 1;
	Data = new T[v_capacity];
}

template<typename T>
MyVector<T>::MyVector(const int VecSize)
{
	v_size = VecSize;
	v_capacity = VecSize * 2;
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
	CheckCap();
	T* newDataForVector = new T[v_capacity];
	for (int i = 0; i < v_size; ++i)
	{
		newDataForVector[i] = Data[i];
	}
	delete[] Data;
	Data = newDataForVector;
	Data[v_size] = _value;
	v_size++;
}

//Insert _value on the first place it finds or expands vector
template<typename T>
inline void MyVector<T>::Insert(const T& _value, const int& _index)
{

	CheckCap();
	T* TempVector = new T[v_capacity];
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

//remove specific _value's and shift all values after back
template<typename T>
inline void MyVector<T>::Remove(const T& _value)
{
	T* TempVector = new T[v_capacity];
	int AmountToAdd = 0;
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

//erase entire vector
template<typename T>
inline void MyVector<T>::Erase()
{
	delete Data;
	Data = nullptr;
	v_size = 0;
}

//doubles capacity if size exceeds capacity
template<typename T>
void MyVector<T>::CheckCap()
{
	if (v_size >= v_capacity)
	{
		v_capacity *= 2;
	}
}

//Return the size of the vector
template<typename T>
int MyVector<T>::GetSize()
{
	return v_size;
}
