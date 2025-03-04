#pragma once
#include <algorithm>
#include <utility>


class Option
{
    private: 
        double Strike_;
        double r_;
        double T_;
        double S_; 
        double sigma_;
        bool isCall_;

        double N(double x, double mean, double stddev) const;  // internal method for normal CDF

    public:
        Option(double Strike, double r, double T, double S, double sigma, bool isCall) : 
            Strike_(Strike), r_(r), T_(T), S_(S), sigma_(sigma), isCall_(isCall) {}
        
        Option(const Option& rhs) : 
            Strike_(rhs.Strike_), r_(rhs.r_), T_(rhs.T_), S_(rhs.S_), sigma_(rhs.sigma_), isCall_(rhs.isCall_) {}
        
        Option& operator=(const Option& rhs) {
            if (this == &rhs)
                return *this;    
            Strike_ = rhs.get_strike();
            r_ = rhs.get_r();
            T_ = rhs.get_T();
            S_ = rhs.get_underlying();
            sigma_ = rhs.get_vol();
            isCall_ = rhs.get_is_call();
            return *this;  // rhs goes out of scope, freeing old memory
            }

        virtual ~Option() {}; 


        double get_strike() const { return Strike_; }
        double get_r() const { return r_; }
        double get_T() const { return T_; }
        double get_underlying() const { return S_; }
        double get_vol() const { return sigma_; }
        bool get_is_call() const { return isCall_; }

        double price_black_scholes() const;
};