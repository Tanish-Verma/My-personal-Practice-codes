`timescale 1ns/100ps

module fibonacci_generator (
    input wire clk,
    input wire enble,
    output reg [7:0] fib_out,
    output reg overflow
);

    reg [7:0] fib_prev = 8'd0;     // Previous Fibonacci number
    reg [7:0] fib_current = 8'd1;  // Current Fibonacci number

    always @(posedge clk) begin
        if (enble) begin
            // Check for overflow before calculating the next term
            if (fib_current + fib_prev > 8'hFF) begin
                overflow <= 1'b1;
                fib_out <= 8'hFF; // Saturate to maximum 8-bit value
            end else begin
                overflow <= 1'b0;
                fib_out <= fib_current;

                // Calculate the next Fibonacci number
                {fib_prev, fib_current} <= {fib_current, fib_current + fib_prev};
            end
        end
    end
endmodule
