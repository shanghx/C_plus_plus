#include<iostream>
using namespace std;
//ֻ��ջ�Ͽ���
//class person
//{
//public:
//	person()
//	{
//		cout << "person()" << endl;
//	}
//	~person()
//	{
//		cout << "~person()" << endl;
//	}
//private:
//	void* operator new(size_t size)
//	{
//		return malloc(size);
//	}
//	void operator delete(void* p)
//	{
//		free(p);
//	}
//};

//ֻ�ڶ��Ͽ���
class person
{
public:
	static person* create()
	{
		return new person();
	}
	void destroy()
	{
		delete this;//���Ȼ���������������ڵ���free�ͷſռ�
	}
	virtual void func()
	{
		cout << "test person" << endl;
	}
protected:
	person()
	{
		cout << "person()" << endl;
	}
	virtual ~person()
	{
		cout << "~person()" << endl;
	}
	
};
class student:public person
{
public:
	
	student()
	{
		cout << "student()" << endl;
	}
	virtual ~student()
	{
		cout << "~student()" << endl;
	}
	virtual void func()
	{
		cout << "test student" << endl;
	}
};
void test(person* p)
{
	p->func();
}


int main()
{

	person* ptr = person::create();
	ptr->destroy();

	//person *ptr=new person;
	//student *sptr=new student;
	//test(ptr);//���ø����func
	//test(sptr);//���������func

	//cout << endl<<"�ͷŸ������:" << endl;
	//ptr->destroy();
	//
	//cout << endl<<"�ͷŸ������:" << endl;
	//sptr->destroy();

	//cout << endl<< "����ָ��ָ���������:" << endl;
	//person* p = new student;
	//cout << endl<<"�ͷŵ��������" << endl;
	//p->destroy();
	system("pause");
	return 0;
}






