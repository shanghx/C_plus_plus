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
		cout << "Î»ÖÃÒì³£" << endl;
	}
	system("pause");

	return 0;
}


