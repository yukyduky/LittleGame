
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//																					//
//							    	Input & Output									//
//																					//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
struct PixelInput {
	
};

struct OutputToRenderTargets {
	float4 asdf0 : SV_Target0;
	float4 asdf1 : SV_Target1;
	float4 asdf2 : SV_Target2;
};

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//																					//
//							    	Main Function									//
//																					//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

OutputToRenderTargets PixelMain(PixelInput input) : SV_TARGET {
	OutputToRenderTargets output = (OutputToRenderTargets)0;

	
	output.asdf0;
	output.asdf1;
	output.asdf2;

	return output;
}