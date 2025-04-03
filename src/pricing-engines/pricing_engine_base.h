/*
Abstract Base Class for a pricing method based on a volatility model. Given an option contract, 
can provide a price and risk sensitivities based on contract parameters. 

Volatility model is defined by the getVolatility() ABM, which computes volatility 
*/
#pragma once


class Option;  // forward declaration


class PricingEngine
{
    protected: 
        double stdNormalCDF(double x) const;  // internal method for normal CDF
        double stdNormalPDF(double x) const;  // internal method for normal PDF

    public: 
        virtual ~PricingEngine() = default; 
        
        virtual double getVolatility(double S, double t) const = 0;  // ABM for representing volatility at a point in time
        virtual double price(const Option& option, double S, double t, double q=0.0) const = 0;
        
        virtual double delta(const Option& option, double S, double t, double q=0.0) const = 0;
        virtual double gamma(const Option& option, double S, double t, double q=0.0) const = 0;
        virtual double theta(const Option& option, double S, double t, double q=0.0) const = 0;
        virtual double vega(const Option& option, double S, double t, double q=0.0) const = 0;
        virtual double rho(const Option& option, double S, double t, double q=0.0) const = 0;
};
