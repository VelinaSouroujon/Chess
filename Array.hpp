#pragma once

template <typename T, const int C>
class Array
{
private:
	int len = 0;
	T arr[C];

public:
	int length() const;
	const T* items() const;

	void add(const T& itemToAdd);
	//void clear();

	const T& operator[](int index) const;
	T& operator[](int index);
};

template<typename T, int C>
inline int Array<T, C>::length() const
{
	return len;
}

template<typename T, int C>
inline const T* Array<T, C>::items() const
{
	return arr;
}

template<typename T, int C>
inline void Array<T, C>::add(const T& itemToAdd)
{
	arr[len] = itemToAdd;
	len++;
}

//template<typename T, int C>
//inline void Array<T, C>::clear()
//{
//	len = 0;
//}

template<typename T, int C>
inline const T& Array<T, C>::operator[](int index) const
{
	return arr[index];
}

template<typename T, int C>
inline T& Array<T, C>::operator[](int index)
{
	return arr[index];
}
