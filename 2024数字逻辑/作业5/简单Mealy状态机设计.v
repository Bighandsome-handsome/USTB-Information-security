module mealy (
    input wire clk,           
    input wire areset,        
    input wire in,            // 输入信号
    output reg out             // 输出信号
);
  reg y,Y;
  parameter A=1'b0,B=1'b1;

  always@(in,y)
  case (y)
    A: if(in)
      begin
        out=0;
        Y=B;
      end
      else
      begin
        out=0;
        Y=A;
      end
    B:if(in)
       begin
        out=1;
        Y=B;
       end
       else
       begin
       out=0;
       Y=A;
       end
    //default:out=0;
  endcase
  always @(negedge areset,posedge clk) 
  if(areset==1) y<=A;
  else y<=Y;

endmodule