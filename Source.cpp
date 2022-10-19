#include <iostream>
#include <windows.h>
#include <iomanip>
#include <string>
using namespace std;
struct Data
{
	int Day = 0;
	int Month = 0;
	int Year = 0;
	int Hour = 0;
	int Minute = 0;
};
struct Doings
{
	string Name;
	string Description;
	Data data;
	int Priority = 0;
	void Add(Doings*& pArr, int& size)
	{
		size++;
		Doings* CopyArr = new Doings[size];
		for (int i = 0; i < size - 1; i++)
			CopyArr[i] = pArr[i];
		delete[] pArr;
		pArr = new Doings[size];
		pArr = CopyArr;
	}
	void Edit(Doings*& pArr, int size, int& num)
	{
		tm now;
		time_t timeObject = time(0);
		localtime_s(&now, &timeObject);
		if (size <= 1)
		{
			cout << "��� ���!\n";
			return;
		}
		cout << "-----------------------------------------------------------------\n";
		cout << "������� ����� ���� ������� ������ �������������(������� 0 ���� ������ ��������� � ����): ";
		cin >> num;
		if (!num)
			return;
		while (num < 1 || num > size - 1)
		{
			cout << "�� ����������� ����� ��������!\n" << "������� ��� ���: ";
			cin >> num;
		}
		for (int i = 0; i < size - 1; i++)
		{
			if (i == num - 1)
			{
				cout << "������� ����� ����\n";
				cout << "������� ��� ����: ";
				getline(cin >> ws, pArr[i].Name);
				cout << "������� ��������: ";
				getline(cin >> ws, pArr[i].Description);
				cout << "������� ����(����): ";
				cin >> pArr[i].data.Day;
				while (pArr[i].data.Day < 1 || pArr[i].data.Day > 31)
				{
					cout << "�� ����������� ����� ��������!\n" << "������� ��� ���: ";
					cin >> pArr[i].data.Day;
				}
				cout << "������� ����(�����): ";
				cin >> pArr[i].data.Month;
				while (pArr[i].data.Month < 1 || pArr[i].data.Month > 12)
				{
					cout << "�� ����������� ����� ��������!\n" << "������� ��� ���: ";
					cin >> pArr[i].data.Month;
				}
				cout << "������� ����(���): ";
				cin >> pArr[i].data.Year;
				while (pArr[i].data.Year < now.tm_year + 1900)
				{
					cout << "�� ����������� ����� ��������!\n" << "������� ��� ���: ";
					cin >> pArr[i].data.Year;
				}
				cout << "������� �����(���): ";
				cin >> pArr[i].data.Hour;
				while (pArr[i].data.Hour < 0 || pArr[i].data.Hour > 24)
				{
					cout << "�� ����������� ����� ��������!\n" << "������� ��� ���: ";
					cin >> pArr[i].data.Hour;
				}
				cout << "������� �����(������): ";
				cin >> pArr[i].data.Minute;
				while (pArr[i].data.Minute < 0 || pArr[i].data.Minute > 60)
				{
					cout << "�� ����������� ����� ��������!\n" << "������� ��� ���: ";
					cin >> pArr[i].data.Minute;
				}
				cout << "������� ���������(0 - 5): ";
				cin >> pArr[i].Priority;
				while (pArr[i].Priority < 0 || pArr[i].Priority > 5)
				{
					cout << "�� ����������� ����� ��������!\n" << "������� ��� ���: ";
					cin >> pArr[i].Priority;
				}
				break;
			}
		}
		cout << "-----------------------------------------------------------------\n";
		cout << "\t\t\t\t���������\n";
		cout << "---------------------------------------------------------------------------------------------------------------\n";
		cout << " - \t\t" << "���" << setw(20) << "����" << setw(32) << "��������" << setw(30) << "���������\n";
		for (int i = 0; i < size - 1; i++)
			AddForPrint(pArr, i);
		cout << "---------------------------------------------------------------------------------------------------------------\n\n";
	}
	void Print(Doings*& pArr, int size)
	{
		cout << "---------------------------------------------------------------------------------------------------------------\n";
		cout << " - \t\t" << "���" << setw(20) << "����" << setw(32) << "��������" << setw(30) << "���������\n";
		for (int i = 0; i < size - 1; i++)
			AddForPrint(pArr, i);
		cout << "---------------------------------------------------------------------------------------------------------------\n\n";
	}
	void ShowOn(Doings*& pArr, int size, int& num)
	{
		tm now;
		time_t timeObject = time(0);
		localtime_s(&now, &timeObject);
		if (size <= 1)
		{
			cout << "��� ���!\n";
			return;
		}
		int num2;
		cout << "-----------------------------------------------------------------\n";
		cout << "������� 1 ����� ������� ������ ��� �� ����, 2 - �� ������, 3 - �� �����(������� 0 ���� ������ ��������� � ����): ";
		cin >> num;
		if (!num)
			return;
		while (num < 1 || num > 3)
		{
			cout << "�� ����������� ����� ��������!\n" << "������� ��� ���: ";
			cin >> num;
		}
		cout << "������� 1 ����� ��������������� ������, 0 - �� �����: ";
		cin >> num2;
		while (num2 != 1 && num2 != 0)
		{
			cout << "�� ����������� ����� ��������!\n" << "������� ��� ���: ";
			cin >> num2;
		}
		Data temp;
		temp.Day = now.tm_mday;
		temp.Month = now.tm_mon + 1;
		temp.Year = now.tm_year + 1900;
		int b = temp.Day + 6;
		int c = temp.Month + 1;
		Doings* copy = new Doings[size];
		for (int i = 0; i < size - 1; i++)
			copy[i] = pArr[i];
		if (num2 == 1)
			Sort(copy, size);
		cout << "---------------------------------------------------------------------------------------------------------------\n";
		switch (num)
		{
		case 1:
		{
			cout << "����� ��� �� ���� ";
			if (num2 == 1)
				cout << "�� �����������\n";
			else
				cout << "��� ����������\n";
			cout << " - \t\t" << "���" << setw(20) << "����" << setw(32) << "��������" << setw(30) << "���������\n";
			for (int i = 0; i < size - 1; i++)
			{
				if (copy[i].data.Day == temp.Day && copy[i].data.Month == temp.Month && copy[i].data.Year == temp.Year)
				{
					cout << " " << i + 1 << setw(18);
					cout << copy[i].Name << setw(16);
					cout << copy[i].data.Day << "." << copy[i].data.Month << "." << copy[i].data.Year << " " << copy[i].data.Hour << ":" << copy[i].data.Minute << setw(26);
					cout << copy[i].Description << setw(18);
					cout << copy[i].Priority << endl;
				}
			}
			break;
		}
		case 2:
		{
			cout << "����� ��� �� ������ ";
			if (num2 == 1)
				cout << "�� �����������\n";
			else
				cout << "��� ����������\n";
			cout << " - \t\t" << "���" << setw(20) << "����" << setw(32) << "��������" << setw(30) << "���������\n";
			for (int i = 0; i < size - 1; i++)
			{
				if (copy[i].data.Day <= b && copy[i].data.Month == temp.Month && copy[i].data.Year == temp.Year)
				{
					cout << " " << i + 1 << setw(18);
					cout << copy[i].Name << setw(16);
					cout << copy[i].data.Day << "." << copy[i].data.Month << "." << copy[i].data.Year << " " << copy[i].data.Hour << ":" << copy[i].data.Minute << setw(26);
					cout << copy[i].Description << setw(18);
					cout << copy[i].Priority << endl;
				}
			}
			break;
		}
		case 3:
		{
			cout << "����� ��� �� ����� ";
			if (num2 == 1)
				cout << "�� �����������\n";
			else
				cout << "��� ����������\n";
			cout << " - \t\t" << "���" << setw(20) << "����" << setw(32) << "��������" << setw(30) << "���������\n";
			for (int i = 0; i < size - 1; i++)
			{
				if (copy[i].data.Day <= b && copy[i].data.Month <= c && copy[i].data.Year == temp.Year)
				{
					cout << " " << i + 1 << setw(18);
					cout << copy[i].Name << setw(16);
					cout << copy[i].data.Day << "." << copy[i].data.Month << "." << copy[i].data.Year << " " << copy[i].data.Hour << ":" << copy[i].data.Minute << setw(26);
					cout << copy[i].Description << setw(18);
					cout << copy[i].Priority << endl;
				}
			}
			break;
		}
		}
		cout << "---------------------------------------------------------------------------------------------------------------\n\n";
		delete[] copy;
	}
	void Search(Doings*& pArr, int size, int& num)
	{
		tm now;
		time_t timeObject = time(0);
		localtime_s(&now, &timeObject);
		if (size <= 1)
		{
			cout << "��� ���!\n";
			return;
		}
		cout << "-----------------------------------------------------------------\n";
		cout << "������� ��� �� ������ ����� ����(1 - �� ��������, 2 - �� ����������, 3 - �� ��������, 4 - �� ����, 0 ���� ������ ��������� � ����): ";
		cin >> num;
		if (!num)
			return;
		while (num < 1 || num > 4)
		{
			cout << "�� ����������� ����� ��������!\n" << "������� ��� ���: ";
			cin >> num;
		}
		switch (num)
		{
		case 1:
		{
			string name;
			cout << "������� ��� ����: ";
			getline(cin >> ws, name);
			cout << "---------------------------------------------------------------------------------------------------------------\n";
			cout << " - \t\t" << "���" << setw(20) << "����" << setw(32) << "��������" << setw(30) << "���������\n";
			for (int i = 0; i < size; i++)
			{
				if (pArr[i].Name == name)
					AddForPrint(pArr, i);
			}
			break;
		}
		case 2:
		{
			int priority = 0;
			cout << "������� ��������� ����: ";
			cin >> priority;
			while (priority < 0 || priority > 5)
			{
				cout << "�� ����������� ����� ��������!\n" << "������� ��� ���: ";
				cin >> priority;
			}
			cout << "---------------------------------------------------------------------------------------------------------------\n";
			cout << " - \t\t" << "���" << setw(20) << "����" << setw(32) << "��������" << setw(30) << "���������\n";
			for (int i = 0; i < size; i++)
			{
				if (pArr[i].Priority == priority)
					AddForPrint(pArr, i);
			}
			break;
		}
		case 3:
		{
			string text;
			cout << "������� �������� ����: ";
			getline(cin >> ws, text);
			cout << "---------------------------------------------------------------------------------------------------------------\n";
			cout << " - \t\t" << "���" << setw(20) << "����" << setw(32) << "��������" << setw(30) << "���������\n";
			for (int i = 0; i < size; i++)
			{
				if (pArr[i].Description == text)
					AddForPrint(pArr, i);
			}
			break;
		}
		case 4:
		{
			Data temp;
			temp.Day = now.tm_mday;
			temp.Month = now.tm_mon + 1;
			temp.Year = now.tm_year + 1900;
			int add;
			cout << "����� �� ������ �� �������(1 - ��, 0 - ���): ";
			cin >> add;
			while (add != 1 && add != 0)
			{
				cout << "�� ����������� ����� ��������!\n" << "������� ��� ���: ";
				cin >> add;
			}
			if (add)
			{
				cout << "������� �����(���): ";
				cin >> temp.Hour;
				while (temp.Hour < 0 || temp.Hour > 24)
				{
					cout << "�� ����������� ����� ��������!\n" << "������� ��� ���: ";
					cin >> temp.Hour;
				}
				cout << "������� �����(������): ";
				cin >> temp.Minute;
				while (temp.Minute < 0 || temp.Minute > 60)
				{
					cout << "�� ����������� ����� ��������!\n" << "������� ��� ���: ";
					cin >> temp.Minute;
				}
			}
			cout << "---------------------------------------------------------------------------------------------------------------\n";
			cout << " - \t\t" << "���" << setw(20) << "����" << setw(32) << "��������" << setw(30) << "���������\n";
			for (int i = 0; i < size; i++)
			{
				if (add)
				{
					if (pArr[i].data.Day == temp.Day && pArr[i].data.Month == temp.Month && pArr[i].data.Year == temp.Year && pArr[i].data.Hour == temp.Hour && pArr[i].data.Minute == temp.Minute)
						AddForPrint(pArr, i);
				}
				else
				{
					if (pArr[i].data.Day == temp.Day && pArr[i].data.Month == temp.Month && pArr[i].data.Year == temp.Year)
						AddForPrint(pArr, i);
				}
			}
			break;
		}
		cout << "---------------------------------------------------------------------------------------------------------------\n\n";
		}
	}
	void Remove(Doings*& pArr, int& size, int& num)
	{
		if (size <= 1)
		{
			cout << "��� ���!\n";
			return;
		}
		cout << "-----------------------------------------------------------------\n";
		cout << "������� ����� ���� ������� ������ �������(������� 0 ���� ������ ��������� � ����): ";
		cin >> num;
		if (!num)
			return;
		while (num < 1 || num > size - 1)
		{
			cout << "�� ����������� ����� ��������!\n" << "������� ��� ���: ";
			cin >> num;
		}
		if (size == 2)
		{
			delete[] pArr;
			size--;
			pArr = new Doings[size];
		}
		else
		{
			Doings* copy = nullptr;
			copy = new Doings[size - 1];
			for (int i = 0, j = 0; i < size - 1; i++)
			{
				if (i == num - 1)
					i++;
				copy[j++] = pArr[i];
			}
			size--;
			delete[] pArr;
			pArr = copy;
		}
		cout << "-----------------------------------------------------------------\n";
		cout << "\t\t\t\t���������\n";
		cout << "---------------------------------------------------------------------------------------------------------------\n";
		cout << " - \t\t" << "���" << setw(20) << "����" << setw(32) << "��������" << setw(30) << "���������\n";
		for (int i = 0; i < size - 1; i++)
			AddForPrint(pArr, i);
		cout << "---------------------------------------------------------------------------------------------------------------\n\n";
	}
	void Sort(Doings*& copy, int size)
	{
		int num;
		cout << "������������� �������(1 - �� ����������, 2 - �� ����): ";
		cin >> num;
		while (num != 1 && num != 2)
		{
			cout << "�� ����������� ����� ��������!\n" << "������� ��� ���: ";
			cin >> num;
		}
		int j = 0;
		string temp1, temp2;
		Data temp3;
		switch (num)
		{
		case 1:
		{
			while (j < size - 1)
			{
				for (int i = 1; ; i++)
				{
					if (i == size - 1)
					{
						j++;
						break;
					}
					if (copy[i - 1].Priority < copy[i].Priority)
					{
						AddForSort(copy, temp1, temp2, temp3, i);
						copy[i].Priority += copy[i - 1].Priority;
						copy[i - 1].Priority = copy[i].Priority - copy[i - 1].Priority;
						copy[i].Priority = copy[i].Priority - copy[i - 1].Priority;
					}
				}
			}
			j = 0;
			break;
		}
		case 2:
		{
			while (j < size - 1)
			{
				for (int i = 1; ; i++)
				{
					if (i == size - 1)
					{
						j++;
						break;
					}
					if (copy[i - 1].data.Year > copy[i].data.Year)
					{
						AddForSort(copy, temp1, temp2, temp3, i);
						copy[i].data.Year += copy[i - 1].data.Year;
						copy[i - 1].data.Year = copy[i].data.Year - copy[i - 1].data.Year;
						copy[i].data.Year = copy[i].data.Year - copy[i - 1].data.Year;
					}
				}
			}
			j = 0;
			while (j < size - 1)
			{
				for (int i = 1; ; i++)
				{
					if (i == size - 1)
					{
						j++;
						break;
					}
					if (copy[i - 1].data.Month > copy[i].data.Month)
					{
						AddForSort(copy, temp1, temp2, temp3, i);
						copy[i].data.Month += copy[i - 1].data.Month;
						copy[i - 1].data.Month = copy[i].data.Month - copy[i - 1].data.Month;
						copy[i].data.Month = copy[i].data.Month - copy[i - 1].data.Month;
					}
				}
			}
			j = 0;
			while (j < size - 1)
			{
				for (int i = 1; ; i++)
				{
					if (i == size - 1)
					{
						j++;
						break;
					}
					if (copy[i - 1].data.Day > copy[i].data.Day)
					{
						AddForSort(copy, temp1, temp2, temp3, i);
						copy[i].data.Day += copy[i - 1].data.Day;
						copy[i - 1].data.Day = copy[i].data.Day - copy[i - 1].data.Day;
						copy[i].data.Day = copy[i].data.Day - copy[i - 1].data.Day;
					}
				}
			}
			j = 0;
			while (j < size - 1)
			{
				for (int i = 1; ; i++)
				{
					if (i == size - 1)
					{
						j++;
						break;
					}
					if (copy[i - 1].data.Hour > copy[i].data.Hour)
					{
						AddForSort(copy, temp1, temp2, temp3, i);
						copy[i].data.Hour += copy[i - 1].data.Hour;
						copy[i - 1].data.Hour = copy[i].data.Hour - copy[i - 1].data.Hour;
						copy[i].data.Hour = copy[i].data.Hour - copy[i - 1].data.Hour;
					}
				}
			}
			j = 0;
			while (j < size - 1)
			{
				for (int i = 1; ; i++)
				{
					if (i == size - 1)
					{
						j++;
						break;
					}
					if (copy[i - 1].data.Minute > copy[i].data.Minute)
					{
						AddForSort(copy, temp1, temp2, temp3, i);
						copy[i].data.Minute += copy[i - 1].data.Minute;
						copy[i - 1].data.Minute = copy[i].data.Minute - copy[i - 1].data.Minute;
						copy[i].data.Minute = copy[i].data.Minute - copy[i - 1].data.Minute;
					}
				}
			}
			break;
		}
		}
		cout << endl;
	}
	void AddForSort(Doings* copy, string& temp1, string& temp2, Data& temp3, int i)
	{
		temp1 = copy[i - 1].Name;
		copy[i - 1].Name = copy[i].Name;
		copy[i].Name = temp1;
		temp2 = copy[i - 1].Description;
		copy[i - 1].Description = copy[i].Description;
		copy[i].Description = temp2;
		temp3 = copy[i - 1].data;
		copy[i - 1].data = copy[i].data;
		copy[i].data = temp3;
	}
	void AddForPrint(Doings*& pArr, int i)
	{
		cout << " " << i + 1 << setw(18);
		cout << pArr[i].Name << setw(16);
		cout << pArr[i].data.Day << "." << pArr[i].data.Month << "." << pArr[i].data.Year << " " << pArr[i].data.Hour << ":" << pArr[i].data.Minute << setw(24);
		cout << pArr[i].Description << setw(18);
		cout << pArr[i].Priority << endl;
	}
};
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	tm now;
	time_t timeObject = time(0);
	localtime_s(&now, &timeObject);
	int size = 1;
	Doings* pArr = new Doings[size];
	Doings a;
	while (true)
	{
		int choice = 0;
		cout << "-----------------------------------------------------------------\n";
		cout << "| " << "\t\t\t\t����" << "\t\t\t\t| " << endl;
		cout << "-----------------------------------------------------------------\n";
		cout << "| " << "\t\t " << "| " << "1 - ������ ����� ����;" << "\t| " << "\t\t| " << endl;
		cout << "| " << "\t\t" << " | " << "2 - ������� ����; " << " \t\t| " << "\t\t| " << endl;
		cout << "| " << "\t\t" << " | " << "3 - ������������� ����;" << "\t| " << "\t\t| " << endl;
		cout << "| " << "\t\t" << " | " << "4 - ����� ����;" << "\t\t| " << "\t\t| " << endl;
		cout << "| " << "\t\t" << " | " << "5 - ����������� ������ ���;" << "\t| " << "\t\t| " << endl;
		cout << "| " << "\t\t" << " | " << "6 - ������� �� ����� ����;" << "\t| " << "\t\t| " << endl;
		cout << "| " << "\t\t" << " | " << "0 - ����� �� ����������;" << "\t| " << "\t\t| " << endl;
		cout << "-----------------------------------------------------------------" << endl;
		cout << "�������� ����� ����: ";
		cin >> choice;
		int temp = 0, num = 0;
		switch (choice)
		{
		case 1:
		{
			do
			{
				cout << "\n�������� " << size << " ����\n";
				cout << "������� ��� ����: ";
				getline(cin >> ws, pArr[size - 1].Name);
				cout << "������� ��������: ";
				getline(cin >> ws, pArr[size - 1].Description);
				cout << "������� ����(����): ";
				cin >> pArr[size - 1].data.Day;
				while (pArr[size - 1].data.Day < 1 || pArr[size - 1].data.Day > 31)
				{
					cout << "�� ����������� ����� ��������!\n" << "������� ��� ���: ";
					cin >> pArr[size - 1].data.Day;
				}
				cout << "������� ����(�����): ";
				cin >> pArr[size - 1].data.Month;
				while (pArr[size - 1].data.Month < 1 || pArr[size - 1].data.Month > 12)
				{
					cout << "�� ����������� ����� ��������!\n" << "������� ��� ���: ";
					cin >> pArr[size - 1].data.Month;
				}
				cout << "������� ����(���): ";
				cin >> pArr[size - 1].data.Year;
				while (pArr[size - 1].data.Year < now.tm_year + 1900)
				{
					cout << "�� ����������� ����� ��������!\n" << "������� ��� ���: ";
					cin >> pArr[size - 1].data.Year;
				}
				cout << "������� �����(���): ";
				cin >> pArr[size - 1].data.Hour;
				while (pArr[size - 1].data.Hour < 0 || pArr[size - 1].data.Hour > 24)
				{
					cout << "�� ����������� ����� ��������!\n" << "������� ��� ���: ";
					cin >> pArr[size - 1].data.Hour;
				}
				cout << "������� �����(������): ";
				cin >> pArr[size - 1].data.Minute;
				while (pArr[size - 1].data.Minute < 0 || pArr[size - 1].data.Minute > 60)
				{
					cout << "�� ����������� ����� ��������!\n" << "������� ��� ���: ";
					cin >> pArr[size - 1].data.Minute;
				}
				cout << "������� ���������(0 - 5): ";
				cin >> pArr[size - 1].Priority;
				while (pArr[size - 1].Priority < 0 || pArr[size - 1].Priority > 5)
				{
					cout << "�� ����������� ����� ��������!\n" << "������� ��� ���: ";
					cin >> pArr[size - 1].Priority;
				}
				a.Add(pArr, size);
				cout << "������ ����������(1 - ��, 0 - ���): ";
				cin >> temp;
			} while (temp);
			break;
		}
		case 2:
		{
			do
			{
				a.Remove(pArr, size, num);
				if (size <= 1)
					break;
				if (!num)
					break;
				cout << "������ ����������(1 - ��, 0 - ���): ";
				cin >> temp;
			} while (temp);
			break;
		}
		case 3:
		{
			do
			{
				a.Edit(pArr, size, num);
				if (size <= 1)
					break;
				if (!num)
					break;
				cout << "������ ����������(1 - ��, 0 - ���): ";
				cin >> temp;
			} while (temp);
			break;
		}
		case 4:
		{
			do
			{
				a.Search(pArr, size, num);
				if (size <= 1)
					break;
				if (!num)
					break;
				cout << "������ ����������(1 - ��, 0 - ���): ";
				cin >> temp;
			} while (temp);
			break;
		}
		case 5:
		{
			do
			{
				a.ShowOn(pArr, size, num);
				if (size <= 1)
					break;
				if (!num)
					break;
				cout << "������ ����������(1 - ��, 0 - ���): ";
				cin >> temp;
			} while (temp);
			break;
		}
		case 6:
		{
			a.Print(pArr, size);
			break;
		}
		case 0:
		{
			cout << "����� �� ���������..." << endl;
			delete[] pArr;
			system("cls");
			return 0;
		}
		default:
		{
			cout << "�� ����� �������� �����. ����������, ���������� ��� ���.\n";
			break;
		}
		}
	}
}