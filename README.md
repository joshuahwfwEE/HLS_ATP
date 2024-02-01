# HLS_ATP
this repos gives an example for explain some HLS basic concept and a shift pattern generator lab, and talk about some data dependency issue and pipeline and how to use co-simulation  


1. shift pattern generator:     
   block-level-protocol: ap_ctrl_hs  
   port-level-protocol: ap_vld      
   ![alt text](https://github.com/joshuahwfwEE/HLS_ATP/blob/main/shift_pattern_ap_ctrl_hs.png?raw=true)  
   
   this module can implement a pattern generator that can output following consistently:    
   3b'110 => 3b'101 => 3b'011 => 3b'110  //(6=>5=>3=>6) consistently while be given a constant 3b'110    
   3b'110 is the first given data to input led_i    
   because we set SHIFT_TIME=6 in testbench, so it repeat the loop for 6 times and then assert ap_idle high and stop the operation  
   
   notice: ap_ctrl_none support cosimulation in few cases, but this case doesn't supported    
   xsim c/rtl cosimulation result:    
   ![alt text](https://github.com/joshuahwfwEE/HLS_ATP/blob/main/HLS_shift_pattern1.png?raw=true)    

   we keep the same code logic but change the block and port level protocol into:    
   block-level-protocol: ap_ctrl_hs    
   port-level-protocol: ap_vld    
   ![alt text](https://github.com/joshuahwfwEE/HLS_ATP/blob/main/shift_pattern_ap_ctrl_none.png?raw=true)  

   you can check the resource usage and latency:  
   ![alt text](https://github.com/joshuahwfwEE/HLS_ATP/blob/main/synthesis_graph.png?raw=true)

   and then if we add extra loop at top without pipelined,  we will get:  
   ![alt text](https://github.com/joshuahwfwEE/HLS_ATP/blob/main/looptop.png?raw=true)  
   we can notice the latency incresing, because we reuse the resource uasge for 48 times( the value of SHIFT_FLAG).  
   
   xsim c/rtl cosimulation result:  
  ![alt text](https://github.com/joshuahwfwEE/HLS_ATP/blob/main/looptop_sim.png?raw=true)    

   if we use more resource to implement this circult:
   




   
3. foo:  
   this module implement an adder and a multplier and a latch in this circuit,
   adder takes l2 and Latch's output as its inputs and then multiplier takes adder's output and l1 as its inputs

   given an example design of testing the combination logic of above 2 module:    
    ![alt text](https://github.com/joshuahwfwEE/HLS_ATP/blob/main/design1_pattern_plus_foo.png?raw=true)    

5. two foo:  
   this module implement use 2 foo module,  
   double foo: implement 2 adder and 2 multiplier and 2 latch (task interval is lower but using larger amount resource)  
   foo reuse: implement 1 adder and 1 multiplier and 1 latch (task interval is higher but using smaller amount resource)  

6. fir filter:
   this module implement a filter that is common used in filter low-pass, high-pass, bandpass ...etc
   if we use gcc comiler such as mb-gcc compiler to compile this code and run in microblaze,
   the assmblely code:
   we can analysis the latency its takes although its have been already optimized by the compiler, it stll need load and store operation because its von neumann architecture

   trasfer to hls:

   use unrolled and pipelined:
   
