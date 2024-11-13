#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

// Класс для блока символов
class Block {
public:
    std::string characters; // Блок символов
    double probability; // Вероятность блока

    Block(const std::string& chars, double p) : characters(chars), probability(p) {}
};

// Сравнение для сортировки блоков по вероятности
bool compareBlocks(const Block& a, const Block& b) {
    return a.probability > b.probability; // Сортировка по убыванию вероятности
}

// Функция для генерации кодов Шеннона-Фано
void generateShannonFanoCodes(const std::vector<Block>& blocks, std::vector<std::pair<std::string, std::string>>& codes, const std::string& code) {
    if (blocks.size() == 1) {
        codes.emplace_back(blocks[0].characters, code);
        return;
    }

    double total = 0.0;
    for (const auto& block : blocks) {
        total += block.probability;
    }

    double cumulative = 0.0;
    size_t splitIndex = 0;
    double minDifference = total;

    for (size_t i = 0; i < blocks.size() - 1; ++i) {
        cumulative += blocks[i].probability;
        double difference = std::abs(total / 2 - cumulative);

        if (difference < minDifference) {
            minDifference = difference;
            splitIndex = i + 1; // Индекс первого элемента второй половины
        }
    }

    generateShannonFanoCodes(std::vector<Block>(blocks.begin(), blocks.begin() + splitIndex), codes, code + "0");
    generateShannonFanoCodes(std::vector<Block>(blocks.begin() + splitIndex, blocks.end()), codes, code + "1");
}

// Функция для подсчета частоты блоков длиной 3 символа
std::vector<Block> calculateBlockFrequencies(const std::vector<char>& symbols, const std::vector<double>& probabilities) {
    std::vector<Block> frequencies;

    for (size_t i = 0; i < symbols.size(); ++i) {
        for (size_t j = 0; j < symbols.size(); ++j) {
            for (size_t k = 0; k < symbols.size(); ++k) {
                std::string block = {symbols[i], symbols[j], symbols[k]};
                double probability = probabilities[i] * probabilities[j] * probabilities[k];
                frequencies.emplace_back(block, probability); // Добавляем блок и его вероятность
            }
        }
    }
    
    return frequencies;
}

// Функция для вычисления средней длины кода с учетом вероятностей
double calculateAverageLength(const std::vector<std::pair<std::string, std::string>>& codes, const std::vector<Block>& frequencies) {
    double averageLength = 0.0;

    for (const auto& pair : codes) {
        for (const auto& freq : frequencies) {
            if (freq.characters == pair.first) {
                averageLength += pair.second.length() * freq.probability;
                break;
            }
        }
    }

    return averageLength;
}

int main() {
    std::vector<char> symbols = {'A', 'B'};
    std::vector<double> probabilities = {0.7, 0.3};

    auto frequencies = calculateBlockFrequencies(symbols, probabilities);
        
    // Сортируем блоки по вероятности
    std::sort(frequencies.begin(), frequencies.end(), compareBlocks);

    // Генерация кодов Шеннона-Фано для блоков
    std::vector<std::pair<std::string, std::string>> shannonFanoCodes;
    generateShannonFanoCodes(frequencies, shannonFanoCodes, "");

    // Вывод кодов
    std::cout << "Коды Шеннона-Фано для блоков:\n";
    for (const auto& pair : shannonFanoCodes) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }

    // Вычисление средней длины кода с учетом вероятностей
    double averageLength = calculateAverageLength(shannonFanoCodes, frequencies);
    
    std::cout << "Средняя длина кода: " << averageLength << "\n";

    return 0;
}