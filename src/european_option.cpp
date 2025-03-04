#include "european_option.h"
#include <cmath>
// TODO: refactor the below functions to all use the getter methods 

double EuropeanOption::price() const {
    // returns option price via black scholes & put-call parity
    
    double S_ = underlying_;
    
    double sigma_sqrt_T = sigma_ * sqrt(T_); 
    double d1 = ( log (S_/strike_) + ( r_ + sigma_ * sigma_ * 0.5 ) * T_ ) / sigma_sqrt_T ;
    double d2 = d1 - sigma_sqrt_T; 
    double call_price = S_ * normalCDF(d1) - strike_ * exp(-r_ * T_) * normalCDF(d2); 

    return (getType() == OptionType::Call) ? call_price : call_price + strike_ * exp(-r_ * T_) - S_;
}


double EuropeanOption::delta() const {
    
    double S_ = underlying_;
    double sigma_sqrt_T = sigma_ * sqrt(T_); 
    double d1 = ( log (S_/strike_) + ( r_ + sigma_ * sigma_ * 0.5 ) * T_ ) / sigma_sqrt_T ;

    return (getType() == OptionType::Call) ? normalCDF(d1) : normalCDF(d1) - 1; 
}


double EuropeanOption::gamma() const {
    
    double S_ = underlying_;
    double d1 = (std::log(S_ / strike_) + (r_ + 0.5 * sigma_ * sigma_) * T_) / (sigma_ * std::sqrt(T_));
        
    return normalPDF(d1) / (S_ * sigma_ * std::sqrt(T_));
}


double EuropeanOption::theta() const {
    double S = getUnderlying();
    double K = getStrike();
    double r = getR();
    double T = getT();
    double sigma = getSigma();
    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);

    double term1 = -S * normalPDF(d1) * sigma / (2 * std::sqrt(T));
    double term2 = r * K * std::exp(-r * T) * normalCDF(d2);
    
    return (getType() == OptionType::Call) ? term1 - term2 : term1 + term2;
}


double EuropeanOption::rho() const {
    double S = getUnderlying();
    double K = getStrike();
    double r = getR();
    double T = getT();
    double sigma = getSigma();
    double d2 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T)) - sigma * std::sqrt(T);
    
    return (getType() == OptionType::Call) ? K * T * std::exp(-r * T) * normalCDF(d2) : -K * T * std::exp(-r * T) * normalCDF(-d2);
}


double EuropeanOption::vega() const {
    double S = getUnderlying();
    double K = getStrike();
    double r = getR();
    double T = getT();
    double sigma = getSigma();
    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));

    return S * normalPDF(d1) * std::sqrt(T);
}