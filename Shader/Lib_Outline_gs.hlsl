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
		//�ǉ��������_�ŐV�����v���~�e�B�u�𐶐�����
   output.RestartStrip();
	//�V�����ʂ̐���
    for (int k = 0; k < 3; k++)
    {
        int j = 2 - k;
		//3D���W�ϊ�
        float4 Pos;
        Pos.xyz = (input[j].normal.xyz * 0.1f)+input[j].pos.xyz;
        Pos.w = 1.0f;
        element.position = mul(Pos, viewProjection); //3D���W�ϊ�
      //  element.position = element.position; //�@�������ɐV����Position���ē��͂���
        element.power = input[j].power;
        //element.normal = mul(World, float4(input[j].Normal, 0));
        //element.wPosition = mul(World, float4(element.Position.xyz, 1)).xyz;
        element.texcoord = input[j].texcoord;
		//�^�����ɂ�����
        element.color = float4(0, 0, 0, 1);

		//�@���������t
		//element.wNormal = -element.wNormal;
		//�����Œ��_�𐶐�����
        output.Append(element);
     
    }
	//�ǉ��������_�ŐV�����v���~�e�B�u�𐶐�����
    output.RestartStrip();
}