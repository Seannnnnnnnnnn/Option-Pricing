#pragma once
#include <algorithm>


class PayOff
{
public:
    PayOff() {}; 
    virtual ~PayOff() {};
    virtual double operator() (const double S) const = 0; 
};


class PayOffCall : public PayOff
{
    private:
        double Strike_;

    public: 
        PayOffCall(double Strike) : Strike_(Strike) {}; 
        virtual ~PayOffCall() {};
        virtual double operator() (const double S) const override { return std::max(S - Strike_, 0.0); }; 
};


class PayOffPut : public PayOff
{
    private:
        double Strike_;

    public: 
        PayOffPut(double Strike) : Strike_(Strike) {}; 
        virtual ~PayOffPut() {};
        virtual double operator() (const double S) const override { return std::max(Strike_ - S, 0.0); }; 
};