/* 
Lattice based pricing engine described by Cox, Ross, Rubenstein: https://en.wikipedia.org/wiki/Binomial_options_pricing_model 
Suitable for American - Style options pricing. 
*/
#pragma once
#include <stddef.h>
#include <vector>
#include "pricing_engine_base.h"


class LatticeCRRPricingEngine : public PricingEngine 
{
    struct LatticeNode 
    {
        double optionPrice; 
        double underlyingPrice; 
    };
    
    
    private:
        double sigma_;  // assumed constant vol
        size_t n_;      // represents height of binary tree in lattice
        std::vector<std::vector<LatticeNode>> lattice_;  // represents underlying lattice structure used for pricing
    
    public: 
        LatticeCRRPricingEngine(double sigma, size_t num_steps=40) : 
            sigma_(sigma), 
            n_(num_steps),
            lattice_(num_steps + 1, std::vector<LatticeNode>(num_steps + 1)) { }

        virtual double getVolatility(double S, double t) const override { return sigma_; }
        virtual void setVolatility(double sigma) { sigma_ = sigma; }
        
        virtual double price(const Option& option, double S, double t, double q) const override; 

        virtual double delta(const Option& option, double S, double t, double q) const override;
        virtual double gamma(const Option& option, double S, double t, double q) const override;
        virtual double theta(const Option& option, double S, double t, double q) const override;
        virtual double vega(const Option& option, double S, double t, double q) const override;
        virtual double rho(const Option& option, double S, double t, double q) const override;
};