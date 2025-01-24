module top_module(
    input  clk,
    input  areset,    // FallingReshly brainwashed Lemmings walk left.
    input  bump_left,
    input  bump_right,
    input  ground,
    input  dig,
    output reg walk_left,
    output reg walk_right,
    output reg aaah, 
    output reg digging 
);

    reg [2:0] state, next_state;
    parameter WalkingLeft = 3'b000, WalkingRight = 3'b001, FallingLeft = 3'b010, 
              FallingRight = 3'b11, DiggingRight = 3'b100, DiggingLeft = 3'b101;
    
    // 定义状态对应的输出值
    function [3:0] state_to_output(input [2:0] s);
        case(s)
            WalkingLeft: state_to_output = 4'b1000;
            WalkingRight: state_to_output = 4'b0100;
            FallingLeft: state_to_output = 4'b0010;
            FallingRight: state_to_output = 4'b0010;
            DiggingLeft: state_to_output = 4'b0001;
            DiggingRight: state_to_output = 4'b0001;
            default: state_to_output = 4'b0000; // 可以添加默认值以处理未定义的状态
        endcase
    endfunction

    // 状态转换逻辑
    always @(*) begin
        case(state)
            WalkingLeft: begin
                if (!ground) begin
                    next_state = FallingLeft;
                end else if (dig) begin
                    next_state = DiggingLeft;
                end else if (bump_left) begin
                    next_state = WalkingRight;
                end else begin
                    next_state = WalkingLeft;
                end
            end
            WalkingRight: begin
                if (!ground) begin
                    next_state = FallingRight;
                end else if (dig) begin
                    next_state = DiggingRight;
                end else if (bump_right) begin
                    next_state = WalkingLeft;
                end else begin
                    next_state = WalkingRight;
                end
            end
            FallingLeft: begin
                if (ground) begin
                    next_state = WalkingLeft;
                end else begin
                    next_state = FallingLeft;
                end
            end
            FallingRight: begin
                if (ground) begin
                    next_state = WalkingRight;
                end else begin
                    next_state = FallingRight;
                end
            end
            DiggingLeft: begin
                if (ground) begin
                    next_state = DiggingLeft;
                end else begin
                    next_state = FallingLeft;
                end
            end
            DiggingRight: begin
                if (ground) begin
                    next_state = DiggingRight;
                end else begin
                    next_state = FallingRight;
                end
            end
            default: next_state = WalkingLeft; // 可以添加默认值以处理未定义的状态
        endcase
    end

    // 状态更新
    always @(posedge clk or posedge areset) begin
        if (areset) begin
            state <= WalkingLeft;
        end else begin
            state <= next_state;
        end
    end

    // 输出更新
    always @(*) begin
        {walk_left, walk_right, aaah, digging} = state_to_output(state);
    end

endmodule