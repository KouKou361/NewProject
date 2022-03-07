
#pragma once
#include <d3d11.h>

//MEMO:static�ɂ����� Blender* m_blander����K�v���Ȃ��Ȃ�̂�
//�������S��static�ɂ��Ă��̂���������

//�e��u�����h�����𗘗p���邽�߂̒萔
enum class Bland_state {
    BS_NONE = 0,//����
    BS_ALPHA,//�A���t�@�u�����h
    BS_ADD,//���Z����
    BS_SUBTRACT,//���Z����
    BS_MULTIPLY,//��Z����

    BS_SCREEN,//�X�N���[������
    BS_LIGHTEN,//��r����(��)
    BS_DARKEN,//��r����(��)
    BS_REPLASE,//�u����������
    BS_END,//
};
class BlendState {
private:
    static BlendState* instance;
    ID3D11BlendState* m_blendState[static_cast<UINT>(Bland_state::BS_END)];
public:
   
      ID3D11BlendState* GetBlendState(Bland_state _BlendState) {
          return m_blendState[static_cast<UINT>(_BlendState)];
      }




   // BlendState() {}
    BlendState(ID3D11Device* _Device);
    ~BlendState() {
         for (int i = 0; i < static_cast<UINT>(Bland_state::BS_END); ++i) {
             if (m_blendState[i]) {
                 m_blendState[i]->Release();
                 m_blendState[i] = nullptr;
             }
         }
    }
    //�C���X�^���X�擾
    static BlendState& Instance()
    {
        return *instance;
    }





    

};