#pragma once


class PayOff
{
public:
    PayOff() {}; 
    virtual ~PayOff() {};
    virtual double operator() (const double S) = 0; 
};


class PayOffCall : public PayOff
{
    private:
        double Strike_;

    public: 
        PayOffCall(double Strike) : Strike_(Strike) {}; 
        virtual ~PayOffCall() {};
        virtual double operater() (const double S) const { return std::max(S - Strike_, 0); }; 
};


class PayOffPut : public PayOff
{
    private:
        double Strike_;

    public: 
        PayOffPut(double Strike) : Strike_(Strike) {}; 
        virtual ~PayOffPut() {};
        virtual double operater() (const double S) const { return std::max(Strike_ - S, 0); }; 
};