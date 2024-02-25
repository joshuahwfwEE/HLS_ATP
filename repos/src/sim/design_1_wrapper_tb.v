`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/01/2024 11:41:21 AM
// Design Name: 
// Module Name: design_1_wrapper_tb
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


module top_tb();

  // Inputs
  reg CLK_IN1_D_0_clk_n;
  reg CLK_IN1_D_0_clk_p;

  // Outputs
  wire [2:0] o_0;

  // Instantiate the design_1_wrapper module
  top uut
    (
      .clk_p(CLK_IN1_D_0_clk_n),
      .clk_n(CLK_IN1_D_0_clk_p),
      .top_o(o_0)
    );

  // Clock generation
  reg clk;
  initial begin
    clk = 0;
    forever #5 clk = ~clk;
  end

  // Apply inputs
  initial begin
    CLK_IN1_D_0_clk_n = 0;
    CLK_IN1_D_0_clk_p = 1;
    #100 $finish;
  end

  always @(posedge clk) begin
    // Toggle clock and other input signals as needed
    CLK_IN1_D_0_clk_n <= ~CLK_IN1_D_0_clk_n;
    CLK_IN1_D_0_clk_p <= ~CLK_IN1_D_0_clk_p;
  end

  // Monitor and display outputs
  always @(posedge clk) $display("o_0 = %b", o_0);

endmodule
