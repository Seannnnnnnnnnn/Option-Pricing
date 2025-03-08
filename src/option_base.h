/* 
Abstract base class that all Options inheret from. Note that the option class represents the Option contract, 
and thus represents the stored information on a contract that is necessary for its pricing; namely strike, payoff, 
expiration and reference date.

To price the contract, clients attach a PricingEngine, which handles vol and pricing logic. 
*/
#pragma once
#include <memory>
#include "payoff.h"
#include "option_type.h"
#include "pricing-engines/pricing_engine_base.h"


class Option 
{
    protected: 
        double strike_;
        double r_;  // represents risk free rate. In reality, this should be some reference rate index like BBSW
        double T_; 
        OptionType type_; 
        std::shared_ptr<PricingEngine> pricingEngine_;
        std::unique_ptr<PayOff> payOff_;  // unique ptr, as different subclasses create ptr on instantiation

    public: 
        Option(double strike, double r, double T, OptionType type, std::shared_ptr<PricingEngine> pricingEngine) : 
            strike_(strike), r_(r), T_(T), type_(type), pricingEngine_(std::move(pricingEngine)), payOff_(nullptr) {}

        virtual ~Option() {}; 

        double getStrike() const { return strike_; }
        double getR() const { return r_; }
        double getT() const { return T_; }
        OptionType getType() const { return type_; }
        
        std::shared_ptr<PricingEngine> getPricingEngine() const { return pricingEngine_; } 
        void setPricingEngine(std::shared_ptr<PricingEngine> pricingEngine) { pricingEngine_ = std::move(pricingEngine); }
        
        // overlays for the pricing engine
        double price(double S, double t) const { return pricingEngine_->price(*this, S, t); }
        double delta(double S, double t) const { return pricingEngine_->delta(*this, S, t); }
        double gamma(double S, double t) const { return pricingEngine_->gamma(*this, S, t); }
        double theta(double S, double t) const { return pricingEngine_->theta(*this, S, t); }
        double vega(double S, double t) const { return pricingEngine_->vega(*this, S, t); }
        double rho(double S, double t) const { return pricingEngine_->rho(*this, S, t); }

        // overlays for the payoff function
        double PayOff(double S) const { return (*payOff_)(S); }

        // for handling early exercise logic in certain pricing engines
        virtual bool canExercise(double t) const = 0;
};
