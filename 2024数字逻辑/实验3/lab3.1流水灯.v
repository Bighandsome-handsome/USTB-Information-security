/*
这是计数器模块
该模块的功能是根据输入的开关状态生成一个低频时钟信号，频率由开关的数量决定。
计数器的设计使得在不同的开关状态下，能够动态调整低频时钟的频率。
*/

`timescale 1ns / 1ps
module counter(
    input  wire clk,       
    input  wire rst,        
    input wire [7:0] num_switch, 
    output wire clk_bps       // 输出低频时钟信号
);
    reg [23: 0] cnt_first, cnt_second; // 用于计数的寄存器
    reg [23:0] count_limit;             // 计数限制值
    reg [3:0] num;                      // 计算高电平开关数量的寄存器

    // 计算num_switch中高电平开关的数量
  // 实时计算num_switch各位之和  
    always @(posedge clk or posedge rst)begin  
       // if (rst)  
       // num <= 4'd0;  
       // else  
        num = num_switch[0] + num_switch[1] + num_switch[2] + num_switch[3] +  
              num_switch[4] + num_switch[5] + num_switch[6] + num_switch[7];  
         if(num==4||rst)
         num<=4'd0;
    end  

    // 根据高电平开关数量设置计数限制
    always@(*) begin
        if(num == 4)
            count_limit = 24'd10000; // 如果高电平开关数量为4，设置计数限制为10000
        else if(num > 4)
            count_limit = (24'd10000 / (num - 4)) * 8; // 如果数量大于4，动态调整计数限制
        else if(num < 4)
            count_limit = (24'd10000 / (4 - num)) * 8; // 如果数量小于4，动态调整计数限制
    end

    // 第一个计数器逻辑
    always @(posedge clk) begin
        if(rst)
            cnt_first <= 24'd0; 
        else if(cnt_first == 24'd10000) 
            cnt_first <= 24'd0; 
        else
            cnt_first <= cnt_first + 1'b1; 
    end

    // 第二个计数器逻辑
    always @(posedge clk) begin
        if(rst)
            cnt_second <= 24'd0; 
        else if(cnt_second == count_limit) // 计数达到设定的限制
            cnt_second <= 24'd0; 
        else if(cnt_first == 24'd10000) 
            cnt_second <= cnt_second + 1'b1; 
    end

    // 生成低频时钟信号
    assign clk_bps = (cnt_second == count_limit) ? 1'b1 : 1'b0; // 第二个计数器达到限制，输出高电平

endmodule

`timescale 1ns / 1ps

module flash_led_ctl(
    input clk,         
    input rst,             
    input dir,                // 方向
    input clk_bps,            // 输入低频时钟信号
    output reg [15:0] led     // 输出16位LED状态
);

    // 在时钟上升沿或复位信号上升沿触发
    always @(posedge clk or posedge rst) 
        if (rst)
            led <= 16'h8000; // 将LED状态初始化为1000 0000 0000 0000（点亮最高位LED）
        else
            case (dir)
                1'b0: 
                    if (clk_bps) // 当低频时钟信号有效
                        if (led != 16'd1) 
                            led <= led >> 1'b1; // 将LED状态右移一位
                        else 
                            led <= 16'h8000; 
                1'b1: 
                    if (clk_bps) // 当低频时钟信号有效
                        if (led != 16'h8000) 
                            led <= led << 1'b1; // 将LED状态左移一位
                        else
                            led <= 16'd1;
            endcase
endmodule

`timescale 1ns / 1ps
module flash_led_top(
    input clk,               
    input rst_n,             // 输入复位信号（低有效）
    input sw0,             
    input [7:0] num_switch,  
    output [15:0] led      
);
    wire clk_bps;            // 低频时钟信号
    wire rst;              
    reg dir;                 // LED闪烁方向
    reg clk_bps_ctrl;        // 控制低频时钟信号
    assign rst = ~rst_n;    

    // 计算num_switch中高电平开关的数量
    wire [3:0] num_high = 
        num_switch[0] + num_switch[1] + num_switch[2] + 
        num_switch[3] + num_switch[4] + num_switch[5] + 
        num_switch[6] + num_switch[7];

    counter counter_inst (
        .clk(clk),          
        .rst(rst),            
        .num_switch(num_switch),
        .clk_bps(clk_bps)     
    );

    // 根据num_high的值确定LED闪烁方向
    always @(posedge clk) begin
        if (num_high < 4)
            dir = ~sw0;   
        else
            dir = sw0;    
    end

    // 控制低频时钟信号
    always @(posedge clk) begin
        if (num_high == 4)
            clk_bps_ctrl <= 0; //stop
        else
            clk_bps_ctrl <= clk_bps; // 保持低频时钟信号
    end

    flash_led_ctl flash_led_ctl_inst (
        .clk(clk),        
        .rst(rst),             
        .dir(dir),              
        .clk_bps(clk_bps_ctrl), 
        .led(led)         
    );

endmodule



//以下是仿真代码
`timescale 1ns / 1ps
module flash_led_top_tb; // 测试模块的定义
    reg clk;                    // 时钟信号
    reg rst_n;                  // 复位信号（低有效）
    reg sw0;                    // 方向控制开关
    reg [7:0] num_switch;       // 8位开关状态
    wire [15:0] led;            // LED状态输出

    // 实例化待测试的模块
    flash_led_top uut (
        .clk(clk),              // 连接时钟信号
        .rst_n(rst_n),          // 连接复位信号
        .sw0(sw0),              // 连接方向控制开关
        .num_switch(num_switch),// 连接开关状态
        .led(led)               // 连接LED输出
    );

    // 生成100 MHz的时钟信号
    always #5 clk = ~clk;  // 每5ns翻转一次时钟信号，周期为10ns，对应频率为100 MHz

    // 初始块，用于设置测试环境
    initial begin
        // 初始化信号
        clk = 0;               // 初始化时钟为0
        rst_n = 0;             // 初始化复位信号为0（有效）
        sw0 = 0;               // 初始化方向控制开关为0
        num_switch = 8'b00000000;  // 初始化开关状态为全0

        // 释放复位信号
        #10 rst_n = 1;  // 10ns后将复位信号设为1，解除复位

        // 测试用例1：设置num_switch为1，num_high应为0
        #20 num_switch = 8'b00000001;  // 设置开关状态为1
        #1000; // 等待1000ns

        // 测试用例2：设置num_switch为3，num_high应为3
        num_switch = 8'b00000111;  // 设置开关状态为3
        #1000; // 等待1000ns

        // 测试用例3：设置num_switch为4，num_high应为4
        num_switch = 8'b00001111;  // 设置开关状态为4
        #1000; // 等待1000ns

        // 测试用例4：设置num_switch为6，num_high应大于4
        num_switch = 8'b00111111;  // 设置开关状态为6
        sw0 = 1;  // 设置方向控制开关为1
        #1000; // 等待1000ns

        // 测试用例5：设置num_switch为8，num_high应为8
        num_switch = 8'b11111111;  // 设置开关状态为8
        #100; // 等待100ns

        // 停止仿真
        $stop; // 停止仿真
    end
endmodule