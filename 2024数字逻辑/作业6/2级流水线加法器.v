module pipeline2(
    input wire clk,
    input wire [31:0] a,
    input wire [31:0] b,
    input wire cin,
    output reg [31:0] sum,
    output reg cout
);

    // 中间信号
    reg [15:0] low_sum;  // 低16位和
    reg cout_mid;        // 中间进位
    reg [15:0] high_a;   // a的高16位
    reg [15:0] high_b;   // b的高16位

    // 在每个时钟上升沿触发
    always @(posedge clk) begin
        // 第一级加法：计算低16位和及中间进位
        {cout_mid, low_sum} <= a[15:0] + b[15:0] + cin;
        
        // 保存a和b的高16位以备第二级加法使用
        high_a <= a[31:16];
        high_b <= b[31:16];
        
        // 第二级加法：使用第一级的进位计算高16位和及最终进位
        {cout, sum[31:16]} <= high_a + high_b + cout_mid;
        
        // 将低16位和直接赋值给sum的低16位
        sum[15:0] <= low_sum;
    end

endmodule