#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

// Структура для хранения комбинации и её частоты
struct Combination {
    std::string value; // Значение комбинации
    int count; // Количество вхождений

    Combination(const std::string& val) : value(val), count(1) {} // Конструктор
};

// Функция для чтения текста из файла
std::string readFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    std::string text;

    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            text += line; // Добавляем строку к тексту
        }
        inputFile.close();
    } else {
        std::cerr << "Не удалось открыть файл." << std::endl; // Сообщение об ошибке
    }

    return text;
}

// Вспомогательная функция для дополнения строки пробелами до заданной длины
std::string padString(const std::string& str, int length) {
    if (str.length() < length) {
        return str + std::string(length - str.length(), ' '); // Дополняем пробелами
    }
    return str;
}

// Функция для подсчета комбинаций в тексте
void countCombination(const std::string& text, std::vector<Combination>& combinations, int number) {
    for (int i = 0; i < text.length(); i += number) {
        if (i + 1 <= text.length()) {
            std::string combination = padString(text.substr(i, number), number); // Получаем комбинацию и дополняем пробелами
            
            // Ищем комбинацию в векторе
            auto it = std::find_if(combinations.begin(), combinations.end(),
                                   [&combination](const Combination& c) { return c.value == combination; });

            if (it != combinations.end()) {
                it->count++; // Увеличиваем счетчик, если комбинация уже существует
            } else {
                combinations.emplace_back(combination); // Добавляем новую комбинацию
            }
        }
    }
}

// Функция для анализа ансамбля и вычисления энтропии и избыточности
void EnsembleAnalysis(const std::vector<Combination>& combinations) {
    int totalCount = 0;

    // Подсчет общего количества комбинаций
    for (const auto& combo : combinations) {
        totalCount += combo.count;
    }

    double entropy = 0.0;
    
    // Вывод вероятностей для каждой комбинации
    std::cout << "Вероятности появления блоков:\n";
    for (const auto& combo : combinations) {
        double probability = static_cast<double>(combo.count) / totalCount; // Вычисляем вероятность
        std::cout << "Комбинация: \"" << combo.value << "\", Вероятность: " << probability << std::endl;

        if (probability > 0) {
            entropy -= probability * log2(probability); // Вычисляем энтропию
        }
    }

    std::cout << "Энтропия: " << entropy << std::endl;

    double maxEntropy = log2(combinations.size()); // Максимальная энтропия
    double redundancy = (entropy == 0.0 && maxEntropy == 0.0) ? (1 - 1) : (1 - entropy / maxEntropy); // Вычисляем избыточность
    
    std::cout << "Избыточность: " << redundancy << std::endl;
    
    std::cout << "\n"; // Разделительная строка
}

int main() {
    std::string filename = "C:/_LABY_/Laby_Infa/2_laba/text.txt"; // Путь к файлу

    std::string text = readFromFile(filename); // Читаем текст из файла

    for (int i = 1; i < 6; i++) { // Перебираем длины блоков от 1 до 5
        std::vector<Combination> combinations; // Вектор для хранения комбинаций
        countCombination(text, combinations, i); // Подсчитываем комбинации
        std::cout << "Для блока длинной : " << i << '\n'; 
        EnsembleAnalysis(combinations); // Анализируем ансамбль
    }

    return 0; // Завершение программы
}