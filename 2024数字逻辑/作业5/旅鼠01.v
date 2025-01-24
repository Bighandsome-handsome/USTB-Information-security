`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2024/12/12 13:12:35
// Design Name: 
// Module Name: 旅鼠01
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
/////////////////////////////////////////////////////////
module top_module(
    input clk,
    input areset,    // Freshly brainwashed Lemmings walk left.
    input bump_left,
    input bump_right,
    output walk_left,
    output walk_right
);

    reg left_reg = 1'b1, right_reg = 1'b0;
    always @(posedge clk) begin
        if (areset) begin
            left_reg  <= 1'b1;
            right_reg <= 1'b0;
        end else begin
            if (bump_left + bump_right == 1) begin
                left_reg  <= ~bump_left;
                right_reg <= bump_left;
            end
            else if (bump_left + bump_right == 2) begin
                left_reg  <= ~left_reg;
                right_reg <= ~right_reg;
            end
        end
    end
    assign walk_left  = left_reg;
    assign walk_right = right_reg;

endmodule