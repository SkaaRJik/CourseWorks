#pragma once




class Stack {
	struct List
	{
		int value; //информационный элемент
		struct List *next; //указатель на следующий элемент
	};
	struct List *head;//Голова стека
	int top;
	int whole;
public:
	class NullException {};
	Stack() {
		head = NULL; //Инициализация стека пустым адресом
		top = 0;
		whole = 0;
	}
	void Add(int value); //Добавление элемента в стек
	void Show();
	int Extract();
};

void Stack::Add(int value) {
	struct List *cur = new List; //Выделение памяти под новый элемент
	cur->value = value; //Вносим элемент в поле valueфс
	cur->next = head; //Указываем, адрес следующего элемента - голова
	head = cur; //Голове присваиваем адрес текущего элемента
	if (whole - top == 0) whole++;
	top++;
}

void Stack::Show() {
	if (head == NULL) {
		printf("\n|        |");
		printf("\n| Пустой |");
		printf("\n|        |");
		printf("\n==========");
	}
	else
	{
		for (int i = 0; i < whole - top; i++) {
			printf("\n|        |");
			printf("\n|        |");
			printf("\n|        |");
			printf("\n==========");
		}
		struct List *cur = head;
		while (cur != NULL)
		{
			printf("\n|        |");
			printf("\n|%8d|",cur->value);
			printf("\n|        |");
			printf("\n==========");
			cur = cur->next;
		}
	}
}

int Stack::Extract() {
	int value;
	if (head == NULL) {
		throw NullException();
	}
	else{
		struct List *cur = head;
			cur = cur->next;
			value = head->value;
			delete head;
			head = cur;
			top--;
			return value;
	}
}