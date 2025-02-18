#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    stru bt;
    btc Btc;
    (void)av;
    if (ac){
        Btc.sort_data(&bt);
        Btc.read_input(av[1], &bt);
    }
    else
        std::cout << "error: number of arg" << std::endl;
    return 0;
}