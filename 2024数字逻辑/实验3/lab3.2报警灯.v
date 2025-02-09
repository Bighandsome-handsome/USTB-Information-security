//数码管显示
`timescale 1ns / 1ps
module segMsg(
    input [3:0] data, 
    output reg [3:0] pos,
    output reg [7:0] seg  
);
    always @(data) begin
        pos = 4'b0001;
        case (data)
            4'b0000: seg = 8'b0011_1111; 
            4'b0001: seg = 8'b0000_0110; 
            4'b0010: seg = 8'b0101_1011; 
            4'b0011: seg = 8'b0100_1111; 
            4'b0100: seg = 8'b0110_0110; 
            4'b0101: seg = 8'b0110_1101; 
            4'b0110: seg = 8'b0111_1101; 
            4'b0111: seg = 8'b0000_0111; 
            4'b1000: seg = 8'b0111_1111; 
            4'b1001: seg = 8'b0110_1111; 
            default: seg = 8'b0000_1000; 
        endcase
    end
endmodule

//消抖模块
`timescale 1ns / 1ps
module remove_shake(
    input clk,         
    input rst,         
    input B1,          
    output reg B1_out  
);
    reg [2:0] judge = 0;     
    reg [20:0] counter = 0;  
    always @ (posedge clk) begin
        if (rst) begin
            judge <= 0;  
            counter <= 0;              
        end
        else begin
            counter <= counter + 1;       
            if (counter == 100000) begin  
                counter <= 0;             
                judge = {judge[1:0], B1}; 
            end
            if (judge[0] == judge[1] == judge[2]) begin
                B1_out = (judge[0] & judge[1] & judge[2]);  
            end
        end
    end
endmodule

//报警灯模块
`timescale 1ns / 1ps
module warning(
    input B1,     
    input B2,     
    input K1,     
    input K2,     
    input clk,    
    input rst_n,     
    output wire [3:0] pos, 
    output reg L1,  
    output wire [7:0] seg  
);
    wire rst, sta_B1; 
    reg [3:0] data = 0;  
    assign rst = ~rst_n;  
    reg able = 0; 
    reg B1_prev = 0;  
    reg [30:0] counter;  
    reg [30:0] speed = 100000000;  
remove_shake rm(  
    .B1(B1),
    .clk(clk),
    .rst(rst),
    .B1_out(sta_B1)
);
segMsg num(  
    .data(data),
    .pos(pos),
    .seg(seg)
);
always @(posedge clk) begin
    speed <= 100000000 >> (K1 + (2 * K2)); 
    if (rst) begin 
        able <= 0;     
        B1_prev <= 0;  
        counter <= 0;  
        L1 <= 0;       
        data <= 0;     
    end
    else if(sta_B1 && ~B1_prev) begin  
        able <= ~able;  
        if(able == 0)  
            data <= data + 1;
    end
        B1_prev <= sta_B1; 
    if (B2) begin 
        data <= 1;  
    end
    if (able) begin  
        counter <= counter + 1;  
        if (counter >= speed / (data + 1)) begin 
            counter <= 0; 
            L1 <= ~L1;  
        end
    end else begin
        counter <= 0;  
        L1 <= 0;  
    end
end
endmodule