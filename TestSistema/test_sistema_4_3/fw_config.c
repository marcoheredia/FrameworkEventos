#include "fw_config.h"

static struct fw_config config0={
  {
    {
      false,
      -1,
      "192.168.1.1",
      "ESP32"
    },
    {
      true,
      -1,
      "192.168.1.1",
      "ESP32"
    },
    30,
    "ESP32",
    2.5
  }};

bool get_A_a1_a1a(){
	return config0.A.a1.a1a;
}

void set_A_a1_a1a(bool new_value){
	config0.A.a1.a1a=new_value;
}

int get_A_a1_a1b(){
	return config0.A.a1.a1b;
}

void set_A_a1_a1b(int new_value){
	config0.A.a1.a1b=new_value;
}

char *get_A_a1_a1c(){
	return config0.A.a1.a1c;
}

void set_A_a1_a1c(char *new_value){
	config0.A.a1.a1c=new_value;
}

char *get_A_a1_a1d(){
	return config0.A.a1.a1d;
}

void set_A_a1_a1d(char *new_value){
	config0.A.a1.a1d=new_value;
}

bool get_A_a2_a1a(){
	return config0.A.a2.a1a;
}

void set_A_a2_a1a(bool new_value){
	config0.A.a2.a1a=new_value;
}

int get_A_a2_a2b(){
	return config0.A.a2.a2b;
}

void set_A_a2_a2b(int new_value){
	config0.A.a2.a2b=new_value;
}

char *get_A_a2_a2c(){
	return config0.A.a2.a2c;
}

void set_A_a2_a2c(char *new_value){
	config0.A.a2.a2c=new_value;
}

char *get_A_a2_a2d(){
	return config0.A.a2.a2d;
}

void set_A_a2_a2d(char *new_value){
	config0.A.a2.a2d=new_value;
}

int get_A_a3(){
	return config0.A.a3;
}

void set_A_a3(int new_value){
	config0.A.a3=new_value;
}

char *get_A_a4(){
	return config0.A.a4;
}

void set_A_a4(char *new_value){
	config0.A.a4=new_value;
}

float get_A_a5(){
	return config0.A.a5;
}

void set_A_a5(float new_value){
	config0.A.a5=new_value;
}
