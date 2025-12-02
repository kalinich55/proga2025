#include <iostream>
using namespace std;

class DynamicArray {
private:
    int *arr;
    int size;

public:
    // конструктор
    DynamicArray(int n) {
        if (n < 0) {
            cout << "Ошибка: размер не может быть отрицательным" << endl;
            size = 0;
            arr = nullptr;
            return;
        }
        size = n;
        arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = 0;
        }
    }

    // конструктор копирования
    DynamicArray(const DynamicArray& other) {
        size = other.size;
        arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = other.arr[i];
        }
    }

    // деструктор
    ~DynamicArray() {
        delete[] arr;
    }

    // сеттер
    void set(int index, int val) {
        if (0 <= index && index < size) {
            if (-100 <= val && val <= 100) {
                arr[index] = val;
            } else {
                cout << "Ошибка: значение " << val << " выходит за пределы [-100, 100]" << endl;
            }
        } else {
            cout << "Ошибка: индекс " << index << " выходит за границы массива" << endl;
        }
    }

    // геттер
    int get(int index) const {
        if (0 <= index && index < size) {
            return arr[index];
        } else {
            cout << "Ошибка: индекс " << index << " выходит за границы массива" << endl;
            return 0;
        }
    }

    // функция вывода
    void print() {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    // значения добавляются в конец
    void add(int val) {
        if (-100 <= val && val <= 100) {
            int* newArr = new int[size + 1];
            
            for (int i = 0; i < size; i++) {
                newArr[i] = arr[i];
            }
            
            newArr[size] = val;
            
            delete[] arr;
            arr = newArr;
            size += 1;
        } else {
            cout << "Ошибка: значение " << val << " выходит за пределы [-100, 100]" << endl;
        }
    }

    // сложение массивов
    DynamicArray operator+(const DynamicArray& other) {
        int maxSize = (size > other.size) ? size : other.size;
        DynamicArray result(maxSize);
        
        for (int i = 0; i < maxSize; i++) {
            int val1 = (i < size) ? arr[i] : 0;
            int val2 = (i < other.size) ? other.arr[i] : 0;
            result.arr[i] = val1 + val2;
        }
        
        return result;
    }

    // вычитание массивов
    DynamicArray operator-(const DynamicArray& other) {
        int maxSize = (size > other.size) ? size : other.size;
        DynamicArray result(maxSize);
        
        for (int i = 0; i < maxSize; i++) {
            int val1 = (i < size) ? arr[i] : 0;
            int val2 = (i < other.size) ? other.arr[i] : 0;
            result.arr[i] = val1 - val2;
        }
        
        return result;
    }

    // геттер для размера
    int getSize() const {
        return size;
    }
};

class Func {
public:
    static void showMsg() {
        cout << "Выполняется вычисление медианного значения" << endl;
    }

    static void med(const DynamicArray& arr) {
        showMsg();
        int n = arr.getSize();
        if (n == 0) {
            cout << "Массив пуст" << endl;
            return;
        }
        
        double m;
        if (n % 2 == 0) {
            m = (arr.get(n / 2 - 1) + arr.get(n / 2)) / 2.0;
        } else {
            m = arr.get(n / 2);
        }
        cout << "Медианное число: " << m << endl;
    }

    static void avg(const DynamicArray& arr) {
        int n = arr.getSize();
        if (n == 0) {
            cout << "Массив пуст" << endl;
            return;
        }
        double s = 0.0;
        for (int i = 0; i < n; i++) { 
            s += arr.get(i);
        }
        cout << "Среднее значение равно: " << s / n << endl;
    }

    static void findMin(const DynamicArray& arr) {
        int n = arr.getSize();
        if (n == 0) {
            cout << "Массив пуст" << endl;
            return;
        }
        int mn = arr.get(0);
        for (int i = 1; i < n; i++) {
            if (mn > arr.get(i)) {
                mn = arr.get(i);
            }
        }
        cout << "Минимальное значение равно " << mn << endl;
    }

    static void findMax(const DynamicArray& arr) {
        int n = arr.getSize();
        if (n == 0) {
            cout << "Массив пуст" << endl;
            return;
        }
        int mx = arr.get(0);
        for (int i = 1; i < n; i++) {
            if (mx < arr.get(i)) {
                mx = arr.get(i);
            }
        }
        cout << "Максимальное значение равно " << mx << endl;
    }
};

int main() {
    
    
    cout << "Создание массива A размером 3:" << endl;
    DynamicArray a(3);
    a.set(0, 10);
    a.set(1, 20);
    a.set(2, 30);
    cout << "Массив A: ";
    a.print();

    cout << "\nСоздание массива B размером 5:" << endl;
    DynamicArray b(5);
    b.set(0, 5);
    b.set(1, 15);
    b.set(2, 25);
    b.set(3, 35);
    b.set(4, 45);
    cout << "Массив B: ";
    b.print();

    cout << "\nТестирование конструктора копирования:" << endl;
    DynamicArray c = a;
    cout << "Массив C (копия A): ";
    c.print();

    cout << "\nДобавление значения 40 в массив A:" << endl;
    a.add(40);
    cout << "Массив A после добавления: ";
    a.print();

    cout << "\nСложение массивов A и B:" << endl;
    DynamicArray sum = a + b;
    cout << "A + B: ";
    sum.print();

    cout << "\nВычитание массивов A и B:" << endl;
    DynamicArray diff = a - b;
    cout << "A - B: ";
    diff.print();

    cout << "\nТестирование обработки ошибок:" << endl;
    a.set(10, 50);
    a.set(0, 150);

    cout << "\n=== АНАЛИЗ МАССИВОВ ===" << endl;
    
    cout << "\nАнализ массива A:" << endl;
    Func::med(a);
    Func::avg(a);
    Func::findMin(a);
    Func::findMax(a);
    
    cout << "\nАнализ массива B:" << endl;
    Func::med(b);
    Func::avg(b);
    Func::findMin(b);
    Func::findMax(b);
    
    cout << "\nАнализ массива C:" << endl;
    Func::med(c);
    Func::avg(c);
    Func::findMin(c);
    Func::findMax(c);

    return 0;
}