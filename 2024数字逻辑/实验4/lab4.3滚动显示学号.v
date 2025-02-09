//顶层模块
module top(
    input clk,
    input rst,
    output [3:0]pos,
    output [7:0]seg
    );
    wire clk_roll,clk_show;
    wire[15:0]num;
    counter counter(
        .clk(clk),
        .rst(rst),
        .clk_roll(clk_roll),
        .clk_show(clk_show)
    );
    rolling rolling(
        .clk(clk),
        .clk_roll(clk_roll),
        .rst(rst),
        .num(num)
    );
    show show(
        .clk_show(clk_show),
        .num(num),
        .pos(pos),
        .seg(seg)
    );
endmodule

//时钟分频模块
module counter(
    input  wire clk,
    input  wire rst,
    output wire clk_roll,
    output wire clk_show
);
    reg [13:0]cnt_first=0;
    reg [13:0]cnt_roll=0;
    reg [7:0]cnt_show=0;

    //10000Hz
    always @(posedge clk)
        if(rst)
            cnt_first<=14'd0;
        else if(cnt_first==14'd10000)
            cnt_first<=14'd0;
        else
            cnt_first<=cnt_first+1'b1;

    //clk_roll   1Hz 滚动速度
    always @(posedge clk)
        if(rst)
            cnt_roll<=14'd0;
        else if(cnt_roll==14'd10000)
            cnt_roll<=14'd0;
        else if(cnt_first==14'd10000)
            cnt_roll<=cnt_roll+1'b1;
    assign clk_roll=cnt_roll==14'd10000 ? 1'b1 : 1'b0;

    //clk_show   取整200Hz（手册190Hz）数码管显示速度
    always @(posedge clk)
        if(rst)
            cnt_show<=8'd0;
        else if(cnt_show==8'd50)
            cnt_show<=8'd0;
        else if(cnt_first==14'd10000)
            cnt_show<=cnt_show + 1'b1;
    assign clk_show=(cnt_show==8'd50 ? 1'b1 : 1'b0);
endmodule

//学号滚动模块
module rolling (
    input clk,
    input clk_roll,
    input rst,
    output[15:0]num
);
    reg [39: 0] msgArray=40'ha202342489;
    parameter NUMBER=40'ha202342489;
    assign num=msgArray[39:24];

    always @(posedge clk)begin
        if(rst) msgArray<=NUMBER;
        else if(clk_roll)begin
            msgArray<={msgArray[35:0],msgArray[39:36]};
        end
    end       
endmodule

//数码管显示模块
module show (
    input clk_show,
    input [15:0]num,
    output reg[3:0]pos,
    output reg[7:0]seg
);
    reg [1:0]state=0;
    reg[3:0]show_num;
    always @(posedge clk_show) begin
        state<=state+1'b1;
        case(state)
            0:begin
                pos<=4'b0001;
                show_num<=num[3:0];
            end
            1:begin
                pos<=4'b0010;
                show_num<=num[7:4];
            end
            2:begin
                pos<=4'b0100;
                show_num<=num[11:8];
            end
            3:begin
                pos<=4'b1000;
                show_num<=num[15:12];
            end
        endcase
    end
    always @(show_num) begin
        case (show_num)
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
            4'b1010: seg = 8'b0011_1110; 
            default: seg = 8'b0000_1000; 
        endcase
    end
endmodule
