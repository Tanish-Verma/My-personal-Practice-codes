`timescale 1ns/1ns
`include "ripplecarryadder.v"

module ripple_carry_adder_tb;
  
  reg [3:0] a, b;                  
  wire [3:0] sum;      
  wire overflow;       

  
  ripple_carry_adder uut (
    .a(a),
    .b(b),
    .sum(sum),
    .overflow(overflow)
  );

  
  initial begin
  $dumpfile("ripplecarryadder.vcd");
  $dumpvars(0,ripple_carry_adder_tb);
    
    
// Original Test Case 1: Add 4'b0000 + 4'b0000
a = 4'b0110; b = 4'b1111; #40;

// Original Test Case 2: Add 4'b0001 + 4'b0001
a = 4'b0001; b = 4'b0001; #40;

// Original Test Case 3: Add 4'b1111 + 4'b0001
a = 4'b1111; b = 4'b0001; #40;

// Original Test Case 4: Add 4'b1001 + 4'b0111
a = 4'b1001; b = 4'b0111; #40;

// Original Test Case 5: Add 4'b0101 + 4'b0101
a = 4'b0101; b = 4'b0101; #40;

// Original Test Case 6: Add 4'b0011 + 4'b1101
a = 4'b0011; b = 4'b1101; #40;

// Additional Test Case 7: Add 4'b0110 + 4'b0010
a = 4'b0110; b = 4'b0010; #40;

// Additional Test Case 8: Add 4'b0010 + 4'b0011
a = 4'b0010; b = 4'b0011; #40;

// Additional Test Case 9: Add 4'b0100 + 4'b0100
a = 4'b0100; b = 4'b0100; #40;

// Additional Test Case 10: Add 4'b1100 + 4'b0010
a = 4'b1100; b = 4'b0010; #40;

// Additional Test Case 11: Add 4'b0111 + 4'b0111 
a = 4'b0111; b = 4'b0111; #40;

// Additional Test Case 12: Add 4'b1110 + 4'b0001 
a = 4'b1110; b = 4'b0001; #40;

    
    $finish; // End the simulation
  end

  always@(*) begin
  $monitor("Time = %0t ns, a = %b, b = %b -> Sum = %b, Overflow = %b", $time, a, b,sum, overflow);
  end


endmodule

