#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Cafe; // предварительное объявление класса

class Meal                           // класс Заказ
{
    private:
        string meal_name;            // название блюда
        string meal_price, meal_weight;  // цена и вес блюда
        
        
        friend Cafe;
        friend Order;
    public:
        Meal()              // конструктор класса, по умолчанию задаёт поля
        {
            meal_name = "NULL";
            meal_price = "NULL";
            meal_weight = "NULL";
        }


        void createMeal()   // метод создания блюда, он вызывается в случае создания блюда официантом
        {
            system("cls");
            cout << "Внесите название блюда: "; getline(cin, meal_name, '\n');
            cout << "Внесите цену блюда: ";     getline(cin, meal_price, '\n');
            cout << "Внесите вес блюда: ";      getline(cin, meal_weight, '\n');
        }

        void createMeal(ifstream* f)     // перегруженный метод создания блюда при запуске программы
        {
            getline(*f, meal_name, '\n');
            getline(*f, meal_price, '\n');
            getline(*f, meal_weight, '\n');
        }

        void getMealList(int const* number) // метод вывода информации об имеющихся блюдах
        {
            cout << "Информация о блюде: " << *number++ << endl;
            cout << "Название блюда: " << meal_name << endl;
            cout << "Цена блюда: " << meal_price << " рублей" << endl;
            cout << "Вес блюда: " << meal_weight << " грамм" << endl;
            cout << "_________________________________________" << endl;
        }
};

class Order     //  класс заказа
{
    private:
        int meal_len = 0;       // количество блюд в заказе
        string total_price;        // итоговая цена блюд
        string table_number;    // номер столика

        void firstMeal()        // создание первого блюда в списке
        {
            meal_list[0].createMeal();    // вызов стандартного метода создания блюда
            meal_len++;
        }

        void firstMeal(ifstream* f)
        {
            meal_list[0].createMeal(f);
        }

        void newMeal()          // внесение блюда
        {
            Meal temp_meal;                         // создаётся временный объект блюда
            temp_meal.createMeal();                 // Заполняется
            Meal* temp_meal_list;                   // Создаётся временный список блюд
            temp_meal_list = new Meal[meal_len++];  // Он на один больше, чем текущий
            for (int i = 0; i < meal_len; i++)      // Все данные из старого списка переносятся в новый
                temp_meal_list[i] = meal_list[i];   
            temp_meal_list[meal_len] = temp_meal;   // последний элемент равен новому блюду
            meal_len++;
            delete[] meal_list;                     // удаляется указатель на старый список
            meal_list = temp_meal_list;             // даётся ссылка на новый список
        }

        void newMeal(ifstream *f)                       // перегруженный метод создания списка блюд
        {
            Meal* temp_meal_list = new Meal[meal_len];  // создаётся временный список объектов Meal равный количеству блюд

            for (int i = 0; i < meal_len; i++)
                temp_meal_list[i].createMeal(f);        // вносится необходимое количество блюд в список

            delete[] meal_list;                         // удаляется старый список
            meal_list = temp_meal_list;                 // даётся ссылка на новый список
        }

        void removeMealList(int const* number)          // метод удаления блюда по номеру
        {
            Meal* temp_meal_list;                       // создается временный список объектов
            int k = 0;                                  // счетчик, используется для прохождения по temp_meal_list
            if (meal_len - 1 == 0)                      // ветвление, на случай удаления последнего блюда
            {
                delete[] meal_list;
                meal_list = new Meal[1];
            }
            else
            {
                // в случае удаления не последнего блюда
                temp_meal_list = new Meal[meal_len - 1];
                for (int i = 0; i < (*number - 1); i++) temp_meal_list[k++] = meal_list[i];
                for (int i = *number; i < meal_len; i++) temp_meal_list[k++] = meal_list[i];
                delete[] meal_list;
                meal_list = temp_meal_list;
            }
        }

        friend Cafe;
        friend Meal;

    public:
        Meal* meal_list;
        string total_price;        // итоговая цена блюд
        string table_number;    // номер столика

        Order()                  // конструктор класса Order
        {
            total_price = "NULL";
            table_number = "NULL";
            if (meal_list == 0)
                meal_list = new Meal[1];
            else
                meal_list = new Meal[meal_len];
        }

        void setInf()
        {
            system("cls");
            cout << "Внесите информацию о заказе: " << endl;
            cout << "Номер столика: "; getline(cin, table_number, '\n');
            cout << "Итоговая цена заказа "; getline(cin, total_price, '\n');
        }

        void setInf(ifstream* f)
        {
            string buf;
            getline(*f, buf, '\n');
            getline(*f, table_number, '\n');
            getline(*f, total_price, '\n');
        }

