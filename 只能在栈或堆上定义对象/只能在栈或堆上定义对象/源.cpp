#include<iostream>
using namespace std;
//只在栈上开辟
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

//只在堆上开辟
class person
{
public:
	static person* create()
	{
		return new person();
	}
	void destroy()
	{
		delete this;//首先会调用析构函数，在调用free释放空间
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
	//test(ptr);//调用父类的func
	//test(sptr);//调用子类的func

	//cout << endl<<"释放父类对象:" << endl;
	//ptr->destroy();
	//
	//cout << endl<<"释放父类对象:" << endl;
	//sptr->destroy();

	//cout << endl<< "父类指针指向子类对象:" << endl;
	//person* p = new student;
	//cout << endl<<"释放掉子类对象" << endl;
	//p->destroy();
	system("pause");
	return 0;
}






