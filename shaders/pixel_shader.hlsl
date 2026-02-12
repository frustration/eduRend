
Texture2D texDiffuse : register(t0);
SamplerState samLinear : register(s0);

struct PSIn
{
	float4 Pos  : SV_Position;
	float3 Normal : NORMAL;
	float2 TexCoord : TEX;
};

float4 PS_main(PSIn input) : SV_Target
{
    return texDiffuse.Sample(samLinear, input.TexCoord);
}
