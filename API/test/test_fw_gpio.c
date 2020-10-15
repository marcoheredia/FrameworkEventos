#include "unity.h"
#include "fw_gpio.h"

//*****Test for fw_gpio_set_mode*****/
TEST_CASE("fw_gpio_set_mode_negativepin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_set_mode(-1, GPIO_MODE_INPUT));
}

TEST_CASE("fw_gpio_set_mode_wrongpin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_set_mode(40, GPIO_MODE_INPUT));
}

TEST_CASE("fw_gpio_set_mode_pin34-39output", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_set_mode(34, GPIO_MODE_OUTPUT));
    TEST_ASSERT_FALSE(fw_gpio_set_mode(35, GPIO_MODE_OUTPUT));
	TEST_ASSERT_FALSE(fw_gpio_set_mode(36, GPIO_MODE_OUTPUT));
    TEST_ASSERT_FALSE(fw_gpio_set_mode(37, GPIO_MODE_OUTPUT));
    TEST_ASSERT_FALSE(fw_gpio_set_mode(38, GPIO_MODE_OUTPUT));
    TEST_ASSERT_FALSE(fw_gpio_set_mode(39, GPIO_MODE_OUTPUT));
}

TEST_CASE("fw_gpio_set_mode_input", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_gpio_set_mode(3, GPIO_MODE_INPUT));
    TEST_ASSERT_TRUE(fw_gpio_set_mode(15, GPIO_MODE_INPUT));
    TEST_ASSERT_TRUE(fw_gpio_set_mode(35, GPIO_MODE_INPUT));
}

TEST_CASE("fw_gpio_set_mode_wrongmode", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_set_mode(20, GPIO_PULLUP_ONLY));
    TEST_ASSERT_FALSE(fw_gpio_set_mode(20, -1));
}

TEST_CASE("fw_gpio_set_mode_output", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_gpio_set_mode(5, GPIO_MODE_OUTPUT));
}

TEST_CASE("fw_gpio_set_mode_outputod", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_gpio_set_mode(5, GPIO_MODE_OUTPUT_OD));
}

TEST_CASE("fw_gpio_set_mode_inputoutput", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_gpio_set_mode(5, GPIO_MODE_INPUT_OUTPUT));
}

TEST_CASE("fw_gpio_set_mode_inputoutputod", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_gpio_set_mode(5, GPIO_MODE_INPUT_OUTPUT_OD));
}

TEST_CASE("fw_gpio_set_mode_disable", "[proyecto]") 
{
    fw_gpio_set_mode(5, GPIO_MODE_OUTPUT);
    TEST_ASSERT_TRUE(fw_gpio_set_mode(5, GPIO_MODE_DISABLE));
}

//*****Test for fw_gpio_set_pull*****/
TEST_CASE("fw_gpio_set_pull_negativepin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_set_pull(-1, GPIO_PULLUP_ONLY));
}

TEST_CASE("fw_gpio_set_pull_wrongpin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_set_pull(40, GPIO_PULLUP_ONLY));
}

TEST_CASE("fw_gpio_set_pull_pin34-39output", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_set_pull(34, GPIO_PULLUP_ONLY));
    TEST_ASSERT_FALSE(fw_gpio_set_pull(35, GPIO_PULLUP_ONLY));
	TEST_ASSERT_FALSE(fw_gpio_set_pull(36, GPIO_PULLDOWN_ONLY));
    TEST_ASSERT_FALSE(fw_gpio_set_pull(37, GPIO_PULLDOWN_ONLY));
    TEST_ASSERT_FALSE(fw_gpio_set_pull(38, GPIO_PULLUP_PULLDOWN));
    TEST_ASSERT_FALSE(fw_gpio_set_pull(39, GPIO_PULLUP_PULLDOWN));
}

TEST_CASE("fw_gpio_set_pull_wrongpull", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_set_pull(10, 7));
    TEST_ASSERT_FALSE(fw_gpio_set_pull(10, -1));
}

