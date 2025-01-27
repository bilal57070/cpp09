#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

# include <iostream>
# include <map>
# include <fstream>


struct stru {
    std::map<std::string, int> data;
};

void sort_data(stru *e, char **av);


#endif