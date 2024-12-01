module top_module (p1a, p1b, p1c, p1d,p1y,p2a, p2b, p2c, p2d,p2y);
    input p1a, p1b, p1c, p1d;
    output p1y;
    input p2a, p2b, p2c, p2d;
    output p2y;
    assign p1y=~(p1a&p1b&p1c&p1d);
    assign p2y=~(p2a&p2b&p2c&p2d);
endmodule