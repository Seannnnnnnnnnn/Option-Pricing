#include "option.h"
#include <cmath>


double Option::N(double x, double mean = 0.0, double stddev = 1.0) const {
    return 0.5 * (1.0 + std::erf((x - mean) / (stddev * std::sqrt(2.0))));
}


double Option::price_black_scholes() const {
    // prices as if it is call option. If a put, we return a transformation according to put-call partiy

    double sigma_sqrt_T = sigma_ * sqrt(T_); 
    double d1 = ( log (S_/Strike_) + ( r_ + sigma_ * sigma_ * 0.5 ) * T_ ) / sigma_sqrt_T ;
    double d2 = d1 - sigma_sqrt_T; 

    double call_price = S_ * N(d1) - Strike_ * exp(-r_ * T_) * N(d2); 

    if (isCall_)
        return call_price; 
    else
        return call_price + Strike_ - S_;  // put-call parity
}