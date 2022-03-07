#include "PointSprite.hlsli"

GSInput main(VSInput input)
{
	//ジオメトリシェーダー側で座標変換するので頂点シェーダーはそのまま送る
    GSInput output = (GSInput) 0;
    output.Position.xyz = input.Position;
    output.Size = input.Size;
    output.Tex = input.Tex;
    output.Color = input.Color;
    return output;
}