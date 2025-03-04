#include <iostream>
#include "../option.h"


int main() {
    Option option(10, 0.05, 1.5, 11, 0.4, true);
    std::cout << option.price_black_scholes() << std::endl;
    return 0;
}