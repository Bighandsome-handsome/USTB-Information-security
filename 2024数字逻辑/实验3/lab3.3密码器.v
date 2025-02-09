module lock(
    input clk,        
    input rst,        
    input in,         
    output reg unlock // 解锁标志（注册输出）
);

    reg [4:0] save = 5'bxxxxx; 

    // 该always块对时钟信号的上升沿敏感
    always @ (posedge clk) begin
        if (rst) begin
            save <= 5'bxxxxx;   
            unlock <= 0;        
        end 
        else if (unlock != 1) begin
            save <= {save[3:0], in}; // 将save寄存器左移，并将新的输入位添加到最低位
            if ({save[2:0], in} == 4'b0010) // 检查最后4位是否匹配序列"0010"
                unlock <= 1; 
            else 
                unlock <= 0; 
        end
    end
endmodule