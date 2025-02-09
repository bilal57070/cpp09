#include "BitcoinExchange.hpp"

void    sort_data(stru *btc){
    std::ifstream input("./data.csv");
    std::string line;
    size_t      found;
    std::string date;
    std::string value;
    float         val;
    int veski = 0;

    if (input){
        while (getline(input, line)){
            if (veski != 0){
                found = line.find(",");
                if (found == std::string::npos){
                    std::cout << "error no coma in input" << std::endl;
                    exit(1);
                }
                date = line.substr(0, found);
                value = line.substr(found + 1);
                std::istringstream iss(value);
                if (!(iss >> val))
                    std::cout << "error conversion" << std::endl;
                btc->data[date] = val;
            }
            veski++;
        }
    }
    print_map(btc->data);
}

void print_map(std::map<std::string, float> &c){
    for (std::map<std::string, float>::iterator it = c.begin(); it != c.end(); ++it)
        std::cout << it->first << " : " << std::fixed << std::setprecision(2) << it->second << std::endl;
}

void read_input(char *input, stru *btc){
    std::ifstream in(input);
    size_t      found;
    int veski = 0;

    if (in){
        while (getline(in, btc->line)){
            if (veski != 0){
                found = btc->line.find("|");
                if (found == std::string::npos){
                    std::cout << "error no | in input" << std::endl;
                    continue;
                }
                if (btc->line[(found - 1)] != ' ' || btc->line[(found + 1)] != ' '){
                    std::cout << "no space between section" << std::endl;
                    continue;
                }
                btc->date = btc->line.substr(0, found - 1);
                btc->value = btc->line.substr(found);
                //std::cout << btc->value << std::endl;
                //std::cout << btc->date << "e" << std::endl;
                std::istringstream iss(btc->value);
                if (!(iss >> btc->val))
                    std::cout << "error conversion" << std::endl;
                if (btc->val < 0){
                    std::cout << "error: not a positive number" << std::endl;
                    continue;
                }
                pars(btc);
            }
            veski++;
        }
    }
}

void pars(stru *btc){

}