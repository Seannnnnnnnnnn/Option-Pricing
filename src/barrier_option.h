#include "option_base.h"
#include "payoff.h"
#include "option_type.h"


class BarrierOption : public Option 
{
    public: 
        BarrierOption(double strike, double r, 
                      double T, 
                      OptionType type,
                      BarrierType barrierType,
                      BarrierDirection barrierDirection,    
                      std::shared_ptr<PricingEngine> pricingEngine) : 
           
            Option(strike, r, T, type, pricingEngine) 
            {
                payOff_ = std::make_unique<StrikedPayOff>(strike, type);
            }
        
        virtual ~BarrierOption() {};

        bool canExercise(double t) const override { return t == T_; }
};