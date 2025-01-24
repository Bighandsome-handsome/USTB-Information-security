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

    localparam IDLE  = 3'b000;
    localparam LOAD  = 3'b001;
    localparam MOVE  = 3'b010;
    localparam STEP1 = 3'b011;
    localparam STEP2 = 3'b100;
    localparam STEP3 = 3'b101;

    reg [2:0] current_state;
    reg [2:0] next_state;
    reg [1:0] Rx_reg;
    reg [1:0] Ry_reg;
    reg [1:0] F_reg;

    // 状态转移逻辑
    always @(posedge clk or posedge rst) begin
        if (rst)
            current_state <= IDLE;
        else
            current_state <= next_state;
    end

    // 输入寄存器更新逻辑
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

    // 状态处理逻辑
    always @(*) begin
        // 初始化输出
        Rin = 4'b0000;
        Rout = 4'b0000;
        Ain = 1'b0;
        Gin = 1'b0;
        Gout = 1'b0;
        addsub = 1'b0;
        externx = 1'b0;
        Done = 1'b0;

        // 状态机逻辑
        case (current_state)
            IDLE: begin
                if (w) begin
                    case (F)
                        2'b00: next_state = LOAD;
                        2'b01: next_state = MOVE;
                        2'b10: next_state = STEP1;
                        2'b11: next_state = STEP1;
                        default: next_state = IDLE;
                    endcase
                end
            end

            LOAD: begin
                set_external_flag(externx);
                set_bit(Rin, Rx_reg);
                set_done(Done);
                next_state = IDLE;
            end

            MOVE: begin
                set_external_flag(externx);
                set_bit(Rin, Rx_reg);
                set_bit(Rout, Ry_reg);
                set_done(Done);
                next_state = IDLE;
            end

            STEP1: begin
                set_bit(Rout, Rx_reg);
                Ain = 1'b1;
                next_state = STEP2;
            end

            STEP2: begin
                set_bit(Rout, Ry_reg);
                addsub = (F_reg == 2'b10) ? 1'b1 : 1'b0;
                Gin = 1'b1;
                next_state = STEP3;
            end

            STEP3: begin
                set_bit(Rin, Rx_reg);
                Gout = 1'b1;
                set_done(Done);
                next_state = IDLE;
            end
        endcase
    end

    // 辅助函数
    function void set_external_flag(output reg flag);
        flag = 1'b1;
    endfunction

    function void set_bit(inout reg [3:0] reg_var, input [1:0] bit_pos);
        reg_var[bit_pos] = 1'b1;
    endfunction

    function void set_done(output reg done_flag);
        done_flag = 1'b1;
    endfunction

endmodule