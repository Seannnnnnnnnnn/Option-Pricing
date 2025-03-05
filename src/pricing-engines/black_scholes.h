#pragma once
#include "pricing_engine_base.h"



class BlackScholesPricingEngine : public PricingEngine 
{
private:
    const double sigma_;   // constant volatility in BS model

public:
    BlackScholesPricingEngine(double sigma) : sigma_(sigma) {}
    
    virtual double getVolatility(double S, double t) const override { return sigma_; }
    
    virtual double price(const Option& option, double S, double t) const override; 

    virtual double delta(const Option& option, double S, double t) const override;
    virtual double gamma(const Option& option, double S, double t) const override;
    virtual double theta(const Option& option, double S, double t) const override;
    virtual double vega(const Option& option, double S, double t) const override;
    virtual double rho(const Option& option, double S, double t) const override;
};