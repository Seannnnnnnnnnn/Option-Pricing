/* Implements an American Option */
#pragma once

#include "option_base.h"

class AmericanOption : public Option
{
    public: 
        AmericanOption(double strike, double r, double T, OptionType type, std::shared_ptr<PricingEngine> pricingEngine) :
            Option(strike, r, T, type, pricingEngine) 
            {
                payOff_ = std::make_unique<StrikedPayOff>(strike, type);
            }
        
        virtual ~AmericanOption() {}

        bool canExercise(double t) const override { return t <= T_; } 
};