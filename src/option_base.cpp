#include "option_base.h"
#include <cmath>


double OptionBase::normalCDF(double x) const {
    return 0.5 * std::erfc(-x / std::sqrt(2));
}