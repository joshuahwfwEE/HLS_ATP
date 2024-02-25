#ifndef SHIFT_PATTERN_H
#define SHIFT_PATTERN_H

#include "ap_int.h"
//T_count x desired_counts_per_second: 0.00000001 * 100000000 = 1  WHICH MEANS :  1/100Mhz * 100Mhz = 1 s

#define MAX_CNT 100/2           // half second: 100000000/2   =>  0.00001/2 second: 100/2
//#define MAX_CNT 100000000     // if we use 100M clk for input clk, we can set MAX_CNT = 100000000, when clk's amount is meet 100M means that is 1 second

#define SHIFT_FLAG MAX_CNT-2    // set this flag will determine the shift operation start at the last 2 cycle near MAX_CNT

#define loop_cnt 48             // this is the for loop amount in the top function (the total latency will be (each loop latency * loop_cnt))


/*custom data type*/
typedef ap_fixed<3,3> led_t;      //datawidth=3, integer bit =3
typedef ap_fixed<32,32> cnt_32_t; //datawidth=32 integer bit =32


/*use int data type*/
//typedef int led_t;
//typedef int cnt_32_t;


void shift_pattern_gen(led_t *led_o, led_t led_i);   //logic function
void shift_pattern_gen_top(led_t *top_led_o, led_t first_value); //top function

#endif
