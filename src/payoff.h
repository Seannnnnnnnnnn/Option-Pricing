#pragma once


class PayOff
{
public:
    PayOff() {}; 
    virtual ~PayOff() {};

    virtual double operator() (const double S) = 0; 
};