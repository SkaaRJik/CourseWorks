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
		cout << "������ � �������";
		cout << "\n 1. �������� ������� � ������";
		cout << "\n 2. ������� ������";
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