TEST_CASE("fw_gpio_set_pull_up", "[proyecto]") 
{
	fw_gpio_set_mode(5,GPIO_MODE_INPUT);
    TEST_ASSERT_TRUE(fw_gpio_set_pull(5, GPIO_PULLUP_ONLY));
}

TEST_CASE("fw_gpio_set_pull_down", "[proyecto]") 
{
	fw_gpio_set_mode(5,GPIO_MODE_INPUT);
    TEST_ASSERT_TRUE(fw_gpio_set_pull(5, GPIO_PULLDOWN_ONLY));
}


TEST_CASE("fw_gpio_set_pull_updown", "[proyecto]") 
{
    fw_gpio_set_mode(2,GPIO_MODE_INPUT);
    TEST_ASSERT_TRUE(fw_gpio_set_pull(2, GPIO_PULLUP_PULLDOWN));
}

TEST_CASE("fw_gpio_set_pull_floating", "[proyecto]") 
{
    fw_gpio_set_mode(13,GPIO_MODE_INPUT);
    TEST_ASSERT_TRUE(fw_gpio_set_pull(13, GPIO_FLOATING));
}

//*****Test for fw_gpio_setup_input*****/
TEST_CASE("fw_gpio_setup_input_negativepin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_setup_input(-1, GPIO_PULLUP_ONLY));
}

TEST_CASE("fw_gpio_setup_input_wrongpin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_setup_input(40, GPIO_PULLUP_ONLY));
}

TEST_CASE("fw_gpio_setup_input_wrongpull", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_setup_input(10, 9));
    TEST_ASSERT_FALSE(fw_gpio_setup_input(10, -1));
}

TEST_CASE("fw_gpio_setup_input_pullup", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_gpio_setup_input(5, GPIO_PULLUP_ONLY));
}

TEST_CASE("fw_gpio_setup_input_pulldown", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_gpio_setup_input(15, GPIO_PULLDOWN_ONLY));
}


TEST_CASE("fw_gpio_setup_input_pullupdown", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_gpio_setup_input(2, GPIO_PULLUP_PULLDOWN));
}


TEST_CASE("fw_gpio_setup_input_floating", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_gpio_setup_input(3, GPIO_FLOATING));
}

//*****Test for fw_gpio_setup_output*****/
TEST_CASE("fw_gpio_setup_output_negativepin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_setup_output(-1, 0));
}

TEST_CASE("fw_gpio_setup_output_wrongpin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_setup_output(40, 0));
}

TEST_CASE("fw_gpio_set_pull_pin34-39output", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_setup_output(34, 0));
    TEST_ASSERT_FALSE(fw_gpio_setup_output(35, 0));
	TEST_ASSERT_FALSE(fw_gpio_setup_output(36, 0));
    TEST_ASSERT_FALSE(fw_gpio_setup_output(37, 0));
    TEST_ASSERT_FALSE(fw_gpio_setup_output(38, 0));
    TEST_ASSERT_FALSE(fw_gpio_setup_output(39, 0));
}

TEST_CASE("fw_gpio_setup_output_wronglevel", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_setup_output(27, 2));
    TEST_ASSERT_FALSE(fw_gpio_setup_output(27, -1));
}

TEST_CASE("fw_gpio_setup_output_leveldown", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_gpio_setup_output(1, 0));
}

TEST_CASE("fw_gpio_setup_output_levelhigh", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_gpio_setup_output(2, 1));
}

//*****Test for fw_gpio_read*****/
TEST_CASE("fw_gpio_read_negativepin", "[proyecto]") 
{
    TEST_ASSERT_EQUAL_INT8(-1,fw_gpio_read(-1));
}

TEST_CASE("fw_gpio_read_wrongpin", "[proyecto]") 
{
    TEST_ASSERT_EQUAL_INT8(-1,fw_gpio_read(40));
}

