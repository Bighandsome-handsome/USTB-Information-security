module top(
    input[7:0] order,   //指令
    input[7:0] data,    //数据
    input clk,
    input w,
    input rst,
    output [3:0]pos1, pos2,  //数码管显示
    output [7:0]seg1, seg2   
    );
    wire w_debounce,clk_show;       //消抖结果，数码管时钟
    wire[15:0] number1,number2;      //数据传输
    wire[3:0] Rin,Rout,address;      //使能信号与地址
    wire[15:0]bus;                  //总线信号
    wire Ain,Gin,Gout;               //两个寄存器reg（8位）信号
    wire addsub;                    //运算信号：加法与减法
    wire externx,Done;              //外部信号和任务完成信号，告诉bus要传数据了
    
    //消抖实例化
    debounce remove_shake(
     .clk(clk),
     .Button(w),
     .Button_stable(w_debounce)
    );
    
    //总线传输实例化
    data_transfer transfer(
       .data(data),
       .externx(externx),
       .bus(bus)
    );
    
    //数码管时钟分频模块实例化
    counter counter(
     .clk(clk),
     .rst(0),
     .clk_show(clk_show)
    );
    
    //数码管显示模块实例化
     segMsg display1(
     .clk_show(clk_show),
     .num(number1),
     .pos(pos1),
     .seg(seg1)
    );
    
    segMsg display2(
     .clk_show(clk_show),
     .num(number2),
     .pos(pos2),
     .seg(seg2)
    );
    
    //寄存器模块实例化
    regfile myregfile(
    .Reg_input(Rin),
    .Reg_output(Rout),
    .clk(clk),
    .rst(rst),
    .bus(bus)
    );
    
    //PC_Memory的模块实例化
    PC_Memory myPC(
        .bus(bus),
        .done_signal(Done),
        .address(address),
        .number1(number1),
        .number2(number2)
    );
    
    //ALU模块实例化
    ALU my_alu(
        .bus(bus),
        .Ain(Ain),
        .Gin(Gin),
        .Gout(Gout),
        .addsub(addsub),
        .clk(clk)
    );
    
    //controller实例化
        controller mycontroller(
        .clk(clk),
        .rst(rst),
        .w(w_debounce),
        .operation(order[7:4]),
        .Rx(order[3:2]),
        .Ry(order[1:0]),
        .Rin(Rin),
        .Rout(Rout),
        .Ain(Ain),
        .Gin(Gin),
        .Gout(Gout),
        .addsub(addsub),
        .externx(externx),
        .Done(Done),
        .address(address)
    );
endmodule

//这是消抖块儿，用的是lab4.1的
module debounce(
    input clk,
    input Button,
    output reg Button_stable 
 );
    reg [19:0] counter;                       
    reg button1,button2,button3;             
    reg stable_state,pre;                    
    always @(posedge clk) begin
        pre <= stable_state;
        if (counter < 500000) begin
            counter <= counter + 1'b1;
        end else begin
            counter <= 0;
            button3 <= button2; 
            button2 <= button1; 
            button1 <= Button;
            // 判断稳定状
            stable_state <= (button1 == button2 && button2 == button3) ? button1 : stable_state;
        end
    end
    always@(posedge clk)begin
        if(stable_state && !pre) Button_stable <= 1;
        else Button_stable <= 0;
    end
endmodule

//总线传输模块
//根据作业6.1，有一个外部信号externx决定是否要向总线里传输数据
module data_transfer(
    input [7:0] data,    //需要我传输的数据
    input externx,       //外部传输信号
    inout [7:0] bus    //总线数据,16位（要传乘法）
 );
    reg [7:0] bus_temp;   //临时存储数据的寄存器
    assign bus = bus_temp;
    always @(*) 
    begin
        if (externx)  bus_temp = data; 
        else          bus_temp = 8'hzz; //不能传递
    end
endmodule

