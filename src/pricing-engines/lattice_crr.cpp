#include "lattice_crr.h"
#include "../option_base.h"
#include <vector>
#include <cmath>

// Lattice-based CRR pricing engine using stored intermediate calculations

double LatticeCRRPricingEngine::price(const Option& option, double S, double t, double q) {
    double dt = option.getT() / static_cast<double>(n_);

    double u = std::exp(sigma_ * std::sqrt(dt));
    double d = 1.0 / u;

    double disc = std::exp(-option.getR() * dt);
    double p = (std::exp((option.getR() - q) * dt) - d) / (u - d);

    // Compute terminal node prices
    for (size_t i = 0; i <= n_; ++i) {
        lattice_[n_][i].underlyingPrice = S * std::pow(u, n_ - i) * std::pow(d, i);
        lattice_[n_][i].optionPrice = option.PayOff(lattice_[n_][i].underlyingPrice);
    }

    // Step backwards through the tree
    for (size_t j = n_; j-- > 0; ) {
        for (size_t i = 0; i <= j; ++i) {
            lattice_[j][i].underlyingPrice = S * std::pow(u, j - i) * std::pow(d, i);
            lattice_[j][i].optionPrice = disc * (p * lattice_[j + 1][i].optionPrice + (1.0 - p) * lattice_[j + 1][i + 1].optionPrice);

            if (option.canExercise(j * dt)) {
                double earlyExercise = option.PayOff(lattice_[j][i].underlyingPrice);
                lattice_[j][i].optionPrice = std::max(lattice_[j][i].optionPrice, earlyExercise);
            }
        }
    }

    return lattice_[0][0].optionPrice;  // Return root node price
}


// TODO: implement the greeks

double LatticeCRRPricingEngine::delta(const Option& option, double S, double t, double q) const { return 0.0; }
double LatticeCRRPricingEngine::gamma(const Option& option, double S, double t, double q) const { return 0.0; }
double LatticeCRRPricingEngine::theta(const Option& option, double S, double t, double q) const { return 0.0; }
double LatticeCRRPricingEngine::vega(const Option& option, double S, double t, double q) const { return 0.0; }
double LatticeCRRPricingEngine::rho(const Option& option, double S, double t, double q) const { return 0.0; }
