/* Implements a European Option */
#pragma once

#include "option_base.h"
#include "payoff.h"


class EuropeanOption : public Option 
{
    public: 
        EuropeanOption(double strike, double r, double T, OptionType type, PricingEngine* pricingEngine) : 
            Option(strike, r, T, type, pricingEngine) {}
};  