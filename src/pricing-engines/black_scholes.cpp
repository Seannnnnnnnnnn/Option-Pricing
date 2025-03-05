#include "black_scholes.h"
#include <cmath>


// Black-Scholes price calculation
double BlackScholesPricingEngine::price(const Option& option, double S, double t) const {
    double K = option.getStrike();
    double T = option.getT();
    double r = option.getR(); 
    double sigma = getVolatility(S, t);
    OptionType type = option.getType();

    double d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * (T - t)) / (sigma * sqrt(T - t));
    double d2 = d1 - sigma * sqrt(T - t);
    double call_price = S * stdNormalCDF(d1) - K * exp(-r * (T - t)) * stdNormalCDF(d2);


    return (type == OptionType::Call) ? call_price : call_price + K * exp(-r * T) - S;
}


// Black-Scholes Delta
double BlackScholesPricingEngine::delta(const Option& option, double S, double t) const {
    
    double K = option.getStrike();
    double T = option.getT();
    double r = option.getR(); 
    double sigma = getVolatility(S, t);
    OptionType type = option.getType();

    double d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * (T - t)) / (sigma * sqrt(T - t));

    return  (type == OptionType::Call) ? stdNormalCDF(d1) : stdNormalCDF(d1) - 1;     
}


// Black-Scholes Gamma
double BlackScholesPricingEngine::gamma(const Option& option, double S, double t) const {
    double K = option.getStrike();
    double T = option.getT();
    double r = option.getR(); 
    double sigma = getVolatility(S, t);

    double d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * (T - t)) / (sigma * sqrt(T - t));

    return stdNormalPDF(d1) / (S * sigma * sqrt(T - t));
}

// Black-Scholes Theta
double BlackScholesPricingEngine::theta(const Option& option, double S, double t) const {
    double K = option.getStrike();
    double T = option.getT();
    double r = option.getR(); 
    double sigma = getVolatility(S, t);
    OptionType type = option.getType();

    double d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * (T - t)) / (sigma * sqrt(T - t));
    double d2 = d1 - sigma * sqrt(T - t);

    double firstTerm = -(S * stdNormalPDF(d1) * sigma) / (2 * sqrt(T - t));
    double secondTerm = r * K * exp(-r * (T - t)) * stdNormalCDF(type == OptionType::Call ? d2 : -d2);
    return firstTerm - (type == OptionType::Call ? secondTerm : -secondTerm);
}

// Black-Scholes Vega
double BlackScholesPricingEngine::vega(const Option& option, double S, double t) const {
    double K = option.getStrike();
    double T = option.getT();
    double r = option.getR(); 
    double sigma = getVolatility(S, t);

    double d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * (T - t)) / (sigma * sqrt(T - t));

    return S * stdNormalPDF(d1) * sqrt(T - t);
}

// Black-Scholes Rho
double BlackScholesPricingEngine::rho(const Option& option, double S, double t) const {
    double K = option.getStrike();
    double T = option.getT();
    double r = option.getR(); 
    double sigma = getVolatility(S, t);
    OptionType type = option.getType();

    double d2 = (log(S / K) + (r - 0.5 * sigma * sigma) * (T - t)) / (sigma * sqrt(T - t));

    if (type == OptionType::Call) {
        return K * (T - t) * exp(-r * (T - t)) * stdNormalCDF(d2);
    } else { // Put option
        return -K * (T - t) * exp(-r * (T - t)) * stdNormalCDF(-d2);
    }
}


