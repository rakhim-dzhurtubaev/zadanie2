#include <windows.h>
#include <iostream>
using namespace std;
int main()
{
	HMODULE hDll; // дескриптор DLL 
	int (*Add)(int); // указатель на функцию Add из 
	int (*Sub)(int); // указатель на функцию Sub из DLL 
	int* pCount; // указатель на переменную count из DLL // загружаем динамически подключаемую библиотеку 
	hDll = LoadLibrary("C:\\Users\\217064\\source\\repos\\Dll1\\x64\\Debug\\Dll1.dll");
	if (!hDll)
	{
		cerr << "Load library failed." << endl;
		return GetLastError();
	}
	pCount = (int*)GetProcAddress(hDll, "count");
	if (!pCount)
	{
		cerr << "Get variable address failed." << endl;
		return GetLastError();
	}
	// выводим начальное значение переменной count 
	cout << "Initial count = " << (*pCount) << endl; // настраиваем адреса функций 
	Add = (int (*)(int))GetProcAddress(hDll, "Add");
	Sub = (int (*)(int))GetProcAddress(hDll, "Sub");
	if (!Add || !Sub)
	{
		cerr << "Get procedure address failed." << endl;
		return GetLastError();
	}
	cout << "count = " << Add(30) << endl;
	cout << "count = " << Sub(20) << endl;

	if (!FreeLibrary(hDll))
	{
		cerr << "Free library failed." << endl;
		return GetLastError();
	}
	cout << "Press any key to exit ";
	cin.get();
	return 0;
}