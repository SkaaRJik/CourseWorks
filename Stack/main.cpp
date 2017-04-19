#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

#include "stack.h"

void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Stack stack;
	while (true) {
		bool escape = false;
		cout << "Работа со стеком";
		cout << "\n 1. Добавить элемент в стек";
		cout << "\n 2. Вывести стек";
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
				stack.Add(value);
				system("cls");
				break;
			}
			case 50: {
				stack.Show();
				cout << "\n";
				system("Pause");
				system("cls");
				break;
			}
			case 51: {
				try {
					cout << "Извлечено:" << stack.Extract();
				}
				catch (Stack::NullException) {
					cout << "Стэк Пуст\n";
					system("Pause");
					system("cls");
				}
				cout << "\n";
				system("Pause");
				system("cls");
				break;
			}
			case 27: {escape = true; break;}
			default: {break;}
		}
		if (escape) break;
	}
}