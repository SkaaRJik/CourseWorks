#pragma once

#include "resource.h"
#include <vector>

class Tree {
	struct List
	{
		int x, y;							//Координаты вывода
		int value;							//информационный элемент
		struct List *left;					//Левая ветвь
		struct List *right;					//Правая ветвь
		UINT level;							//Уровень листа		
		short int balance;					//Показатель баланса
		Image* logo;						//Картинка узла
	};
	struct List *head;						//семечко дерева
	int X, Y;								//Позиция "роста" дерева
	int width, hight;						//Радиус листов элемента(Для функции рисования)
	int distance;							//Расстояние между потомком и родителем
	Image** pictures;						//Массив картинок для узлов
	const WCHAR textLevel[8] = L"Уровень";	//Константная строка для вывода в Инфо. табло
	const WCHAR textBalance[7] = L"Баланс";	//Константная строка для вывода в Инфо. табло
public: std::vector<int> elements;			//Вектор всех элементов дерева
public:
	class NullException {};					//Класс исключения: Пустое дерево
	class NotFoundException {};				//Класс исключения: Элемент не найден
	Tree();									//Конструктор без параметров
	~Tree();								//Деструктор
	POINT getResolutionOfNode();			//Возвращает ширину, высоту каждого узла(Графика)
	void loadResourse();					//Загрузка картинок в область памяти
	void setX(int x);						//Сетер координаты X
	void setY(int y);						//Сетер координаты Y
	void offsetXY(int offsetX, int offsetY);	//Функция смещения корня дерева на вектора OffsetX и OffesetY
	void offsetXY(List* cur, int offsetX, int offsetY);	//Рекурсивная функция смещения ВСЕГО дерева на вектора.
	bool CheckIfEmpty();					//Проверка дерева на пустоту; Генерирует исключение
	void Add(int value, bool checkRot);		//Добавление элемента в дерево
	void showGDI(Graphics *temp, List *curPrev, List *cur);	//Рекурсивная функция показа всех узлов дерева
	void showGDI(HWND hWnd, int x, int y);					//Функция вызова показа дерева рекрсивно
	void setLogo(List *cur);				//Установка картинки для узла
	void Delete(int value);					//Удаление элемента
	void deleteAll(List* cur);				//Рекурсивная функция удаления узла
	void deleteAll();						//Функция вызова рекурсивного удаления всего дерева
	void SetLevels(List* curPrev, List* cur);//Рекурсивная функция расстоновки уровней
	void RefreshXY(List* curPrev, List* cur); //Выравнивание листов дерева соответственно уровню
	void setBalance(List* cur, List* curPrev);//Установка баланса
	void checkRotation(List* cur, List* curPrev);//Проверка дерева на сбалансированность
	void leftRotation(List* cur, List* curPrev);//Малый левый поворот
	void rightRotation(List* cur, List* curPrev);//Малый правый поворот
	void bigLeftRightRot(List* unstableCur);//Большой левый поворот
	void bigRightLeftRot(List* unstableCur);//Большой правый поворот
	void rankingXY(List* cur, int multiplier);//Функция для расширения узлов на экране(Графика)
	void getAllElements();					//Гетер всех значений дерева
	void fillVec(List *cur);				//Рекурсивная функция,заполняющая вектор elements
	struct List* getEdgeRightNode();		//гетер указателя крайнего лево-нижнего узла
	struct List* getEdgeLeftNode();			//гетер указателя крайнего право-нижнего узла
	POINT getNodeXY(List* cur);				//гетер координат x и y узла
	List* getHead();						//гетер указателя головы
	struct List* findUnstableNode(List* underNode);	//функция поиска нестабильного узла
	void setInfoBox(Rect* infoBox, List* cur);		//Функция для рисования табло под узлом

};