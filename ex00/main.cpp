#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    stru btc;
    (void)av;
    if (ac){
        sort_data(&btc);
        read_input(av[1], &btc);
    }
    else
        std::cout << "error: number of arg" << std::endl;
    return 0;
}