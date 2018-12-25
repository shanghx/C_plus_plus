#pragma once

//����std::vectorʵ��һ����̬����Ҫ��������룬ɾ�������ҹ���
#include<iostream>
#include<vector>
using namespace std;
typedef int T;
//template<class T>
 struct ListNode
{
	T _value;
	size_t _next;
	ListNode()
	{
		_value = T(0);
		_next = -1;
	}
};
 template<class T>
class List
{
public:
	List()
	{
		_remove.resize(0);
		_head = -1;
		_list.resize(0);
	}
	size_t find(T data)
	{
		size_t i = _head;
		for (i = _head; i!=-1;)
		{
			if (_list[i]._value == data)
				return i;
			i = _list[i]._next;
		}
	}
	size_t Size()
	{
		size_t count = 0;
		for (int i = _head; i != -1;)
		{
			count++;
			i = _list[i]._next;
		}
		return count;
	}
	void PushFront(T data)//ͷ��
	{
		ListNode *cur = new ListNode();
		//������Ϊ��
		if (_head == -1)
		{
			cur->_next = -1;
			cur->_value = data;
			_list.push_back(*cur);
			_head = 0;
			return;
		}
		//��Ϊ��
		if (_remove.size() != 0)
		{
			size_t tmp = _remove[_remove.size() - 1];
			_remove.erase(_remove.end());
			_list[tmp]._value = data;
			_list[tmp]._next = _head;
		}
		else
		{
			cur->_next = _head;
			cur->_value = data;

			_list.push_back(*cur);
			_head = _list.size() - 1;
		}
		
		return;
		
	}
	void PushBack(T data)
	{
		ListNode *cur = new ListNode();
		//������Ϊ��
		if (_head == -1)
		{
			cur->_next = -1;
			cur->_value = data;
			_list.push_back(*cur);
			_head = 0;
			return;
		}
		//��Ϊ��
		int i = 0;
		for (int i = _head; _list[i]._next!=-1;)
		{
			i = _list[i]._next;
		}
		
		
		if (_remove.size() != 0)
		{
			size_t tmp = _remove[_remove.size() - 1];
			_remove.erase(_remove.end());
			_list[i]._next = tmp;
			_list[tmp]._value = data;
			_list[tmp]._next = -1;
		}
		else
		{
			cur->_next = -1;
			cur->_value = data;
			_list.push_back(*cur);
			_list[i]._next = _list.size() - 1;
		}
		
		return;
			
	}
	void Insert(size_t pos,T value)
	{
		if (_head == -1)
		{
			if (pos == NULL)
			{
				ListNode *cur = new ListNode();
				cur->_next = -1;
				cur->_value = value;
				_list.push_back(*cur);
				_head = 0;

			}
			else
			cout << "����Ϊ�գ��޷����룡" << endl;
			return;
		}
		
		size_t i = _head;
		for (i = _head; i != pos;)
		{
			i = _list[i]._next;
		}
		//����п��еĿռ䣬�����ÿ��еĿռ����
		size_t next = _list[i]._next;
		if (_remove.size() != 0)
		{
			size_t tmp = _remove[_remove.size() - 1];
			_remove.erase(_remove.end());
			_list[i]._next = tmp;
			_list[tmp]._value = value;
			_list[tmp]._next = next;
		}
		//����push_back
		else
		{
			ListNode* cur = new ListNode();
			cur->_next = next;
			cur->_value = value;
			_list.push_back(*cur);
			_list[i]._next = _list.size() - 1;

		}
		
		return;
	}
	void print()
	{
		size_t i = _head;
		for (i = _head; i!=-1;)
		{
			cout << _list[i]._value << "->";
			i = _list[i]._next;
		}
		cout <<"NULL"<< endl;
		
	}
	void PopFront()
	{
		if (_head == -1)
		{
			cout << "����Ϊ�գ��޷�ɾ����" << endl;
			return;
		}
		//ֻ��һ���ڵ�
		if (Size() == 0)
		{
			_remove.push_back(_head);
			_head = -1;
			return;
		}

		
		//�ж���ڵ�
		_remove.push_back(_head);
		_head = _list[_head]._next;
		return;
		
	}
	void PopBack()
	{
		if (_head == -1)
		{
			cout << "����Ϊ�գ��޷�ɾ����" << endl;
			return;
		}
		//���ֻ��һ���ڵ�
		if (Size() == 1)
		{
			_remove.push_back(_head);
			_head = -1;
			return;
		}
		//�ж���ڵ�
			size_t i = _head, j = _head;
		for (i = _head; _list[i]._next != -1;)
		{
			j = i;

			i = _list[i]._next;
		}
		_list[j]._next = -1;
		_remove.push_back(i);
	}
	void Erase(size_t pos)
	{
		if (pos > Size())
		{
			return;
		}
		size_t j = _head;
		for (size_t i = _head; i != -1;)
		{

			if (i == pos-1)
			{
				_list[j]._next = _list[i]._next;
				_remove.push_back(i);
			}
			j = i;
			i = _list[i]._next;
		}
	}
private:
	vector<ListNode> _list;
	vector<int> _remove;
	size_t _head;
	
};

void test()
{
	List<int> l;
	l.PushBack(0);
	l.print();
	l.PushFront(1);
	l.print();
	l.PushFront(2);
	l.print();
	l.PushFront(3);
	l.print();
	l.PushFront(4);
	l.print();
	l.PushFront(5);
	l.print();
	l.PushFront(6);
	l.print();
	l.PushBack(7);
	l.print();
	l.PopBack();
	l.print();
	l.PopFront();
	l.print();
	l.PopFront();
	l.print();
	l.PopFront();
	l.print();
	l.PopFront();
	l.print();
	l.PopFront();
	l.print();
	l.PopFront();
	l.print();
	l.PopFront();
	l.print();
	l.PopFront();
	l.print();
	//l.Insert(NULL, 1);
	size_t  pos= l.find(1);
	//l.Insert(pos, 1);
	

}












