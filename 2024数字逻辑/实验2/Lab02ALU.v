//ι运算（新定义运算）的模块
/*
任务：
（1）根据操作数 2 的高四位中最低位的 1 的位置对操作数 1 进行不同的拼接操作；
（2）与操作数 2 的低四位进行拼接（操作数 2 的低四位位于拼接的高位）后进行循环位移
（3）操作数1中未用来进行上述拼接操作的剩余四位按照操作数1中原来顺序进行拼接，
     最低位作为位移方向判断，0 为右移，1 为左移

*/
module Calculation(        
    input wire [7:0] alu_src1,    
    input wire [7:0] alu_src2,               
    output wire [7:0] alu_result    
);    
    wire [3:0]special_result1;                     
    wire [3:0]special_result2=alu_src2[3:0];   
    wire [7:0] special_result;
    wire [3:0] pos = alu_src2[7:4];                //从alu_src2中提取高4位，作为位移或旋转的位置指示 
    wire [7:0] shifted_result;
    wire [3:0] remaining_bits;
    //根据表2.1中pos的不同位设置special_result1的值，进行特定的位重组
    assign special_result1 = (pos[0] == 1'b1) ? {alu_src1[1:0], alu_src1[7:6]} :
                             (pos[1] == 1'b1) ? {alu_src1[5:4], alu_src1[3:2]} :
                             (pos[2] == 1'b1) ? {alu_src1[7:6], alu_src1[3:2]} :
                             (pos[3] == 1'b1) ? {alu_src1[5:4], alu_src1[1:0]} : 4'b0;

    assign special_result={special_result2,special_result1}; //根据任务（1）和（2）完成拼接


    //下面这段代码是操作数1中未用来进行上述拼接操作的剩余四位按照操作数1中原来顺序进行拼接，
    assign remaining_bits = (pos[0] == 1'b1) ? alu_src1[5:2] :                         
      //pos[0] == 1'b1时，alu_src1中第0~1,6~7位参与了重组，而2~5没有参与，因此2~5位需要进行拼接，进行循环位移
      //下面的代码同理
                            (pos[1] == 1'b1) ? {alu_src1[7:6], alu_src1[1:0]} :
                            (pos[2] == 1'b1) ? {alu_src1[5:4], alu_src1[1:0]} :
                            (pos[3] == 1'b1) ? {alu_src1[7:6], alu_src1[3:2]} : 4'b0;



    //这是依据remaining_bits，就是操作数1中剩下的数第3~1位进行循环位移，我先不判定循环位移方向
    wire [7:0] rotate_right = (special_result >> remaining_bits[3:1]) | (special_result << (8 - remaining_bits[3:1]));
    wire [7:0] rotate_left = (special_result << remaining_bits[3:1]) | (special_result >> (8 - remaining_bits[3:1]));


    //这是依据remaining_bits的最低位判断循环方向，要是0就循环右移，取rotate_right；否则左移。
    assign shifted_result = (remaining_bits[0] == 1'b0) ? 
                        (rotate_right) : 
                        (rotate_left);

    assign  alu_result=shifted_result;
    endmodule

//ALU模块
//这个模块就是根据传入的操作码alu_op选择对应的运算符，计算传入的alu_src1和alu_src2两个参数，并通过alu_result输出
//大致框架：分别写出ALU中包含的12种运算，再根据alu_op传入的信号利用if/case语句选择相应的运算
module ALU (        
    input wire [7:0] alu_src1,    
    input wire [7:0] alu_src2,        
    input wire [11:0] alu_op,        
    output wire [7:0] alu_result    
);    
    //计算方法01~04的实现
    wire[7:0] ALUresult_calution01= alu_src1 + alu_src2;                      //加
    wire[7:0] ALUresult_calution02= alu_src1 - alu_src2;                      //减
    wire[7:0] ALUresult_calution03= alu_src1 & alu_src2;                      //按位与
    wire[7:0] ALUresult_calution04= alu_src1 || alu_src2;                     //逻辑或

    //计算方法05~08的实现
    wire[7:0] ALUresult_calution05= alu_src1 << alu_src2[1:0];     //逻辑左移 a << b[1 : 0]
    wire[7:0] ALUresult_calution06=$signed(alu_src1) >>> alu_src2[1:0];       //算术右移 a >>> b[1 : 0]
    /*
    算术右移 a >>> b：将数值 a 的二进制表示向右移动 b 位，左边（高位）空出的位用原数值的符号位（即最左边的位）的值填充
    保持数值的符号不变，适用于有符号整数（为了保险起见，我在alu_src1前面加了signed符号表明需要考虑符号）
    */
    wire[7:0] ALUresult_calution07=(alu_src1 >> alu_src2[1:0]) | (alu_src1 << (8-alu_src2[1:0]));//循环右移 a >>>> b[1 : 0]
    /*
     查阅CSDN：位移的数量是n，那么alu_src1右移n位的结果和alu_src1左移(8-n)位的结果进行按位或操作，可以模拟出循环右移n位的效果（假设alu_src1是8位宽）
    */
    wire[7:0] ALUresult_calution08=$signed(alu_src1) < $signed(alu_src2);    //小于比较

    //计算方法09~12的实现
    wire[7:0] ALUresult_calution09= ($unsigned(alu_src1) < $unsigned(alu_src2)) ? 8'b1 : 8'b0; //无符号小于比较
    wire[7:0] ALUresult_calution11 = alu_src1 ^ alu_src2;                                      //亦或

    //保留最高位进位加法，如有进位，舍弃最后一位
    wire [8:0] full_sum = {1'b0, alu_src1} + {1'b0, alu_src2}; //full_sum定义的是9位宽，而alu_src1和2均是8位宽，最高位补0可以变成9位宽
    wire [7:0] result_without_carry = full_sum[7:0];           //结果没有进位，full_sum最高位为0，直接取后八位
    wire [7:0] result_with_carry = full_sum[8:1];              //结果存在进位，full_sum最高位为1，需要舍弃最后一位，
                                                               //结果取full_sum的第9~1位（即full_sum[8]~full_sum[1],full_sum[0]扔掉）
    wire [7:0] final_add_result=(full_sum[8]==1) ? result_with_carry:result_without_carry;
    //这个就是根据full_sum最高位为是否为1判断加法是否有进位，要是有进位就输出result_with_carry，否则就输出result_without_carry；
    
    //新定义运算的模块调用，Calculation_result是存储计算结果，Calculation calc_inst是对先前定义的模块进行实例化
    wire[7:0]Calculation_result;
    Calculation calc_inst (  
        .alu_src1(alu_src1),  
        .alu_src2(alu_src2),  
        .alu_result(Calculation_result)  
    ); 
   //根据操作数选择
     always @(*) begin
        case(alu_op)
            12'h001: temp_alu_result = ALUresult_calution01;
            12'h002: temp_alu_result = ALUresult_calution02;
            12'h004: temp_alu_result = ALUresult_calution03;
            12'h008: temp_alu_result = ALUresult_calution04;
            12'h010: temp_alu_result = ALUresult_calution05;
            12'h020: temp_alu_result = ALUresult_calution06;
            12'h040: temp_alu_result = ALUresult_calution07;
            12'h080: temp_alu_result = ALUresult_calution08;
            12'h100: temp_alu_result = ALUresult_calution09;
            12'h200: temp_alu_result = final_add_result;
            12'h400: temp_alu_result = ALUresult_calution11;
            12'h800: temp_alu_result = Calculation_result;
            default: temp_alu_result = 8'b0;
        endcase
    end
endmodule