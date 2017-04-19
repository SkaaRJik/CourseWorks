#include<iostream>
#include<cstdio>
#include<string>
#include<conio.h>
#include<windows.h>

using namespace std;
int W, K;
int curW;
int curP, bestP, lostP;
int MaxP;


void metodvg(int j, int *p, int *w, int *x, int *y) {
	if (j == K) {
		if (bestP < curP && curW <= W) {
			for (int i = 0; i < K; ++i) y[i] = x[i];
			bestP = curP;
		}
		return;
	}
	lostP += p[j];
	if (bestP <= MaxP - lostP)
		metodvg(j + 1, p, w, x, y);
	lostP -= p[j];
	curW += w[j];  curP += p[j];
	if (curW <= W) {
		x[j] = 1;
		metodvg(j + 1, p, w, x, y);
		x[j] = 0;
	}
	curW -= w[j]; curP -= p[j];
}


int main() {
	setlocale(LC_ALL, "Russian");
	cout << "Backpack capacity = "; cin >> W;
	freopen("input.txt", "r", stdin);  cin >> K;
	string  *s = new string[K];
	int *p = new int[K];
	int *w = new int[K];
	int *x = new int[K];
	int *y = new int[K];
	for (int i = 0; i<K; ++i) { x[i] = 0;  y[i] = 0; }
	cout << "\nПредмет_вес_ценность";
	for (int i = 0; i<K; ++i) cin >> s[i] >> w[i] >> p[i];
	for (int i = 0; i<K; i++) MaxP += p[i];
	metodvg(0, p, w, x, y); //идем в рекурсивную функцию
	cout << "\ny ";
	for (int i = 0; i<K; ++i) cout << y[i] << "  ";
	cout << endl;
	for (int i = 0; i<K; ++i)
		if (y[i]) cout << s[i] << endl;
	cout << endl;
	cout << "\nbestP = " << bestP << endl;
	cout << endl;

	getch();
	return 1;
}