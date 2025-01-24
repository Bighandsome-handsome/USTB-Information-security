module top_module(
    input clk,
    input areset,    // Freshly brainwashed Lemmings walk left.
    input bump_left,
    input bump_right,
    input ground,
    output reg walk_right,
    output reg walk_left,
    output reg aaah 
);

    reg [1:0] state, next_state;
    parameter WalkLeft = 2'b00, WalkRight = 2'b01, FlyLeft = 2'b10, FlyRight = 2'b11;
    
    // 定义状态对应的输出值
    function [2:0] state_to_output(input [1:0] s);
        case(s)
            WalkLeft: state_to_output = 3'b100;
            WalkRight: state_to_output = 3'b010;
            FlyLeft: state_to_output = 3'b001;
            FlyRight: state_to_output = 3'b001;
            default: state_to_output = 3'b000; 
        endcase
    endfunction

    // 状态转换逻辑
    always @(*) begin
        case(state)
            WalkLeft: next_state = ground ? (bump_left ? WalkRight : WalkLeft) : FlyLeft;
            WalkRight: next_state = ground ? (bump_right ? WalkLeft : WalkRight) : FlyRight;
            FlyLeft: next_state = ground ? WalkLeft : FlyLeft;
            FlyRight: next_state = ground ? WalkRight : FlyRight;
            default: next_state = WalkLeft ; 
        endcase
    end

    // 状态更新
    always @(posedge clk or posedge areset) begin
        if (areset) begin
            state <= WalkLeft;
        end else begin
            state <= next_state;
        end
    end

    // 输出更新
    always @(*) begin
        {walk_left, walk_right, aaah} = state_to_output(state);
    end

endmodule