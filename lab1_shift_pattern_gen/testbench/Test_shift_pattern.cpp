#include "./../src/shift_pattern.h"
#include "stdio.h"
int main(){
        led_t led_i = 0x6; //given a initial value 6
        led_t led_o;
        const int SHIFT_TIME =6; //given the test period: 6 loop
        int i;
                    for(i=0;i<SHIFT_TIME;i++){
                    shift_pattern_gen( &led_o, led_i);  //&led_o: get the value which is stored in the memory of led_o pointer
                    led_i = led_o; // give output data to input
                    fprintf(stdout,"shift out:%x", led_o&0x7);
                    }
          }
