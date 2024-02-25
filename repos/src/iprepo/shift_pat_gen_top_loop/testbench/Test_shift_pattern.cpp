#include "./../src/shift_pattern.h"
#include "stdio.h"
int main(){
        led_t first_value = 0x6; //given a initial value 6
        led_t led_o;
        const int SHIFT_TIME =6; //given the test period: 6 loop
        int i;
                    for(i=0;i<SHIFT_TIME;i++){
                    shift_pattern_gen_top( &led_o, first_value);  //&led_o: get the value which is stored in the memory of led_o pointer
                    fprintf(stdout,"shift out:%x\r\n", led_o&0x7);
                    }
          }