        void makeOrder()        // метод создания заказа
        {
            system("cls");
            char choice = '0';
            while (choice != '4')
            {
                system("cls");
                cout << endl << "Выберите, что вы хотите сделать: " << endl;
                cout << "_________________________________________" << endl
                    << "1. Добавить блюдо в заказ" << endl
                    << "2. Список всех блюд в заказе" << endl
                    << "3. Удалить блюдо из заказа" << endl
                    << "4. Закончить с заказом" << endl
                    << "____________________________________" << endl;
                cout << "Выберите действие: "; cin >> choice;

                string buf;         // переменная для чтения символа конца строки 
                getline(cin, buf);  // подчищаем ввод 

                switch (choice)
                {
                    case '1':               // Добавление блюда в заказ
                        if (meal_len == 0)  // Если в заказе ещё нет блюд
                            firstMeal();
                        else                // Если в заказе уже есть блюда
                            newMeal();
                        break;
                    case '2':
                        system("cls");
                        if (meal_len != 0)
                            for (int i = 0; i < meal_len; i++) meal_list[i].getMealList(&i);
                        else
                            cout << "--БЛЮД НЕТ--" << endl;
                        system("pause");
                    case '3':
                        int n_meal;
                        if (meal_len)
                        {
                            system("cls");
                            cout << "Укажите номер блюда: "; cin >> n_meal;
                            if (meal_len < n_meal)
                            {
                                cout << "---БЛЮДО С ДАННЫМ НОМЕРОМ ОТСУТСТВУЕТ---" << endl;
                                system("pause");
                            }
                            else
                            {
                                removeMealList(&n_meal);
                            }
                        }
                        else
                        {
                            system("cls");
                            cout << "---БЛЮД НЕТ---" << endl;
                            system("pause");
                        }
                        break;
                }

            }

        }

        void read_file(ifstream* f)
        {
            *f >> meal_len;
            string buf;
            getline(*f, buf, '\n');
            if (meal_len)
            {
                if (meal_len == 1)
                    firstMeal(f);
                else
                    newMeal(f);
            }
        }
};

class Cafe          // класс Кафе
{        
    private:
        int len = 0;    // длина списка заказов
        Order* list_order = new Order[1];       // список заказов

        void firstOrder()
        {
            list_order[0].setInf();
            len++;
        }

        void firstOrder(ifstream* f)
        {
            list_order[0].setInf(f);
        }

        void newOrder()
        {
            Order temp_order;
            temp_order.setInf();
            Order* temp_list;
            temp_list = new Order[len++];
            for (int i = 0; i < len; i++) temp_list[i] = list_order[i];
            temp_list[len] = temp_order;
            len++;
            delete[] list_order;
            list_order = temp_list;
        }
    public:
        Cafe()      // конструктор класса
        {
            ifstream file;
            file.open("data.txt");
            file >> len;

            if (len)        // аналог метода init
            {
                list_order = new Order[len];
                if (len == 1)
                {
                    firstOrder(&file);
                    list_order[0].read_file(&file);
                }
                else
                {
                    for (int i = 0; i < len; i++)
                    {
                        list_order[i].setInf(&file);
                        list_order[i].read_file(&file);
                    }
                }
            }
            file.close();
        }

        void init()
        {
            if (len == 0)
                firstOrder();
            else
                newOrder();
        }

        void menu()
        {
            system("cls");
            int i = 0;
            for (; i < len; i++)
            {
                list_order[i].makeOrder();
                break;
            }
        }

        void write_to_file()
        {
            ofstream file;
            file.open("data.txt");

            file << len << '\n';

            for (int i = 0; i < len; i++)
            {
                file << list_order[i].table_number << '\n'; // вводится номер столика
                file << list_order[i].total_price << '\n';  // вводится итоговая цена заказа
                file << list_order[i].meal_len << '\n';     // вводится количество заказов
                for (int j = 0; j < list_order[i].meal_len; j++)    // вводятся сами блюда
                {
                    file << list_order[i].meal_list[j].meal_name << '\n';
                    file << list_order[i].meal_list[j].meal_price << '\n';
                    file << list_order[i].meal_list[j].meal_weight << '\n';
                }
            }
            file.close();
        }

};

int main()
{
    setlocale(0, "");

    char choice = '0';
    Cafe demo;
    string a;

    while (choice != '2')
    {
        system("cls");
        cout << endl << "Выберите, что вы хотите сделать: " << endl;
        cout << "_________________________________________" << endl
            << "1. Cделать заказ " << endl
            << "2. Выйти из программы" << endl
            << "_____________________________";
        cout << endl << "Ваш выбор: "; cin >> choice;
        getline(cin, a, '\n');

        switch (choice)
        {
        case '1':
            demo.menu();
            break;
        }
    }

    demo.write_to_file();

    return 0;
}