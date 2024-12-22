module id(
    input wire[15:0] fs_to_ds_bus,
    output wire[27:0] ds_to_es_bus,
    output wire [1:0] rx,
    output wire [1:0] ry,
    input wire [7:0] rx_value,
    input wire [7:0] ry_value
    );
    assign rx = fs_to_ds_bus[1:0];                           //1
    assign ry = fs_to_ds_bus[3:2];                           //2
    assign ds_to_es_bus[7:0]=fs_to_ds_bus[15:8];             //3          
    assign ds_to_es_bus[23:16]=ry_value;                     //4                 
    assign ds_to_es_bus[15:8]=rx_value;                      //5
    assign ds_to_es_bus[27:24] = (fs_to_ds_bus[7:4] == 4'b0001) ? 4'b1000 : //6
                                 (fs_to_ds_bus[7:4] == 4'b0010) ? 4'b0100 : //7
                                 (fs_to_ds_bus[7:4] == 4'b0011) ? 4'b0010 : //8
                                 (fs_to_ds_bus[7:4] == 4'b0100) ? 4'b0001 : //9
                                 4'b0000;                                   //10
endmodule
/*结合实验目的，注释如下
0. lab2实验文档前面的那些没看懂，所以我只能根据实验任务完成代码的功能
1. fs_to_ds_bus的PC值，就是fs的第15~8位，赋值给ds_to_es_bus的PC值，ds_to_es_bus的PC值是ds第8~0位，语句3就是实现这个任务
2. 将输入的rx_value 赋值给 ds_to_es_bus.RX_VALUE，ds的rx_value对应的第8~15位，语句4是实现这个任务
3. 将输入的ry_value 赋值给 ds_to_es_bus.RY_VALUE，ds的ry_value对应的第23~16位，语句5是实现这个任务
4. 将fs_to_ds_bus.RY赋值给ry端口，ry端口是fs的第3~2位，语句2是实现这个任务
5. 将fs_to_ds_bus.RX赋值给rx端口，rx端口是fs的第0~1位，语句1是实现这个任务
6. 将 fs_to_ds_bus.OP转换为独热码，fs_to_ds_bus.OP==0001 时，ds_to_es_bus.OP_ONE_HOT赋值为1000，以此类推
   （1）找到独热码的位置，fs的独热码是第7~4位，需要把这四位上的数传给ds上，ds接受独热码的位置是第27~24位
   （2）根据fs的独热码觉得ds第27~24位的数字，题目要求fs是0001时，ds是1000；因此(fs,ds)=(0001,1000),(0010,0100),(0011,0010),(0100,0001)
   语句6~10就是实现这个任务，我用一个选择语句实现，相当于case语句。最后4'b0000就是default的作用。
*/

