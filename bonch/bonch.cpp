#include <iostream>
#include <clocale>

using namespace std;

// Класс "Телефон-факс" (Вариант 14)
class FaxTelephone {
private:
    bool isHookUp;      // false - трубка на базе, true - снята
    int paperCount;     // запас бумаги (0..50)
    bool isFaxActive;   // статус передачи/приема

public:
    // Конструктор по умолчанию
    FaxTelephone();

    // Конструктор с параметрами
    FaxTelephone(bool hook, int paper);

    // Методы
    void changeHook();
    void loadPaper(int count);
    void sendFax();
    void receiveFax();
    void printState() const;
};

// Реализация конструктора по умолчанию
FaxTelephone::FaxTelephone() {
    isHookUp = false;
    paperCount = 10;
    isFaxActive = false;
}

// Реализация конструктора с параметрами
FaxTelephone::FaxTelephone(bool hook, int paper) {
    isHookUp = hook;
    isFaxActive = false;

    if (paper < 0) paperCount = 0;
    else if (paper > 50) paperCount = 50;
    else paperCount = paper;
}

void FaxTelephone::changeHook() {
    if (isFaxActive) {
        cout << "[Ошибка]: Факс активен, нельзя менять положение трубки!" << endl;
        return;
    }
    isHookUp = !isHookUp;
    cout << "[Действие]: Трубка " << (isHookUp ? "снята." : "повешена.") << endl;
}

void FaxTelephone::loadPaper(int count) {
    if (count <= 0) {
        cout << "[Ошибка]: Число листов должно быть больше нуля." << endl;
        return;
    }
    paperCount += count;
    if (paperCount > 50) paperCount = 50;
    cout << "[Инфо]: Листов в лотке: " << paperCount << endl;
}

void FaxTelephone::sendFax() {
    if (!isHookUp) {
        cout << "[Ошибка]: Для передачи факса снимите трубку!" << endl;
        return;
    }
    isFaxActive = true;
    cout << "[Факс]: Передача документа..." << endl;
    isFaxActive = false;
    cout << "[Факс]: Документ успешно передан!" << endl;
}

void FaxTelephone::receiveFax() {
    if (isHookUp) {
        cout << "[Ошибка]: Линия занята разговором!" << endl;
        return;
    }
    if (paperCount <= 0) {
        cout << "[Ошибка]: В лотке нет бумаги!" << endl;
        return;
    }
    isFaxActive = true;
    cout << "[Факс]: Прием и печать документа..." << endl;
    paperCount--;
    isFaxActive = false;
    cout << "[Факс]: Напечатано. Осталось листов: " << paperCount << endl;
}

void FaxTelephone::printState() const {
    cout << "\n========== СОСТОЯНИЕ ==========" << endl;
    cout << "Трубка: " << (isHookUp ? "СНЯТА (занято)" : "ПОЛОЖЕНА (свободно)") << endl;
    cout << "Бумага: " << paperCount << " / 50 шт." << endl;
    cout << "Факс:   " << (isFaxActive ? "АКТИВЕН" : "В ПОКОЕ") << endl;
    cout << "===============================\n" << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    // 1. Создание объекта конструктором по умолчанию
    FaxTelephone defaultDevice;
    defaultDevice.printState();

    // 2. Создание объекта конструктором с параметрами
    FaxTelephone customDevice(true, 25);
    customDevice.printState();

    return 0;
}