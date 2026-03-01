module summator

	(
		input wire[3:0] a,b,
		input wire c0 = 1'b0,
		output wire[3:0] y,
		output wire cout
	);

	reg[3:0] gn = 4'b0000;
	reg[3:0] pn = 4'b0000;
	reg[4:0] cn = 5'b00000;
	reg[3:0] res = 4'b0000;

	integer i;
	always @* begin
		assign cn[0] = c0;

		for(i=0;i<4;i++) begin
			assign gn[i] = a[i] & b[i];
			assign pn[i] = a[i] ^ b[i];
			assign res[i] = a[i] ^ b[i] ^ cn[i];
			assign cn[i+1] = gn[i] | (pn[i] & cn[i]);
		end

	end

	assign cout = cn[4];
	assign y = res;

endmodule
