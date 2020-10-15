#include "unity.h"
#include "fw_adc.h"

TEST_CASE("fw_adc_enable_negativepin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_adc_enable(-1));
}

TEST_CASE("fw_adc_enable_wrongvalue", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_adc_enable(5));
}

TEST_CASE("fw_adc_enable_unit1", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_adc_enable(32));
    TEST_ASSERT_TRUE(fw_adc_enable(33));
    TEST_ASSERT_TRUE(fw_adc_enable(34));
    TEST_ASSERT_TRUE(fw_adc_enable(35));
    TEST_ASSERT_TRUE(fw_adc_enable(36));
    TEST_ASSERT_TRUE(fw_adc_enable(37));
    TEST_ASSERT_TRUE(fw_adc_enable(38));
    TEST_ASSERT_TRUE(fw_adc_enable(39));
}
//Only supported ADC1 for now
/*TEST_CASE("fw_adc_enable_unit2", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_adc_enable(0));
    TEST_ASSERT_TRUE(fw_adc_enable(2));
    TEST_ASSERT_TRUE(fw_adc_enable(4));
    TEST_ASSERT_TRUE(fw_adc_enable(12));
    TEST_ASSERT_TRUE(fw_adc_enable(13));
    TEST_ASSERT_TRUE(fw_adc_enable(14));
    TEST_ASSERT_TRUE(fw_adc_enable(15));
    TEST_ASSERT_TRUE(fw_adc_enable(25));
    TEST_ASSERT_TRUE(fw_adc_enable(26));
    TEST_ASSERT_TRUE(fw_adc_enable(27));
}*/

TEST_CASE("fw_adc_read_negativepin", "[proyecto]") 
{
    TEST_ASSERT_EQUAL_INT(-1,fw_adc_read(-2));
}

TEST_CASE("fw_adc_read_wrongpin", "[proyecto]") 
{
    TEST_ASSERT_EQUAL_INT(-1,fw_adc_read(5));
}

TEST_CASE("fw_adc_read_unit1", "[proyecto]") 
{
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read(32));
    TEST_ASSERT_LESS_OR_EQUAL(4096, fw_adc_read(32));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read(33));
    TEST_ASSERT_LESS_OR_EQUAL(4096, fw_adc_read(33));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read(34));
    TEST_ASSERT_LESS_OR_EQUAL(4096, fw_adc_read(34));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read(35));
    TEST_ASSERT_LESS_OR_EQUAL(4096, fw_adc_read(35));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read(36));
    TEST_ASSERT_LESS_OR_EQUAL(4096, fw_adc_read(36));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read(37));
    TEST_ASSERT_LESS_OR_EQUAL(4096, fw_adc_read(37));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read(38));
    TEST_ASSERT_LESS_OR_EQUAL(4096, fw_adc_read(38));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read(39));
    TEST_ASSERT_LESS_OR_EQUAL(4096, fw_adc_read(39));
}
//Only supported ADC1 for now
/*TEST_CASE("fw_adc_read_unit2", "[proyecto]") 
{
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read(0));
    TEST_ASSERT_LESS_OR_EQUAL(4096, fw_adc_read(0));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read(2));
    TEST_ASSERT_LESS_OR_EQUAL(4096, fw_adc_read(2));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read(4));
    TEST_ASSERT_LESS_OR_EQUAL(4096, fw_adc_read(4));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read(12));
    TEST_ASSERT_LESS_OR_EQUAL(4096, fw_adc_read(12));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read(13));
    TEST_ASSERT_LESS_OR_EQUAL(4096, fw_adc_read(13));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read(14));
    TEST_ASSERT_LESS_OR_EQUAL(4096, fw_adc_read(14));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read(15));
    TEST_ASSERT_LESS_OR_EQUAL(4096, fw_adc_read(15));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read(25));
    TEST_ASSERT_LESS_OR_EQUAL(4096, fw_adc_read(25));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read(26));
    TEST_ASSERT_LESS_OR_EQUAL(4096, fw_adc_read(26));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read(27));
    TEST_ASSERT_LESS_OR_EQUAL(4096, fw_adc_read(27));
}*/

TEST_CASE("fw_adc_read_voltage_negativepin", "[proyecto]") 
{
    TEST_ASSERT_EQUAL_INT(-1,fw_adc_read_voltage(-2));
}

TEST_CASE("fw_adc_read_voltage_wrongpin", "[proyecto]") 
{
    TEST_ASSERT_EQUAL_INT(-1,fw_adc_read_voltage(5));
}

TEST_CASE("fw_adc_read_voltage_unit1", "[proyecto]") 
{
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read_voltage(32));
    TEST_ASSERT_LESS_OR_EQUAL(3300, fw_adc_read_voltage(32));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read_voltage(33));
    TEST_ASSERT_LESS_OR_EQUAL(3300, fw_adc_read_voltage(33));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read_voltage(34));
    TEST_ASSERT_LESS_OR_EQUAL(3300, fw_adc_read_voltage(34));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read_voltage(35));
    TEST_ASSERT_LESS_OR_EQUAL(3300, fw_adc_read_voltage(35));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read_voltage(36));
    TEST_ASSERT_LESS_OR_EQUAL(3300, fw_adc_read_voltage(36));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read_voltage(37));
    TEST_ASSERT_LESS_OR_EQUAL(3300, fw_adc_read_voltage(37));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read_voltage(38));
    TEST_ASSERT_LESS_OR_EQUAL(3300, fw_adc_read_voltage(38));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read_voltage(39));
    TEST_ASSERT_LESS_OR_EQUAL(3300, fw_adc_read_voltage(39));
}
//Only supported ADC1 for now
/*TEST_CASE("fw_adc_read_voltage_unit2", "[proyecto]") 
{
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read_voltage(0));
    TEST_ASSERT_LESS_OR_EQUAL(3300, fw_adc_read_voltage(0));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read_voltage(2));
    TEST_ASSERT_LESS_OR_EQUAL(3300, fw_adc_read_voltage(2));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read_voltage(4));
    TEST_ASSERT_LESS_OR_EQUAL(3300, fw_adc_read_voltage(4));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read_voltage(12));
    TEST_ASSERT_LESS_OR_EQUAL(3300, fw_adc_read_voltage(12));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read_voltage(13));
    TEST_ASSERT_LESS_OR_EQUAL(3300, fw_adc_read_voltage(13));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read_voltage(14));
    TEST_ASSERT_LESS_OR_EQUAL(3300, fw_adc_read_voltage(14));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read_voltage(15));
    TEST_ASSERT_LESS_OR_EQUAL(3300, fw_adc_read_voltage(15));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read_voltage(25));
    TEST_ASSERT_LESS_OR_EQUAL(3300, fw_adc_read_voltage(25));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read_voltage(26));
    TEST_ASSERT_LESS_OR_EQUAL(3300, fw_adc_read_voltage(26));
    TEST_ASSERT_GREATER_OR_EQUAL(0, fw_adc_read_voltage(27));
    TEST_ASSERT_LESS_OR_EQUAL(3300, fw_adc_read_voltage(27));
}*/