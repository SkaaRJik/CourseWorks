#include <cstdio>
#include <iostream>
#include <windows.h>
#include <conio.h>


using namespace std;

#include "Tree.h"

void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Tree tree;
	while (true) {
		bool escape = false;
		cout << "Работа с деревом";
		cout << "\n 1. Добавить элемент в дерево";
		cout << "\n 2. Вывести дерево";
		cout << "\n 3. Извлечь элемент из стека";
		cout << "\n esc. Выход";
		cout << "\n\nВаш выбор => ";
		int choice = _getch();
		system("cls");
		switch (choice)
		{
		case 49: {
			int value;
			cout << "Введите число => ";
			cin >> value;
			tree.Add(value);
			system("cls");
			break;
		}
		case 50: {
			tree.Show();
			//cout << "\n";
			system("Pause");
			system("cls");
			break;
		}
		case 51: {
			system("Pause");
			system("cls");
			break;
		}
		case 27: {escape = true; break; }
		default: {break; }
		}
		if (escape) break;
	}

	system("Pause");
}