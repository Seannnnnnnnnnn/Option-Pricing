/* Implements a European Option */
#pragma once

#include "option_base.h"
#include "payoff.h"

class EuropeanOption : public OptionBase 
{
    public: 
        EuropeanOption(double strike, double underlying, double r, double T, double sigma, OptionType type) : 
            OptionBase(strike, underlying, r, T, sigma, type) {}

        virtual double price() const override; 
        
        virtual double delta() const override;
        virtual double gamma() const override;
        virtual double theta() const override;
        virtual double vega() const override;
        virtual double rho() const override;
};  