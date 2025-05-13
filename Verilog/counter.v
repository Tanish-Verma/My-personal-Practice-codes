`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 23.01.2025 18:21:55
// Design Name: 
// Module Name: counter1
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
module clock_gen(
    output reg clk
);
    initial begin
        clk = 0;
    end

    always begin
        #10 clk = ~clk;
    end
endmodule

module counter1(
    input enable,
    input rst,
    input clk,
    output reg [3:0]count
    );
    
    always @(posedge clk) begin
    if(enable) begin
        if(rst) begin
            count<=4'b0000;
        end else begin
            if(count==10) begin
                count<=4'b0000;
            end else
                count<=count+1;
            end
     end
   end
endmodule