TEST_CASE("fw_gpio_read_rightpin", "[proyecto]") 
{
	fw_gpio_setup_input(9,GPIO_PULLUP_PULLDOWN);
    int8_t value=fw_gpio_read(9);
    TEST_ASSERT_GREATER_OR_EQUAL_INT8(0,value);
    TEST_ASSERT_LESS_OR_EQUAL_INT8(1,value);
}

//*****Test for fw_gpio_write*****/
TEST_CASE("fw_gpio_write_negativepin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_write(-1, 0));
}

TEST_CASE("fw_gpio_write_wrongpin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_write(40, 0));
}

TEST_CASE("fw_gpio_write_pin34-39output", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_write(34, 0));
    TEST_ASSERT_FALSE(fw_gpio_write(35, 0));
	TEST_ASSERT_FALSE(fw_gpio_write(36, 0));
    TEST_ASSERT_FALSE(fw_gpio_write(37, 0));
    TEST_ASSERT_FALSE(fw_gpio_write(38, 0));
    TEST_ASSERT_FALSE(fw_gpio_write(39, 0));
}

TEST_CASE("fw_gpio_write_wronglevel", "[proyecto]") 
{
	fw_gpio_set_mode(1, GPIO_MODE_OUTPUT);
    TEST_ASSERT_FALSE(fw_gpio_write(1, 2));
    TEST_ASSERT_FALSE(fw_gpio_write(1, -1));
}

TEST_CASE("fw_gpio_write_leveldown", "[proyecto]") 
{
	fw_gpio_set_mode(2, GPIO_MODE_OUTPUT);
    TEST_ASSERT_TRUE(fw_gpio_write(2, 0));
}

TEST_CASE("fw_gpio_write_levelhigh", "[proyecto]") 
{
	fw_gpio_set_mode(3, GPIO_MODE_OUTPUT);
    TEST_ASSERT_TRUE(fw_gpio_write(3, 1));
}

//****Test for fw_gpio_toggle*****
TEST_CASE("fw_gpio_toggle_negativepin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_toggle(-1));
}

TEST_CASE("fw_gpio_toggle_wrongpin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_toggle(40));
}

TEST_CASE("fw_gpio_toggle_pin34-39output", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_toggle(34));
    TEST_ASSERT_FALSE(fw_gpio_toggle(35));
	TEST_ASSERT_FALSE(fw_gpio_toggle(36));
    TEST_ASSERT_FALSE(fw_gpio_toggle(37));
    TEST_ASSERT_FALSE(fw_gpio_toggle(38));
    TEST_ASSERT_FALSE(fw_gpio_toggle(39));
}

TEST_CASE("fw_gpio_toggle_rightpin", "[proyecto]") 
{
	fw_gpio_setup_output(3, 0);
    TEST_ASSERT_TRUE(fw_gpio_toggle(3));
    TEST_ASSERT_TRUE(fw_gpio_toggle(3));
}

TEST_CASE("fw_gpio_toggle_leveldown", "[proyecto]") 
{
	fw_gpio_setup_output(3, 0);
    TEST_ASSERT_TRUE(fw_gpio_toggle(3));
    TEST_ASSERT_EQUAL_INT8(fw_gpio_read_out(3),1);
}

TEST_CASE("fw_gpio_toggle_levelhigh", "[proyecto]") 
{
	fw_gpio_setup_output(3, 1);
    TEST_ASSERT_TRUE(fw_gpio_toggle(3));
    TEST_ASSERT_EQUAL_INT8(0,fw_gpio_read_out(3));
}

//*****Test for fw_gpio_read_out*****
TEST_CASE("fw_gpio_read_out_negativepin", "[proyecto]") 
{
    TEST_ASSERT_EQUAL_INT8(-1,fw_gpio_read_out(-1));
}

TEST_CASE("fw_gpio_read_out_wrongpin", "[proyecto]") 
{
    TEST_ASSERT_EQUAL_INT8(-1,fw_gpio_read_out(40));
}

