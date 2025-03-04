/* base class that all Options inheret from */
#pragma once
#include "option_type.h"


class OptionBase 
{
    protected: 
        double strike_;
        double underlying_;
        double r_;
        double T_; 
        double sigma_; 
        OptionType type_; 

        double normalCDF(double x) const;  // internal method for normal CDF
        double normalPDF(double x) const;  // internal method for normal PDF

    public: 
        OptionBase(double strike, double underlying, double r, double T, double sigma, OptionType type) : 
            strike_(strike), underlying_(underlying), r_(r), T_(T), sigma_(sigma), type_(type) {}

        virtual ~OptionBase() {}; 

        virtual double delta() const = 0;
        virtual double gamma() const = 0;
        virtual double theta() const = 0;
        virtual double rho() const = 0;
        virtual double vega() const = 0;

        virtual double price() const = 0;  // abstract pricing function to be implemented 

        double getStrike() const { return strike_; }
        double getUnderlying() const { return underlying_; }
        double getR() const { return r_; }
        double getT() const { return T_; }
        double getSigma() const { return sigma_; }
        OptionType getType() const { return type_; }
};
