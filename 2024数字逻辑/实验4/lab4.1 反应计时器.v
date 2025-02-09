//顶层模块
module top(
    input clk,
    input rst,
    input key,
    output [4:0]led,
    output [7:0]seg,
    output [1:0]pos
    );
    wire clk_light,clk_num,clk_react,key_de;
    wire flag;
    wire[7:0]timegap; 
    debounce de( 
        .clk(clk),
        .Button(key),
        .Button_stable(key_de)
    );
    counter counter(
        .clk(clk),
        .rst(rst),
        .clk_light(clk_light),
        .clk_num(clk_num),
        .clk_react(clk_react)
    );
    light light(
        .clk(clk),
        .clk_light(clk_light),
        .rst(rst),
        .key(key_de),
        .led(led),
        .flag(flag)
    );
    react react(
        .clk(clk),
        .clk_react(clk_react),
        .flag(flag),
        .rst(rst),
        .key(key_de),
        .timegap(timegap)
    );
    show show(
        .num(timegap),
        .clk_num(clk_num),
        .seg(seg),
        .pos(pos)
    );   
endmodule

//消抖模块
module debounce(
    input clk,
    input Button,      //key
    output wire Button_stable 
);

    reg [19:0] counter;         // 计时器
    reg b1, b2, b3;             // 按键的三次采样值
    reg stable_state;           // 稳定状态

    always @(posedge clk) begin
        if (counter < 500000) begin     //常见抖动持续时间
            counter <= counter + 1'b1;
        end else begin
            counter <= 0;
            b3 <= b2; 
            b2 <= b1; 
            b1 <= Button;
            // 判断稳定状态
            stable_state <= (b1 == b2 && b2 == b3) ? b1 : stable_state;
        end
    end
    assign Button_stable = stable_state;
endmodule


//分频模块
module counter(
    input clk,rst,
    output clk_light,clk_react,clk_num
);
    reg [13: 0]cnt_first;
    reg [13:0]cnt_light;
    reg [7:0]cnt_react;

//三个时钟周期    
    //clk_num (0.1ms)(0-10^(-4))  数码管显示时钟
    always @(posedge clk)
        if(rst)
            cnt_first<=14'd0;
        else if(cnt_first==14'd10000)
            cnt_first<=14'd0;
        else
            cnt_first<=cnt_first+1'b1;
    assign clk_num=cnt_first==14'd10000 ? 1'b1 : 1'b0;

    //clk_light  clk_light的周期=10000个clk周期=1s
    //小灯1s亮一下
    always @(posedge clk)
        if(rst)
            cnt_light<=14'd0;
        else if(cnt_light==14'd10000)//cnt_light计数达到1万清零
            cnt_light<=14'd0;
        else if(cnt_first==14'd10000)
            cnt_light<=cnt_light+1'b1;
    assign clk_light=cnt_light==14'd10000 ? 1'b1 : 1'b0;

    //clk_react clk_react的周期=100个clk周期=1ms
    //要求;10ms一个时间
    always @(posedge clk)
        if(rst)
            cnt_react<=8'd0;
        else if(cnt_react==8'd100)//cnt_react计数达到100清零
            cnt_react<=8'd0;
        else if(cnt_first==14'd10000)
            cnt_react<=cnt_react+1'b1;
    assign clk_react=
           (cnt_react==8'd100 ? 1'b1 : 1'b0);
    
endmodule


//灯闪烁模块
module light (
    input clk,
    input clk_light,
    input rst,
    input key,
    output reg[4:0]led,  //五个灯信号，为1表示亮
    output reg flag      //灯全部熄灭信号
);

    wire [31:0] gap = 32'd100000000 + $urandom_range(0,32'd200000000);  //随机间隔生成
    
    //led闪烁
    reg start = 0;
    always @(posedge clk_light,posedge rst,posedge flag)begin
        if(rst||flag)begin
            led<=5'b0;
            start<=0;
        end
        else if(!flag) begin
        led<={led[3:0],1'b1};
        if(led==5'b11111) start<=1;
        end
    end   
    //计时
    reg [31:0]count=0;
    always @(posedge clk)begin
        if(rst)begin
            count<=0;
            flag<=0;
        end 
        else begin
            if(key) flag<=1;
            else  begin
                if(start)
                 begin    //控制灯灭
                    count<=count+1;
                    if(count==gap)
                    begin
                        flag<=1;
                        count<=0;
                    end
                end
            end
        end
    end
endmodule


//反应模块
module react(
    input clk,clk_react,rst,
    input flag,               //所有灯全灭为1
    input key,                //按下按钮信号
    output reg [7:0]timegap //时间间隔输出
);
//计数器
    reg [7:0]cnt=0;
    always @(posedge clk)begin
        if(rst) cnt<=0;
        if(flag)begin
            if(clk_react)begin
                if(cnt>=99)
                    cnt<=8'd99;
                else 
                    cnt<=cnt+1;
            end
        end
    end

//时间间隔输出
    always @(posedge key,posedge rst)begin
        if(rst) timegap<=0;
        else begin
            if(cnt<=10) timegap<=8'd99;     //小于10*10ms，作弊
            else timegap<=cnt;
        end
    end
endmodule

//数码管显示模块
module show (
    input[7:0]num,
    input clk_num,
    output reg[7:0]seg,
    output reg[1:0]pos
);
    reg state=0;
    reg[3:0]show_num;
    always @(posedge clk_num) begin
        state=~state;
        if(state)begin
            pos<=2'b10;
            show_num<=num/10;
        end
        else begin
            pos<=2'b01;
            show_num<=num%10;
        end
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
            default: seg = 8'b0000_1000; 
        endcase
    end
endmodule