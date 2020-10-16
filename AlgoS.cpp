#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <cstring>
#include <iomanip>

using namespace std;

//Класс динамического массива(Больше список, старался повторить ArrayList из Java)
template <class T> 
class ArrayList
{
public:
    const int step = 10; //На сколько вырастает массив при заполнении
    int size = 0;
    T* point = nullptr;
    void growup();//Увеличить максимальный обьём списка
    void add(T);//Добавить элемент
    void del(int N);//Удалить элемент под номером N;
    void change(T, int N);//Изменить элемент
    T get(int N);//Получить элемент
    void erase();//Очистить массив
    int getS()
    {
        return size;
    }
};

//Конструкторы для ArrayList
template <typename T>
void ArrayList<T>::growup()
{
    T* cloud = new T[size + step];
    for (int i = 0; i < size; i++)
    {
        cloud[i] = point[i];
    }
    delete[] point;
    point = cloud;
}

template <typename T>
void ArrayList<T>::add(T Tip)
{
    if (size % step == 0)
    {
        growup();
    }
    point[size] = Tip;
    size++;
}

template <typename T>
void ArrayList<T>::del(int N)
{
    if (N < size)
    {
        size--;
        for (int i = N - 1; i < size; i++)
        {
            point[i] = point[i + 1];
        }
    }
    if (N == size)
    {
        size--;
        point[N-1] = 0;
    }
}

template <typename T>
void ArrayList<T>::change(T, int N)
{
    point[N - 1] = T;
}

template <typename T>
T ArrayList<T>::get(int N)
{
    if (N <= size)
    {
        return point[N - 1];
    }
}

template <typename T>
void ArrayList<T>::erase()
{
    delete[] point;
    // Присваиваем значение nullptr для m_data, чтобы на выходе не получить висячий указатель!
    point = nullptr;
    size = 0;
}

// Класс СТЭКа
template <class T>
class LIFO : public ArrayList<T> //Стэк, который наследует функции и переменный ArrayList
{
public:
    T show();//Посмотреть последний элемент
    T take();//Взять последний элемент
};

//Конструкторы для LIFO
template <typename T>
T LIFO<T>::take()
{
    T result = ArrayList<T>::get(ArrayList<T>::size);
    ArrayList<T>::del(ArrayList<T>::size);
    return result;
}

template <typename T>
T LIFO<T>::show()
{
    return ArrayList<T>::get(ArrayList<T>::size);
}

//Класс члена связного списка
template <class T> 
class LinkedElement
{
public:
    T meaning = 0; 
    LinkedElement* link = nullptr;
    void setM(T);
};

//Конструкторы для LinkedElement
template <typename T>
void LinkedElement<T>::setM(T Tip)
{
    meaning = Tip;
}

//Класс связного списка
template <class T>
class LinkedList
{
    LinkedElement<T>* FirstPtr = nullptr;
    int size = 0;
public:
    void add(T); //Добавить элемент
    void dellast(); //Удалить последний элемент
    T get(int N); //Получить элемент с номером N
    void erase();
    int getS()
    {
        return size;
    }
};

//Конструкторы для LinkedList
template <typename T>
void LinkedList<T>::add(T Tip)
{
    LinkedElement<T>* Check;
    switch (size)
    {
    case 0:
        FirstPtr = new LinkedElement<T>;
        (*FirstPtr).setM(Tip);
        size++;
        break;
    case 1:
        (*FirstPtr).link = new LinkedElement<T>;
        (*((*FirstPtr).link)).setM(Tip);
        size++;
        break;
    default:
        Check = FirstPtr->link;
        for (int i = 1; i < size-1; i++)
        {
            if (Check)
                Check = Check->link;
            else
                break;
        }
        (*Check).link = new LinkedElement<T>; // Создание нового элемента
        (*(Check->link)).setM(Tip); // Присваивание новому элементу значение
        size++;
    }
}

