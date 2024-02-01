#ifndef SHIFT_PATTERN_H
#define SHIFT_PATTERN_H

//T_count x desired_counts_per_second: 0.0000001 * 10000000 = 1  WHICH MEANS :  1/10Mhz * 10Mhz = 1 s
//#define MAX_CNT 10000000  // when clk's amount is meet 10M means that is 1 second

#define MAX_CNT 100/2   // half second: 10000000/2,  0.00001/2 second: 100/2
#define SHIFT_FLAG MAX_CNT-2
#include "ap_int.h"



/*custom data type*/
typedef ap_fixed<3,3> led_t;      //datawidth=3, integer bit =3
typedef ap_fixed<32,32> cnt_32_t; //datawidth=32 integer bit =32


/*use int data type*/
//typedef int led_t;
//typedef int cnt_32_t;


void shift_pattern_gen(led_t *led_o, led_t led_i);   //top function


#endif
