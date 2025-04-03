#include "lattice_crr.h"
#include "../option_base.h"
#include <vector>
#include <cmath>

// TODO: update to use the lattice structure


double LatticeCRRPricingEngine::price(const Option& option, double S, double t, double q) const {
    // Time step size
    double dt = option.getT() / static_cast<double>(n_);
    
    // Up and down factors (CRR Model)
    double u = std::exp(sigma_ * std::sqrt(dt));
    double d = 1.0 / u;
    
    // Risk-neutral probability
    double disc = std::exp(-option.getR() * dt);
    double p = (std::exp((option.getR() - q) * dt) - d) / (u - d);
    
    // Lattice storage
    std::vector<double> prices(n_ + 1);
    std::vector<double> values(n_ + 1);
    
    // Compute terminal node prices
    for (size_t i = 0; i <= n_; ++i) {
        prices[i] = S * std::pow(u, static_cast<int>(n_ - i)) * std::pow(d, static_cast<int>(i));
        values[i] = option.PayOff(prices[i]); // Compute payoff at expiry
    }
    
    // Step backwards through the tree
    for (int j = static_cast<int>(n_) - 1; j >= 0; --j) {
        for (size_t i = 0; i <= static_cast<size_t>(j); ++i) {
            prices[i] = S * std::pow(u, static_cast<int>(j - i)) * std::pow(d, static_cast<int>(i));
            
            // Risk-neutral discounted expectation
            values[i] = disc * (p * values[i] + (1.0 - p) * values[i + 1]);
            
            // Check early exercise
            if (option.canExercise(j * dt)) {
                double earlyExercise = option.PayOff(prices[i]);
                values[i] = std::max(values[i], earlyExercise);
            }
        }
    }
    
    return values[0]; // The root node contains the option price
}


// TODO: implement the greeks

double LatticeCRRPricingEngine::delta(const Option& option, double S, double t, double q) const { return 0.0; }
double LatticeCRRPricingEngine::gamma(const Option& option, double S, double t, double q) const { return 0.0; }
double LatticeCRRPricingEngine::theta(const Option& option, double S, double t, double q) const { return 0.0; }
double LatticeCRRPricingEngine::vega(const Option& option, double S, double t, double q) const { return 0.0; }
double LatticeCRRPricingEngine::rho(const Option& option, double S, double t, double q) const { return 0.0; }
