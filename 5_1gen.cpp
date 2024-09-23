#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>

int main() {
    const int n = 5000000; // 10^7
    std::vector<int> numbers(n);

    // Заполняем вектор уникальными числами от 0 до n-1
    for (int i = 0; i < n; ++i) {
        numbers[i] = i;
    }

    // Перемешиваем числа для случайного порядка
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(numbers.begin(), numbers.end(), g);

    // Создаем и открываем файл для записи
    std::ofstream outFile("unique_numbers.txt");
    if (!outFile) {
        std::cerr << "Ошибка при открытии файла!" << std::endl;
        return 1;
    }

    // Записываем числа в файл
    for (int i = 0; i < n; ++i) {
        outFile << numbers[i] << "\n";
    }

    outFile.close();
    std::cout << "Файл 'unique_numbers.txt' успешно создан с " << n << " уникальными неотрицательными целыми числами." << std::endl;

    return 0;
}
