#include "cstdio"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

#include "HashTable.h"

void main()
{
	int size;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	HashTable hashTable(2000);
	cout << "\n Метод Деление по модулю t:";
	hashTable.pushModT(100);
	hashTable.pushModT(200);
	hashTable.pushModT(500);
	hashTable.pushModT(1000);
	hashTable.pushModT(1500);
	hashTable.pushModT(2000);
	cout << "\n Метод Средняя часть квадрата:";
	hashTable.pushAverageType(100);
	hashTable.pushAverageType(200);
	hashTable.pushAverageType(500);
	hashTable.pushAverageType(1000);
	hashTable.pushAverageType(1500);
	hashTable.pushAverageType(2000);
	cout << "\n Метод Свертки:";
	hashTable.pushSum(100);
	hashTable.pushSum(200);
	hashTable.pushSum(500);
	hashTable.pushSum(1000);
	hashTable.pushSum(1500);
	hashTable.pushSum(2000);
	cout << "\n";
	system("pause");
}