#include<iostream>
using namespace std;
#include<assert.h>
#include<string>
#include"Queue.h"
#include"Stack.h"

//要求:
// 模板实现顺序表--考虑深层次的深浅拷贝问题 
// 带头节点的双向循环链表--思考结构的优势 
//template
// 1.适配器模式 
// 2.模板的模板参数 
int main()
{
	
	Queue<string,List<string>>q1;
	q1.Push("111");
	q1.Push("222");
	q1.Push("333");
	q1.print();
	Queue<int, SeqList<int>>q2;
	q2.Push(1);
	q2.Push(2);
	q2.Push(3);
	q2.print(); 
	cout << "Front:" << q2.Front() << endl;

	Stack<string, List<string>>s1;
	s1.Push("111");
	s1.Push("222");
	s1.Push("333");
	s1.print();
	Stack<int, SeqList<int>>s2;
	s2.Push(1);
	s2.Push(2);
	s2.Push(3);
	s2.print(); 
	cout << "Top:" << s2.Top() << endl;
	system("pause");
	return 0;
}
