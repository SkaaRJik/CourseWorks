#pragma once



class Tree {
	struct List
	{
		int x, y;  //���������� ������
		int value; //�������������� �������
		struct List *left;
		struct List *right;
	};
	struct List *head;//������� �����
	int X, Y;
	int width, hight;
public:
	class NullException {};
	Tree() {
		head = NULL; //������������� ������ ������ ��������  
		Y = 10;
		width = 30;
		hight = 30;
	}
	void GiveX(int x){ X = x; }
	void Add(int value); //���������� �������� � ������
	void Show();
	void GoStepByStep(List *cur);

};

void Tree::Add(int value) {
	if (head == NULL)
	{
		head = new List; //����������� �������
		//_tcscat(value, head->value); //������ ������� � ���� value
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
		while (cur!=NULL) 
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
		}
		else
		{
			curPrev->right = cur;
			cur->x = curPrev->x + width + 25;
			cur->y = curPrev->y + hight + 30;
		}
		//_tcscat(value, cur->value); //������ ������� � ���� value
		cur->value=value;
		cur->left = NULL;
		cur->right = NULL;
	}
}

void Tree::Show() {
	//hdc = GetDC(hWnd);
	
	if (!head) 
	{
		//TextOut(hdc, X, Y, _T("�������� ������� � ������"), 30);
	}
	else 
	{
		GoStepByStep(head);
	}
	//ReleaseDC(hWnd,hdc);
}

void Tree::GoStepByStep(List *cur) 
{
	if (cur!=NULL) 
	{
		if (cur == head)
			cout << "������: " << head->value;
		if (cur->left != NULL)
		{
			if(cur!=head)
			cout << " ����: " << cur->value;
			cur = cur->left;
			GoStepByStep(cur);
		}
		if (cur->right != NULL)
		{
			if (cur != head)
			cout << " �����: " << cur->value;
			cur = cur->right;
			GoStepByStep(cur);
		}
		

	}
}
