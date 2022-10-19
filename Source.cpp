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
			cout << "Нет дел!\n";
			return;
		}
		cout << "-----------------------------------------------------------------\n";
		cout << "Введите номер дела которое хотите редактировать(введите 0 если хотите вернуться в меню): ";
		cin >> num;
		if (!num)
			return;
		while (num < 1 || num > size - 1)
		{
			cout << "Вы неправильно ввели значение!\n" << "Введите еще раз: ";
			cin >> num;
		}
		for (int i = 0; i < size - 1; i++)
		{
			if (i == num - 1)
			{
				cout << "Введите новое дело\n";
				cout << "Введите имя дела: ";
				getline(cin >> ws, pArr[i].Name);
				cout << "Введите описание: ";
				getline(cin >> ws, pArr[i].Description);
				cout << "Введите дату(день): ";
				cin >> pArr[i].data.Day;
				while (pArr[i].data.Day < 1 || pArr[i].data.Day > 31)
				{
					cout << "Вы неправильно ввели значение!\n" << "Введите еще раз: ";
					cin >> pArr[i].data.Day;
				}
				cout << "Введите дату(месяц): ";
				cin >> pArr[i].data.Month;
				while (pArr[i].data.Month < 1 || pArr[i].data.Month > 12)
				{
					cout << "Вы неправильно ввели значение!\n" << "Введите еще раз: ";
					cin >> pArr[i].data.Month;
				}
				cout << "Введите дату(год): ";
				cin >> pArr[i].data.Year;
				while (pArr[i].data.Year < now.tm_year + 1900)
				{
					cout << "Вы неправильно ввели значение!\n" << "Введите еще раз: ";
					cin >> pArr[i].data.Year;
				}
				cout << "Введите время(час): ";
				cin >> pArr[i].data.Hour;
				while (pArr[i].data.Hour < 0 || pArr[i].data.Hour > 24)
				{
					cout << "Вы неправильно ввели значение!\n" << "Введите еще раз: ";
					cin >> pArr[i].data.Hour;
				}
				cout << "Введите время(минуты): ";
				cin >> pArr[i].data.Minute;
				while (pArr[i].data.Minute < 0 || pArr[i].data.Minute > 60)
				{
					cout << "Вы неправильно ввели значение!\n" << "Введите еще раз: ";
					cin >> pArr[i].data.Minute;
				}
				cout << "Введите приоритет(0 - 5): ";
				cin >> pArr[i].Priority;
				while (pArr[i].Priority < 0 || pArr[i].Priority > 5)
				{
					cout << "Вы неправильно ввели значение!\n" << "Введите еще раз: ";
					cin >> pArr[i].Priority;
				}
				break;
			}
		}
		cout << "-----------------------------------------------------------------\n";
		cout << "\t\t\t\tРезультат\n";
		cout << "---------------------------------------------------------------------------------------------------------------\n";
		cout << " - \t\t" << "Имя" << setw(20) << "Дата" << setw(32) << "Описание" << setw(30) << "Приоритет\n";
		for (int i = 0; i < size - 1; i++)
			AddForPrint(pArr, i);
		cout << "---------------------------------------------------------------------------------------------------------------\n\n";
	}
	void Print(Doings*& pArr, int size)
	{
		cout << "---------------------------------------------------------------------------------------------------------------\n";
		cout << " - \t\t" << "Имя" << setw(20) << "Дата" << setw(32) << "Описание" << setw(30) << "Приоритет\n";
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
			cout << "Нет дел!\n";
			return;
		}
		int num2;
		cout << "-----------------------------------------------------------------\n";
		cout << "Введите 1 чтобы вывести список дел на день, 2 - на неделю, 3 - на месяц(введите 0 если хотите вернуться в меню): ";
		cin >> num;
		if (!num)
			return;
		while (num < 1 || num > 3)
		{
			cout << "Вы неправильно ввели значение!\n" << "Введите еще раз: ";
			cin >> num;
		}
		cout << "Введите 1 чтобы отсортирировать список, 0 - не нужно: ";
		cin >> num2;
		while (num2 != 1 && num2 != 0)
		{
			cout << "Вы неправильно ввели значение!\n" << "Введите еще раз: ";
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
			cout << "Вывод дел на день ";
			if (num2 == 1)
				cout << "из сортировкой\n";
			else
				cout << "без сортировки\n";
			cout << " - \t\t" << "Имя" << setw(20) << "Дата" << setw(32) << "Описание" << setw(30) << "Приоритет\n";
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
			cout << "Вывод дел на неделю ";
			if (num2 == 1)
				cout << "из сортировкой\n";
			else
				cout << "без сортировки\n";
			cout << " - \t\t" << "Имя" << setw(20) << "Дата" << setw(32) << "Описание" << setw(30) << "Приоритет\n";
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
			cout << "Вывод дел на месяц ";
			if (num2 == 1)
				cout << "из сортировкой\n";
			else
				cout << "без сортировки\n";
			cout << " - \t\t" << "Имя" << setw(20) << "Дата" << setw(32) << "Описание" << setw(30) << "Приоритет\n";
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
			cout << "Нет дел!\n";
			return;
		}
		cout << "-----------------------------------------------------------------\n";
		cout << "Введите как вы хотите найти дело(1 - по названию, 2 - по приоритету, 3 - по описанию, 4 - по дате, 0 если хотите вернуться в меню): ";
		cin >> num;
		if (!num)
			return;
		while (num < 1 || num > 4)
		{
			cout << "Вы неправильно ввели значение!\n" << "Введите еще раз: ";
			cin >> num;
		}
		switch (num)
		{
		case 1:
		{
			string name;
			cout << "Введите имя дела: ";
			getline(cin >> ws, name);
			cout << "---------------------------------------------------------------------------------------------------------------\n";
			cout << " - \t\t" << "Имя" << setw(20) << "Дата" << setw(32) << "Описание" << setw(30) << "Приоритет\n";
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
			cout << "Введите приоритет дела: ";
			cin >> priority;
			while (priority < 0 || priority > 5)
			{
				cout << "Вы неправильно ввели значение!\n" << "Введите еще раз: ";
				cin >> priority;
			}
			cout << "---------------------------------------------------------------------------------------------------------------\n";
			cout << " - \t\t" << "Имя" << setw(20) << "Дата" << setw(32) << "Описание" << setw(30) << "Приоритет\n";
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
			cout << "Введите описание дела: ";
			getline(cin >> ws, text);
			cout << "---------------------------------------------------------------------------------------------------------------\n";
			cout << " - \t\t" << "Имя" << setw(20) << "Дата" << setw(32) << "Описание" << setw(30) << "Приоритет\n";
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
			cout << "Нужно ли искать по времени(1 - да, 0 - нет): ";
			cin >> add;
			while (add != 1 && add != 0)
			{
				cout << "Вы неправильно ввели значение!\n" << "Введите еще раз: ";
				cin >> add;
			}
			if (add)
			{
				cout << "Введите время(час): ";
				cin >> temp.Hour;
				while (temp.Hour < 0 || temp.Hour > 24)
				{
					cout << "Вы неправильно ввели значение!\n" << "Введите еще раз: ";
					cin >> temp.Hour;
				}
				cout << "Введите время(минуты): ";
				cin >> temp.Minute;
				while (temp.Minute < 0 || temp.Minute > 60)
				{
					cout << "Вы неправильно ввели значение!\n" << "Введите еще раз: ";
					cin >> temp.Minute;
				}
			}
			cout << "---------------------------------------------------------------------------------------------------------------\n";
			cout << " - \t\t" << "Имя" << setw(20) << "Дата" << setw(32) << "Описание" << setw(30) << "Приоритет\n";
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
			cout << "Нет дел!\n";
			return;
		}
		cout << "-----------------------------------------------------------------\n";
		cout << "Введите номер дела который хотите удалить(введите 0 если хотите вернуться в меню): ";
		cin >> num;
		if (!num)
			return;
		while (num < 1 || num > size - 1)
		{
			cout << "Вы неправильно ввели значение!\n" << "Введите еще раз: ";
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
		cout << "\t\t\t\tРезультат\n";
		cout << "---------------------------------------------------------------------------------------------------------------\n";
		cout << " - \t\t" << "Имя" << setw(20) << "Дата" << setw(32) << "Описание" << setw(30) << "Приоритет\n";
		for (int i = 0; i < size - 1; i++)
			AddForPrint(pArr, i);
		cout << "---------------------------------------------------------------------------------------------------------------\n\n";
	}
	void Sort(Doings*& copy, int size)
	{
		int num;
		cout << "Отсортировать задания(1 - по приоритету, 2 - по дате): ";
		cin >> num;
		while (num != 1 && num != 2)
		{
			cout << "Вы неправильно ввели значение!\n" << "Введите еще раз: ";
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
		cout << "| " << "\t\t\t\tМЕНЮ" << "\t\t\t\t| " << endl;
		cout << "-----------------------------------------------------------------\n";
		cout << "| " << "\t\t " << "| " << "1 - Ввести новое дело;" << "\t| " << "\t\t| " << endl;
		cout << "| " << "\t\t" << " | " << "2 - Удалить дело; " << " \t\t| " << "\t\t| " << endl;
		cout << "| " << "\t\t" << " | " << "3 - Редактировать дело;" << "\t| " << "\t\t| " << endl;
		cout << "| " << "\t\t" << " | " << "4 - Поиск дела;" << "\t\t| " << "\t\t| " << endl;
		cout << "| " << "\t\t" << " | " << "5 - Отображения списка дел;" << "\t| " << "\t\t| " << endl;
		cout << "| " << "\t\t" << " | " << "6 - Вывести на экран дела;" << "\t| " << "\t\t| " << endl;
		cout << "| " << "\t\t" << " | " << "0 - Выйти из приложения;" << "\t| " << "\t\t| " << endl;
		cout << "-----------------------------------------------------------------" << endl;
		cout << "Выберите пункт меню: ";
		cin >> choice;
		int temp = 0, num = 0;
		switch (choice)
		{
		case 1:
		{
			do
			{
				cout << "\nВведение " << size << " дела\n";
				cout << "Введите имя дела: ";
				getline(cin >> ws, pArr[size - 1].Name);
				cout << "Введите описание: ";
				getline(cin >> ws, pArr[size - 1].Description);
				cout << "Введите дату(день): ";
				cin >> pArr[size - 1].data.Day;
				while (pArr[size - 1].data.Day < 1 || pArr[size - 1].data.Day > 31)
				{
					cout << "Вы неправильно ввели значение!\n" << "Введите еще раз: ";
					cin >> pArr[size - 1].data.Day;
				}
				cout << "Введите дату(месяц): ";
				cin >> pArr[size - 1].data.Month;
				while (pArr[size - 1].data.Month < 1 || pArr[size - 1].data.Month > 12)
				{
					cout << "Вы неправильно ввели значение!\n" << "Введите еще раз: ";
					cin >> pArr[size - 1].data.Month;
				}
				cout << "Введите дату(год): ";
				cin >> pArr[size - 1].data.Year;
				while (pArr[size - 1].data.Year < now.tm_year + 1900)
				{
					cout << "Вы неправильно ввели значение!\n" << "Введите еще раз: ";
					cin >> pArr[size - 1].data.Year;
				}
				cout << "Введите время(час): ";
				cin >> pArr[size - 1].data.Hour;
				while (pArr[size - 1].data.Hour < 0 || pArr[size - 1].data.Hour > 24)
				{
					cout << "Вы неправильно ввели значение!\n" << "Введите еще раз: ";
					cin >> pArr[size - 1].data.Hour;
				}
				cout << "Введите время(минуты): ";
				cin >> pArr[size - 1].data.Minute;
				while (pArr[size - 1].data.Minute < 0 || pArr[size - 1].data.Minute > 60)
				{
					cout << "Вы неправильно ввели значение!\n" << "Введите еще раз: ";
					cin >> pArr[size - 1].data.Minute;
				}
				cout << "Введите приоритет(0 - 5): ";
				cin >> pArr[size - 1].Priority;
				while (pArr[size - 1].Priority < 0 || pArr[size - 1].Priority > 5)
				{
					cout << "Вы неправильно ввели значение!\n" << "Введите еще раз: ";
					cin >> pArr[size - 1].Priority;
				}
				a.Add(pArr, size);
				cout << "Хотите продолжить(1 - да, 0 - нет): ";
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
				cout << "Хотите продолжить(1 - да, 0 - нет): ";
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
				cout << "Хотите продолжить(1 - да, 0 - нет): ";
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
				cout << "Хотите продолжить(1 - да, 0 - нет): ";
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
				cout << "Хотите продолжить(1 - да, 0 - нет): ";
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
			cout << "Выход из программы..." << endl;
			delete[] pArr;
			system("cls");
			return 0;
		}
		default:
		{
			cout << "Вы ввели неверный номер. Пожалуйста, попробуйте еще раз.\n";
			break;
		}
		}
	}
}