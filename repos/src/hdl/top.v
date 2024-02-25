`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/30/2024 09:37:34 PM
// Design Name: 
// Module Name: top
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module top
(
input  wire clk_p,
input  wire clk_n,
output wire [2:0]top_o
    );
    
wire clk_o;
wire [2:0] first_value = 3'b110;
wire rst = 1'b1;

   IBUFDS #(
      .CCIO_EN_M("TRUE"),
      .CCIO_EN_S("TRUE") 
   )
   IBUFDS_inst (
      .O(clk_o),   // 1-bit output: Buffer output
      .I(clk_p),   // 1-bit input: Diff_p buffer input (connect directly to top-level port)
      .IB(clk_n)  // 1-bit input: Diff_n buffer input (connect directly to top-level port)
   );


shift_pattern_gen_bd shift_pattern_gen_bd_inst
(
.clk_in1_0(clk_o),          
.ext_reset_in_0(rst),
.first_value_0(first_value),  
.top_led_o_0(top_o)   
);



endmodule