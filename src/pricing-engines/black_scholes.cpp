#include "black_scholes.h"
#include "../option_base.h"
#include <cmath>

// Black-Scholes price calculation
double BlackScholesPricingEngine::price(const Option& option, double S, double t, double q) const {
    double K = option.getStrike();
    double T = option.getT();
    double r = option.getR(); 
    double sigma = getVolatility(S, t);
    OptionType type = option.getType();

    double d1 = (log(S / K) + (r - q + 0.5 * sigma * sigma) * (T - t)) / (sigma * sqrt(T - t));
    double d2 = d1 - sigma * sqrt(T - t);
    double call_price = S * exp(-q * (T - t)) * stdNormalCDF(d1) - K * exp(-r * (T - t)) * stdNormalCDF(d2);

    return (type == OptionType::Call) ? call_price : call_price + K * exp(-r * (T - t)) - S * exp(-q * (T - t));
}

// Black-Scholes Delta
double BlackScholesPricingEngine::delta(const Option& option, double S, double t, double q) const {
    double K = option.getStrike();
    double T = option.getT();
    double r = option.getR(); 
    double sigma = getVolatility(S, t);
    OptionType type = option.getType();

    double d1 = (log(S / K) + (r - q + 0.5 * sigma * sigma) * (T - t)) / (sigma * sqrt(T - t));

    return (type == OptionType::Call) ? exp(-q * (T - t)) * stdNormalCDF(d1) : exp(-q * (T - t)) * (stdNormalCDF(d1) - 1);
}

// Black-Scholes Gamma
double BlackScholesPricingEngine::gamma(const Option& option, double S, double t, double q) const {
    double K = option.getStrike();
    double T = option.getT();
    double r = option.getR(); 
    double sigma = getVolatility(S, t);

    double d1 = (log(S / K) + (r - q + 0.5 * sigma * sigma) * (T - t)) / (sigma * sqrt(T - t));

    return (stdNormalPDF(d1) * exp(-q * (T - t))) / (S * sigma * sqrt(T - t));
}

// Black-Scholes Theta
double BlackScholesPricingEngine::theta(const Option& option, double S, double t, double q) const {
    double K = option.getStrike();
    double T = option.getT();
    double r = option.getR(); 
    double sigma = getVolatility(S, t);
    OptionType type = option.getType();

    double d1 = (log(S / K) + (r - q + 0.5 * sigma * sigma) * (T - t)) / (sigma * sqrt(T - t));
    double d2 = d1 - sigma * sqrt(T - t);

    double firstTerm = -(S * exp(-q * (T - t)) * stdNormalPDF(d1) * sigma) / (2 * sqrt(T - t));
    double secondTerm = r * K * exp(-r * (T - t)) * stdNormalCDF(type == OptionType::Call ? d2 : -d2);
    double thirdTerm = q * S * exp(-q * (T - t)) * stdNormalCDF(type == OptionType::Call ? d1 : -d1);
    
    return firstTerm - (type == OptionType::Call ? secondTerm - thirdTerm : -secondTerm + thirdTerm);
}

// Black-Scholes Vega
double BlackScholesPricingEngine::vega(const Option& option, double S, double t, double q) const {
    double K = option.getStrike();
    double T = option.getT();
    double r = option.getR(); 
    double sigma = getVolatility(S, t);

    double d1 = (log(S / K) + (r - q + 0.5 * sigma * sigma) * (T - t)) / (sigma * sqrt(T - t));

    return S * exp(-q * (T - t)) * stdNormalPDF(d1) * sqrt(T - t);
}

// Black-Scholes Rho
double BlackScholesPricingEngine::rho(const Option& option, double S, double t, double q) const {
    double K = option.getStrike();
    double T = option.getT();
    double r = option.getR(); 
    double sigma = getVolatility(S, t);
    OptionType type = option.getType();

    double d2 = (log(S / K) + (r - q - 0.5 * sigma * sigma) * (T - t)) / (sigma * sqrt(T - t));
    
    return (type == OptionType::Call) ? K * (T - t) * exp(-r * (T - t)) * stdNormalCDF(d2) : -K * (T - t) * exp(-r * (T - t)) * stdNormalCDF(-d2);
}