TEST_CASE("fw_gpio_read_out_pin34-39output", "[proyecto]") 
{
    TEST_ASSERT_EQUAL_INT8(-1,fw_gpio_read_out(34));
    TEST_ASSERT_EQUAL_INT8(-1,fw_gpio_read_out(35));
	TEST_ASSERT_EQUAL_INT8(-1,fw_gpio_read_out(36));
    TEST_ASSERT_EQUAL_INT8(-1,fw_gpio_read_out(37));
    TEST_ASSERT_EQUAL_INT8(-1,fw_gpio_read_out(38));
    TEST_ASSERT_EQUAL_INT8(-1,fw_gpio_read_out(39));
}

TEST_CASE("fw_gpio_read_out_leveldown", "[proyecto]") 
{
	fw_gpio_setup_output(1, 0);
    TEST_ASSERT_EQUAL_INT8(0,fw_gpio_read_out(1));
}

TEST_CASE("fw_gpio_read_out_levelhigh", "[proyecto]") 
{
	fw_gpio_setup_output(2, 1);
    TEST_ASSERT_EQUAL_INT8(1,fw_gpio_read_out(2));
}

//*****Test for fw_gpio_reset*****
TEST_CASE("fw_gpio_reset_negativepin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_reset(-1));
}

TEST_CASE("fw_gpio_reset_wrongpin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_reset(40));
}

TEST_CASE("fw_gpio_reset_rightpin", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_gpio_reset(3));
}

//*****Test for fw_gpio_enable_int*****
TEST_CASE("fw_gpio_enable_int_negativepin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_enable_int(-1,GPIO_INTR_POSEDGE));
}

TEST_CASE("fw_gpio_enable_int_wrongpin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_enable_int(40,GPIO_INTR_POSEDGE));
}

TEST_CASE("fw_gpio_enable_int_negativetype", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_enable_int(2,-1));
}

TEST_CASE("fw_gpio_enable_int_wrongtype", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_enable_int(2,6));
}

TEST_CASE("fw_gpio_enable_int_disable", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_gpio_enable_int(2,GPIO_INTR_DISABLE));
}

TEST_CASE("fw_gpio_enable_int_posedge", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_gpio_enable_int(4,GPIO_INTR_POSEDGE));
}

TEST_CASE("fw_gpio_enable_int_negedge", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_gpio_enable_int(4,GPIO_INTR_NEGEDGE));
}

TEST_CASE("fw_gpio_enable_int_anyedge", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_gpio_enable_int(5,GPIO_INTR_ANYEDGE));
}

TEST_CASE("fw_gpio_enable_int_lowlevel", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_gpio_enable_int(13,GPIO_INTR_LOW_LEVEL));
}

TEST_CASE("fw_gpio_enable_int_highlevel", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_gpio_enable_int(15,GPIO_INTR_HIGH_LEVEL));
}

//*****Test for fw_gpio_disable_int*****
TEST_CASE("fw_gpio_disable_int_negativepin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_disable_int(-1));
}

TEST_CASE("fw_gpio_disable_int_wrongpin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_disable_int(40));
}

TEST_CASE("fw_gpio_disable_int_rightpin", "[proyecto]") 
{
    TEST_ASSERT_TRUE(fw_gpio_disable_int(3));
}

//*****Test for fw_gpio_set_int_handler*****
void handle_test(){
    printf("Test the handler\n");
}

TEST_CASE("fw_gpio_set_int_handler_negativepin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_set_int_handler(-1,handle_test,NULL));
}

TEST_CASE("fw_gpio_set_int_handler_wrongpin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_set_int_handler(40,handle_test,NULL));
}

TEST_CASE("fw_gpio_set_int_handler_nohandler", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_set_int_handler(40,NULL,NULL));
}


TEST_CASE("fw_gpio_remove_int_handler_negativepin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_remove_int_handler(-1));
}

TEST_CASE("fw_gpio_remove_int_handler_wrongpin", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_remove_int_handler(40));
}

TEST_CASE("fw_gpio_remove_int_handler_removenohandler", "[proyecto]") 
{
    TEST_ASSERT_FALSE(fw_gpio_remove_int_handler(7));
}