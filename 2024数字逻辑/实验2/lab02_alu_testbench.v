`timescale 1ns/1ps

module alu_tb;

    
    reg [7:0] alu_src1;
    reg [7:0] alu_src2;
    reg [11:0] alu_op;
    

    wire [7:0] alu_result;
    

    ALU marigold (
        .alu_src1(alu_src1),
        .alu_src2(alu_src2),
        .alu_op(alu_op),
        .alu_result(alu_result)
    );


    initial begin

        $display("Time\talu_op\t\talu_src1\talu_src2\talu_result");


        alu_src1 = 8'b1011_0110;  
        alu_src2 = 8'b1100_1110;    
        alu_op = 12'h001;         
        #10;
        $display("%0dns\t%h\t%b\t%b\t%b", $time, alu_op, alu_src1, alu_src2, alu_result);


        alu_op = 12'h002;       
        #10;
        $display("%0dns\t%h\t%b\t%b\t%b", $time, alu_op, alu_src1, alu_src2, alu_result);


        alu_op = 12'h004;         
        #10;
        $display("%0dns\t%h\t%b\t%b\t%b", $time, alu_op, alu_src1, alu_src2, alu_result);


        alu_op = 12'h008;          
        #10;
        $display("%0dns\t%h\t%b\t%b\t%b", $time, alu_op, alu_src1, alu_src2, alu_result);


        alu_op = 12'h010;   
        #10;
        $display("%0dns\t%h\t%b\t%b\t%b", $time, alu_op, alu_src1, alu_src2, alu_result);


        alu_op = 12'h020;          
        #10;
        $display("%0dns\t%h\t%b\t%b\t%b", $time, alu_op, alu_src1, alu_src2, alu_result);


        alu_op = 12'h040;       
        #10;
        $display("%0dns\t%h\t%b\t%b\t%b", $time, alu_op, alu_src1, alu_src2, alu_result);


        alu_op = 12'h080;          
        #10;
        $display("%0dns\t%h\t%b\t%b\t%b", $time, alu_op, alu_src1, alu_src2, alu_result);


        alu_op = 12'h100;          
        #10;
        $display("%0dns\t%h\t%b\t%b\t%b", $time, alu_op, alu_src1, alu_src2, alu_result);


        alu_op = 12'h200;         
        #10;
        $display("%0dns\t%h\t%b\t%b\t%b", $time, alu_op, alu_src1, alu_src2, alu_result);


        alu_op = 12'h400;          
        #10;
        $display("%0dns\t%h\t%b\t%b\t%b", $time, alu_op, alu_src1, alu_src2, alu_result);


        alu_op = 12'h800;           
        #10;
        $display("%0dns\t%h\t%b\t%b\t%b", $time, alu_op, alu_src1, alu_src2, alu_result);


        $finish;
    end

endmodule
