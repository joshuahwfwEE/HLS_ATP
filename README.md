# HLS_ATP
this repos gives an example for explain some HLS basic concept and a shift pattern generator lab, and talk about some data dependency issue and pipeline and how to use co-simulation  


1. shift pattern generator:
   block-level-protocal: ap_ctrl_none
   this module cam implement a pattern generator that can output following consistently:
   3b'110 => 3b'101 => 3b'011 => 3b'110  //(6=>5=>3=>6) consistently while be given a constant 3b'110  
   ![alt text](https://github.com/joshuahwfwEE/HLS_ATP/blob/main/HLS_shift_pattern.png?raw=true)
   
3. foo:  
   this module implement an adder and a multplier and a latch in this circuit,
   adder takes l2 and Latch's output as its inputs and then multiplier takes adder's output and l1 as its inputs

4. two foo:  
   this module implement use 2 foo module,  
   double foo: implement 2 adder and 2 multiplier and 2 latch (task interval is lower but using larger amount resource)  
   foo reuse: implement 1 adder and 1 multiplier and 1 latch (task interval is higher but using smaller amount resource)  

5. fir filter:
   this module implement a filter that is common used in filter low-pass, high-pass, bandpass ...etc
   if we use gcc comiler such as mb-gcc compiler to compile this code and run in microblaze,
   the assmblely code:
   we can analysis the latency its takes although its have been already optimized by the compiler, it stll need load and store operation because its von neumann architecture

   trasfer to hls:

   use unrolled and pipelined:
   