template <typename T>
void LinkedList<T>::dellast()
{
    LinkedElement<T>* Check = FirstPtr;//Элемент который мы рассматриваем на данной итерации
    switch (size)
    {
        case 0:
            break;
        case 1:
            (*FirstPtr).meaning = 0;
            size--;
            break;
        default:
            int i;
            for (i = 1; i < size; i++)
            {
                Check = (*Check).link;
            }
            delete (*Check).link;
            size--;
    }
}

template <typename T>
T LinkedList<T>::get(int N)
{
    LinkedElement<T>* Check = FirstPtr;
    for (int i = 1; i < N; i++)
    {
        if (Check)
            Check = Check->link;
        else
            break;
    }
    return Check->meaning;
}

template <typename T>
void LinkedList<T>::erase()
{
    while (FirstPtr)
    {
        dellast();
    }
}

bool CheckALPH(char c)//Проверка является ли символ буквой латинского алфавита нижнего регистра
{
    if (c > 96 && c < 123) // Латинские буквы нижнего регистра
        return true;
    else
        return false;
}
bool CheckPM(char c)//Проверка является ли символ + или -
{
    if (c == '+' || c == '-') // Латинские буквы нижнего регистра
        return true;
    else
        return false;
}
bool CheckXY(char c)//Проверка является ли символ * или /
{
    if (c == '*' || c == '/') // Латинские буквы нижнего регистра
        return true;
    else
        return false;
}
bool CheckBE(char c)//Проверка является ли символ ( или )
{
    if (c == '(' || c == ')') // Латинские буквы нижнего регистра
        return true;
    else
        return false;
}
int getPriority(char c)
{
    if (c == '(' || c == ')') // Латинские буквы нижнего регистра
        return 1;
    if (c == '+' || c == '-') // Латинские буквы нижнего регистра
        return 2;
    if (c == '*' || c == '/') // Латинские буквы нижнего регистра
        return 3;
}

int main()
{
 //Проверка ArrayList

    //int a;
    //float b = 1;
    //ArrayList<float> One;
    //while (b != 0)
    //{
    //    cin >> b;
    //    One.add(b);
    //}
    //for (int i = 1; i < One.getS(); i++)
    //    cout << endl << i << ')' << ' ' << One.get(i);
    //cout << endl << One.get(10);
//Проверка LinkedList
 /* 
    int a;
    float b = 1;
    LinkedList<float> One;
    while (b != 0)
    {
        cin >> b;
        One.add(b);
    }
    for (int i = 1; i < One.getS(); i++)
        cout << endl << i << ')' << ' ' << One.get(i);
    One.dellast();
    cout << endl;
    for (int i = 1; i < One.getS(); i++)
        cout << endl << i << ')' << ' ' << One.get(i);
*/
//Реализация перевода на польский язык)
    ArrayList<char>California;//Сюда будет попадать готовый продукт
    LIFO<char>Texas;// А это отстойник для операторов
    bool end = false;
    char c;
    int count = 0;
    do
    {
        c = _getche();
        if (CheckALPH(c)) // Латинские буквы нижнего регистра
        {
            California.add(c);
        }
        if (!CheckALPH(c) && !(c == ';') && !(c == ')'))
        {
            while (Texas.getS() > 0 && (getPriority(c) <= getPriority(Texas.show())))
            {
                California.add(Texas.take());
            }
            Texas.add(c);
        }
        if (c == ')')
        {
            while (Texas.show() != '(')
            {
                California.add(Texas.take());
            }
            Texas.take();
        }
        if (c == ';' || c =='\n')
        {
            while (Texas.getS() > 0)
                California.add(Texas.take());
            end = true;
        }
    } while (!end);
    cout << endl;
    setlocale(LC_CTYPE, "");
    cout << "Символ ';' завершает ввод примера, enter не работает, защищённого ввода нет ,к сожалению, поэтому с этой программой нужно обращаться нежно...\n";
    setlocale(LC_CTYPE, "С");
    for (int i = 1; i <= California.getS(); i++)
        cout <<California.get(i);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
