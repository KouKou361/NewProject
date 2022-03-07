
#include "Cascade.hlsli"

PSInput main(VSInput input)
{
    float3 p = { 0, 0, 0 };
    float3 n = { 0, 0, 0 };
    for (int i = 0; i < 4; i++)
    {
        p += (input.boneWeights[i] * mul(input.position, boneTransforms[input.boneIndices[i]])).xyz;
        n += (input.boneWeights[i] * mul(float4(input.normal.xyz, 0), boneTransforms[input.boneIndices[i]])).xyz;
    }

    	//Ú‹óŠÔ‚RŽ²‚Ìì¬
    float3 VZ = n;
    float3 VY = { 0, 1, 0.001 }; //‰¼
    float3 VX;
    VY = normalize(VY);
    VX = normalize(cross(VY, VZ)); //ŠOÏ
    VY = normalize(cross(VZ, VX));

    PSInput output;
    
    output.VX = VX;
    output.VY = VY;
    output.VZ = VZ;
    

    output.position = mul(float4(p, 1.0f), viewProjection);
	//output.position = mul(position, viewProjection);
    output.Wposition = p;
    output.color = materialColor;
    output.normal = n;
    output.texcoord = input.texcoord;
	//output.vShadow = float3( 1,1,1 );
    //output.vShadow = GetShadowTex(LightViewProjection, p.xyz);

    return output;
}
