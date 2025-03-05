#include "pricing_engine_base.h"
#include <cmath>


double PricingEngine::stdNormalCDF(double x) const {
    return 0.5 * std::erfc(-x / std::sqrt(2));
}


double PricingEngine::stdNormalPDF(double x) const {
    return std::exp(-0.5 * x * x) / std::sqrt(2 * M_PI);
}