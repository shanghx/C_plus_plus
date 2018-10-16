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
				_array = new T[s._size];//���￪��_size��_capacity��С�Ŀռ䶼����
				//memcpy(newarray, _array, sizeof(T)*_size);	//memcpy������string�Ķ���
				for (size_t i = 0; i < s._size; ++i)
				{
					_array[i] = s._array[i];		
				}
				_size =_capacity = s._size;

			}		
	}
	SeqList<T>& operator=(SeqList<T>& s)	//��ͳд��
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
	SeqList<T>& operator=(SeqList<T> s)	//�ִ�д��,���ܼ�����
	{
		//s����s2��ֵ��������Ϊ��ֵ���ݣ�����ֻ��Ҫ����*this��s2��ֵ����
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
		//���ж�pos��ֵ�Ƿ����,���ų�posΪ0�����
		assert(pos <= _size);
		//���ж�capacity�Ƿ��㹻���������ȿ��ٿռ�
		if (_size == _capacity)		//�ռ���
		{
			size_t newcapacity = _capacity == 0 ? 3 : _capacity * 2;
			T* newarray = new T[newcapacity];
			for (size_t i = 0; i < _size; ++i)//��Ԫ��
			{
				newarray[i] = _array[i];
			}
			delete[] _array;//�ͷžɿռ�
			_array = newarray;
			_capacity = newcapacity;
		}
		
			//֮�󣬲������ݣ�����Ҫ����posΪ0�����,��ʱ��ֱ�Ӳ���Ԫ��,��posλ�ò��룬������pos����±��������
			size_t j = 0; 
			for (j = _size; j > pos; --j)//����Ԫ��
			{
				_array[j] = _array[j - 1];		
			}

			_array[j] = x;	
			_size += 1;
	}
	void Erase(size_t pos)
	{
		//���ж�pos�Ƿ����
		assert(pos <= _size - 1);
		//��posλ��Ԫ��
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

