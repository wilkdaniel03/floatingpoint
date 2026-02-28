module summator

	(
		input wire[3:0] a,b,
		input wire c0 = 1'b0,
		output wire[3:0] y,
		output wire cout
	);

	wire[3:0] gn;
	wire[3:0] pn;
	wire[4:0] cn;

	assign cn[0] = c0;

	genvar i;
	for(i=0;i<4;i++) begin
		assign gn[i] = a[i] & b[i];
		assign pn[i] = a[i] ^ b[i];
		assign y[i] = a[i] ^ b[i] ^ cn[i];
		assign cn[i+1] = gn[i] | (pn[i] & cn[i]);
	end

endmodule
