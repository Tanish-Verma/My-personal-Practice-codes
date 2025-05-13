`timescale 1ns/1ns

module nand_gate(
  input a,
  input b,
  output y
);
  nand #1 (y, a, b);
endmodule

module or_gate(
  input a,
  input b,
  output y
);
  wire [1:0] y2;
  
  nand_gate uut(.a(a), .b(a), .y(y2[1]));
  nand_gate dut(.a(b), .b(b), .y(y2[0]));
  nand_gate dsut(.a(y2[1]), .b(y2[0]), .y(y));
endmodule

module xor_gate(
  input a,
  input b,
  output y
);
  wire [2:0] y1;
  
  nand_gate uut(.a(a), .b(b), .y(y1[2]));
  nand_gate dut(.a(a), .b(y1[2]), .y(y1[1]));
  nand_gate fut(.a(y1[2]), .b(b), .y(y1[0]));
  nand_gate ut(.a(y1[0]), .b(y1[1]), .y(y));
endmodule

module half_adder(
  input a,
  input b,
  output [1:0] y
);
  wire carry;

  nand_gate uut(.a(a), .b(b), .y(carry));
  xor_gate sum_gate(.a(a), .b(b), .y(y[0]));
  nand_gate dut(.a(carry), .b(carry), .y(y[1]));
endmodule

module full_adder(
  input a,
  input b,
  input ck_1,
  output sum,
  output carry_out
);
  wire [1:0] y;
  wire [1:0] result;

  half_adder first_sum(.a(a), .b(b), .y(y));
  half_adder second_sum(.a(y[0]), .b(ck_1), .y(result));

  assign sum = result[0];
  or_gate carry(.a(y[1]), .b(result[1]), .y(carry_out));
endmodule

module ripple_carry_adder(
  input [3:0] a,b,
  output [3:0] sum,
  output overflow
);
  wire [2:0] carry;
  wire carry_out_of_last_fa;
  reg carry0=0;
  full_adder fa0(.a(a[0]), .b(b[0]), .ck_1(carry0), .sum(sum[0]), .carry_out(carry[0]));
  full_adder fa1(.a(a[1]), .b(b[1]), .ck_1(carry[0]), .sum(sum[1]), .carry_out(carry[1]));
  full_adder fa2(.a(a[2]), .b(b[2]), .ck_1(carry[1]), .sum(sum[2]), .carry_out(carry[2]));
  full_adder fa3(.a(a[3]), .b(b[3]), .ck_1(carry[2]), .sum(sum[3]), .carry_out(carry_out_of_last_fa));
  xor_gate overflow_logic(
    .a(carry_out_of_last_fa),.b(carry[2]),.y(overflow)
  );
  // assign overflow = ((!a[3])&(!b[3])&(carry[2]))|((a[3])&(b[3])&(!carry[2]));  // Overflow detection in one way usong truth table
// assign overflow = carry[2] ^ carry_out_of_last_fa; // more systematic approach  using carry_out_of_last_fa


endmodule
