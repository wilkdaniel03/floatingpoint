module main

	(
		input wire[3:0] x1,x2,
		output wire[3:0] y
	);

	summator sum_1 (.a(x1),.b(x2),.y(y),.cout());
	
endmodule
