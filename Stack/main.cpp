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
		cout << "������ �� ������";
		cout << "\n 1. �������� ������� � ����";
		cout << "\n 2. ������� ����";
		cout << "\n 3. ������� ������� �� �����";
		cout << "\n esc. �����";
		cout << "\n\n��� ����� => ";
		int choice = _getch();
		system("cls");
		switch (choice)
		{
			case 49: {
				int value;
				cout << "������� ����� => "; 
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
					cout << "���������:" << stack.Extract();
				}
				catch (Stack::NullException) {
					cout << "���� ����\n";
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