`include "design.v"
`timescale 1ns/100ps

module fibonacci_tb;
    reg clk;
    reg enble;
    wire [7:0] fib_out;
    wire overflow;

    fibonacci_generator dut (
        .clk(clk),
        .enble(enble),
        .fib_out(fib_out),
        .overflow(overflow)
    );

    // Clock generation: 10ns period
    always #5 clk = ~clk;

    initial begin

        clk = 0;
        enble = 1;

        // Simulate the Fibonacci sequence for the first 15 terms
        repeat (15) begin
            @(posedge clk);
            #1; // Delay for visibility in waveforms
            $display("Fibonacci Output: %d, Overflow: %b", fib_out, overflow);
        end

        $finish;
    end
endmodule
