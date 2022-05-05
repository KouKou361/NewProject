#include "Lib_Outline.hlsli"

[maxvertexcount(6)]
void main(
	triangle GSInput input[3],
	inout TriangleStream<PSInput> output
)
{
   PSInput element;
	for (uint i = 0; i < 3; i++)
	{
	
      element.position = mul(input[i].pos, viewProjection);
     // element.normal = mul(input[i].normal, viewProjection);
      element.color = input[i].color;
      element.texcoord = input[i].texcoord;
      element.power = input[i].power;
		output.Append(element);
	}
		//追加した頂点で新しいプリミティブを生成する
   output.RestartStrip();
	//新しい面の生成
    for (int k = 0; k < 3; k++)
    {
        int j = 2 - k;
		//3D座標変換
        float4 Pos;
        Pos.xyz = (input[j].normal.xyz * 0.1f)+input[j].pos.xyz;
        Pos.w = 1.0f;
        element.position = mul(Pos, viewProjection); //3D座標変換
      //  element.position = element.position; //法線方向に新しいPositionを再入力する
        element.power = input[j].power;
        //element.normal = mul(World, float4(input[j].Normal, 0));
        //element.wPosition = mul(World, float4(element.Position.xyz, 1)).xyz;
        element.texcoord = input[j].texcoord;
		//真っ黒にしたい
        element.color = float4(0, 0, 0, 1);

		//法線方向を逆
		//element.wNormal = -element.wNormal;
		//ここで頂点を生成する
        output.Append(element);
     
    }
	//追加した頂点で新しいプリミティブを生成する
    output.RestartStrip();
}