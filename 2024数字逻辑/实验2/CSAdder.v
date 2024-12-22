 
//选择进位加法器   
 module csadd32 (
       input  wire [31: 0] a   ,
       input  wire [31: 0] b   ,
       input  wire   cin ,
       output wire [31: 0] s   ,
       output wire   cout
                ); 
      wire c0,c1,c2;
      wire [16:0]s0,s1,s2;
        add16_select A(a[15:0],b[15:0],cin,s0,c0);
        add16_select B(a[31:16],b[31:16],0,s1,c1);
        add16_select C(a[31:16],b[31:16],1,s2,c2);
        assign s=c0?{s2[15:0],s0[15:0]}:{s1[15:0],s0[15:0]};
        assign cout=c0?c2:c1; 
       
    
endmodule
 
module add16_select(input wire [15:0] a,
                    input wire [15:0] b,
                    input wire cin, 
                    output wire [15:0] s,
                    output wire cout);
        wire c0,c1,c2;
        wire [8:0]s0,s1,s2;
        add8 A(a[7:0],b[7:0],cin,s0,c0);
        add8 B(a[15:8],b[15:8],0,s1,c1);
        add8 C(a[15:8],b[15:8],1,s2,c2);
        assign s=c0?{s2[7:0],s0[7:0]}:{s1[7:0],s0[7:0]};
        assign cout=c0?c2:c1;
endmodule
 
module add8(input wire [7:0] a,
                    input wire [7:0] b,
                    input wire cin, 
                    output wire [7:0] s,
                    output wire cout);
        wire c0,c1,c2;
        wire [3:0]s0,s1,s2;
        add4 A(a[3:0],b[3:0],cin,s0,c0);
        add4 B(a[7:4],b[7:4],c0,s1,c1);
        assign s={s1[3:0],s0[3:0]};
        assign cout=c1;
endmodule
 
module add4 (input wire [3:0] a,
                    input wire [3:0] b,
                    input wire cin, 
                    output wire [3:0] s,
                    output wire cout);
        wire carry[3:0];
        add1 A(a[0],b[0],cin,s[0],carry[0]);
        add1 B(a[1],b[1],carry[0],s[1],carry[1]);
        add1 C(a[2],b[2],carry[1],s[2],carry[2]);
        add1 D(a[3],b[3],carry[2],s[3],cout);
endmodule 
 
module add1(
	input a,
	input b,
	input cin,
	output sum,
	output cout);
	assign #4 sum = a ^ b ^ cin;
	assign #2 cout =  (cin==1)|(cin==0)?(a & cin) | (b & cin)| (a & b):1'b0;
endmodule