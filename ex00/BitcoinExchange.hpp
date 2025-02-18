#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

# include <iostream>
# include <map>
# include <fstream>
# include <cstdlib>
# include <sstream>
# include <iomanip>


struct stru {
    std::string datecsv;
    std::string line;
    std::string date;
    std::string value;
    float val;
    int year;
    int months;
    int days;
    int datecsvfused;
    int dateinputfused;
};

class btc{
    public:
        btc();
        ~btc();
        btc(btc const &cp);
        btc& operator=(btc const &cpi);

        void sort_data(stru *e);
        void print_map(std::map<std::string, float> &c);
        void read_input(char *av, stru *c);
        int  pars(stru *btc);
        int  parsval(stru *btc);
        void fusecsv(std::string date, stru *btc);
        void fuseinput(stru *btc);
        void apply_ExRate(stru *btc);

    private:
        std::map<int, float> data;
};

#endif