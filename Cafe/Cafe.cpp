#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Meal                           // класс Заказ
{
    private:
        string meal_name;            // название блюда
        string meal_price, meal_weight;  // цена и вес блюда
        
        
        //friend <класс официанта и заказа>
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

        void getMeal(int const* number) // метод вывода информации об имеющихся блюдах
        {
            cout << "Информация о блюде: " << *number++ << endl;
            cout << "Название блюда: " << meal_name << endl;
            cout << "Цена блюда: " << meal_price << endl;
            cout << "Вес блюда: " << meal_weight << endl;
        }
        
};

int main()
{
    Meal bread;
    bread.createMeal();
    bread.getMeal(0);
}

