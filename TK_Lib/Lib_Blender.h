
#pragma once
#include <d3d11.h>

//MEMO:staticにしたら Blender* m_blanderする必要がなくなるので
//いっそ全部staticにしてやるのもいいかも

//各種ブレンド処理を利用するための定数
enum class Bland_state {
    BS_NONE = 0,//無効
    BS_ALPHA,//アルファブレンド
    BS_ADD,//加算合成
    BS_SUBTRACT,//減算合成
    BS_MULTIPLY,//乗算合成

    BS_SCREEN,//スクリーン合成
    BS_LIGHTEN,//比較合成(明)
    BS_DARKEN,//比較合成(暗)
    BS_REPLASE,//置き換え合成
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
    //インスタンス取得
    static BlendState& Instance()
    {
        return *instance;
    }





    

};