module top_module(
    input clk,
    input areset,    // Asynchronous reset to state S0
    input in,
    output reg out
);


    parameter S0 = 1'b0, S1 = 1'b1;
    reg state;


    always @(posedge clk or posedge areset) begin
        if (areset) begin
            state <= S0;
            out <= 1;
        end else begin
            case (state)
                S0: begin
                    if (in) begin                        
                        state <= S0;
                        out <= 1;
                    end else begin
                        state <= S1;
                        out <= 0;
                    end
                end
                S1: begin
                    if (in) begin
                        state <= S1;
                        out <= 0;
                    end else begin
                        state <= S0;
                        out <= 1;
                    end
                end
                default: begin
                    state <= S0;
                    out <= 1;
                end
            endcase
        end
    end

endmodule