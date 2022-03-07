#include "PointSprite.hlsli"
[maxvertexcount(4)]
void main(
	point GSInput In[1],
	inout TriangleStream<PSInput> ParticleStream
)
{
	//���W�ϊ��i���[���h���W�[���r���[���W�j
    float4 pos = mul(View, float4(In[0].Position, 1.0f));
	//�_��ʂɂ���
    float w = In[0].Size.x;
    float h = In[0].Size.y;
    
    float4 pos_left_top = pos + float4(-w, h, 0.0f, 0.0f); //����
    float4 pos_left_bottom = pos + float4(-w, -h, 0.0f, 0.0f); //����
    float4 pos_right_top = pos + float4(w, h, 0.0f, 0.0f); //�E��
    float4 pos_right_bottom = pos + float4(w, -h, 0.0f, 0.0f); //�E��

	//UV�B�F���v�Z���ďo��
    PSInput Out = (PSInput) 0;
    int type = int(In[0].Tex.x);
	//UV���W
    float u = (type % (int)TextureNum.x) * TextureSize.x;
    float v = (type / (int)TextureNum.y) * TextureSize.y;

    Out.Color = In[0].Color;
	
	//����
    Out.Position = mul(Projection, pos_left_top);
    Out.Tex = float2(u, v);
    ParticleStream.Append(Out);
	//�E��
    Out.Position = mul(Projection, pos_right_top);
    Out.Tex = float2(u + TextureSize.x, v);
    ParticleStream.Append(Out);

	//����
    Out.Position = mul(Projection, pos_left_bottom);
	
    Out.Tex = float2(u, v + TextureSize.y);
    ParticleStream.Append(Out);

	//�E��
    Out.Position = mul(Projection, pos_right_bottom);
    Out.Tex = float2(u + TextureSize.x, v + TextureSize.y);
    ParticleStream.Append(Out);




    ParticleStream.RestartStrip();


}