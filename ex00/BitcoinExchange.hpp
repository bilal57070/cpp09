#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

# include <iostream>
# include <map>
# include <fstream>
# include <cstdlib>
# include <sstream>
# include <iomanip>


struct stru {
    std::map<std::string, float> data;
    std::string line;
    std::string date;
    std::string value;
    float val;
    int year;
    int months;
    int days;
};

void sort_data(stru *e);
void print_map(std::map<std::string, float> &c);
void read_input(char *av, stru *c);
int  pars(stru *btc);
int  parsval(stru *btc);


#endif