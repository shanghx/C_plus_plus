#pragma once
//AutoPtr<A> ap(new A);

// ����ָ��
// 1.RAII
// 2.operator*/operator->  ��ָ��һ��ȥʹ��

// ��չ��ʷ
// 1.auto_ptr ����Ȩת��	��˾�ϸ��ֹʹ���� // C++98

// 2.scoped_ptr/scoped_array ������		�Ƽ�ʹ��		   // boost
// 3.shared_ptr/shared_array �������ü���	�Ƽ�		   // boost
// 4.weak_ptr	���ѭ�����õ����⡢����shared_ptr // boost

// 5��unique_ptr/shared_ptr/weak_ptr		// C++11

#include<iostream>
using namespace std;
template<class T>
class AutoPtr
{
public:
	//���캯��
	AutoPtr(T* ptr)
		:_ptr(ptr)
	{ }
	//��������
	//ap2(ap1)
	AutoPtr(AutoPtr<T>& ap)
		:_ptr(ap._ptr)
	{
		ap._ptr = NULL;
	}
	//��ֵ���������
	//ap1=ap3
	AutoPtr<T>& operator=(AutoPtr<T>& ap)
	{
		if (this != &ap)
		{
			delete _ptr;
			_ptr = ap._ptr;
			ap._ptr = NULL;
		}
		return *this;
	}
	//����������
	T& operator*()
	{
		return *_ptr;
	}
	//��ͷ����
	T* operator->()
	{
		return _ptr;
	}
	//��������
	~AutoPtr()
	{
		delete _ptr;
	}
protected:
	T* _ptr;
};

template<class T>
class ScopedPtr
{
public:
	//����
	ScopedPtr(T* ptr)
		:_ptr(ptr)
	{}
	//����
	~ScopedPtr()
	{
		delete _ptr;
	}
	//����������
	T& operator*()
	{
		return *_ptr;
	}
	//��ͷ����
	T* operator->()
	{
		return _ptr;
	}

	
private:
	//��ķ�����,ֻ������������͸�ֵ��������أ���������
	ScopedPtr(const ScopedPtr<T>& sp);
	ScopedPtr<T>& operator=(const ScopedPtr<T>& sp);

protected:
	T* _ptr;
};

template<class T>
class ScopedArray
{
public:
	//����
	ScopedArray(T* ptr)
		:_ptr(ptr)
	{ }
	//����
	~ScopedArray()
	{
		delete[] _ptr;
	}
	//[]���������
	T& operator[](size_t pos)
	{
		return _ptr[pos];
	}
	
private:
	// ��ķ�����
	ScopedArray(const ScopedArray<T>& ap);
	ScopedArray<T>& operator=(const ScopedArray<T>& ap);
protected:
	T* _ptr;
};

template<class T>
class SharedPtr
{
	template<class T>
	friend class  WeakPtr;
public:
	//����
	SharedPtr(T* ptr = NULL)
		:_ptr(ptr)
		,_pCount(new int(1))
	{}
	//����
	~SharedPtr()
	{
		
		cout << "~SharedPtr()" << endl;
		//��ֻ��һ��ָ��ָ�����ʱ��������Ҫ�ͷŸ�ָ��
		if (--(*_pCount) == 0)
		{
			delete _ptr;
			delete _pCount;
			cout << "_ptr ���ͷ�" << endl;
		}
	}
	//
	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}
	//��������
	//sp2(sp1)
	SharedPtr(SharedPtr<T>& sp)
		:_ptr(sp._ptr)
		,_pCount(sp._pCount)
	{
		++(*_pCount);
	}
	//��ֵ���������
	//sp1=sp3
	SharedPtr<T>& operator=(const SharedPtr<T>& sp)
	{
		if (_ptr != sp._ptr)
		{
			//�����ǰֻ��һ��ָ��ָ��������Ƚ����ͷ�
			if (--(*_pCount) == 0)
			{
				delete _ptr;
				delete _pCount;
			}
			//���¸�ֵ
			//_pCount = sp._pCount; 
			//++(*_pCount);
			_ptr = sp._ptr;
			++(*sp._pCount);
			_pCount = sp._pCount;
		}
		return *this;
	}
protected:
	T* _ptr;
	int* _pCount;
};

template <class T>
class WeakPtr
{
public:
	WeakPtr()
		:_ptr(NULL)
	{
		
	}
	WeakPtr(const SharedPtr<T>& sp)
		:_ptr(sp._ptr)
	{
		
	}
	WeakPtr(const WeakPtr<T>& wp)
		:_ptr(wp._ptr)
	{
		
	}
	WeakPtr<T>& operator=(SharedPtr<T>& sp)
	{
		_ptr = sp._ptr;
		return *this;
	}
	/*weak_ptrû������* ��->
	*/
protected:
	T* _ptr;
};

/*struct ListNode
{
	SharedPtr<ListNode> _next;
	SharedPtr<ListNode> _prev;
	~ListNode()
	{
		cout << "~ListNode()" << endl;
	}
	
};*/
struct ListNode
{
	WeakPtr<ListNode> _next;
	WeakPtr<ListNode> _prev;
	~ListNode()
	{
		cout << "~ListNode()" << endl;
	}

};

//ѭ������
void TestCycle()
{
	SharedPtr<ListNode> n1 = new ListNode;
	SharedPtr<ListNode> n2 = new ListNode;

	n1->_next = n2;
	n2 ->_prev = n1;
	//cout << *n1._pCount << " " << *n2._pCount << endl;

}