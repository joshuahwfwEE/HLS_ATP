//#ifndef SHIFT_PATTERN_C_
//#define SHIFT_PATTERN_C_
//#endif
#include "shift_pattern.h"
#define ap_ctrl_none
//#define ap_ctrl_hs


void shift_pattern_gen(led_t *led_o, led_t led_i)
{

#ifdef ap_ctrl_hs /*for ap_ctrl_hs mode ( used for co-simulation)*/
 #pragma HLS INTERFACE mode=ap_ovld port=led_o
 #pragma HLS INTERFACE mode=ap_vld port=led_i
#endif


#ifdef ap_ctrl_none
	/*for ap_ctrl_none mode*/
	#pragma HLS INTERFACE ap_ctrl_none port=return
	#pragma HLS INTERFACE ap_none port=led_i
	#pragma HLS INTERFACE ap_none port=led_o
#endif
        led_t temp_led; //buffer for input: led_i
        cnt_32_t i;    //used for for loop variable i

        temp_led = led_i;

        for(i=0; i< MAX_CNT; i++)
        {
                if(i==SHIFT_FLAG){                                                     // temp[2:1:0] => temp[1:0:X]  // least 3 bit valid
                                                                                       // temp[2:1:0] => temp[2]      // least 1 bit valid
                        temp_led  = ((temp_led>>2) & 0x01) + ((temp_led<<1) & 0x06);   // temp[2:1:0] => temp[1:0:2]

    //  verilog:  temp_led <= {temp_led[1:0],temp_led[2]}    // means that ori:temp[2:1:0] => temp[1:0:2]

    //   the sequence is : 3b'110 => 3b'101 => 3b'011 => 3b'110  (6=>5=>3=>6)


                *led_o = temp_led; // led_o: pointer, *led_o: memory relative led_o
            }
        }

}