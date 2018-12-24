#pragma once
//AutoPtr<A> ap(new A);

// 智能指针
// 1.RAII
// 2.operator*/operator->  像指针一样去使用

// 发展历史
// 1.auto_ptr 管理权转移	公司严格禁止使用它 // C++98

// 2.scoped_ptr/scoped_array 防拷贝		推荐使用		   // boost
// 3.shared_ptr/shared_array 共享、引用计数	推荐		   // boost
// 4.weak_ptr	解决循环引用的问题、辅助shared_ptr // boost

// 5、unique_ptr/shared_ptr/weak_ptr		// C++11

#include<iostream>
using namespace std;
template<class T>
class AutoPtr
{
public:
	//构造函数
	AutoPtr(T* ptr)
		:_ptr(ptr)
	{ }
	//拷贝构造
	//ap2(ap1)
	AutoPtr(AutoPtr<T>& ap)
		:_ptr(ap._ptr)
	{
		ap._ptr = NULL;
	}
	//赋值运算符重载
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
	//解引用重载
	T& operator*()
	{
		return *_ptr;
	}
	//箭头重载
	T* operator->()
	{
		return _ptr;
	}
	//析构函数
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
	//构造
	ScopedPtr(T* ptr)
		:_ptr(ptr)
	{}
	//析构
	~ScopedPtr()
	{
		delete _ptr;
	}
	//解引用重载
	T& operator*()
	{
		return *_ptr;
	}
	//箭头重载
	T* operator->()
	{
		return _ptr;
	}

	
private:
	//类的防拷贝,只声明拷贝构造和赋值运算符重载，而不定义
	ScopedPtr(const ScopedPtr<T>& sp);
	ScopedPtr<T>& operator=(const ScopedPtr<T>& sp);

protected:
	T* _ptr;
};

template<class T>
class ScopedArray
{
public:
	//构造
	ScopedArray(T* ptr)
		:_ptr(ptr)
	{ }
	//析构
	~ScopedArray()
	{
		delete[] _ptr;
	}
	//[]运算符重载
	T& operator[](size_t pos)
	{
		return _ptr[pos];
	}
	
private:
	// 类的防拷贝
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
	//构造
	SharedPtr(T* ptr = NULL)
		:_ptr(ptr)
		,_pCount(new int(1))
	{}
	//析构
	~SharedPtr()
	{
		
		cout << "~SharedPtr()" << endl;
		//当只有一个指针指向对象时，析构就要释放该指针
		if (--(*_pCount) == 0)
		{
			delete _ptr;
			delete _pCount;
			cout << "_ptr 被释放" << endl;
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
	//拷贝构造
	//sp2(sp1)
	SharedPtr(SharedPtr<T>& sp)
		:_ptr(sp._ptr)
		,_pCount(sp._pCount)
	{
		++(*_pCount);
	}
	//赋值运算符重载
	//sp1=sp3
	SharedPtr<T>& operator=(const SharedPtr<T>& sp)
	{
		if (_ptr != sp._ptr)
		{
			//如果当前只有一个指针指向对象，则先将它释放
			if (--(*_pCount) == 0)
			{
				delete _ptr;
				delete _pCount;
			}
			//重新赋值
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
	/*weak_ptr没有重载* 和->
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

//循环引用
void TestCycle()
{
	SharedPtr<ListNode> n1 = new ListNode;
	SharedPtr<ListNode> n2 = new ListNode;

	n1->_next = n2;
	n2 ->_prev = n1;
	//cout << *n1._pCount << " " << *n2._pCount << endl;

}