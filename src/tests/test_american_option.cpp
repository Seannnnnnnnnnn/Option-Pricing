#include <gtest/gtest.h>
#include "testing_constants.h"
#include "../american_option.h"
#include "../option_type.h"
#include "../pricing-engines/lattice_crr.h"

// TODO: write more unit tests! 

class AmericanCallOptionTest : public ::testing::Test {
protected:
    // Set up the test environment, initializing values for the European Call Option
    void SetUp() override {
        strike_ = 52.0;
        underlying_ = 50.0;
        r_ = 0.05;
        T_ = 2.0;
        sigma_ = 0.3;
    
        pricingEngine_ = std::make_shared<LatticeCRRPricingEngine>(sigma_); 
        option_ = new AmericanOption(strike_, r_, T_, OptionType::Call, pricingEngine_);
    }

    // Tear down the environment after each test
    void TearDown() override {
        delete option_;
    }

    double strike_;
    double underlying_;
    double r_;
    double T_;
    double sigma_;
    Option* option_;
    std::shared_ptr<PricingEngine> pricingEngine_; 
};

// Test pricing
TEST_F(AmericanCallOptionTest, PriceTest) {
    // Expected price calculated manually or via a reference
    double expected_price = 9.7442;
    EXPECT_NEAR(option_->price(underlying_, 0.0), expected_price, MIN_TICK_SIZE);
}
