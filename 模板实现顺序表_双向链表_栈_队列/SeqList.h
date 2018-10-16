#pragma once
template<typename T>
class SeqList
{
public:
	SeqList()
		:_array(NULL)
		, _size(0)
		,_capacity(0)
	{}

	SeqList(const SeqList<T>& s)
	{
			if (s._size == 0)
			{
				_array = NULL;
				_size = _capacity = 0;
			}
			else
			{
				_array = new T[s._size];//这里开辟_size或_capacity大小的空间都可以
				//memcpy(newarray, _array, sizeof(T)*_size);	//memcpy处理不了string的对象
				for (size_t i = 0; i < s._size; ++i)
				{
					_array[i] = s._array[i];		
				}
				_size =_capacity = s._size;

			}		
	}
	SeqList<T>& operator=(SeqList<T>& s)	//传统写法
	{
		if (this != &s)
		{
			if (s._size != 0)
			{
				delete[] _array;
				_array = new T[s._capacity];
				for (size_t i = 0; i < s._size; ++i)
				{
					_array[i] = s._array[i];
				}
				_size = s._size;
				_capacity = s._capacity;
			}
			_size = _capacity = 0;
			_array = s._array;
		}
			
		return *this;
	}
	//s1(s2)
	SeqList<T>& operator=(SeqList<T> s)	//现代写法,不能加引用
	{
		//s就是s2的值拷贝，因为是值传递，所以只需要交换*this和s2的值即可
		swap(_array, s._array);
		swap(_size, s._size);
		swap(_capacity, s._capacity);
		return *this;
	}

	~SeqList()
	{
		if (_array)
		{
			delete[] _array;
			_array = NULL;
			_size = 0;
			_capacity = 0;
		}
	}

	void PushBack(const T& x)
	{
		Insert(_size, x);
	}
	void PopBack()
	{
		Erase(_size - 1);
	}
	void Insert(size_t pos, const T& x)
	{
		//先判断pos的值是否合理,不排除pos为0的情况
		assert(pos <= _size);
		//再判断capacity是否足够，不够则先开辟空间
		if (_size == _capacity)		//空间满
		{
			size_t newcapacity = _capacity == 0 ? 3 : _capacity * 2;
			T* newarray = new T[newcapacity];
			for (size_t i = 0; i < _size; ++i)//搬元素
			{
				newarray[i] = _array[i];
			}
			delete[] _array;//释放旧空间
			_array = newarray;
			_capacity = newcapacity;
		}
		
			//之后，插入数据，这里要考虑pos为0的情况,此时就直接插入元素,在pos位置插入，就是在pos这个下标插入数据
			size_t j = 0; 
			for (j = _size; j > pos; --j)//后移元素
			{
				_array[j] = _array[j - 1];		
			}

			_array[j] = x;	
			_size += 1;
	}
	void Erase(size_t pos)
	{
		//先判断pos是否合理
		assert(pos <= _size - 1);
		//找pos位置元素
		for (int i = pos; i <_size - 1; ++i)
		{
			_array[i] = _array[i + 1];
			
		}
		--_size;
	}
	T& operator[](size_t pos)const
	{
		assert(pos <= _size);
		return _array[pos];


	}
	size_t Find(const T& x)
	{
		for (size_t i = 0; i < _size; ++i)
		{
			if (_array[i] == x)
				return i;
		}
		return -1;
	}
	size_t Size()
	{
		return _size;
	}
	T& Top()
	{
		return _array[0];
	}
	T& Tail()
	{
		return _array[_size - 1];
	}
	void Print()
	{
		size_t i = 0;
		while (i < _size)
		{
			cout << _array[i] << " ";
			++i;
		}
		cout << endl;
	}
private:
	T* _array;
	size_t _size;
	size_t _capacity;
};

void TestSeqList()
{
	/*SeqList<int> s2;
	s2.Insert(0, 1);
	s2.Insert(1, 2);
	s2.Insert(1, 3);
	s2.PushBack(10);
	s2.PushBack(9);
	s2.PushBack(8);
	s2.Print();*/
	
	SeqList<string> s2;
	s2.PushBack("aaaaaaaaaaaaaaaaaaa");
	s2.PushBack("bbb");
	s2.PushBack("ccc");
	s2.PushBack("ddd");
	s2.Print();
}

