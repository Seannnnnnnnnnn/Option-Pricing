#include "european_option.h"
#include <cmath>

double EuropeanOption::price() const {
    // returns option price via black scholes & put-call parity
    
    double S_ = underlying_;
    
    double sigma_sqrt_T = sigma_ * sqrt(T_); 
    double d1 = ( log (S_/strike_) + ( r_ + sigma_ * sigma_ * 0.5 ) * T_ ) / sigma_sqrt_T ;
    double d2 = d1 - sigma_sqrt_T; 
    double call_price = S_ * normalCDF(d1) - strike_ * exp(-r_ * T_) * normalCDF(d2); 

    return (getType() == OptionType::Call) ? call_price : call_price + strike_ * exp(-r_ * T_) - S_;
}