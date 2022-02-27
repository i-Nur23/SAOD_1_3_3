#include <set>
#include <locale>
#include <iostream>

using namespace std;
const int maxSize = 21;

struct ListItem
{
    int info;
    int next;
};

int CheckedInput(int begin, int end) // Ввод целочисленного значения с проверкой
{
    int choice;
    while (true)
    {
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Вводите данные корректно: ";
            continue;
        }
        cin.ignore(32767, '\n');
        if (choice < begin || choice > end)
        {
            cout << "Вводите данные корректно: ";
            continue;
        }
        break;
    }
    return choice;
}

int CheckedInput() // Ввод целочисленного значения с проверкой
{
    int choice;
    while (true)
    {
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Вводите данные корректно: ";
            continue;
        }
        cin.ignore(32767, '\n');
        break;
    }
    return choice;
}

void InitList(ListItem* StatList[maxSize]) // инициализация списка
{
    for (int i = 0; i < maxSize; i++)
    {
        StatList[i] = new ListItem;
        StatList[i]->info = 0; StatList[i]->next = -1;
    }
}

bool isEmpty(ListItem* StatList[maxSize]) // проверка списка на пустоту
{
    if (StatList[0]->next == -1)
    {
        return true;
    }
    return false;
}

bool isFull(ListItem* StatList[maxSize]) // проверка списка на заполненность
{
    for (int i = 0; i < maxSize; i++)
    {
        if (StatList[i]->next == -1)
        {
            return false;
        }
    }
    return true;
}

void PrintList(ListItem* StatList[maxSize]) // вывод списка 
{
    int current = StatList[0]->next;
    while (current != 0)
    {
        cout << StatList[current]->info << " ";
        current = StatList[current]->next;
    }
}

int Search(ListItem* StatList[maxSize], int infoToSearch) // поиск элемента по инфо-части
{
    int current = StatList[0]->next;
    if (isEmpty(StatList))
    {
        return -1;
    }
    while (current != 0)
    {
        if (StatList[current]->info == infoToSearch)
        {
            return current;
        }
        current = StatList[current]->next;
    }
    return -1;
}

void Delete(ListItem* StatList[maxSize], int indexToAdd) // удаление элемента
{
    int current = StatList[0]->next;
    int previous = 0;
    while (current != indexToAdd && current != 0)
    {
        previous = current;
        current = StatList[current]->next;
    }
    if (current == 0)
    {
        cout << "Данная ячейка пустая.";
    }
    else
    {
        StatList[previous]->next = StatList[current]->next;
        StatList[current]->next = -1; StatList[current]->info = 0;
    }
    
}

void Add(ListItem* StatList[maxSize], int infoToAdd) // добавление элемента 
{
    if (isEmpty(StatList))
    {
        StatList[0]->next = 1;
        StatList[1]->info = infoToAdd;
        StatList[1]->next = 0;
    }
    else
    {
        int current = StatList[0]->next;
        int previous = 0;
        while (current != 0)
        {
            if (StatList[current]->info > infoToAdd)
            {
                int index = 1;
                while (StatList[index]->next != -1)
                {
                    index ++;
                }
                StatList[index]->info = infoToAdd;
                StatList[index]->next = current;
                StatList[previous]->next = index;
                break;
            }
            previous = current;
            current = StatList[current]->next;
        }
        if (current == 0)
        {
            int index = 1;
            while (StatList[index]->next != -1)
            {
                index++;
            }
            StatList[index]->info = infoToAdd;
            StatList[index]->next = 0;
            StatList[previous]->next = index;
        }
    }
}

void DeleteAll(ListItem* StatList[maxSize]) // очищение памяти
{
    for (int i = 0; i < maxSize; i++)
    {
        delete StatList[i];
    }
}

void CallMenu(ListItem* StatList[maxSize]) // меню
{
    bool work = true;
    int choice;
    while (work)
    {
        cout << "Выбор действия:\n1 - Вывод списка\n2 - Поиск элемента с заданной информационной частью\n3 - Добавление элемента\n4 - Удаление заданного элемента\n5 - Завершить работу\n";
        cout << "Действие: "; choice = CheckedInput(1, 5);
        switch (choice)
        {
        case 1:
            if (isEmpty(StatList))
            {
                cout << "Список пустой.";
            }
            else
            {
                cout << "Список: "; PrintList(StatList);
            }
            cout << "\n\n";
            break;
        case 2:
            int elemsIndex;
            cout << "Введите информационную часть, индекс которой надо найти: "; elemsIndex = Search(StatList, CheckedInput());
            if (elemsIndex == -1)
            {
                cout << "Такого элемента в списке нет.";
            }
            else
            {
                cout << "Элемент " << elemsIndex << "-ый в списке.";
            }
            cout << "\n\n";
            break;
        case 3:
            if (isFull(StatList))
            {
                cout << "Список полон. Добавить элемент нельзя.\n\n";
                break;
            }
            cout << "Введите элемент, который хотели бы добавить: "; Add(StatList,CheckedInput());
            cout << "\n\n";
            break;
        case 4:
            if (isEmpty(StatList))
            {
                cout << "Список пустой. Удалять нечего\n\n";
                break;
            }
            cout << "Введите индекс удаляемого элемента (от 1 до 20): "; Delete(StatList, CheckedInput(1, 20));
            cout << "\n\n";
            break;
        case 5:
            work = false;
            DeleteAll(StatList);
            break;
        default:
            break;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "RUS");
    ListItem* StatList[maxSize];
    InitList(StatList);
    CallMenu(StatList);
}
