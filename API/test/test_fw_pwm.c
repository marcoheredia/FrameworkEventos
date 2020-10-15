#include "unity.h"
#include "fw_pwm.h"

//*****Test for fw_pwm_set*****/
TEST_CASE("fw_pwm_set_negativepin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_pwm_set(-1, 0, 0));
}

TEST_CASE("fw_pwm_set_wrongpin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_pwm_set(34, 0, 0));
    TEST_ASSERT_FALSE(fw_pwm_set(38, 0, 0));
    TEST_ASSERT_FALSE(fw_pwm_set(41, 0, 0));
}

TEST_CASE("fw_pwm_set_rightpin", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_pwm_set(3, 50, 50));
    TEST_ASSERT_TRUE(fw_pwm_set(15, 200, 0));
    TEST_ASSERT_TRUE(fw_pwm_set(25, 1000, 100));
}

TEST_CASE("fw_pwm_set_negativefreq", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_pwm_set(4, -40, 0));
}

TEST_CASE("fw_pwm_set_negativeduty", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_pwm_set(5, 50, -20));
}

TEST_CASE("fw_pwm_set_wrongduty", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_pwm_set(5, 50, 110));
}

TEST_CASE("fw_pwm_set_zerofrequency", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_pwm_set(3, 0, 30));
}
