#include <gtest/gtest.h>
#include "../european_option.h"
#include "../option_type.h"
#include "../pricing-engines/black_scholes.h"


class EuropeanCallOptionTest : public ::testing::Test {
protected:
    // Set up the test environment, initializing values for the European Call Option
    void SetUp() override {
        strike_ = 100.0;
        underlying_ = 100.0;
        r_ = 0.05;
        T_ = 1.0;
        sigma_ = 0.2;
    
        pricingEngine_ = std::make_shared<BlackScholesPricingEngine>(sigma_); 
        option_ = new EuropeanOption(strike_, r_, T_, OptionType::Call, pricingEngine_);
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
TEST_F(EuropeanCallOptionTest, PriceTest) {
    // Expected price calculated manually or via a reference
    double expected_price = 10.4506;
    EXPECT_NEAR(option_->price(underlying_, 0.0), expected_price, 0.0001);
}

// Test Delta
TEST_F(EuropeanCallOptionTest, DeltaTest) {
    double expected_delta = 0.6368;
    EXPECT_NEAR(option_->delta(underlying_, 0.0), expected_delta, 0.0001);
}

// Test Gamma
TEST_F(EuropeanCallOptionTest, GammaTest) {
    double expected_gamma = 0.0187;
    EXPECT_NEAR(option_->gamma(underlying_, 0.0), expected_gamma, 0.0001);
}

// Test Theta
TEST_F(EuropeanCallOptionTest, ThetaTest) {
    double expected_theta = -6.4140;
    EXPECT_NEAR(option_->theta(underlying_, 0.0), expected_theta, 0.0001);
}

// Test Rho
TEST_F(EuropeanCallOptionTest, RhoTest) {
    double expected_rho = 53.2325;
    EXPECT_NEAR(option_->rho(underlying_, 0.0), expected_rho, 0.01);
}

// Test Vega
TEST_F(EuropeanCallOptionTest, VegaTest) {
    double expected_vega = 37.5240;
    EXPECT_NEAR(option_->vega(underlying_, 0.0), expected_vega, 0.0001);
}
