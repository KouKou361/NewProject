#include "TargetScreen.hlsli"
float4 main(PSInput input) : SV_TARGET0
{
   //float4 color = diffuseTexture.Sample(diffuseSampler, input.tex);
   float4 color = float4(1,0,0,1);
  // return color;
    
    //��
    float weight = input.tex.y * LineDark;
    weight = 1-min(weight, 1);
    weight *= LineWeight;
    color *= weight;
    
    //��
    weight = (1 - input.tex.y) * LineDark;
    weight = 1 - min(weight, 1);
    weight *= LineWeight;
    color *= weight;

    
        //��
 //  weight = (1 - input.tex.x) * LineDark;
 //  weight = 1 - min(weight, 1);
 //  weight *= LineWeight;
 //  color *= weight;
    
  //  //��
  //  weight = input.tex.x * LineDark;
  //  weight = 1 - min(weight, 1);
  //  weight *= LineWeight;
  //  color *= weight;
    
    return color;
}