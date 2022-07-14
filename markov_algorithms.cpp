//--------------------------------------------------------------------
// Институт компьютерных технологий и информационной безопасности ЮФУ
// Кафедра МОП ЭВМ
// Программирование и основы теории алгоритмов
// Проектирование и реализация Алгоритма Маркова
// 06.06.2022
//--------------------------------------------------------------------
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//--------------------------------------------------------------------
// функция проверки введённой строки на корректность
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
                if (str.at(i) != '*')
                {
                    t = false;
                }
            }
        }
        
        if (str.find('*') == std::string::npos)
        {
            t = false;
        }
    }

    return t;

}

//--------------------------------------------------------------------
// функция реализация шага работы алгоритма Маркова
// на вход получает строку и структуру команд
// осуществляет проход циклом по структуре команд, пока не находит строку для замены из списка подстановок,
// после чего заменяет циклом подстроку
// выводит строку до и после замены подстроки а также номер подстановки
// возвращает 0 в случае заключительного состояния
//--------------------------------------------------------------------
int analyze(string& str, vector<pair<string, string>> commands)
{
    bool find_undstr = 0;
    int current = 0;

    for (int i = 0; i < 22; i++)
    {
        if (str.find(commands.at(i).first) != std::string::npos)
        {
            find_undstr = true;
            current = i;
            break;
        }
    }

    if (str.find('*') == std::string::npos && str.find('z') == std::string::npos && str.find('*') == std::string::npos &&
        str.find('a') == std::string::npos && str.find('b') == std::string::npos && str.find('f') == std::string::npos &&
        str.find('#') == std::string::npos && str.find('?') == std::string::npos)
    {
        return 0;
    }

    if (find_undstr)
    {
        size_t pos = 0, cnt = 0;

        cout << '(' << current + 1 << ')' << ' ' << str << " -> ";

        while ((pos = str.find(commands.at(current).first, pos)) != string::npos)
        {
            str.replace(pos, commands.at(current).first.size(), commands.at(current).second);
            pos += commands.at(current).second.size();
            cnt++;
        }

        cout << str << endl;
    }

    return 1;
}

int main()
{
    setlocale(0, "rus");

    string str;

    //--------------------------------------------------------------------
    // структура хранения подстановок алгоритма Маркова - вектор с парой значений
    // первое значение - подстрока, которую нужно заменить
    // второе значение - строка на которую нужно заменить подстроку в строке str
    //--------------------------------------------------------------------
    vector<pair<string, string>> commands(100);

    //--------------------------------------------------------------------
    // список команд
    //--------------------------------------------------------------------
    commands.at(0) = make_pair("z1", "1z");
    commands.at(1) = make_pair("z0", "0z");
    commands.at(2) = make_pair("1a#", "#1");
    commands.at(3) = make_pair("0a#", "#0");
    commands.at(4) = make_pair("0b#", "#1");
    commands.at(5) = make_pair("1b#", "#1");
    commands.at(6) = make_pair("b0", "0b");
    commands.at(7) = make_pair("b1", "1b");
    commands.at(8) = make_pair("a0", "0a");
    commands.at(9) = make_pair("a1", "1a");
    commands.at(10) = make_pair("*", "?z");
    commands.at(11) = make_pair("1z", "1#f");
    commands.at(12) = make_pair("0z", "0#f");
    commands.at(13) = make_pair("1?", "?a");
    commands.at(14) = make_pair("0?", "?b");
    commands.at(15) = make_pair("?#", "");
    commands.at(16) = make_pair("f", "");
    commands.at(17) = make_pair("?a", "?");
    commands.at(18) = make_pair("?b", "?");
    commands.at(19) = make_pair("?1", "?");
    commands.at(20) = make_pair("?0", "?");

    while (true)
    {
        cout << "Введите входное слово или 'exit' для выхода из программы" << endl;

        cin >> str;

        if (str == "exit")
        {
            return 0;
        }

        if (!correct(str))
        {
            cout << "Введённое слово некорректно" << endl;
        }

        else
        {
            while (analyze(str, commands));

            cout << "Результат: " << str << endl;
        }
    }

    return 0;
}
