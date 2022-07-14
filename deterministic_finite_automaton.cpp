//--------------------------------------------------------------------
// Институт компьютерных технологий и информационной безопасности ЮФУ
// Кафедра МОП ЭВМ
// Программирование и основы теории алгоритмов
// Проектирование и реализация конечного атомата
// 27.04.2022
//--------------------------------------------------------------------
#include <iostream>
#include <string>
using namespace std;

//--------------------------------------------------------------------
// функция проверки введённого троичного числа на корректность
// на вход подаётся строка, введённая пользователем
// возвращает false, если в строке присутствуют недопустимые символы
// возвращает true, если строка корректна
//--------------------------------------------------------------------
bool correct(string str)
{
    bool t = true;

    for (int i = 0; i < str.length(); i++)
    {
        if (str.at(i) != '0')
        {
            if (str.at(i) != '1')
            {
                if (str.at(i) != '2')
                {
                    t = false;
                }
            }
        }
    }

    return t;
}

//--------------------------------------------------------------------
// структура хранения таблицы переходов
//--------------------------------------------------------------------
struct Table
{
    char table[7][5];
};

//--------------------------------------------------------------------
// функция инициализации таблицы переходов
// возвращает построенную таблицу
//--------------------------------------------------------------------
struct Table init()
{
    struct Table thing =
    {
        {
            {' ', '0', '1', '2', 'd'},
            {'S', '0', '1', '2', 'N'},
            {'0', '0', '1', '2', 'Y'},
            {'1', '3', '4', '0', 'N'},
            {'2', '1', '2', '3', 'N'},
            {'3', '4', '0', '1', 'N'},
            {'4', '2', '3', '4', 'N'},
        }
    };

    return thing;
}

//--------------------------------------------------------------------
// функция посимвольной обработки из входной строки
// на вход подаётся строка, позиция цифры в троичном числе, текущее состояние
// возвращает новое состояние после обработки текущего символа
//--------------------------------------------------------------------
char analyze(string str, int pos, char state)
{
    struct Table thing = init();

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (thing.table[i][0] == state && thing.table[0][j] == str.at(pos))
            {
                state = thing.table[i][j];
                return state;
            }
        }
    }
}

int main()
{
    string str;

    setlocale(0, "rus");

    struct Table thing = init();

    int start = 1;

    while (true)
    {
        if (start == 1)
        {
            cout << "Введите входное слово: " << endl;
            start++;
        }
        else
        {
            cout << "Введите входное слово, или 'exit' для выхода из программы: " << endl;
        }

        cin >> str;

        if (str == "exit")
        {
            return 0;
        }

        else if (correct(str))
        {
            char state = 'S';

            int len = str.length();
            int pos = 0;

            while (pos < len)
            {
                cout << str.at(pos) << ' ' << state << " -> ";

                state = analyze(str, pos, state);

                cout << state << endl;

                pos++;
            }
            if (state == '0')
            {
                cout << endl << "Yes" << endl;
            }
            else
            {
               cout << endl << "No" << endl;
            }
        }

        else
        {
            cout << endl << "Введённое слово некорректно!" << endl;
        }
    }

    return 0;
}