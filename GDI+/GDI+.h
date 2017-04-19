#pragma once

#include "resource.h"
#include <vector>

class Tree {
	struct List
	{
		int x, y;							//���������� ������
		int value;							//�������������� �������
		struct List *left;					//����� �����
		struct List *right;					//������ �����
		UINT level;							//������� �����		
		short int balance;					//���������� �������
		Image* logo;						//�������� ����
	};
	struct List *head;						//������� ������
	int X, Y;								//������� "�����" ������
	int width, hight;						//������ ������ ��������(��� ������� ���������)
	int distance;							//���������� ����� �������� � ���������
	Image** pictures;						//������ �������� ��� �����
	const WCHAR textLevel[8] = L"�������";	//����������� ������ ��� ������ � ����. �����
	const WCHAR textBalance[7] = L"������";	//����������� ������ ��� ������ � ����. �����
public: std::vector<int> elements;			//������ ���� ��������� ������
public:
	class NullException {};					//����� ����������: ������ ������
	class NotFoundException {};				//����� ����������: ������� �� ������
	Tree();									//����������� ��� ����������
	~Tree();								//����������
	POINT getResolutionOfNode();			//���������� ������, ������ ������� ����(�������)
	void loadResourse();					//�������� �������� � ������� ������
	void setX(int x);						//����� ���������� X
	void setY(int y);						//����� ���������� Y
	void offsetXY(int offsetX, int offsetY);	//������� �������� ����� ������ �� ������� OffsetX � OffesetY
	void offsetXY(List* cur, int offsetX, int offsetY);	//����������� ������� �������� ����� ������ �� �������.
	bool CheckIfEmpty();					//�������� ������ �� �������; ���������� ����������
	void Add(int value, bool checkRot);		//���������� �������� � ������
	void showGDI(Graphics *temp, List *curPrev, List *cur);	//����������� ������� ������ ���� ����� ������
	void showGDI(HWND hWnd, int x, int y);					//������� ������ ������ ������ ���������
	void setLogo(List *cur);				//��������� �������� ��� ����
	void Delete(int value);					//�������� ��������
	void deleteAll(List* cur);				//����������� ������� �������� ����
	void deleteAll();						//������� ������ ������������ �������� ����� ������
	void SetLevels(List* curPrev, List* cur);//����������� ������� ����������� �������
	void RefreshXY(List* curPrev, List* cur); //������������ ������ ������ �������������� ������
	void setBalance(List* cur, List* curPrev);//��������� �������
	void checkRotation(List* cur, List* curPrev);//�������� ������ �� ������������������
	void leftRotation(List* cur, List* curPrev);//����� ����� �������
	void rightRotation(List* cur, List* curPrev);//����� ������ �������
	void bigLeftRightRot(List* unstableCur);//������� ����� �������
	void bigRightLeftRot(List* unstableCur);//������� ������ �������
	void rankingXY(List* cur, int multiplier);//������� ��� ���������� ����� �� ������(�������)
	void getAllElements();					//����� ���� �������� ������
	void fillVec(List *cur);				//����������� �������,����������� ������ elements
	struct List* getEdgeRightNode();		//����� ��������� �������� ����-������� ����
	struct List* getEdgeLeftNode();			//����� ��������� �������� �����-������� ����
	POINT getNodeXY(List* cur);				//����� ��������� x � y ����
	List* getHead();						//����� ��������� ������
	struct List* findUnstableNode(List* underNode);	//������� ������ ������������� ����
	void setInfoBox(Rect* infoBox, List* cur);		//������� ��� ��������� ����� ��� �����

};