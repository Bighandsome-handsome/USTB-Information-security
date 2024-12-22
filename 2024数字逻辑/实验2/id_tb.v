`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2024/10/18 01:38:46
// Design Name: 
// Module Name: id_tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module tb_id;  
    // ���������ź�����  
    reg [15:0] fs_to_ds_bus;  
    wire [27:0] ds_to_es_bus;  
    wire [1:0] rx;  
    wire [1:0] ry;  
    reg [7:0] rx_value;  
    reg [7:0] ry_value;  
  
    // ʵ���������Ե�ģ��  
    id uut (  
        .fs_to_ds_bus(fs_to_ds_bus),  
        .ds_to_es_bus(ds_to_es_bus),  
        .rx(rx),  
        .ry(ry),  
        .rx_value(rx_value),  
        .ry_value(ry_value)  
    );  
  
    initial begin  
        // ��ʼ�������ź�  
        fs_to_ds_bus = 16'hABCD;  
        rx_value = 8'h12;  
        ry_value = 8'h34;  
  
        // �ȴ�һ��ʱ���Թ۲����  
        #10;  
  
        // �ı������ź��Խ�һ������  
        fs_to_ds_bus = 16'h5678;  
        rx_value = 8'h56;  
        ry_value = 8'h78;  
  
        // �ٴεȴ�  
        #10;  
  
        // ��������  
        $finish;  
    end  
  
    // �����źű仯����ѡ��  
    initial begin  
        $monitor("Time = %0t, fs_to_ds_bus = %h, rx = %b, ry = %b, ds_to_es_bus = %h", $time, fs_to_ds_bus, rx, ry, ds_to_es_bus);  
    end  
endmodule
