#pragma once


class HashTable
{
private:
	vector<unsigned long int> mas;
	//vector<unsigned int>::iterator i;
	int size;
public:
	HashTable(int size);
	void pushModT(int number);
	void pushAverageType(int number);
	void pushSum(int number);
	
};

HashTable::HashTable(int size)
{
		ifstream in("input.txt", ios::in);
		for (int i = 0; i<size; i++) {
			int val;
			in >> val;
			mas.push_back(val);
		}
		in.close();
		this->size = size;
}

void HashTable::pushModT(int number)
{
	vector<int> adress;
	int count = 0;
	int j;
	for (int i = 0; i < number; i++)
	{
		j = mas[i] % 1009;
		adress.push_back(j);
	}
	sort(adress.begin(), adress.end());
	for (int i = 0; i < adress.size() - 1; i++)
	{
		if (adress[i] == adress[i + 1]) count++;
	}
	cout << "\nКоллизия для деления по модулю t (" << number << "): " << count;
}

void HashTable::pushAverageType(int number)
{
	vector<unsigned long int> adress;
	int count = 0;
	for (int i = 0; i < number; i++)
	{
		adress.push_back(((mas[i] * mas[i]) % 1000000)/1000);
	}
	sort(adress.begin(), adress.end());
	for (int i = 0; i < adress.size() - 1; i++)
	{
		if (adress[i] == adress[i + 1]) count++;
	}
	cout << "\nКоллизия для средняя часть квадрата (" << number << "): " << count;
}

void HashTable::pushSum(int number)
{
	vector<unsigned int> adress;
	int count = 0;
	for (int i = 0; i < number; i++)
	{
		int j = mas[i] % 1000 + mas[i] / 1000;
		if (j >= 1000) 
		{ j = j % 1000; }
		adress.push_back( j );
	}
	sort(adress.begin(), adress.end());
	for (int i = 0; i < adress.size() - 1; i++)
	{
		if (adress[i] == adress[i + 1]) count++;
	}
	cout << "\nКоллизия для метода свертки (" << number << "): " << count;
}