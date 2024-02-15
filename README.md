# HLS_lab1 shift pattern generator
this repos gives an example for explain some HLS basic concept and a shift pattern generator lab, with pipeline concept and how to use co-simulation  


1. shift pattern generator:

   this module implement a pattern generator that can output a fix shifting value regularly and consistently:    
   3b'110 => 3b'101 => 3b'011 => 3b'110  //(6=>5=>3=>6) consistently while be given a constant 3b'110    
   3b'110 is the first given data to input led_i in top.v      
   
we can configuration 2 mode:  

ap_ctrl_hs mode:  
   block-level-protocol: ap_ctrl_hs    
   port-level-protocol: ap_vld    
   ![alt text](https://github.com/joshuahwfwEE/HLS_ATP/blob/main/hw_interface1.png?raw=true)   
   ![alt text](https://github.com/joshuahwfwEE/HLS_ATP/blob/main/shift_pattern_ap_ctrl_hs_high_latency.png?raw=true)  

because we set SHIFT_TIME=6 in testbench, so it repeat the loop for 6 times and then assert ap_idle high and stop the operation in following co-sim result  
xsim c/rtl cosimulation result:      
   ![alt text](https://github.com/joshuahwfwEE/HLS_ATP/blob/main/HLS_shift_pattern1.png?raw=true)    
   
ap_ctrl_none mode:   
   block-level-protocol: ap_ctrl_none    
   port-level-protocol: ap_none      
  ![alt text](https://github.com/joshuahwfwEE/HLS_ATP/blob/main/hw_interface2.png?raw=true)  
  ![alt text](https://github.com/joshuahwfwEE/HLS_ATP/blob/main/shift_pattern_ap_ctrl_none_high_latency.png?raw=true)
    
   notice: ap_ctrl_none support cosimulation in few cases, but this case doesn't supported, so I use ap_ctrl_hs for co-sim.    

   


   the resource usage and latency of a single sub function:  
   ![alt text](https://github.com/joshuahwfwEE/HLS_ATP/blob/main/synthesis_graph.png?raw=true)    
   



   and then if we add extra loop at top without pipelined,  we will get:  
   ![alt text](https://github.com/joshuahwfwEE/HLS_ATP/blob/main/looptop.png?raw=true)  
   we can notice the latency incresing, because we reuse the same resource again and again for 48 times( 2400/50=48 is the value of SHIFT_FLAG).
   
   
   xsim c/rtl cosimulation result(ap_ctrl_hs):  
  ![alt text](https://github.com/joshuahwfwEE/HLS_ATP/blob/main/looptop_sim.png?raw=true)  

  vivado simulation result(ap_ctrl_none):  
  ![alt text](https://github.com/joshuahwfwEE/HLS_ATP/blob/main/sim1.png?raw=true)  
  each loop (shift_pattern_gen)'s operation time is 960ns  

  resource usage:  
![alt text](https://github.com/joshuahwfwEE/HLS_ATP/blob/main/usage1.png?raw=true)  
![alt text](https://github.com/joshuahwfwEE/HLS_ATP/blob/main/usage2.png?raw=true)




 if we add some buffer in loop:  
 it will increase the task interval latency, and reduced the period of updating the output.  
 it can be achieved by simply adding some buffer in the loop.
 ![alt text](https://github.com/joshuahwfwEE/HLS_ATP/blob/main/addbufinloopsyth.png?raw=true)  
 
 ![alt text](https://github.com/joshuahwfwEE/HLS_ATP/blob/main/addbufinloop.png?raw=true)  

 the difference of above 2 result is the task interval and the period of updating output value:   
 
 result 1 update output once in each loop (the period of updating the output as the same as the period of a loop)  
 
 result 2 update multiple times during a loop (the period of updating the output is 10ns(as same as the clk)),  
 and then assert idle and then restart the loop (idle period is 540.500ns)  


 
bidirection issue solution:   
in ap_hs_mode:  
ap_vald will affect the output result while ap_hs_none is always active.  
we only focus on the logic function so we ignore ap_vald's corrective here.

shift_pattern_gen_top( led_t *top_led_o, led_t first_value){  
 
	led_t tmp_o; //first output  

	shift_pattern_gen(&tmp_o, first_value);       //generate the first output value &tmp_o  
 
    for (int i = 0; i < SHIFT_FLAG; i++) {       //SHIFT_FLAG=48  
         shift_pattern_gen(top_led_o, tmp_o);                                    
         tmp_o = *top_led_o;  
    }  

      //this code will cause synthesis tool treat top_led_o as bi-directional port,  
    	//because of reading a value from a pointer often implies both read and write access,  
    	//it may lead to a bidirectional inference, the following code will cause top_led_o as a bi-directional port  
}  


sol:  
shift_pattern_gen_top( led_t *top_led_o, led_t first_value){  
	led_t tmp_o;          //first output        
	led_t temp_top_led_o; // temporary variable        

	shift_pattern_gen(&tmp_o, first_value);       //generate the first output value &tmp_o  
    
   for (int i = 0; i < SHIFT_FLAG; i++) {        //SHIFT_FLAG=48    
    	shift_pattern_gen(&temp_top_led_o, tmp_o);    
        tmp_o = temp_top_led_o;         // update tmp_o for the next iteration    
        *top_led_o = temp_top_led_o;    // assign the value to top_led_o, the ap_ovld will assert only when temp_top_led_o update to top_led_o  
    }    

        // Swap the pointers to prepare for the next iteration  
        led_t *temp_ptr = top_led_o;  
        top_led_o = &temp_top_led_o;  
        temp_top_led_o = *temp_ptr;  
    }  

    	//the different part is this code will avoid synthesis tool treat top_led_o as bi-directional port,    
    	//by add an extra pointer: temp_ptr replace original top_led_o  
}  



latency and area tradeoff:  
1. long latency with less usage:
   ![alt text](https://github.com/joshuahwfwEE/HLS_ATP/blob/main/shift_pattern_ap_ctrl_none.png?raw=true)
   
2. low latency with more usage:
   ![alt text](https://github.com/joshuahwfwEE/HLS_ATP/blob/main/shift_pattern_ap_ctrl_none.png?raw=true)  


 vivado block design:  
 ![alt text](https://github.com/joshuahwfwEE/HLS_ATP/blob/main/shift_pattern_gen_loopwithbuffer_bd.png?raw=true)  

 simulation result in vivado:  
 ![alt text](https://github.com/joshuahwfwEE/HLS_ATP/blob/main/shift_pattern_gen_loopwithbuffer_wcfg.png?raw=true)    

   if we use more resource to implement this circult:
   




   
3. foo:  
   this module implement an adder and a multplier and a latch in this circuit,
   adder takes l2 and Latch's output as its inputs and then multiplier takes adder's output and l1 as its inputs

   given an example design of testing the combination logic of above 2 module:    
    ![alt text](https://github.com/joshuahwfwEE/HLS_ATP/blob/main/design1_pattern_plus_foo.png?raw=true)    

5. double foo:  
   this module implement use 2 foo module,  
   double foo: implement 2 adder and 2 multiplier and 2 latch (task interval is lower but using larger amount resource)  
   foo reuse: implement 1 adder and 1 multiplier and 1 latch (task interval is higher but using smaller amount resource)  

6. fir filter:
   this module implement a filter that is common used in filter low-pass, high-pass, bandpass ...etc
   if we use gcc comiler such as mb-gcc compiler to compile this code and run in microblaze,
   the assmblely code:
   we can analysis the latency its takes although its have been already optimized by the compiler, it stll need load and store operation because its von neumann architecture trasfer to hls:


question:  
1. how to solve timing violation in hls stage:
sol: according your code 

  

   use unrolled and pipelined:
   
