############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project pattern_gen_frm
set_top shift_pattern_gen_top
add_files src/shift_pattern.cpp
add_files src/shift_pattern.h
add_files -tb testbench/Test_shift_pattern.cpp
open_solution "solution1" -flow_target vivado
set_part {xcvu19p_CIV-fsva3824-2-e}
create_clock -period 10 -name default
config_export -output /home/joshua/work/HLSIP/atp_lesson/pattern_gen_frm/repos/src/iprepo/shift_pat_gen_top_loop/pattern_gen_frm/solution1
#source "./pattern_gen_frm/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog -output /home/joshua/work/HLSIP/atp_lesson/pattern_gen_frm/repos/src/iprepo/shift_pat_gen_top_loop/pattern_gen_frm/solution1
