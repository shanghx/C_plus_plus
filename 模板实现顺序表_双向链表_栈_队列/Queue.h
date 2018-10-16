#pragma once
#include"SeqList.h"
#include"List.h"
template <class T, class Container>
class Queue
{
public:
	void Push(const T& x)
	{
		_con.PushBack(x);
	}
	void Pop()
	{
		_con.PopFront();
	}
	T Front()
	{
		return _con.Top();
	}
	void print()
	{
		cout << "∂”Õ∑--->∂”Œ≤:";
		_con.Print();
	}
protected:
	Container _con;
};
