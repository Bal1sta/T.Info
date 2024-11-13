#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>

// Класс для блока символов
class Block {
public:
    std::string tokens;
    double probability;

    Block(const std::string& chars, double p) : tokens(chars), probability(p) {}
};

// Структура для хранения кодов
struct CodeEntry {
    std::string token;
    std::string code;
};

// Класс для узла дерева Хаффмана
class HuffmanNode {
public:
    std::string token;
    double probability;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(const std::string& t, double p) : token(t), probability(p), left(nullptr), right(nullptr) {}
};

// Функция для генерации кодов Хаффмана
void generateHuffmanCodes(HuffmanNode* root, const std::string& code, std::vector<CodeEntry>& huffmanCodes) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCodes.push_back({root->token, code});
        return;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

// Функция для построения дерева Хаффмана и генерации кодов
std::vector<CodeEntry> huffmanCoding(const std::map<std::string, double>& frequencyMap) {
    std::vector<HuffmanNode*> nodes;

    // Создаем узлы для каждого блока из мапы
    for (const auto& entry : frequencyMap) {
        nodes.push_back(new HuffmanNode(entry.first, entry.second));
    }

    // Построение дерева Хаффмана
    while (nodes.size() > 1) {
        std::sort(nodes.begin(), nodes.end(), [](HuffmanNode* a, HuffmanNode* b) {
            return a->probability > b->probability;
        });

        HuffmanNode* right = nodes.back(); nodes.pop_back();
        HuffmanNode* left = nodes.back(); nodes.pop_back();

        HuffmanNode* newNode = new HuffmanNode("", left->probability + right->probability);
        newNode->left = left;
        newNode->right = right;

        nodes.push_back(newNode);
    }

    // Генерация кодов Хаффмана
    std::vector<CodeEntry> huffmanCodes;
    generateHuffmanCodes(nodes[0], "", huffmanCodes);

    return huffmanCodes;
}

// Функция для подсчета частоты блоков длиной 3 символа. Принимает вектор символов и вероятностей.
std::map<std::string, double> calculateBlockFrequencies(const std::vector<char>& symbols, const std::vector<double>& probabilities) {
// map используется для хранения блоков и их вероятностей. Ключом будет строка (блок), а значением — вероятность этого блока
    std::map<std::string, double> frequencyMap;

    for (size_t i = 0; i < symbols.size(); ++i) {
        for (size_t j = 0; j < symbols.size(); ++j) {
            for (size_t k = 0; k < symbols.size(); ++k) { 
                std::string block = {symbols[i], symbols[j], symbols[k]};
                double probability = probabilities[i] * probabilities[j] * probabilities[k];
// Если блок с таким ключом уже существует, его вероятность увеличивается на рассчитанную вероятность
// Если блока нет, он автоматически добавляется в мапу с начальным значением вероятности
                // Обновляем вероятность в мапе
                frequencyMap[block] = probability;
            }
        }
    }
// Возвращаемый тип: Функция возвращает std::map<std::string, double>, где ключом является строка (блок символов), а значением — вероятность этого блока.
    return frequencyMap; // Возвращаем мапу вместо вектора
}

// Функция для вычисления средней длины кода с учетом вероятностей
double calculateAverageLength(const std::vector<CodeEntry>& codes, const std::map<std::string, double>& frequencyMap) {
    // Переменная для накопления средней длины кодов
    double averageLength = 0.0;

    // Перебираем все элементы в векторе codes. 
    // Переменная code представляет текущий элемент (объект типа CodeEntry)
    for (const auto& code : codes) {
        // Ищем токен текущего кода в мапе частот
        auto it = frequencyMap.find(code.token);
        
        // Проверяем, найден ли токен в мапе
        if (it != frequencyMap.end()) {
            // Если токен найден, добавляем к средней длине произведение длины кода на его вероятность
            averageLength += code.code.length() * it->second; // it->second - вероятность блока
        }
    }

    // Возвращаем рассчитанную среднюю длину кодов
    return averageLength;
}

int main() {
    std::vector<char> symbols = {'A', 'B'};
    std::vector<double> probabilities = {0.7, 0.3};

    // Подсчет частот блоков
    auto frequencyMap = calculateBlockFrequencies(symbols, probabilities);

    // Вывод частот блоков
    std::cout << "Частоты блоков:\n";
    for (const auto& entry : frequencyMap) {
        std::cout << "Блок: " << entry.first << ", Вероятность: " << entry.second << "\n";
    }

    // Генерация кодов Хаффмана для блоков
    auto huffmanCodes = huffmanCoding(frequencyMap);

    // Вывод кодов Хаффмана
    std::cout << "\nКоды Хаффмана для блоков:\n";
    for (const auto& entry : huffmanCodes) {
        std::cout << entry.token << ": " << entry.code << "\n";
    }

    // Вычисление средней длины кода с учетом вероятностей для Хаффмана
    double averageLengthHuffman = calculateAverageLength(huffmanCodes, frequencyMap);
    std::cout << "Средняя длина кода Хаффмана: " << averageLengthHuffman << "\n";

    return 0;
}