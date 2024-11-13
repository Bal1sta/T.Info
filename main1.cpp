#include <iostream> 
#include <vector> 
#include <map> 
#include <algorithm> 
#include <cmath> 

class Symbol {
public:
    char character; // Символ
    double probability; // Вероятность символа

    // Конструктор класса Symbol, инициализирующий символ и его вероятность
    Symbol(char c, double p) : character(c), probability(p) {}
};

// Сравнение для сортировки символов по вероятности
bool compareSymbols(const Symbol& a, const Symbol& b) {
    return a.probability > b.probability; // Сортировка по убыванию вероятности
}

// Функция для генерации кодов Шеннона-Фано
void generateShannonFanoCodes(const std::vector<Symbol>& symbols, std::map<char, std::string>& codes, const std::string& code) {
    // Проверка на единственный символ
    if (symbols.size() == 1) { // Если остался только один символ
        codes[symbols[0].character] = code; // Присваиваем код единственному символу. Присваиваем его коду текущую строку (например, 0 или 1»).
        return; 
    }

    // Суммируем вероятности всех символов. Это значение будет использоваться для определения точки разделения.
    double total = 0.0;
    for (const auto& symbol : symbols) {
        total += symbol.probability; // Проходим по всем символам и суммируем их вероятности.
    }

    // Инициализация переменных для нахождения точки разделения
    double cumulative = 0.0; // Переменная для накопления вероятностей по мере итерации
    size_t splitIndex = 0; // Индекс, который будет указывать на границу между двумя подмножествами. Индекс разделения
    double minDifference = total; // Переменная для хранения минимальной разницы между половиной общей вероятности и кумулятивной вероятностью.


// Итерация по символам для нахождения точки разделения
    for (size_t i = 0; i < symbols.size() - 1; i++) { // Проходимся по всем элементам вектора (кроме последнего), чтобы избежать выхода за пределы массива.
        cumulative += symbols[i].probability; // Текущая вероятность сложенных символов
        double difference = std::abs(total / 2 - cumulative); // Вычисляем разницу между половиной общей вероятности и суммой


// Если текущая разница меньше, чем ранее найденная минимальная разница minDifference, обновляем minDifference и устанавливаем splitIndex как индекс следующего элемента
        
        if (difference < minDifference){ // Если текущая разница меньше минимальной
            minDifference = difference; // Обновляем минимальную разницу
            splitIndex = i + 1; // Индекс первого элемента второй половины
        }
        
    }

    // Рекурсивно вызываем функцию для первой половины символов, добавляя 0 или 1 к текущему коду.
    generateShannonFanoCodes(std::vector<Symbol>(symbols.begin(), symbols.begin() + splitIndex), codes, code + "0"); // Для первой половины добавляем "0"
    generateShannonFanoCodes(std::vector<Symbol>(symbols.begin() + splitIndex, symbols.end()), codes, code + "1"); // Для второй половины добавляем "1"
}

// Функция для вывода информации о энтропии и избыточности
void Print() {
    double z1 = 0.25; // Вероятность первого символа
    double result1 = log2(z1); // Логарифм по основанию 2 от вероятности

    double z2 = 0.19; 
    double result2 = log2(z2);

    double z3 = 0.15;
    double result3 = log2(z3);

    double z4 = 0.11;
    double result4 = log2(z4);

    double z5 = 0.09;
    double result5 = log2(z5);

    double z6 = 0.09;
    double result6 = log2(z6);

    double z7 = 0.07;
    double result7 = log2(z7);

    double z8 = 0.05;
    double result8 = log2(z8);

    double EntropiaMAX = log2(8); // Максимальная энтропия для 8 символов

    // Вычисляем энтропию на основе вероятностей и логарифмов
    double ZResult = -(z1 * result1 + z2 * result2 + z3 * result3 + z4 * result4 + z5 * result5 + z6 * result6 + z7 * result7 + z8 * result8);

    std::cout << "Энтропия: " << ZResult << std::endl << std::endl; // Выводим значение энтропии

    double AverageLength = (2 * 0.44 + 3 * 0.26 + 4 * 0.3); // Средняя длина кода (примерные значения)

    // Избыточность: рассчитываем как отношение фактической длины к максимальной энтропии
    double Redundancy = 1 - (ZResult / EntropiaMAX); 

    std::cout << "Средняя длина кода: " << AverageLength << std::endl << std::endl; 
    std::cout << "Избыточность: " << Redundancy << std::endl << std::endl;

    std::cout << "Максимальная энтропия: " << EntropiaMAX << std::endl; 
}


int main() {
    std::vector<Symbol> symbols = { 
        {'A', 0.25}, 
        {'B', 0.19}, 
        {'C', 0.15}, 
        {'D', 0.11}, 
        {'E', 0.09}, 
        {'F', 0.09}, 
        {'G', 0.07}, 
        {'H', 0.05} 
    }; 

    std::sort(symbols.begin(), symbols.end(), compareSymbols); // Сортируем символы по убыванию вероятности

    // Генерация кодов Шеннона-Фано
    std::map<char, std::string> shannonFanoCodes; 
    generateShannonFanoCodes(symbols, shannonFanoCodes, ""); 

    // Вывод кодов Шеннона-Фано
    std::cout << "Коды Шеннона-Фано:\n"; 
    for (const auto& pair : shannonFanoCodes) { 
        std::cout << pair.first << ": " << pair.second << "\n"; // Выводим каждый символ и его соответствующий код
    }

    Print(); // Вызываем функцию для вывода информации о энтропии избыточности и ср длины

    return 0; // Завершаем программу с кодом возврата 0 (успешное выполнение)
}