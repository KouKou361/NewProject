#include "PointSprite.hlsli"

GSInput main(VSInput input)
{
	//�W�I���g���V�F�[�_�[���ō��W�ϊ�����̂Œ��_�V�F�[�_�[�͂��̂܂ܑ���
    GSInput output = (GSInput) 0;
    output.Position.xyz = input.Position;
    output.Size = input.Size;
    output.Tex = input.Tex;
    output.Color = input.Color;
    return output;
}