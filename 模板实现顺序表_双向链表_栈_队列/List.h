#pragma once

template<class T>	//struct 这个结构体也相当于类 
struct ListNode		//双向带头循环链表
{
	T _data;
	ListNode<T>* _next;	//ListNode 是类名	ListNode<T>是类的对象对应的类型名
	ListNode<T>* _prev;
};

template<class T>
class List
{
	typedef ListNode<T> Node;
public:
	List()
	{
		_head = new Node;	//构造头节点
		_head->_prev = _head;
		_head->_next = _head;
		//_head->_data = (T);
	}
	List(const List<T>& l)
	{
		Node* _head = new Node;
		_head->_prev = _head;
		_head->_next = _head;
		Node* pCur = l._head->_next;
		Node* Cur = _head;
		while (pCur != l._head)
		{
			Node* NewNode = new Node;
			Cur->_next = NewNode;
			NewNode->_prev = Cur;
			NewNode->_data = pCur->_data;
			Cur = NewNode;
			pCur = pCur->_next;
		}
		pCur->_next = _head;

	}
	List& operator=(const List<T>& l)
	{
		Node* Cur = _head;
		Node* pCur = l._head->_next;
		if (this != &l)
		{
			while (pCur != l._head)
			{
				PushBack(pCur->_data);
				pCur = pCur->_next;

			}

		}
		return *this;
	}
	~List()
	{
		Node* Cur = _head->_next;
		while (Cur != _head)
		{
			Node* Next = Cur->_next;
			delete[] Cur;
			Cur = Next;
		}
		delete[] _head;
		_head = NULL;
	}
	void PushBack(const T& x)
	{
		Insert(_head, x);
	}
	void PopBack()
	{
		Erase(_head->_prev);
	}
	void PushFront(const T& x)
	{
		Insert(_head->_next, x);
	}
	void PopFront()
	{
		Erase(_head->_next);
	}
	void Insert(Node* pos, const T& x)
	{
		assert(pos);
		Node* NewNode = new Node;
		Node* pre = pos->_prev;
		pre->_next = NewNode;
		NewNode->_prev = pre;
		NewNode->_next = pos;
		pos->_prev = NewNode;
		NewNode->_data = x;
	}
	void Erase(Node* pos)
	{
		assert(pos);
		Node* Cur = pos->_next;

		pos->_prev->_next = Cur;
		pos->_prev = Cur->_prev;
		delete[] pos;
		pos = NULL;
	}

	Node* Find(const T& x)
	{
		Node* pCur = _head->_next;
		while (pCur != _head)
		{
			if (pCur->_data == x)
			{
				return pCur;

			}
			pCur = pCur->_next;
		}
		return NULL;
	}
	size_t Size()
	{
		size_t count = 0;
		Node* pCur = _head->_next;
		while (pCur != _head)
		{
			count++;
			pCur = pCur->_next;
		}
		return count;
	}
	bool Empty()
	{
		return _head->_next == _head;
	}
	T& Top()
	{
		return _head->_next->_data;
	}
	T& Tail()
	{
		return _head->_prev->_data;
	}
	void Print()
	{
		Node* pCur = _head->_next;
		while (pCur != _head)
		{
			cout << pCur->_data << " ";
			pCur = pCur->_next;
		}
		cout << endl;
	}
private:
	Node* _head;
};

void TestList()
{
	List<int> l;
	List<int> s;
	//l.Insert(l,1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	//List<int>s(l);
	//s = l;
	l.Print();
	l.PopBack();
	l.Print();
	// s.Print();
}
