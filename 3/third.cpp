#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <random>

using namespace std;


char company[10][32] = {"Apple", "Microsoft", "JetBrains", "Gazprom",
                        "DigitalDen", "Tesla", "PoeShit", "Tinkoff",
                        "Rosneft", "IBM"};

char surname[10][32] = {"Korshunov", "Bekaldiev", "Belyaev", "Semenov",
                        "Ystinov", "Hananyev", "Voronin", "Kuptzova",
                        "Ivanizkiy", "Shkabara"};

struct insurancePolicy {
    int id;
    string company;
    string surname;
};

class HashTable {
private:
    vector<insurancePolicy> table;
    int sizeTable;
    int num;
    int curEnt = 0;
    const int c = 1;
    const int d = 2;
    const int e = 0;


    int binSheme(int index) {
        int newIndex;
        for (int i = 0;; i++) {
            newIndex = index + c * i + d * i * i;
            if (newIndex >= table.size())
                break;
            if (table[newIndex].id == 0)
                return newIndex;
        }
        for (int j = 0;; j++) {
            newIndex = index + c * j + e * j * j;
            if (newIndex >= table.size()) {
                cout << "Что-то пошло не так..." << endl;
                exit(0);
            }
            if (table[newIndex].id == 0)
                return newIndex;
        }
    }

public:
    HashTable(int num) {
        this->num = num;
        this->sizeTable = num * 2;
        this->table = vector<insurancePolicy>(sizeTable);
    }

    void addElement(int index, insurancePolicy data) {
        if (curEnt > table.size() * 3 / 4) {
            newHash();
        }
        if (table[index].id == 0) {
            table[index] = data;
        } else {
            table[binSheme(index)] = data;
        }
        curEnt++;
    }

    int findElement(int id) {
        if (table[hashFunction(id)].id == id) {
            int i = hashFunction(id);
            cout << i << " || " << table[i].id << " || " << table[i].company << " || " << table[i].surname << endl;
            return i;
        } else {
            int index = hashFunction(id);
            int newIndex;
            for (int i = 0;; i++) {
                newIndex = index + c * i + d * i * i;
                if (newIndex >= table.size())
                    break;
                if (table[newIndex].id == id) {
                    cout << newIndex << " || " << table[newIndex].id << " || " << table[newIndex].company << " || "
                         << table[newIndex].surname << endl;
                    return newIndex;
                }
            }
            for (int i = 0;; i++) {
                newIndex = index + e * i + c * i * i;
                if (newIndex >= table.size())
                    break;
                if (table[newIndex].id == id) {
                    cout << newIndex << " || " << table[newIndex].id << " || " << table[newIndex].company << " || "
                         << table[newIndex].surname << endl;
                    return newIndex;
                }
            }
        }
    }

    void deleteElement(int id) {
        int index = findElement(id);
        table[index].id = -1;
    }

    int getNum() {
        return this->num;
    }


    int hashFunction(int number) {
        return number % this->num;
    }

    void newHash() {
        vector<insurancePolicy> oldTable = table;
        this->num = curEnt * 1.25;
        curEnt = 0;
        this->table = vector<insurancePolicy>(oldTable.size() * 2);

        for (int i = 0; i < oldTable.size(); i++) {
            if (oldTable[i].id == 0 || oldTable[i].id == -1)
                continue;
            else {
                insurancePolicy card;
                card.id = oldTable[i].id;
                card.company = oldTable[i].company;
                card.surname = oldTable[i].surname;
                addElement(hashFunction(oldTable[i].id), card);
            }
        }
    }

    void print() {
        for (int i = 0; i < table.size(); i++) {
            if (table[i].id != 0 && table[i].id != -1) {
                cout << i << " || " << table[i].id << " || " << table[i].company << " || " << table[i].surname << endl;
            }
        }
    }
};


void fillInfo(HashTable &table) {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<unsigned int> dis(100000, 999999);

    for (int i = 0; i < table.getNum(); i++) {
        insurancePolicy card;
        card.id = dis(generator) % 1000000;
        card.company = company[dis(generator) % 10];
        card.surname = surname[dis(generator) % 10];

        table.addElement(table.hashFunction(card.id), card);
    }
}

void addInfo(HashTable &table, int numberOfCards) {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<unsigned int> dis(100000, 999999);

    for (int i = 0; i < numberOfCards; i++) {
        insurancePolicy card;
        card.id = dis(generator) % 1000000;
        card.company = company[dis(generator) % 10];
        card.surname = surname[dis(generator) % 10];

        table.addElement(table.hashFunction(card.id), card);
    }
}


HashTable initTable(int num) {
    HashTable table = HashTable(num);
    return table;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int num;
    cout << "Введите размер таблицы " << endl;
    cin >> num;
    HashTable table = initTable(num);
    fillInfo(table);
    while (true) {
        int n = 0;
        int id = 0;
        int variant = 0;
        cout << "Вывести таблицу - 1" << endl;
        cout << "Добавить элементы в таблицу - 2" << endl;
        cout << "Удалить элемент из таблицы - 3" << endl;
        cout << "Найти элемент в таблице - 4" << endl;
        cout << "Конец работы - 5" << endl;
        cin >> variant;
        switch (variant) {
            case 1:
                table.print();
                break;
            case 2:
                cout << "Сколько элементов добавить в таблицу "<< endl;
                cin >> n;
                addInfo(table, n);
                break;
            case 3:
                cout << "Номер удаляемого элемента "<< endl;
                cin >> id;
                table.deleteElement(id);
                cout << "Удален" << endl;
                break;
            case 4:
                cout << "Номер искомого элемента " << endl;
                cin >> id;
                table.findElement(id);
                break;
            case 5:
                exit(0);
        }
        cout << "======================================" << endl;
    }
}
