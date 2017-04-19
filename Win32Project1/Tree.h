#pragma once

#include <string>

class Tree {
	struct List
	{
		int x, y;							//Координаты вывода
		int value;							//информационный элемент
		struct List *left;					//Левая ветвь
		struct List *right;					//Правая ветвь
		UINT level;							//Уровень листа		
		short int balance;					//Показатель баланса
		Image* logo;
	};
	struct List *head;						//семечко дерева
	int X, Y;								//Позиция "роста" дерева
	int width, hight;						//Радиус листов элемента(Для функции рисования)
	int distance;
	Image** pictures;
	const WCHAR textLevel[8] = L"Уровень";
	const WCHAR textBalance[7] = L"Баланс";
	bool classic;
public: std::vector<int> elements;
public:
	class NullException {					//Класс исключения: Пустое дерево
		TCHAR GetError() { TCHAR Error[22]; lstrcpy(Error, _T("Error: дерево пустое")); return *Error; }
	};
	class NotFoundException {				//Класс исключения: Элемент не найден
		TCHAR GetError() { TCHAR Error[26]; lstrcpy(Error, _T("Error: элемент не найден")); return *Error; }
	};
	Tree()
	{								//Конструктор без параметров
		head = NULL;						//Инициализация семечка дерева пустым адрессом  
										//Первоначальная позиция Y
		width = 60;							//Задаем диаметр
		hight = 60;							//листов 
		distance = hight*1.8;
		classic = false;
	}
	~Tree()							//Деструктор
	{
		deleteAll();
	}
	POINT getResolutionOfNode() {	//Возвращает ширину, высоту каждого узла(Графика)
		POINT res = { width, hight };
		return res;
	}
	void loadResourse();			//
	void setX(int x);
	void setY(int y);
	void offsetXY(int offsetX, int offsetY);
	void offsetXY(List* cur, int offsetX, int offsetY);
	bool CheckIfEmpty() { if (head == NULL) { throw Tree::NullException(); return 1; } else return 0; }	//Проверка дерева на пустоту
	bool CheckIfEmpty(bool a) { if (head == NULL) { return 1; } else return 0; }	//Проверка дерева на пустоту
	void Add(int value, bool checkRot);					//Добавление элемента в дерево
	void showGDI(Graphics *temp, List *curPrev, List *cur); 
	void showGDI(HWND hWnd, int x, int y);
	void setLogo(List *cur);
	void Delete(int value);					//Удаление элемента
	void deleteAll(List* cur);
	void deleteAll();
	void SetLevels(List* curPrev, List* cur);//Рекурсивная функция расстоновки уровней
	void RefreshXY(List* curPrev, List* cur); //Выравнивание листов дерева соответственно уровню
	void setBalance(List* cur, List* curPrev);
	void checkRotation(List* cur, List* curPrev);
	void leftRotation(List* cur, List* curPrev);
	void rightRotation(List* cur, List* curPrev);
	void bigLeftRightRot(List* unstableCur);
	void bigRightLeftRot(List* unstableCur);
	void rankingXY(List* cur, int multiplier);
	void getAllElements();
	void fillVec(List *cur);
	struct List* getEdgeRightNode();
	struct List* getEdgeLeftNode();
	POINT getNodeXY(List* cur)
	{
		POINT xy = { cur->x, cur->y };
		return xy;
	}
	//void saveTree();
	List* getHead() { return head; }
	struct List* findUnstableNode(List* underNode);
	void setInfoBox(Rect* infoBox, List* cur);
	
};

void Tree::loadResourse()
{
	pictures = new Image*[17];
	char format[5] = ".png";
	for (int i = 0; i <= 17; i++)
	{
		char buf[30] = "pic\\";
		char num[3];
		WCHAR res[30];
		_itoa(i, num, 10);
		strcat_s(buf, 30, num);
		strcat_s(buf, 30, format);
		swprintf_s(res, L"%S", buf);
		pictures[i] = Image::FromFile(res, 1);
	}
}

