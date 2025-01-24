module pipeline_adder(
    input wire clk,
    input wire [31:0] a,
    input wire [31:0] b,
    input wire cin,
    output wire cout,
    output wire [31:0] sum
);

    reg cout_stage1, cout_stage2, cout_stage3, cout_stage4;
    reg [7:0] partial_sum1;
    reg [15:0] partial_sum2;
    reg [23:0] partial_sum3;
    reg [31:0] partial_sum4;
    reg [23:0] remaining_a1, remaining_b1;
    reg [15:0] remaining_a2, remaining_b2;
    reg [7:0] remaining_a3, remaining_b3;

    always @(posedge clk) begin
        {cout_stage1, partial_sum1} <= {1'b0, a[7:0]} + {1'b0, b[7:0]} + {7'b0000_000, cin};
        remaining_a1 <= a[31:8];
        remaining_b1 <= b[31:8];
    end

    always @(posedge clk) begin
        {cout_stage2, partial_sum2[15:8]} <= {1'b0, remaining_a1[7:0]} + {1'b0, remaining_b1[7:0]} + {7'b0000_000, cout_stage1};
        partial_sum2[7:0] <= partial_sum1;
        remaining_a2 <= remaining_a1[23:8];
        remaining_b2 <= remaining_b1[23:8];
    end

    always @(posedge clk) begin
        {cout_stage3, partial_sum3[23:16]} <= {1'b0, remaining_a2[7:0]} + {1'b0, remaining_b2[7:0]} + {7'b0000_000, cout_stage2};
        partial_sum3[15:0] <= partial_sum2;
        remaining_a3 <= remaining_a2[15:8];
        remaining_b3 <= remaining_b2[15:8];
    end

    always @(posedge clk) begin
        {cout_stage4, partial_sum4[31:24]} <= {1'b0, remaining_a3[7:0]} + {1'b0, remaining_b3[7:0]} + {7'b0000_000, cout_stage3};
        partial_sum4[23:0] <= partial_sum3;
    end

    assign sum = partial_sum4;
    assign cout = cout_stage4;

endmodule