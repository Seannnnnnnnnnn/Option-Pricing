#pragma once
#include <algorithm>


class PayOff
{
public:
    PayOff() {}; 
    virtual ~PayOff() {};
    virtual double operator() (const double S) const = 0; 
};


class StrikedPayOff : public PayOff
{
    private: 
        double K_;
        OptionType type_;
    
    public:     
        StrikedPayOff(double Strike, OptionType type) : K_(Strike), type_(type) {};
        virtual ~StrikedPayOff() {};
        virtual double operator() (const double S) const override { return (type_ == OptionType::Call) ? std::max(S - K_, 0.0) : std::max(K_ - S, 0.0); }
};
