#pragma once
#include"SeqList.h"
#include"List.h"
template<class T, class Container >
class Stack
{
public:
	void Push(const T& x)
	{
		_con.PushBack(x);
	}
	void Pop()
	{
		_con.PopBack();

	}
	T Top()
	{
		return _con.Tail();
	}
	void print()
	{
		cout << "Õ»µ×--->Õ»¶¥:";
		_con.Print();
	}
protected:
	Container _con;
};

