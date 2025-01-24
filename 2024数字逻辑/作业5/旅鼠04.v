//`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: l
// 
// Create Date: 2024/12/12 17:40:23
// Design Name: 
// Module Name: 旅鼠04
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
    input ground,
    input dig,
    output reg  walk_left,
    output  reg walk_right,
    output  reg aaah,
    output  reg digging 
    );

    parameter WalkLeft = 3'b00, WalkRight = 3'b001, 
              FlyLeft = 3'b010, FlyRight = 3'b011,
              DigLeft = 3'b100, DigRight = 3'b101,
              Splat = 3'b110;
    reg [100:0] counter;
    reg [2:0] state,next;

    //状态转移函数
    always @(*) begin
    if (state == WalkLeft) begin
        if (ground) begin
            if (dig)
                next = DigLeft;
            else if (bump_left)
                next = WalkRight;
            else
                next = WalkLeft;
        end else begin
            next = FlyLeft;
        end
    end else if (state == WalkRight) begin
        if (ground) begin
            if (dig)
                next = DigRight;
            else if (bump_right)
                next = WalkLeft;
            else
                next = WalkRight;
        end else begin
            next = FlyRight;
        end
    end else if (state == FlyLeft) begin
        if (ground) begin
            if (counter > 19)
                next = Splat;
            else
                next = WalkLeft;
        end else begin
            next = FlyLeft;
        end
    end else if (state == FlyRight) begin
        if (ground) begin
            if (counter > 19)
                next = Splat;
            else
                next = WalkRight;
        end else begin
            next = FlyRight;
        end
    end else if (state == DigLeft) begin
        if (ground)
            next = DigLeft;
        else
            next = FlyLeft;
    end else if (state == DigRight) begin
        if (ground)
            next = DigRight;
        else
            next = FlyRight;
    end else if (state == Splat) begin
        next = Splat;
    end else begin
        next = Splat; 
    end
end

    //时钟
    always @(posedge clk or posedge areset)
        begin
        if(areset) state <= WalkLeft;
        else if  ( state == FlyLeft || state == FlyRight)             
                          begin
                              state <= next;
                              counter = counter + 1;
                          end
 
        else begin 
            state <= next;  
            counter = 0;
        end
        end 
    always @(*)
        case(state)
            WalkLeft : {walk_left,walk_right,aaah,digging} = 4'b1000;
            WalkRight : {walk_left,walk_right,aaah,digging} = 4'b0100;
            FlyLeft : {walk_left,walk_right,aaah,digging} = 4'b0010;
            FlyRight : {walk_left,walk_right,aaah,digging} = 4'b0010;
            DigLeft : {walk_left,walk_right,aaah,digging} = 4'b0001;
            DigRight : {walk_left,walk_right,aaah,digging} = 4'b0001;
            Splat: {walk_left,walk_right,aaah,digging} = 4'b0000;  
        endcase 

endmodule