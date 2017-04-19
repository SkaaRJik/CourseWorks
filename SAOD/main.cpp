#define _CRT_SECURE_NO_WARNINGS

#include <conio.h>

#include <cstdio>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>



using namespace std;

void includingSort(int arrA[], int size);
void includingSortFor(int arrA[], int size);
void countingSort(int arrAFull[], int size);
void extractSort(int arrAFull[], int size);
void swapSort(int arrAFull[], int size);
void showArray(int *arrAFull, int size);

	void main()  {
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		ifstream in("input.txt", ios::in);
		cout << "Размерность массива => ";
		int size;
		cin >> size;
		int arrAFull[50000];
		//int[] arrB = new int[size];

		for (int i = 0; i<size; i++) {
		in >> arrAFull[i];
		}

		int a[10];

		/*for (int x : a) {
			x = 0;
			cout << x << " ";
		}*/
		
		
		/*includingSort(arrAFull, size);
		includingSortFor(arrAFull,size);
		countingSort(arrAFull, size);
		swapSort(arrAFull, size);
		extractSort(arrAFull, size);*/
		
		system("Pause");
	}

	void includingSort(int arrA[], int size) {
		cout <<"\nРАБОТАЕТ: Метод включением";
		LARGE_INTEGER start, finish, freq;
		int* arrB = new int[size];
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&start);
		int bCount = 0;
		arrB[bCount] = arrA[bCount];//заносим в массив b первый элемент массива a
		bCount++;
		
		

		for (int i = 1; i < size; i++) {
			if (arrA[i]<arrB[bCount - 1]) {
				int j = bCount - 1;
				while (arrA[i]<arrB[j]) {
					arrB[j + 1] = arrB[j];
					j--;
					if (j<0) { break; }
				}
				arrB[++j] = arrA[i];
				bCount++;
			}
			else {
				arrB[bCount] = arrA[i];
				bCount++;
			}
		}
		QueryPerformanceCounter(&finish);
		double d = (finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
		cout << "\nВремя выполнения " << d << "милисек.";


		showArray(arrB, size);
	}

	void includingSortFor(int arrA[], int size) {
		cout << "\nРАБОТАЕТ: Метод включением через for";
		LARGE_INTEGER start, finish, freq;
		int* arrB = new int[size];
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&start);
		int bCount = 0;
		arrB[bCount] = arrA[bCount];//заносим в массив b первый элемент массива a
		bCount++;
		for (int i = 1; i < size; i++) {
			if (arrA[i] < arrB[bCount - 1]) {
				int key = 0;
				for (int j = bCount-1; j >= 0; j--) {
					if (arrA[i] < arrB[j]) {
						arrB[j+1] = arrB[j];
					}
					else {
						key = j+1;
						break;
					}
					key = j;
					//if (j <= 0) key = 0;
				}
				arrB[key] = arrA[i];
				bCount++;
			}
			else {
				arrB[bCount] = arrA[i];
				bCount++;
			}
		}
		QueryPerformanceCounter(&finish);
		double d = (finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
		cout << "\nВремя выполнения " << d << "милисек.";


		showArray(arrB, size);
	}

	void countingSort(int arrAFull[], int size) {
		cout <<"\nРАБОТАЕТ: Метод подсчетом";
		LARGE_INTEGER start, finish, freq;
		int count = 0;
		for (int i = 0; i<size; i++) {
			for (int k = i + 1; k < size; k++) {
				if (arrAFull[k] == arrAFull[i] && i != k) {
					count++;
					break;
				}
			}
		}
		int* buffer = new int[count];
		int bufCount = 0;
		int* arrA = new int[size - count];
		int* arrB = new int[size - count];
		count = 0;

		boolean repeat = false;

		for (int i = 0; i<size; i++) {
			for (int j = i; j<size; j++) {
				if (arrAFull[i] == arrAFull[j] && i != j) repeat = true;
			}
			if (repeat == false)
				arrA[count++] = arrAFull[i];
			else {
				buffer[bufCount++] = arrAFull[i];
				repeat = false;
			}
		}
		int k = 0;
		QueryPerformanceFrequency(&freq);QueryPerformanceCounter(&start);
		for (int i = 0; i<count; i++) {
			k = 0;
			for (int j = 0; j<count; j++) {
				if (arrA[j] < arrA[i]) k++;
			}
			arrB[k] = arrA[i];
		}
		QueryPerformanceCounter(&finish);
		double d = (finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
		//cout << "Элементов=" << count;
		cout << "\nВремя выполнения " << d << "милисек.";
		showArray(arrB, size);


	}

	void swapSort(int arrAFull[], int size) {
		cout <<"\nРАБОТАЕТ: Метод обменом";
		LARGE_INTEGER start, finish, freq;
		QueryPerformanceFrequency(&freq);QueryPerformanceCounter(&start);
		for (int i = 0; i < size - 1; i++) {
		         bool swapped = false;
		          for (int j = 0; j < size - i - 1; j++) {
		              if (arrAFull[j] >arrAFull[j + 1]) {
		                  int b = arrAFull[j];
						  arrAFull[j] = arrAFull[j + 1];
						  arrAFull[j + 1] = b;
		                  swapped = true;
		
				}
			}
			
				         if (!swapped)
				           break;

		}
		QueryPerformanceCounter(&finish);
		double d = (finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
		cout << "\nВремя выполнения " << d << "милисек.";
		showArray(arrAFull, size);
	}

	void extractSort(int arrAFull[], int size) {

		cout <<"\nРАБОТАЕТ: Метод извлечением";
		
		LARGE_INTEGER start, finish, freq;
		QueryPerformanceFrequency(&freq);QueryPerformanceCounter(&start);
		for (int i = 0; i<size; i++) {
			int min = i;
			for (int j = i + 1; j < size; j++) {
				if (arrAFull[min]>arrAFull[j] && min != j) min = j;
			}
			int buffer = arrAFull[i];
			arrAFull[i] = arrAFull[min];
			arrAFull[min] = buffer;
		}
		QueryPerformanceCounter(&finish);
		double d = (finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
		cout << "\nВремя выполнения " << d << "милисек.";
		showArray(arrAFull, size);
	}

	void showArray(int *arrAFull, int size) {
		if (size > 11) {
			cout <<"\nПервые 10 элементов массива:\n";
			for (int i = 0; i < 10; i++) {
				cout <<arrAFull[i] << " ";
				if (i == 9) cout <<" ...";
			}
		}
		else {
			for (int i = 0; i < size; i++) {
				cout <<arrAFull[i] << " ";
			}
		}
		cout <<"\n";
	}


