#include"SmartPtr.h"
int main()
{
	try
	{
			TestCycle();
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
	catch (...)
	{
		cout << "λ���쳣" << endl;
	}
	system("pause");

	return 0;
}