void Tree::showGDI(HWND hWnd, int x, int y)
{
	HDC hdc = GetDC(hWnd);
	Graphics g(hdc);
	
	
	if (!head)
	{
		WCHAR welcome[] = L"Добавьте элемент в дерево!";

		RectF bounds(0,0, abs(x), abs(y));
		LinearGradientBrush brush(bounds, Color(255, 255, 0, 0), Color(255, 0, 255, 0),
			LinearGradientModeVertical);

		// Готовим формат и параметры шрифта
		StringFormat format;
		format.SetAlignment(StringAlignmentCenter);
		format.SetLineAlignment(StringAlignmentCenter);
		Font font(L"Arial", 48, FontStyleBold);

		// Выводим текст приветствия, длина -1 означает, 
		// что строка заканчивается нулем
		g.DrawString(welcome, -1, &font, bounds, &format, &brush);
	}
	else
	{
		
		Bitmap* buf = new Bitmap(x,y);
		Graphics *temp = new Graphics(buf);
		Tree::showGDI(temp,head, head);
		g.DrawImage(buf, 0, 0, x, y);
		delete(buf);
		delete(temp);

	}
	ReleaseDC(hWnd, hdc);
}

void Tree::showGDI(Graphics *temp, List *curPrev, List *cur)
{
	if (cur != NULL || curPrev != NULL)
	{
		Pen *line = new Pen(Color(130, 130, 130));
		if (curPrev != cur)
		{
			Point Prev((curPrev->x + width / 2), (curPrev->y + hight + hight*0.4));
			Point Current((cur->x + width / 2), cur->y);
			temp->DrawLine(line, Prev, Current);
		}
		temp->DrawImage(cur->logo, cur->x, cur->y, width, hight);
		if (!classic)
		{
			int rectH = (hight / 2) * 3 / 4, rectW = rectH;
			Rect* infoBox = new Rect[6];
			setInfoBox(infoBox, cur);

			RectF* gradientRect = new RectF(infoBox[0].X, infoBox[0].Y, infoBox[2].X + infoBox[2].Width, infoBox[2].Y + infoBox[2].Height);
			LinearGradientBrush *brush = new LinearGradientBrush(*gradientRect, Color(255, 0, 0, 0), Color(125, 255, 255, 255),
				LinearGradientModeBackwardDiagonal);
			temp->FillRectangles(brush, infoBox, 3);
			delete brush;
			delete gradientRect;


			gradientRect = new RectF(infoBox[3].X, infoBox[3].Y, infoBox[3].X + infoBox[3].Width, infoBox[3].Y + infoBox[3].Height);
			brush = new LinearGradientBrush(*gradientRect, Color(255, 155,45, 48), Color(255, 255, 0, 0),
				LinearGradientModeVertical);
			for (int i = 3; i < 6; i++)
				temp->FillRectangle(brush, infoBox[i]);
			delete brush;
			delete gradientRect;

			temp->DrawRectangles(line, infoBox, 6);
			
			temp->SetPageUnit(UnitPixel);
			StringFormat format;
			format.SetAlignment(StringAlignmentCenter);
			format.SetLineAlignment(StringAlignmentCenter);
			Font font(L"TimesNewRoman", 12, FontStyleBold);

			SolidBrush textBrush(Color::GhostWhite);

			//WCHAR *value = new WCHAR[10];
			WCHAR value[10];
			_stprintf(value, (L"%d"), cur->value);
			PointF *textPanel = new PointF(infoBox[4].X , infoBox[4].Y);
			temp->DrawString(value,-1,&font, *textPanel,&textBrush);
			delete textPanel;

			
			_stprintf(value, (L"%d"), cur->level);
			textPanel = new PointF(infoBox[3].X + infoBox[3].Width / 5, infoBox[3].Y + infoBox[3].Height / 5);
			temp->DrawString(value, -1, &font, *textPanel, &textBrush);
			Font font1(L"TimesNewRoman", 6, FontStyleBold);

			PointF *titlePanel = new PointF(infoBox[3].X-5, infoBox[3].Y-10);
			temp->DrawString(textLevel, -1, &font1, *titlePanel, &textBrush);
			delete textPanel;
			delete titlePanel;

			
			_stprintf(value, (L"%d"), cur->balance);
			textPanel = new PointF(infoBox[5].X + infoBox[5].Width / 5, infoBox[5].Y + infoBox[5].Height / 5);
			temp->DrawString(value, -1, &font, *textPanel, &textBrush);

			titlePanel = new PointF(infoBox[5].X - 5, infoBox[5].Y - 10);
			temp->DrawString(textBalance, -1, &font1, *titlePanel, &textBrush);
			delete textPanel;
			delete titlePanel;
			

		}
		delete line;
		if (cur->left != NULL)
		{
			//GoStepByStep(cur, cur->left, hWnd, hdc);
			showGDI(temp, cur, cur->left);
		}
		if (cur->right != NULL)
		{
			//GoStepByStep(cur, cur->right, hWnd, hdc);
			showGDI(temp, cur, cur->right);
		}
	}
}

