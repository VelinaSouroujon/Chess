#pragma once

template <typename T>
class List
{
private:
	static const int MIN_CAPACITY = 16;

	T* buffer = nullptr;
	size_t size = 0;
	size_t capacity = MIN_CAPACITY;

	void copy(const List<T>& other);
	void free();

public:
	List();
	List(const List<T>& other);
	List<T>& operator=(const List<T>& other);
	~List();

	size_t count() const;
	size_t getCapacity() const;

	void add(const T& value);
	void reserve(size_t newCapacity);
	bool removeLast();
	void shrinkToFit();
	void resetSize();
	void clear();
	bool insertAt(size_t index, const T& value);
	bool removeAt(size_t index);
	int findIndex(const T& value) const;
	bool contains(const T& value) const;
	T& operator[](size_t index);
	const T& operator[](size_t index) const;
};

template<typename T>
inline void List<T>::copy(const List<T>& other)
{
	size = other.size;
	capacity = other.capacity;

	T* newBuffer = new T[capacity];

	for (size_t i = 0; i < size; i++)
	{
		newBuffer[i] = other.buffer[i];
	}

	buffer = newBuffer;
}

template<typename T>
inline void List<T>::free()
{
	delete[] buffer;
	buffer = nullptr;
}

template<typename T>
inline List<T>::List()
{
	buffer = new T[MIN_CAPACITY];
	capacity = MIN_CAPACITY;
}

template<typename T>
inline List<T>::List(const List<T>& other)
{
	copy(other);
}

template<typename T>
inline List<T>& List<T>::operator=(const List<T>& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}

	return *this;
}

template<typename T>
inline List<T>::~List()
{
	free();
}

template<typename T>
inline size_t List<T>::count() const
{
	return size;
}

template<typename T>
inline size_t List<T>::getCapacity() const
{
	return capacity;
}

template<typename T>
inline void List<T>::add(const T& value)
{
	if (size == capacity)
	{
		reserve(size * 2);
	}

	buffer[size] = value;
	size++;
}

template<typename T>
inline void List<T>::reserve(size_t newCapacity)
{
	if (newCapacity < size)
	{
		return;
	}

	T* newBuffer = new T[newCapacity];

	for (size_t i = 0; i < size; i++)
	{
		newBuffer[i] = buffer[i];
	}

	free();

	capacity = newCapacity;
	buffer = newBuffer;
}

template<typename T>
inline bool List<T>::removeLast()
{
	if (size == 0)
	{
		return false;
	}

	size--;
	return true;
}

template<typename T>
inline void List<T>::shrinkToFit()
{
	reserve(size);
}

template<typename T>
inline void List<T>::resetSize()
{
	size = 0;
}

template<typename T>
inline void List<T>::clear()
{
	free();

	size = 0;
	capacity = MIN_CAPACITY;
	buffer = new T[capacity];
}

template<typename T>
inline bool List<T>::insertAt(size_t index, const T& value)
{
	if (index > size)
	{
		return false;
	}

	if (size == capacity)
	{
		reserve(capacity * 2);
	}

	if (index == size)
	{
		add(value);
		return true;
	}

	for (int i = size; i > index; i--)
	{
		buffer[i] = buffer[i - 1];
	}

	buffer[index] = value;
	size++;

	return true;
}

template<typename T>
inline bool List<T>::removeAt(size_t index)
{
	if (index >= size)
	{
		return false;
	}

	for (size_t i = index; i < size - 1; i++)
	{
		buffer[i] = buffer[i + 1];
	}

	removeLast();

	return true;
}

template<typename T>
inline int List<T>::findIndex(const T& value) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (buffer[i] == value)
		{
			return i;
		}
	}

	return -1;
}

template<typename T>
inline bool List<T>::contains(const T& value) const
{
	return findIndex(value) != -1;
}

template<typename T>
inline T& List<T>::operator[](size_t index)
{
	return buffer[index];
}

template<typename T>
inline const T& List<T>::operator[](size_t index) const
{
	return buffer[index];
}
