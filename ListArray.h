#ifndef LISTARRAY_H
#define LISTARRAY_H
#include <ostream>
#include <stdexcept>
#include "List.h"

template <typename T>
class ListArray : public List<T>
{
private:
	T *arr = nullptr;
	int max;
	int n;
	static const int MINSIZE = 2;

	void resize(int newsize)
	{
		if (newsize < MINSIZE)
			newsize = MINSIZE;
		T *newarr = new T[newsize];
		for (int i = 0; i < n && i < newsize; i++)
			newarr[i] = arr[i];
		delete[] arr;
		arr = newarr;
		max = newsize;
		if (n > max)
			n = max;
	}

public:
	ListArray() : max(MINSIZE), n(0) { arr = new T[MINSIZE]; }
	~ListArray() { delete[] arr; }

	// Firma requerida por List<T>: insert(pos, elem)
	void insert(int pos, T e) override
	{
		if (pos < 0 || pos > n)
			throw std::out_of_range("La posición no es válida (fuera del intervalo de la lista)");
		if (n == max)
			resize(2 * max);
		for (int i = n; i > pos; i--)
			arr[i] = arr[i - 1];
		arr[pos] = e;
		n++;
	}

	void append(T e) override { insert(n, e); }
	void prepend(T e) override { insert(0, e); }

	T remove(int pos) override
	{
		if (pos < 0 || pos >= n)
			throw std::out_of_range("La posición no es válida (fuera del intervalo de la lista)");
		T elem = arr[pos];
		for (int i = pos; i < n - 1; i++)
			arr[i] = arr[i + 1];
		n--;
		if (n < max / 4)
			resize(max / 2);
		return elem;
	}

	T get(int pos) override
	{
		if (pos < 0 || pos >= n)
			throw std::out_of_range("La posición no es válida (fuera del intervalo de la lista)");
		return arr[pos];
	}

	int search(T e) override
	{
		for (int i = 0; i < n; i++)
		{
			if (arr[i] == e)
				return i;
		}
		return -1;
	}

	bool empty() override { return n == 0; }
	int size() override { return n; }

	T operator[](int pos)
	{
		if (pos < 0 || pos >= n)
			throw std::out_of_range("La posición no es válida (fuera del intervalo de la lista)");
		return arr[pos];
	}

	friend std::ostream &operator<<(std::ostream &out, const ListArray<T> &list)
	{
		out << "[";
		for (int i = 0; i < list.n; i++)
		{
			out << list.arr[i];
			if (i < list.n - 1)
				out << ", ";
		}
		out << "]";
		return out;
	}
};

#endif