void Tree::setInfoBox(Rect* infoBox, List* cur)
{
	int rectH = (hight / 2) * 3 / 4, rectW = rectH;
	infoBox[0].X = cur->x - rectW*1.3;
	infoBox[0].Y = cur->y + hight - rectW*1.3 + rectH;
	infoBox[0].Width = rectW*1.3;
	infoBox[0].Height = rectH*1.3;

	infoBox[1].X = cur->x;
	infoBox[1].Y = cur->y + hight;
	infoBox[1].Width = width;
	infoBox[1].Height = rectH;

	infoBox[2].X = cur->x +width;
	infoBox[2].Y = cur->y + hight - rectW*1.3 + rectH;
	infoBox[2].Width = rectW*1.3;
	infoBox[2].Height = rectH*1.3;

	infoBox[3].X = infoBox[0].X+ infoBox[0].Width/10;
	infoBox[3].Y = infoBox[0].Y + infoBox[0].Height / 10;
	infoBox[3].Width = infoBox[0].Width - 2*(infoBox[0].Width/10);
	infoBox[3].Height = infoBox[0].Height - 2* (infoBox[0].Height / 10);

	infoBox[4].X = infoBox[1].X + infoBox[1].Width / 20;
	infoBox[4].Y = infoBox[1].Y + infoBox[1].Height / 10;
	infoBox[4].Width = infoBox[1].Width - 2 * (infoBox[1].Width / 20);
	infoBox[4].Height = infoBox[1].Height - 2 * (infoBox[1].Height / 10);

	infoBox[5].X = infoBox[2].X + infoBox[2].Width / 10;
	infoBox[5].Y = infoBox[2].Y + infoBox[2].Height / 10;
	infoBox[5].Width = infoBox[2].Width - 2 * (infoBox[2].Width / 10);
	infoBox[5].Height = infoBox[2].Height - 2 * (infoBox[2].Height / 10);
}

void Tree::setLogo(List* cur)
{
	if(cur->value <= 0) cur->logo = pictures[0];
	else if (cur->value > 0 && cur->value <= 1) {cur->logo = pictures[rand()%2+1];} //Бабочка или мышка
	else if (cur->value >1 && cur->value <= 5) cur->logo = pictures[3]; //орел
	else if (cur->value >5 && cur->value <= 9) cur->logo = pictures[4]; //Кот
	else if (cur->value >9 && cur->value <= 30) cur->logo = pictures[5]; //Индюшка
	else if (cur->value >30 && cur->value <= 50) cur->logo = pictures[rand() % 2 + 6]; //обезьяна собачка
	else if (cur->value >50 && cur->value <= 80) cur->logo = pictures[8];// Овца
	else if (cur->value >80 && cur->value <= 100) cur->logo = pictures[9];//Панда
	else if (cur->value >100 && cur->value <=180) cur->logo = pictures[10];//Черепеаха 
	else if (cur->value >180 && cur->value <= 300) cur->logo = pictures[rand() % 2 + 11]; //Тигр дельфин
	else if(cur->value >300 && cur->value <=350) cur->logo = pictures[13];//Зебра
	else if (cur->value >350 && cur->value <= 900) cur->logo = pictures[14];//Морж
	else if (cur->value >900 && cur->value <= 1200) cur->logo = pictures[15];//жираф
	else if (cur->value >1200 && cur->value <= 3000) cur->logo = pictures[16];//Бегемот
	else if (cur->value >3000) cur->logo = pictures[17];	
}

