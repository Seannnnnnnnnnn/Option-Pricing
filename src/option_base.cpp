#include "option_base.h"
#include <cmath>


double OptionBase::normalCDF(double x) const {
    return 0.5 * std::erfc(-x / std::sqrt(2));
}



double OptionBase::normalPDF(double x) const {
    return std::exp(-0.5 * x * x) / std::sqrt(2 * M_PI);
}