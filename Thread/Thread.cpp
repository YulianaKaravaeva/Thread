#include <thread>
#include <iostream>
#include <mutex>

std::mutex out_mutex;
int globalNumber = 1000000; // кол-во чисел, которые надо сложить (по условию не помню сколько надо)
int finalSum = 0; // переменная, в которой будет накапливаться сумма

// переменная, в которой будет накапливаться сумма, от дельная для каждого потока
int sum1 = 0;
int sum2 = 0;
int sum3 = 0;
int sum4 = 0;

// ф-ия суммирования чисел от start до end
void sumThread(const int start, const int end, int* sum) {

    // инициализация мьютекса (mutex)
    std::lock_guard<std::mutex>_g(out_mutex);

    // цикл по цифрам от start до end
    for (int i = start; i < end; i++) {

        // добавление к накопленной сумме
        finalSum += i;
        *sum += i;

    }
}

int main() {

    // инициализация нитей (по условию 4 нити)
    std::thread thread1(sumThread, 1, globalNumber / 4, &sum1);
    std::thread thread2(sumThread, (globalNumber / 4), (globalNumber * 2) / 4, &sum2);
    std::thread thread3(sumThread, ((globalNumber * 2) / 4), (globalNumber * 3) / 4, &sum3);
    std::thread thread4(sumThread, ((globalNumber * 3) / 4), globalNumber + 1, &sum4);

    // запуск нитей
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();

    // вывод результата
    std::cout << "Способ 1: " << finalSum << std::endl;
    std::cout << "Способ 2: " << sum1 + sum2 + sum3 + sum4 << std::endl;

    // для сравнения
    int sum = 0;

    for (int j = 1; j <= globalNumber; j++) {
        sum += j;
    }

    std::cout << "Проверка: " << sum;
}