//数码管显示模块，时钟分频，200Hz取整（来自与lab04.1)
module counter(
    input  wire clk,
    input  wire rst,
    output wire clk_show
 );
    reg [13: 0] cnt_first = 0;
    reg [13:0] cnt_down = 0;
    reg [7:0] cnt_show = 0;
    always @(posedge clk)
        if(rst)
            cnt_first <= 14'd0;
        else if(cnt_first == 14'd10000)
            cnt_first <= 14'd0;
        else
            cnt_first <= cnt_first + 1'b1;

    //数码管显示模块，200Hz的分频（取整，应该190Hz，差不多）
    always @(posedge clk)
        if(rst)
            cnt_show <= 8'd0;
        else if(cnt_show == 8'd50)
            cnt_show <= 8'd0;
        else if(cnt_first == 14'd10000)
            cnt_show <= cnt_show + 1'b1;
    assign clk_show = cnt_show == 8'd50 ? 1'b1 : 1'b0;
endmodule

//数码管显示模块（lab4.1提供的代码)
module segMsg(
    input clk_show,
    input [15:0] num,
    output reg[3:0] pos,
    output reg[7:0] seg
    );
    reg [1:0] state = 0;
    reg [3:0] show_num;
    always @(posedge clk_show) begin
        state <= state + 1'b1;
        case(state)
            0:begin
                pos <= 4'b0001;
                show_num <= num[3:0];
            end
            1:begin
                pos <= 4'b0010;
                show_num <= num[7:4];
            end
            2:begin
                pos <= 4'b0100;
                show_num <= num[11:8];
            end
            3:begin
                pos <= 4'b1000;
                show_num <= num[15:12];
            end
        endcase
    end
    always @(show_num) begin
        case (show_num)
            4'b0000: seg = 8'b0011_1111;  //0
            4'b0001: seg = 8'b0000_0110;  //1
            4'b0010: seg = 8'b0101_1011;  //2
            4'b0011: seg = 8'b0100_1111;  //3
            4'b0100: seg = 8'b0110_0110;  //4
            4'b0101: seg = 8'b0110_1101;  //5
            4'b0110: seg = 8'b0111_1101;  //6
            4'b0111: seg = 8'b0000_0111;  //7
            4'b1000: seg = 8'b0111_1111;  //8
            4'b1001: seg = 8'b0110_1111;  //9
            default: seg = 8'b0000_1000;  //其他情况
        endcase
    end
endmodule

//主要控制8位的，8位单个寄存器
module single_reg(
    inout [7:0] bus,         //总线上的数据
    input input_enable,      //存储器可以输入信号
    input output_enable,     //存储器可以输出信号
    input clk,               //时钟信号
 );
    reg [7:0] tempary_data;    //临时存放数据
    always @(posedge clk)
         if(input_enable)         
            tempary_data <= bus;
    assign bus = output_enable ? tempary_data: 16'hzz;
endmodule

//将一个寄存器构成一堆寄存器存储数据
module regfile(
    input [3:0] Reg_input,   //四位输入信号
    input [3:0] Reg_output,  //四位输出信号
    input clk,
    inout [15:0]bus
 );
    single_reg  myreg1(bus, Reg_input[0], Reg_output[0], clk);
    single_reg  myreg2(bus, Reg_input[1], Reg_output[1], clk);
    single_reg  myreg3(bus, Reg_input[2], Reg_output[2], clk);
    single_reg  myreg4(bus, Reg_input[3], Reg_output[3], clk);
endmodule


//PC地址和内存模块
module PC_Memory(
   input [7:0] bus,             //总线数据
    input done_signal,          //完成信号
    input [3:0] address,        //地址输入
    output reg[15:0]number1,   //寄存器输出A
    output reg[15:0]number2   //寄存器输出B
 );
    reg [3:0] result[7:0];
    reg [3:0] pc;
    initial begin               //初始化（pc=0）
        pc = 4'b0000;
    end
    always @(negedge done_signal) begin
        if(pc < 4'b1111)      //别让PC越界
        begin
        result[pc] <= bus;
        pc <= pc + 1;
        end 
        else pc <= 0;          //pc溢出，啊啊啊啊啊
    end
    always @(address) begin
        number1 = { 12'b0, address };
        number2 = { 8'b0, result[address]};
    end
endmodule

//ALU运算器
module ALU(
    inout[7:0] bus, //数据总线输入输出
    input Ain,       //A输入使能
    input Gin,      //G输入使能
    input Gout,     //G输出使能
    input addsub,   //加减选择
    input clk        
 );
  reg [7:0] regA, regG, reg_result;
  always @(addsub, regA, bus) 
    reg_result = (addsub == 1'b1) ? (regA + bus) : (regA - bus);

 always @(posedge clk) 
     begin
        if (Ain) regA <= bus;
        if (Gin) regG <= reg_result;
    end 
 assign bus = Gout ? regG : 8'hzz;  
endmodule

//控制模块（状态机）
module controller(
   input wire clk,          
    input wire rst,         
    input wire w,                  //写信号
    input wire [3:0]operation,    //功能码，用于选择不同的操作
    input wire [1:0]Rx,          //寄存器x的地址
    input wire [1:0]Ry,       //寄存器y的地址

    output reg [3:0]Rin,       //输入寄存器，用于存储输入值
    output reg [3:0]Rout,     //输出寄存器，用于存储输出值
    output reg Ain,             //算术输入使能
    output reg Gin,     //输入使能
    output reg Gout,   //输出使能
    output reg addsub, //加减使能信号
    output reg externx, //外部信号输入使能
    output reg Done, //操作完成信号
    output reg [3:0]address    //地址输出
    );
 reg [1:0] state = 0;

 //清空信号
 wire clear;
 assign clear = ~w & (state == 0) | Done | rst;   

 //状态更新函数
 always @(posedge clk or posedge clear) 
 begin
    if (clear) state <= 0;
    else state <= state + 1;
 end

 //写入数据的部分：rx，ry地址写入，操作码写入
 reg [1:0] Rx_temporary_reg;
 reg [1:0] Ry_temporary_reg;
     always @(posedge w) 
     begin
        Rx_temporary_reg <= Rx;
        Ry_temporary_reg <= Ry;
     end
 reg [3:0]operation_reg;   //存储操作码
 always @(posedge w) 
    if(w)   operation_reg = operation;
    
 //操作码定义（operation）
 parameter Load = 4'b0000;    //加载数据
 parameter Move = 4'b0001;    //移动数据
 parameter Add  = 4'b0010;    //加法
 parameter Sub  = 4'b0011;    //减法
 parameter Show = 4'b1111;    //展现数据

 //状态转移函数
 always @(posedge clk) begin
    case(state)
    2'b01:
    begin
    case(operation_reg)
        Load:
        begin         
            externx <= 1;  //传输数据
            Rin <= 4'b0001 << Rx_temporary_reg;
            Done <= 1;
            Rout <= 4'b0000;
            Ain <= 0;
            Gin <= 0;
            Gout <= 0;
            addsub <= 0;
        end
        Move:
        begin
            Rin <= 4'b0001 << Rx_temporary_reg;
            Rout <= 4'b0001 << Ry_temporary_reg;
            Done <= 1;
            Ain <= 0;
            Gin <= 0;
            Gout <= 0;
            addsub <= 0;
            externx <= 0;
        end
        Add:
        begin
            Rout <= 4'b0001<<Rx_temporary_reg;
            Ain <= 1;
            Rin <= 4'b0000;
            Gin <= 0;
            Gout <= 0;
            addsub <= 0;
            externx <= 0;
            Done <= 0;
        end
        Sub:
        begin
            Rout <= 4'b0001<<Rx_temporary_reg;
            Ain <= 1;
            Rin <= 4'b0000;
            Gin <= 0;
            Gout <= 0;
            addsub <= 0;
            externx <= 0;
            Done <= 0;
        end
        /*Show:
        begin
        address = {Rx_temporary_reg, Ry_temporary_reg};
        Done = 1;
        Rin <= 4'b0000;
        Rout <= 4'b0000;
        Ain <= 0;
        Gin <= 0;
        Gout <= 0;
        addsub <= 0;
        externx <= 0;
        end*/
        endcase
        end
        
    2'b10:
    begin
        Ain <= 0;
        Gout <= 0;
        externx <= 0;
        Done <= 0;
        Rout <= 4'b0001 << Ry_temporary_reg;
        Gin <= 1;
        Rin <= 4'b0000;
        if(operation_reg == 4'b0010) addsub <= 1;
        else addsub <= 0;
    end
    
    2'b11:
    begin
        Rout <= 4'b0000;
        Ain <= 0;
        Gin <= 0;
        addsub <= 0;
        externx <= 0;
        Gout <= 1;
        Done <= 1;
        Rin <= 4'b0001 << Rx_temporary_reg;
    end
    
    default:
    begin
        Rin <= 4'b0000;
        Rout <= 4'b0000;
        Ain <= 0;
        Gin <= 0;
        Gout <= 0;
        addsub <= 0;
        externx <= 0;
        Done <= 0;
        if(operation_reg == 4'b1111)
            address = {Rx_temporary_reg,Ry_temporary_reg};
    end
    endcase
 end
endmodule

//仿真代码
module cpu_testbench;
 reg[7:0] order,data;
 reg  clk,w,rst;
 wire[3:0]pos1,pos2;
 wire[7:0]seg1,seg2;
 top top(
    .order(order),
    .data(data),
    .clk(clk),
    .w(w),
    .rst(rst),
    .pos1(pos1),
    .pos2(pos2),
    .seg1(seg1),
    .seg2(seg2)
 );
 always #5 clk=~clk;
 initial begin
    clk=0;
    data=8'h01;
    order=8'b0000_0000;
    rst=0;
    w=0;
    #1000;w=1;
    #1000;w=0;
    #1000;

    data=8'h02;
    order=8'b0000_0100;
    w=1;#1000;
    w=0;
    #1000;

    order=8'b0001_1001;
    w=1;#1000;
    w=0;
    #1000;

    order=8'b0010_0001;
    w=1;#1000;w=0;
    #1000;

    order=8'b0011_0001;
    w=1;#1000;w=0;
    #1000;

    order=8'b1111_0011;
    w=1;#1000;w=0;
    #1000;
    $stop;
 end
endmodule

/*  
测试案例：       
PC    拨码        操作数    指令         寄存器00            寄存器01       寄存器02         寄存器03                               
0. 0000_0000   0000_0010   输入2            2      
1. 0000_0100   0000_0101   输入5            2                  5
2. 0000_1000   0000_0011   输入3            2                  5             3             
3. 0000_1100   0000_1000   输入8            2                  5             3                 8
4. 0001_0010               move             3                  5             3                8
5. 0010_0001               3 + 5            8                  5             3                8
6. 0011_1110               8 - 3            8                  5             3                5
7. 1111_0110               显示6_5
8. 1111_0101               显示5_8
9. 1111_0100               显示4_3
10.1111_0011               显示3_8
11.1111_0010               显示2_3
*/    