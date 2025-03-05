/* 
base class that all Options inheret from. Note that the option class represents the Option contract, 
and does not contian any logic related to pricing or volatility.

Pricing and volatility logic is contained in the PricingEngine which is passed to contract.
*/
#pragma once
#include "option_type.h"
#include "pricing-engines/pricing_engine_base.h"


class Option 
{
    protected: 
        double strike_;
        double r_;
        double T_; 
        OptionType type_; 
        PricingEngine* pricingEngine_;

    public: 
        Option(double strike, double r, double T, OptionType type, PricingEngine* pricingEngine) : 
            strike_(strike), r_(r), T_(T), type_(type), pricingEngine_(pricingEngine) {}

        virtual ~Option() {}; 

        double getStrike() const { return strike_; }
        double getR() const { return r_; }
        double getT() const { return T_; }
        OptionType getType() const { return type_; }
        
        PricingEngine* getPricingEngine() const { return pricingEngine_; } 
        void setPricingEngine(PricingEngine* pricingEngine) { pricingEngine_ = pricingEngine; }
        
        // overlays for the pricing engine
        double price(double S, double t) const { return pricingEngine_->price(*this, S, t); }
        double delta(double S, double t) const { return pricingEngine_->delta(*this, S, t); }
        double gamma(double S, double t) const { return pricingEngine_->gamma(*this, S, t); }
        double theta(double S, double t) const { return pricingEngine_->theta(*this, S, t); }
        double vega(double S, double t) const { return pricingEngine_->vega(*this, S, t); }
        double rho(double S, double t) const { return pricingEngine_->rho(*this, S, t); }
};