void Tree::offsetXY(int offsetX, int offsetY)
{
	if (head)
	{
		X += offsetX;
		Y += offsetY;
		head->x += offsetX;
		head->y += offsetY;
		if (head->right) offsetXY(head->right, offsetX, offsetY);
		if (head->left) offsetXY(head->left, offsetX, offsetY);
	}
}

void Tree::offsetXY(List* cur, int offsetX, int offsetY)
{
	cur->x += offsetX;
	cur->y += offsetY;

	if (cur->right) offsetXY(cur->right, offsetX, offsetY);
	if (cur->left) offsetXY(cur->left, offsetX, offsetY);
}

void Tree::getAllElements()
{
	if (head)
	{
		if (!elements.empty()) { std::vector<int> empty; elements.swap(empty); }
		fillVec(head);
	}
}

void Tree::fillVec(List* cur)
{
	elements.push_back(cur->value);
	if (cur->left) fillVec(cur->left);
	if (cur->right) fillVec(cur->right);
}

void Tree::Add(int value, bool checkRot) {

	if (head == NULL)
	{
		head = new List; //Закладываем семечко
		head->level = 1;
		head->value = value;
		head->x = X;
		head->y = Y;
		head->left = NULL;
		head->right = NULL;
		setBalance(head, head);
		setLogo(head);
	}
	else
	{
		List *cur = head;
		List *curPrev = head;
		List *curPrevPrev = head;
		while (true)
		{
			if (value < cur->value)
			{
				curPrevPrev = curPrev;
				curPrev = cur;
				cur = cur->left;
			}
			else
			{
				curPrevPrev = curPrev;
				curPrev = cur;
				cur = cur->right;
			}

			if (!cur)
			{
				cur = new List;
				cur->level = 1;
				cur->y = curPrev->y + distance;
				;
				if (value < curPrev->value)
				{
					curPrev->left = cur;
				}
				else
				{
					curPrev->right = cur;
				}
				break;
			}
		}

		cur->value = value;
		cur->left = NULL;
		cur->right = NULL;
		setLogo(cur);
		SetLevels(head, head);
		rankingXY(head, head->level - 1);
		setBalance(head, head);
		if (checkRot) checkRotation(head, head);
		
	}
}

void Tree::SetLevels(List *curPrev, List *cur)
{

	if (cur->right)
		SetLevels(cur, cur->right);
	if (cur->left)
		SetLevels(cur, cur->left);



	if (!cur->right && !cur->left)
	{
		cur->level = 1;
	}
	else if (cur->right && !cur->left)
	{
		cur->level = cur->right->level + 1;
	}
	else if (!cur->right && cur->left)
	{

		cur->level = cur->left->level + 1;
	}
	else if (cur->right && cur->left)
	{
		if (cur->right->level >= cur->left->level)
		{
			cur->level = cur->right->level + 1;
		}
		else
		{
			cur->level = cur->left->level + 1;
		}
	}

}

