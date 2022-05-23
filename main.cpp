#include <iostream>

using namespace std;

struct Houses {
    int variation;//Вариант дома 1)- BlockOfFlat 2)- Detached 3)- Cottage
    int population;// Сколько человек живет в доме
    union {
        struct {
            int entrance;//Подъезд
            int flat;//Номер кватриры
        } BlockOfFlat;
        struct {
            int c;// количество комнат
            double s;// Площадь
        } Detached;
        struct {
            double s;// Площадь участка
            int f;// Количество этажей
        } Cottage;
    };
};
void writing(Houses home) {
    if (home.variation == 1) {
        cout << "Многоквартирый дом в котором проживает: " << home.population << " жильцов\n";
        cout <<"Человек живёт в " << home.BlockOfFlat.entrance
             << " подъезде и в кватрире номер " << home.BlockOfFlat.flat << "\n\n";
    } else if (home.variation == 2) {
        cout << "Частный дом в котором проживает: " << home.population << " жильцов\n";
        cout << "Человек живёт в доме с " << home.Detached.c << " комнатами и площадью  "
             << home.Detached.s << " м^2\n\n";
    } else {
        cout << "Загородный дом дом в котором проживает: " << home.population << " жильцов\n";
        cout << "Человек живёт в доме с " << home.Cottage.f << " этажами и площадью  "
             << home.Cottage.s << " м^2\n\n";
    }
}
/**
 * ячейка в которой лежит дом
 */
struct Node{
    Houses home;
    Node* next;

    Node(Houses home) : home(home), next(nullptr) {}
};

struct SingleList{
    Node* head;
    int size = 0;

    SingleList() : head(nullptr){}

    /**
     * @return пустой ли список
     */
    bool isEmpty(){
        return head == nullptr;
    }
    /**
     * Добавление к голове
     * @param home новый дом
     */
    void add(Houses home) {
        Node* temp = new Node(home);
        if (isEmpty()) {
            head = temp;
            size++;
            return;
        }
        temp->next = head;
        head = temp;
        size++;
    }
    /**
     *Удаление элемента по индексу
     * @param index индекс удаляемого элемента
     */
    void deleteByIndex(int index){
        if(index < 0 || index > size - 1){
            cout << "Ваш индекс некорректен" << endl;
            return;
        }
        Node* curr = head;
        int counter = 0;
        while (counter != index - 1) {
            curr = curr->next;
            counter++;
        }
        Node* nodeToDel = curr->next;
        curr->next = curr->next->next;
        delete nodeToDel;
        size--;
    }
    /**
     * print whole list
     */
    void print() {
        if (isEmpty()) return;
        Node* temp = head;
        while (temp) {
            writing(temp->home);
            temp = temp->next;
        }
        cout << endl;
    }
};
Houses createHouse(){
    int var;
    Houses homes{};
    cout << "Введите вариант дома:\n1)- Многоквартирный\n2)- Частный дом\n3)- Загородный дом\n";
    cin >> var;
    homes.variation = var;
    cout << "Сколько человек живет в доме?\n";
    cin >> var;
    homes.population = var;
    if (homes.variation == 1) {
        cout << "Введите номер подъезда\n";
        cin >> var;
        homes.BlockOfFlat.entrance = var;
        cout << "Введите номер квартиры\n";
        cin >> var;
        homes.BlockOfFlat.flat = var;
    } else if (homes.variation == 2) {
        double var2;
        cout << "Введите количество комнат\n";
        cin >> var;
        homes.Detached.c = var;
        cout << "Введите площадь дома\n";
        cin >> var2;
        homes.Detached.s = var2;
    } else if (homes.variation == 3) {
        double var2;
        cout << "Введите площадь участка в м^2\n";
        cin >> var2;
        homes.Cottage.s = var2;
        cout << "Введите количество этажей\n";
        cin >> var;
        homes.Cottage.f = var;
    } else {
        cout << "Некорректные данные!!!";
    }
    return homes;
}

int main() {
    system("chcp 65001");

    Houses testHouse{};
    testHouse.variation = 1;
    testHouse.population = 1000;
    testHouse.BlockOfFlat.flat = 4;
    testHouse.BlockOfFlat.entrance = 3;

    SingleList* myList = new SingleList;
    myList->add(createHouse());
    myList->add(createHouse());
    myList->add(createHouse());
    cout << "====================== Добавление элементов\n";
    myList->print();
    cout << "======================удаление элемента по индексу\n";

    myList->deleteByIndex(1);
    myList->print();
    cout << "======================Добаление элемента\n";

    myList->add(testHouse);
    myList->print();
    return 0;
}
/**
     *Удаление головы (последний добавленный элемент)
     *//*

void deleteFirst(){
    if (isEmpty()) return;
    Node* p = head;
    head = p->next;
    delete p;
    size--;
}*/
