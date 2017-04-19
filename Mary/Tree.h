#pragma once



class Tree {
	struct List
	{
		int x, y;  							//���������� ������
		int value; 							//�������������� �������
		struct List *left;					//����� �����
		struct List *right;					//������ �����
	};
	struct List *head;						//������ ������
	int X, Y;								//�������������� ������� ����� ������
	int width, hight;						//������ � ������ ��������
public:
	class NullException {};					//����� ����������: ������ ������
	class NotFoundException {};				//����� ����������: ������� �� ������
	Tree() {								//�����������
		head = NULL;						//������������� ������ ������ ��������  	
		width = 30;							//����������� ������
		hight = 30;							//��������
	}
	void GiveXY(int x, int y) { X = x; Y = y; }											//������������ ������ �� ������ ������� �������
	void IsEmpty() { if (head == NULL)	throw Tree::NullException(); }	//�������� �� ������� ������
	void Add(int value);												//���������� �������� � ������
	void Show(HWND hWnd, HDC &hdc);										//����� ������
	void Show(List *curPrev, List *cur, HWND hWnd, HDC &hdc);			//������������� ����������� ������� ������ ������ ������ ����
	void Delete(int value);												//�������� ��������
};


void Tree::Add(int value) {
		if (head == NULL)
		{
			head = new List; //����������� �������
			head->value = value;
			head->x = X;
			head->y = Y;
			head->left = NULL;
			head->right = NULL;
		}
		else
		{
			List *cur = head;
			List *curPrev = head;
			while (cur != NULL)
			{
				if (value < cur->value)
				{
					curPrev = cur;
					cur = cur->left;
					
				}
				else
				{
					curPrev = cur;
					cur = cur->right;
				}
			}
			cur = new List;
			if (value < curPrev->value)
			{
				curPrev->left = cur;
				cur->x = curPrev->x - 25;
				cur->y = curPrev->y + 30;
				if (curPrev == head)
				{
					cur->x = curPrev->x - 150;
					cur->y = curPrev->y + 30;
				}
			}
			else
			{
				curPrev->right = cur;
				cur->x = curPrev->x + 25;
				cur->y = curPrev->y + 30;
				if (curPrev == head) 
				{
					cur->x = curPrev->x + 150;
					cur->y = curPrev->y + 30;
				}
			}
			cur->value = value;
			cur->left = NULL;
			cur->right = NULL;
	}
}



void Tree::Show(HWND hWnd, HDC &hdc) {
	if (!head) 
	{
		SetBkColor(hdc, RGB(0, 255, 0));
		TextOut(hdc, X-70, Y, _T("�������� ������"), 15);
	}
	else 
	{
		Show(head, head, hWnd, hdc);
	}
}



void Tree::Show(List *curPrev, List *cur,HWND hWnd, HDC &hdc) 
{
	if (cur!=NULL || curPrev!=NULL) 
	{
		hdc = GetDC(hWnd);
		MoveToEx(hdc, curPrev->x + width/2.1, curPrev->y + hight, NULL);
		LineTo(hdc, cur->x + width / 3, cur->y + hight / 4);
		HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 255));
		HRGN hRgnEllipse = CreateEllipticRgn(cur->x, cur->y, cur->x+width, cur->y+hight);
		FillRgn(hdc, hRgnEllipse, hBrush);
		DeleteObject(hRgnEllipse);
		DeleteObject(hBrush);
		TCHAR value[10];
		_stprintf(value, _T("%d"), cur->value);
		SetBkColor(hdc, RGB(0, 255, 255));
		TextOut(hdc, cur->x+width/3, cur->y+hight/4, value, _tcslen(value));
		ReleaseDC(hWnd, hdc);
		if (cur->left!=NULL) 
		Show(cur, cur->left,hWnd, hdc);
		if (cur->right != NULL)
		Show(cur, cur->right,hWnd, hdc);
	}
}

void Tree::Delete(int value)
{
	if (head == NULL)	throw Tree::NullException();
	else
	{
		/* ������ ������*/
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
		/* ����� ������*/

	
		if (!key)  throw Tree::NotFoundException(); //���� �� ������
		else
		{
			//if (key == head) { delete head; head = NULL; }
			/* ������ �������� �����*/
			if (!key->right && !key->left)
			{

				if (value < curPrev->value)
				{
					curPrev->left = NULL;
				}
				else if (value > curPrev->value)
				{
					curPrev->right = NULL;
				}
				if (key == head) head = NULL;
				delete key;
			}
			/* ����� �������� �����*/
			/* ������ �������� ���� � 1 ��������*/
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
				}
				delete key;
			}
			/* ����� �������� ���� � 1 ��������*/
			/* ������ �������� ���� � 2 ���������*/
			else if (key->right && key->left)
			{
				List *cur = key->right;
				if (!cur->left)
				{
					if (key != head)
					{
						List *buffer = key->left;
						if (value < curPrev->value)
						{
							curPrev->left = cur;
						}
						else if (value > curPrev->value)
						{
							curPrev->right = cur;
						}
						cur->x = key->x;
						cur->y = key->y;
						cur->left = buffer;
						delete key;
					}
					else
					{
						key->value = cur->value;
						key->right = cur->right;
					}
				}
				else
				{

					while (cur->left) {
						curPrev = cur;
						cur = cur->left;
					}
					curPrev->left = NULL;
					key->value = cur->value;
					//if (key == head) { cur = head; }
					delete cur;
				}
			}
			/* ����� �������� ���� � 1 ��������*/
		}
	}
}