void Tree::Delete(int value)
{
	if (head == NULL)	throw Tree::NullException();
	else
	{
		List *key = head;
		List *curPrev = key;
		while (key)
		{
			if (value < key->value)
			{
				curPrev = key;
				key = key->left;
			}
			else if (value > key->value)
			{
				curPrev = key;
				key = key->right;
			}
			else if (value == key->value) break;
		}
		if (!key)  throw Tree::NotFoundException();
		else
		{
			if (!key->right && !key->left)
			{

				if (key == curPrev->left)
				{
					curPrev->left = NULL;
				}
				else if (key == curPrev->right)
				{
					curPrev->right = NULL;
				}
				if (key == head) head = NULL;
				delete key;
				key = head;
				while (key)
				{
					if (value < key->value)
					{
						if (key->level > 1) key->level--;
						key = key->left;
					}
					else if (value > key->value)
					{
						if (key->level > 1) key->level--;
						key = key->right;
					}
				}
			}
			else if ((key->right && !key->left) || (!key->right && key->left))
			{
				if (key->right)
				{
					if (key == head)
					{
						head = key->right;
					}
					else
					{
						if (curPrev->right == key)
						{
							curPrev->right = key->right;
						}
						if (curPrev->left == key)
						{
							curPrev->left = key->right;
						}
					}
				}
				else
				{
					if (key == head)
					{
						head = key->left;
					}
					else
					{
						if (curPrev->right == key)
						{
							curPrev->right = key->left;
						}
						if (curPrev->left == key)
						{
							curPrev->left = key->left;
						}
					}
					curPrev->level--;
				}
				delete key;
			}
			else if (key->right && key->left)
			{
				List *cur = key->right;
				Image *bufImage = cur->logo;
				if (!cur->left)
				{
					if (key != head)
					{
						List *buffer = key->left;
						if (key == curPrev->left)
						{
							curPrev->left = cur;
						}
						else if (key == curPrev->right)
						{
							curPrev->right = cur;
						}
						cur->x = key->x;
						cur->y = key->y;
						cur->left = buffer;
						cur->logo = bufImage;
						delete key;
					}
					else
					{
						key->value = cur->value;
						key->right = cur->right;
						key->logo = cur->logo;
						delete cur;
					}
				}
				else
				{
					while (cur->left) {
						curPrev = cur;
						cur = cur->left;
					}
					if (cur->right)
					{
						curPrev->left = cur->right;
					}
					else
					{
						curPrev->left = NULL;
					}
					key->value = cur->value;
					key->logo = cur->logo;
					delete cur;
				}
			}
		}
		if (head)
		{
			SetLevels(head, head);
			setBalance(head, head);
			checkRotation(head, head);
			
			Tree::RefreshXY(head, head);
			rankingXY(head, head->level);
		}
	}
}

void Tree::RefreshXY(List *curPrev, List*cur)
{
	if (head)
	{
		if (cur == head)
		{
			head->x = X;
			head->y = Y;
		}
		if (cur)
		{
			if (curPrev != cur)
			{

				if (curPrev->y + hight != cur->y)
				{
					cur->y = curPrev->y + hight;
					if (curPrev->right == cur)
					{
						if (curPrev == head) cur->x = curPrev->x + 150;
						else cur->x = curPrev->x + 25;
					}
					if (curPrev->left == cur)
					{
						if (curPrev == head) cur->x = curPrev->x - 150;
						else cur->x = curPrev->x - 25;
					}
				}
			}
		}
		if (cur->right)
			RefreshXY(cur, cur->right);
		if (cur->left)
			RefreshXY(cur, cur->left);
	}
}

void Tree::setBalance(List *cur, List *curPrev)
{
	if (cur->left != NULL) setBalance(cur->left, cur);
	if (cur->right != NULL) setBalance(cur->right, cur);
		
	if (cur->right == NULL && cur->left == NULL) cur->balance = 0;
	else if (cur->right == NULL  && cur->left != NULL) cur->balance = -1;
	else if (cur->right != NULL  && cur->left == NULL) cur->balance = 1;
	else
	{
		cur->balance = cur->right->level - cur->left->level;
	}
	if (curPrev == head)
	{

		if (!curPrev->left && curPrev->right)
		{
			if (curPrev->right->right || curPrev->right->left)
			{
				curPrev->balance = 2;
			}
		}
		else if (curPrev->left && !curPrev->right)
		{
			if (curPrev->left->right || curPrev->left->left)
			{
				curPrev->balance = -2;
			}
		}
	}

}

void Tree::checkRotation(List* cur, List* curPrev)
{
	if (head->balance == -2) rightRotation(head, head);
	else if (head->balance == 2) leftRotation(head, head);
	if (head->balance == -2)
	{
		rightRotation(head, head);
		bigRightLeftRot(findUnstableNode(head->right));
		leftRotation(head, head);
	}
	else if (head->balance == 2)
	{
		leftRotation(head, head);
		bigLeftRightRot(findUnstableNode(head->left));
		rightRotation(head, head);
	}
	SetLevels(head, head);
	
	setBalance(head, head);
	RefreshXY(head, head);
	rankingXY(head, head->level);


}

