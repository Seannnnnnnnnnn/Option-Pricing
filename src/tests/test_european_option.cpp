#include <iostream>
#include "../european_option.h"


int main() {
    EuropeanOption option(10.0, 8.0, 0.041, 1.5, 0.5, OptionType::Call);
    std::cout<<"call price: " << option.price() << std::endl;
    std::cout<<"call delta: " << option.delta() << std::endl;
}