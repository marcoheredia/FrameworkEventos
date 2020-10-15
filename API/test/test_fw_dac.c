#include "unity.h"
#include "fw_dac.h"

TEST_CASE("fw_dac_enable_negativepin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_dac_enable(-1));
}

TEST_CASE("fw_dac_enable_wrongpin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_dac_enable(23));
}

TEST_CASE("fw_dac_enable_rightpin25", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_dac_enable(25));
}

TEST_CASE("fw_dac_enable_rightpin26", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_dac_enable(26));
}


TEST_CASE("fw_dac_output_voltage_negativepin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_dac_output_voltage(-1,0));
}

TEST_CASE("fw_dac_output_voltage_wrongpin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_dac_output_voltage(23,0));
}

TEST_CASE("fw_dac_output_voltage_rightpin25", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_dac_output_voltage(25,0));
}

TEST_CASE("fw_dac_output_voltage_rightpin26", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_dac_output_voltage(26,0));
}

TEST_CASE("fw_dac_output_voltage_negativevalue", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_dac_output_voltage(25,-1));
}

TEST_CASE("fw_dac_output_voltage_wrongvalue", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_dac_output_voltage(25,3400));
}

TEST_CASE("fw_dac_output_voltage_rightvalue", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_dac_output_voltage(25,1000));
}

TEST_CASE("fw_dac_disable_negativepin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_dac_disable(-1));
}

TEST_CASE("fw_dac_disable_wrongpin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_dac_disable(23));
}

TEST_CASE("fw_dac_disable_rightpin25", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_dac_disable(25));
}

TEST_CASE("fw_dac_disable_rightpin26", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_dac_disable(26));
}
