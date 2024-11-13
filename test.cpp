#include <iostream>
#include <vector>
#include <string>


class Block {
public:
    std::string characters; // Блок символов
    double probability; // Вероятность блока

    Block(const std::string& chars, double p) : characters(chars), probability(p) {}
};


void Blocks(std::vector<char>& symbols, std::vector<double>& probabilityes, std::vector<Block>& frenquencies){
    

    for(size_t i = 0; i < symbols.size(); ++i){
        for(size_t j = 0; j < symbols.size(); ++j){
            for(size_t k = 0; k < symbols.size(); ++k){
                std::string block = {symbols[i], symbols[j], symbols[k]};
                double probability = probabilityes[i] * probabilityes[j] * probabilityes[k];
                frenquencies.push_back({block, probability});
            }
        }
    }
}


void rez(const std::vector<Block>& frenquencies){

}


int main(){
    std::vector<char> symbols = {'A', 'B'};
    std::vector<double> probabilityes = {0.7, 0.3};

    std::vector<Block> frenquencies;
    Blocks(symbols, probabilityes, frenquencies);
    for(const auto& block : frenquencies){
        std::cout << block.characters << " " << block.probability << std::endl; 
    }
    
}