void Tree::rightRotation(List* cur, List* curPrev)
{
	List *buf;
	if (cur == head)
	{
		buf = head;
		head = buf->left;
		int bufx = head->x;
		int bufy = head->y;
		head->x = buf->x;
		head->y = buf->y;
		RefreshXY(head, head);
		buf->left = head->right;
		head->right = buf;
	}
	SetLevels(head, head);
	
	setBalance(head, head);
	RefreshXY(head, head);
	rankingXY(head, head->level);
}

void Tree::leftRotation(List *cur, List* curPrev)
{
	List *buf;
	if (cur == head)
	{
		buf = head;
		head = buf->right;
		int bufx = head->x;
		int bufy = head->y;
		head->x = buf->x;
		head->y = buf->y;
		RefreshXY(head, head);
		buf->right = head->left;
		head->left = buf;
	}
	SetLevels(head, head);
	
	setBalance(head, head);
	RefreshXY(head, head);
	rankingXY(head, head->level);
}

void Tree::rankingXY(List* cur, int multiplier)
{
	int buf = 1;
	for (int i = multiplier - 1; i > 0; i--)
	{
		buf *= i;
	}


	if (cur->right)
	{
		cur->right->x = (cur->x + width*3/2 * buf);
		cur->right->y = cur->y + distance;
	}
	if (cur->left)
	{
		cur->left->x = (cur->x - width*3/2 * buf);
		cur->left->y = cur->y + distance;
	}

	if (cur->right) rankingXY(cur->right, multiplier - 1);
	if (cur->left) rankingXY(cur->left, multiplier - 1);
}

void Tree::bigLeftRightRot(List* unstableCur)
{
	List *buf;
	List* curPrev = unstableCur;
	unstableCur = unstableCur->right;
	if (curPrev->balance == 1)
	{
		buf = unstableCur->left;
		unstableCur->left = curPrev;
		curPrev->right = buf;
		head->left = unstableCur;
	}
	SetLevels(head, head);
	
	setBalance(head, head);
	RefreshXY(head, head);
	rankingXY(head, head->level);
}

void Tree::bigRightLeftRot(List* unstableCur)
{
	List *buf;
	List* curPrev = unstableCur;
	unstableCur = unstableCur->left;
	if (curPrev->balance == -1)
	{
		buf = unstableCur->right;
		unstableCur->right = curPrev;
		curPrev->left = buf;
		head->right = unstableCur;
	}
	SetLevels(head, head);
	
	setBalance(head, head);
	RefreshXY(head, head);
	rankingXY(head, head->level);
}

Tree::List* Tree::findUnstableNode(List* underNode)
{
	List* cur = underNode;
	List* curPrev = cur;
	List* curPrevPrev = cur;
	while (cur->balance != 0)
	{
		curPrevPrev = curPrev;
		curPrev = cur;
		if (cur->balance == 1) cur = cur->right;
		else if (cur->balance == -1) cur = cur->left;
	}
	return curPrevPrev;
}

void Tree::deleteAll() { if (head)deleteAll(head); }

void Tree::deleteAll(List* cur)
{

	if (cur->left) deleteAll(cur->left);
	if (cur->right) deleteAll(cur->right);

	if (cur == head) head = NULL;
	delete cur;
	cur = NULL;

}

Tree::List* Tree::getEdgeRightNode()
{
	if (head)
	{
		List* cur = head;
		while (cur->right || cur->left)
		{
			if (cur->right) cur = cur->right;
			else if (cur->left) cur = cur->left;
		}
		return cur;
	}
	else return nullptr;
}

Tree::List* Tree::getEdgeLeftNode()
{
	if (head)
	{
		List* cur = head;
		while (cur->right || cur->left)
		{
			if (cur->left) cur = cur->left;
			else if (cur->right) cur = cur->right;
		}
		return cur;
	}
	else return nullptr;
}

void Tree::setX(int x)
{
	if (!head) X = x;
	else {
		head->x = x;
		head->y = Y;
		rankingXY(head, head->level);
	}
}


void Tree::setY(int y)
{
	if (!head) Y = y;
	else {
		head->x = X;
		head->y = y;
		rankingXY(head, head->level);
	}
}

