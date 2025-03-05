/* Implements a European Option */
#pragma once

#include <memory>
#include "option_base.h"
#include "payoff.h"


class EuropeanOption : public Option 
{
    public: 
        EuropeanOption(double strike, double r, double T, OptionType type, PricingEngine* pricingEngine) : 
            Option(strike, r, T, type, pricingEngine) 
            {
                payOff_ = std::make_unique<StrikedPayOff>(strike, type);
            }

        virtual ~EuropeanOption() {};
};  