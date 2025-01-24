module proc_fsm(
    input wire clk,
    input wire rst,
    input wire w,
    input wire [1:0] F,
    input wire [1:0] Rx,
    input wire [1:0] Ry,
    output reg [3:0] Rin,
    output reg [3:0] Rout,
    output reg Ain,
    output reg Gin,
    output reg Gout,
    output reg addsub,
    output reg externx,
    output reg Done
);

    // 状态定义
    localparam IDLE  = 3'b000;
    localparam LOAD  = 3'b001;
    localparam MOVE  = 3'b010;
    localparam STEP1 = 3'b011;
    localparam STEP2 = 3'b100;
    localparam STEP3 = 3'b101;

    reg [2:0] current_state;
    reg [2:0] next_state;

    // 用于存储寄存器值
    reg [1:0] Rx_reg;  
    reg [1:0] Ry_reg;  
    reg [1:0] F_reg;  

    // 状态机更新
    always @(posedge clk or posedge rst) begin
        if (rst)
            current_state <= IDLE;
        else
            current_state <= next_state;
    end

    // 输入信号同步到寄存器
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            Rx_reg <= 2'b00;
            Ry_reg <= 2'b00;
            F_reg <= 2'b00;
        end else if (w) begin
            Rx_reg <= Rx;
            Ry_reg <= Ry;
            F_reg <= F;
        end
    end

    // 初始化控制信号的任务
    task reset_signals;
        begin
            Rin = 4'b0000;
            Rout = 4'b0000;
            Ain = 1'b0;
            Gin = 1'b0;
            Gout = 1'b0;
            addsub = 1'b0;
            externx = 1'b0;
            Done = 1'b0;
        end
    endtask

    // 状态机逻辑
    always @(*) begin
        reset_signals();  // 默认初始化信号

        case (current_state)
            IDLE: begin
                if (w) begin
                    case (F)
                        2'b00: next_state = LOAD;  // Load
                        2'b01: next_state = MOVE;  // Move
                        2'b10, 2'b11: next_state = STEP1; // Add/Sub
                        default: next_state = IDLE;
                    endcase
                end else begin
                    next_state = IDLE;
                end
            end

            LOAD: begin
                externx = 1'b1;  // 外部输入标志
                Rin[Rx_reg] = 1'b1;  // 将数据加载到Rx
                Done = 1'b1;  // 操作完成
                next_state = IDLE;
            end

            MOVE: begin
                Rout[Ry_reg] = 1'b1;  // 从Ry输出
                Rin[Rx_reg] = 1'b1;  // 写入Rx
                Done = 1'b1;  // 操作完成
                next_state = IDLE;
            end

            STEP1: begin
                Rout[Rx_reg] = 1'b1;  // 从Rx输出
                Ain = 1'b1;  // 数据写入A寄存器
                next_state = STEP2;
            end

            STEP2: begin
                Rout[Ry_reg] = 1'b1;  // 从Ry输出
                addsub = (F_reg == 2'b10) ? 1'b1 : 1'b0;  // 加/减选择
                Gin = 1'b1;  // 数据写入G寄存器
                next_state = STEP3;
            end

            STEP3: begin
                Gout = 1'b1;  // 从G寄存器输出
                Rin[Rx_reg] = 1'b1;  // 写入Rx
                Done = 1'b1;  // 操作完成
                next_state = IDLE;
            end
        endcase
    end
endmodule