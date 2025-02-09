//顶层模块
module top(
    input clk,rst,
    output led
    );
    wire clk_bps;
    counter counter(
        .clk(clk),
        .rst(rst),
        .clk_bps(clk_bps)
    );
    breathing_led breathing_led(
        .clk(clk),
        .clk_bps(clk_bps),
        .rst(rst),
        .led(led)
    );

endmodule

//时钟分频模块
module counter(
    input  wire clk,
    input  wire rst,
    output wire clk_bps
);
    reg [13: 0] cnt_first;

    always @(posedge clk)   //0.1ms分频
        if(rst)
            cnt_first<=14'd0;
        else if(cnt_first==14'd10000)
            cnt_first<=14'd0;
        else
            cnt_first<=cnt_first+1'b1;
    assign clk_bps=(cnt_first==14'd10000 ? 1'b1 : 1'b0);
endmodule

//呼吸灯模块（调整占空比）
module breathing_led(
    input  clk, 
    input  clk_bps,      
    input  rst,        
    output reg led        
);
    reg [15:0]pwm=0;   //控制LED亮度，pwm和亮度成正比
    reg [8:0]cnt=0; 
    reg up=1;          //控制pwn方向实现控制亮度渐变效果
    always @(posedge clk_bps,posedge rst)begin
        if(rst)begin
            cnt<=0;
            pwm<=0;
            up<=1;
        end
        else begin
            if(clk_bps)begin
                if(cnt==100)begin  //100个clk更新
                    cnt<=0; 
                    if(up)begin
                        if(pwm==16'd10000)up<=0;
                        else pwm<=pwm+16'd100;
                    end
                    else begin
                        if(pwm==16'd0)up<=1; 
                        else pwm<=pwm-16'd100;
                    end
                end
                else cnt<=cnt+1;
            end
        end
    end 
    reg[16:0]cnt_led=0;
    always@(posedge clk)begin
        if(rst)begin
            led<=0;
            cnt_led<=0;
        end
        else begin
            if(cnt_led==16'd10000)cnt_led<=0;
            else begin
                cnt_led<=cnt_led+1;
                if(cnt_led<=pwm)led<=1;
                else led<=0;
            end
        end
    end
endmodule