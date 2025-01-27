#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    stru btc;

    if (ac == 2){
        sort_data(&btc, av);
    }
    else
        std::cout << "error: number of arg" << std::endl;
}