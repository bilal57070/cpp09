#include "BitcoinExchange.hpp"


btc::btc(){}

btc::~btc(){}

btc::btc(btc const &cp){
    *this = cp;
}

btc&    btc::operator=(btc const &cp){
    if (data != cp.data)
        data = cp.data;
    return *this;
}

void    btc::sort_data(stru *btc){
    std::ifstream input("./data.csv");
    std::string line;
    size_t      found;
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
                btc->datecsv = line.substr(0, found);
                fusecsv(btc->datecsv, btc);
                value = line.substr(found + 1);
                std::istringstream iss(value);
                if (!(iss >> val))
                    std::cout << "error conversion" << std::endl;
                data[btc->datecsvfused] = val;
            }
            veski++;
        }
    }
    //print_map(btc->data);
}

void btc::fusecsv(std::string date, stru *btc){
    date.erase(4, 1);
    date.erase(6, 1);
    btc->datecsvfused = atoi(date.c_str());
}

/*void print_map(std::map<std::string, float> &c){
    for (std::map<std::string, float>::iterator it = c.begin(); it != c.end(); ++it)
        std::cout << it->first << " : " << std::fixed << std::setprecision(2) << it->second << std::endl;
}*/

void btc::read_input(char *input, stru *btc){
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
                if (btc->line[11] != '|'){
                    std::cout << "bad writing of date" << std::endl;
                    continue;
                }
                if (btc->line[(found - 1)] != ' ' || btc->line[(found + 1)] != ' '){
                    std::cout << "no space between section" << std::endl;
                    continue;
                }
                btc->date = btc->line.substr(0, found - 1);
                btc->value = btc->line.substr(found + 2);
                std::istringstream iss(btc->value);
                if (!(iss >> btc->val))
                    std::cout << "errorrrrrr conversion" << std::endl;
                if (btc->val < 0){
                    std::cout << "error: not a positive number" << std::endl;
                    continue;
                }
                if (pars(btc) == 1 || parsval(btc) == 1)
                    continue;
                fuseinput(btc);
                apply_ExRate(btc);
            }
            veski++;
        }
    }
}

int btc::pars(stru *btc){
    std::string y;
    std::string m;
    std::string d;
    size_t f, f1, f2;

    f = btc->date.find("-");
    if (f != 4){
        std::cout << "wrong write" << std::endl;
        return 1;
    }
    y = btc->date.substr(0, f);
    f1 = btc->date.find("-", f + 1);
    if (f1 != 7){
        std::cout << "wrong writing of date" << std::endl;
        return 1;
    }
    m = btc->date.substr(f + 1, f1 - f - 1);
    f2 = btc->date.find("-", f1 + 1);
    d = btc->date.substr(f1 + 1, f2 - f1 - 1);
    btc->year = atoi(y.c_str());
    btc->months = atoi(m.c_str());
    btc->days = atoi(d.c_str());

    for (int i = 0; i < 4; i++){
        if (!(isdigit(y[i])) || (btc->year > 2025 || btc->year < 2009)){
            std::cout << "years not right" << std::endl;
            return 1;
        }
    }
    for (int i = 0; i < 2; i++){
        if (!(isdigit(m[i])) || (btc->months > 12 || btc->months < 0)){
            std::cout << "months not right" << std::endl;
            return 1;
        }
    }
    for (int i = 0; i < 2; i++){
        if (!isdigit(d[i])){
            std::cout << "days not right" << std::endl;
            return 1;
        }
    }
    if ((btc->months == 4 || btc->months == 6 || btc->months == 9 || btc->months == 11) 
        && (btc->days > 30 || btc->days < 1)){
            std::cout << "day doesnt exist" << std::endl;
            return 1;
        }
    if ((btc->months == 1 || btc->months == 3 ||btc->months == 5 || btc->months == 7
        || btc->months == 8 || btc->months == 10 || btc->months == 12) && (btc->days > 31 || btc->days < 1)){
            std::cout << "day doesnt exist" << std::endl;
            return 1;
        }
    if (btc->months == 2){
        if (((btc->year % 4 == 0 && btc->year % 100 != 0) || (btc->year % 400 == 0)) && (btc->days > 29 || btc->days < 1)){
            std::cout << "febrary is not right" << std::endl;
            return 1;
        }
        else if(!((btc->year % 4 == 0 && btc->year % 100 != 0) || (btc->year % 400 == 0)) && (btc->days > 28 || btc->days < 1)){
            std::cout << "february is not right" << std::endl;
            return 1;
        }
    }
    return 0;
}

int btc::parsval(stru *btc){
    std::istringstream iss(btc->value);
    if (!(iss >> btc->val)){
        std::cout << "errorrrrrr conversion" << std::endl;
        return 1;
    }
    if (btc->val < 0 || btc->val > 1000){
        std::cout << "exchange rate value not right" << std::endl;
        return 1;
    }
    return 0;
}

void btc::fuseinput(stru *btc){
    btc->date.erase(4, 1);
    btc->date.erase(6, 1);
    btc->dateinputfused = atoi(btc->date.c_str());
}

void btc::apply_ExRate(stru *btc){
    std::map<int, float>::iterator it;
    it = data.find(btc->dateinputfused);
    std::string convertit;
    if (it != data.end()){
        btc->date.insert(4, "-");
        btc->date.insert(7, "-");
        std::cout << btc->date << " => " << btc->val << " = " << btc->val * it->second << std::endl;
    }
    else{
        it = data.lower_bound(btc->dateinputfused);
        it--;
        if (it != data.end()){
            btc->date.insert(4, "-");
            btc->date.insert(7, "-");
            std::cout << btc->date << " => " << btc->val << " = " << btc->val * it->second << std::endl;
        }
        else
            std::cout << "no element foundable" << std::endl;
    }
}
