//顶层模块
module top(
    input clk,
    input up,
    input down,
    input left,
    input right,
    input rst,
    output [3:0]pos1,
    output [7:0]seg1,
    output [3:0]pos2,
    output [7:0]seg2
    );
    wire clk_down,clk_show;
    wire up_de,down_de,left_de,right_de;
    wire [15:0]nowtime,num;
    //分别去抖up down left right
    debounce de1(
        .clk(clk),
        .Button(up),
        .Button_stable(up_de)
    );
    debounce de2(
        .clk(clk),
        .Button(down),
        .Button_stable(down_de)
    );
    debounce de3(
        .clk(clk),
        .Button(left),
        .Button_stable(left_de)
    );
    debounce de4(
        .clk(clk),
        .Button(right),
        .Button_stable(right_de)
    );
    counter counter(
        .clk(clk),
        .rst(0),
        .clk_down(clk_down),
        .clk_show(clk_show)
    );
    timedown timedown(
        .clk_down(clk_down),
        .rst(rst),
        .nowtime(nowtime)
    );
    myinput myinput(
        .up(up_de),
        .down(down_de),
        .left(left_de),
        .right(right_de),
        .rst(rst),
        .num(num)
    );
    show show1(
        .clk_show(clk_show),
        .num(nowtime),
        .pos(pos1),
        .seg(seg1)
    );
    show show2(
        .clk_show(clk_show),
        .num(num),
        .pos(pos2),
        .seg(seg2)
    );
endmodule

//防消抖模块
module debounce(
    input clk,
    input Button,
    output wire Button_stable 
);

    reg [19:0]counter;           // 计时器
    reg b1,b2,b3;               // 采样值
    reg stable_state;           // 稳定状态

    always @(posedge clk) begin
        if (counter<500000) begin
            counter<=counter + 1'b1;
        end else begin
            counter<=0;
            b3<=b2; 
            b2<=b1; 
            b1<=Button;
            // 判断稳定状态
            if (b1==b2&&b2==b3) 
            begin
            stable_state<=b1;
            end
        end
    end
    assign Button_stable=stable_state;
endmodule

//时钟分频模块
module counter(
    input  wire clk,
    input  wire rst,
    output wire clk_down,
    output wire clk_show
);
    reg [13: 0] cnt_first=0;
    reg [13:0]cnt_down=0;
    reg [7:0]cnt_show=0;

    always @(posedge clk)
        if(rst)
            cnt_first <= 14'd0;
        else if(cnt_first == 14'd10000)
            cnt_first <= 14'd0;
        else
            cnt_first <= cnt_first + 1'b1;

    //倒计时 1s/次
    always @(posedge clk)
        if(rst)
            cnt_down <= 14'd0;
        else if(cnt_down == 14'd10000)
            cnt_down <= 14'd0;
        else if(cnt_first == 14'd10000)
            cnt_down <= cnt_down + 1'b1;
    assign clk_down = cnt_down == 14'd10000 ? 1'b1 : 1'b0;

    //数码管显示 200Hz（190Hz取整）
    always @(posedge clk)
        if(rst)
            cnt_show<= 8'd0;
        else if(cnt_show == 8'd50)
            cnt_show <= 8'd0;
        else if(cnt_first == 14'd10000)
            cnt_show <= cnt_show + 1'b1;
    assign clk_show = cnt_show == 8'd50 ? 1'b1 : 1'b0;
endmodule

//倒计时模块
module timedown (
    input clk_down,
    input rst,
    output [15:0]nowtime
);
    reg [10:0]cnt=11'd99;   //初始化为99s开始
    reg [7:0]name=8'hbc;
    wire [3:0]num1,num2;
    
    assign num1=cnt/10;  //存放十位
    assign num2=cnt%10;  //存放个位
    assign nowtime={name,num1,num2};
    
    always @(posedge clk_down,posedge rst) begin
        if(rst)cnt<=cnt;
        else if(clk_down)begin
            if(cnt==0)cnt<=99;//从99s开始继续
            else cnt<=cnt-1;
        end
    end
endmodule

//输入学号模块
module myinput (
    input up,
    input down,
    input left,
    input right,
    input rst,
    output[15:0]num
);
    reg[3:0]num3=0,num2=0,num1=0,num0=0;     //数字的千位、百位、十位和个位，初值给0
    assign num={num3,num2,num1,num0};
    reg [1:0]pos=0;                            //存储当前选中的数字位（0-3）
    
    //left和right按钮来选择数字的位
    always @(posedge left,posedge right,posedge rst) begin
        if(rst)pos<=3;
        else begin
            if(left)begin
                if(pos==3) pos<=0;       //回到个位
                else       pos<=pos+1;   //下一位移进来
            end
            else begin
                if(pos==0)pos<=3;
                else pos<=pos-1;
            end
        end
    end
    //up和down按钮来增加或减少当前选中位的数值
    always @(posedge rst,posedge up,posedge down) begin 
        if (rst) begin
            num0<=0;
            num1<=0;
            num2<=0;
            num3<=0;
        end else begin
            if (up) begin
                case(pos)
                    0:begin
                        if (num0==4'd9) num0<=0;
                        else num0<=num0+1;
                    end
                    1:begin
                        if (num1==4'd9) num1<=0;
                        else num1<=num1+1;
                    end
                    2:begin
                        if (num2==4'd9) num2<=0;
                        else num2<=num2+1;
                    end
                    3:begin
                        if (num3==4'd9) num3<=0;
                        else num3<=num3+1;
                    end
                endcase  
            end else if (down) begin
                case(pos)
                    0:begin
                        if (num0==4'd0) num0<=9;
                        else num0<=num0-1;
                    end
                    1:begin
                        if (num1==4'd0) num1<=9;
                        else num1<=num1-1;
                    end
                    2:begin
                        if (num2==4'd0) num2<=9;
                        else num2 <= num2-1;
                    end
                    3:begin
                        if (num3==4'd0) num3<=9;
                        else num3<=num3-1;
                    end
                endcase
            end
        end
    end
endmodule

//数码管显示模块
module show (
    input clk_show,
    input [15:0]num,  //输入的数据总线
    output reg[3:0]pos,//数码管计数器
    output reg[7:0]seg //数据的一部分
);
    reg [1:0]state=0;
    reg [3:0]show_num; 
    always @(posedge clk_show) begin
        state<=state+1'b1;
        case(state)
        //将数据总线的3:0位显示在第一个数码管上
            0:begin
                pos<=4'b0001;
                show_num<=num[3:0];
            end
            //将数据总线的7:4位显示在第2个数码管上
            1:begin
                pos<=4'b0010;
                show_num<=num[7:4];
            end
            //将数据总线的11:8位显示在第3个数码管上
            2:begin
                pos<=4'b0100;
                show_num<=num[11:8];
            end
             //将数据总线的15:12位显示在第3个数码管上
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
            4'b1010: seg = 8'b0011_1110; //U
            4'b1011: seg = 8'b0011_1000; //L
            4'b1100: seg = 8'b0101_1010; //Z
            default: seg = 8'b0000_1000; 
        endcase
    end
endmodule
