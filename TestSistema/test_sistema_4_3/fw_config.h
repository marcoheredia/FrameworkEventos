/* generated from ./config.json - do not edit */
#ifndef FW_CONFIG_H_
#define FW_CONFIG_H_
#include <stddef.h>
#include <stdbool.h>


struct fw_config {
  struct fw_config_A {
    struct fw_config_A_a1 {
      int a1a;
      int a1b;
      char *a1c;
      char *a1d;
    } a1;
    struct fw_config_A_a2 {
      int a1a;
      int a2b;
      char *a2c;
      char *a2d;
    } a2;
    int a3;
    char *a4;
    float a5;
  } A;
};


bool get_A_a1_a1a();

void set_A_a1_a1a(bool new_value);

int get_A_a1_a1b();

void set_A_a1_a1b(int new_value);

char *get_A_a1_a1c();

void set_A_a1_a1c(char *new_value);

char *get_A_a1_a1d();

void set_A_a1_a1d(char *new_value);

bool get_A_a2_a1a();

void set_A_a2_a1a(bool new_value);

int get_A_a2_a2b();

void set_A_a2_a2b(int new_value);

char *get_A_a2_a2c();

void set_A_a2_a2c(char *new_value);

char *get_A_a2_a2d();

void set_A_a2_a2d(char *new_value);

int get_A_a3();

void set_A_a3(int new_value);

char *get_A_a4();

void set_A_a4(char *new_value);

float get_A_a5();

void set_A_a5(float new_value);

#endif /* FW_CONFIG_H_ */

