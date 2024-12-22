`timescale 1ns / 1ps

module add1(
	input a,
	input b,
	input cin,
	output sum,
	output cout);
	assign #4 sum = a ^ b ^ cin;
	assign #2 cout =  (cin==1)|(cin==0)?(a & cin) | (b & cin)| (a & b):1'bx;
endmodule

module	rcadd32(
    a,b,cin,s,cout
);
    input [31:0] a,b;
	input cin;
    output [31:0] s;
    output wire cout;
    wire [30:0] CY;

  // 实例化32个1位加法器，每个处理一位的加法运算和进位传递
  /* 从U1开始，每次调用add1，传入a和b和上一位加法产生的进位。
     如U10:传入a[9],b[9],CY[8]（a[8]和b[8]计算产生的进位），
	 输出s[10]和进位CY[10]
	 最后一位U31时，进位CY[31]就是计算过程中最后产生的进位cout。
  */
    add1 U0(a[0],b[0],cin,s[0],CY[0]);
    add1 U1(a[1],b[1],CY[0],s[1],CY[1]);
	add1 U2(a[2],b[2],CY[1],s[2],CY[2]);
	add1 U3(a[3],b[3],CY[2],s[3],CY[3]);
	add1 U4(a[4],b[4],CY[3],s[4],CY[4]);
	add1 U5(a[5],b[5],CY[4],s[5],CY[5]);
	add1 U6(a[6],b[6],CY[5],s[6],CY[6]);
	add1 U7(a[7],b[7],CY[6],s[7],CY[7]);
	add1 U8(a[8],b[8],CY[7],s[8],CY[8]);
	add1 U9(a[9],b[9],CY[8],s[9],CY[9]);
	add1 U10(a[10],b[10],CY[9],s[10],CY[10]);
	add1 U11(a[11],b[11],CY[10],s[11],CY[11]);
	add1 U12(a[12],b[12],CY[11],s[12],CY[12]);
	add1 U13(a[13],b[13],CY[12],s[13],CY[13]);
	add1 U14(a[14],b[14],CY[13],s[14],CY[14]);
	add1 U15(a[15],b[15],CY[14],s[15],CY[15]);
	add1 U16(a[16],b[16],CY[15],s[16],CY[16]);
	add1 U17(a[17],b[17],CY[16],s[17],CY[17]);
	add1 U18(a[18],b[18],CY[17],s[18],CY[18]);
	add1 U19(a[19],b[19],CY[18],s[19],CY[19]);
	add1 U20(a[20],b[20],CY[19],s[20],CY[20]);
	add1 U21(a[21],b[21],CY[20],s[21],CY[21]);
	add1 U22(a[22],b[22],CY[21],s[22],CY[22]);
	add1 U23(a[23],b[23],CY[22],s[23],CY[23]);
	add1 U24(a[24],b[24],CY[23],s[24],CY[24]);
	add1 U25(a[25],b[25],CY[24],s[25],CY[25]);
	add1 U26(a[26],b[26],CY[25],s[26],CY[26]);
	add1 U27(a[27],b[27],CY[26],s[27],CY[27]);
	add1 U28(a[28],b[28],CY[27],s[28],CY[28]);
	add1 U29(a[29],b[29],CY[28],s[29],CY[29]);
	add1 U30(a[30],b[30],CY[29],s[30],CY[30]);
	add1 U31(a[31],b[31],CY[30],s[31],cout);

endmodule