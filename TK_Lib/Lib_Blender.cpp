#include "Lib_Blender.h"
BlendState* BlendState::instance=nullptr;
BlendState::BlendState(ID3D11Device* _Device)
{
    
     BlendState::instance = this;
     for (UINT i = 0; i < static_cast<UINT>(Bland_state::BS_END); ++i) {
         m_blendState[i] = nullptr;
     }
     HRESULT hr = S_OK;
     D3D11_BLEND_DESC BlendDese = {};

     {//NONE
         BlendDese.AlphaToCoverageEnable = false; //マルチサンプリングを使用するかどうか
         BlendDese.IndependentBlendEnable = false;
         //    BlendDese.RenderTarget[0].BlendEnable = true;//ブレンドを有効にするか
         BlendDese.RenderTarget[0].BlendEnable = false;//
         BlendDese.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
         hr = _Device->CreateBlendState(&BlendDese, &m_blendState[static_cast<UINT>(Bland_state::BS_NONE)]);
         if (FAILED(hr))return;
     }
     {//ALPHA
         BlendDese.AlphaToCoverageEnable = FALSE;
         BlendDese.IndependentBlendEnable = FALSE;
         BlendDese.RenderTarget[0].BlendEnable = TRUE;
         BlendDese.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
         BlendDese.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
         BlendDese.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
         BlendDese.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
         BlendDese.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
         BlendDese.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
         BlendDese.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
         hr = _Device->CreateBlendState(&BlendDese, &m_blendState[static_cast<UINT>(Bland_state::BS_ALPHA)]);
         if (FAILED(hr))return;

     }
     {//ADD
         BlendDese.RenderTarget[0].BlendEnable = true;//
         BlendDese.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
         BlendDese.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
         BlendDese.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
         BlendDese.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
         BlendDese.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
         BlendDese.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
         BlendDese.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
         hr = _Device->CreateBlendState(&BlendDese, &m_blendState[static_cast<UINT>(Bland_state::BS_ADD)]);
         if (FAILED(hr))return;
     }
     {//SUBTRACT
         BlendDese.RenderTarget[0].BlendEnable = true;//
         BlendDese.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
         BlendDese.RenderTarget[0].BlendOp = D3D11_BLEND_OP_SUBTRACT;
         BlendDese.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
         BlendDese.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
         BlendDese.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_SUBTRACT;
         BlendDese.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
         BlendDese.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
         hr = _Device->CreateBlendState(&BlendDese, &m_blendState[static_cast<UINT>(Bland_state::BS_SUBTRACT)]);
         if (FAILED(hr))return;
     }
     {//MULTIPLY
         BlendDese.RenderTarget[0].BlendEnable = true;//
         BlendDese.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_COLOR;
         BlendDese.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
         BlendDese.RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO;
         BlendDese.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
         BlendDese.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
         BlendDese.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
         BlendDese.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
         hr = _Device->CreateBlendState(&BlendDese, &m_blendState[static_cast<UINT>(Bland_state::BS_MULTIPLY)]);
         if (FAILED(hr))return;
     }
     {//BS_SCREEN
         BlendDese.RenderTarget[0].BlendEnable = true;//
         BlendDese.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_COLOR;
         BlendDese.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
         BlendDese.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
         BlendDese.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
         BlendDese.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
         BlendDese.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
         BlendDese.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
         hr = _Device->CreateBlendState(&BlendDese, &m_blendState[static_cast<UINT>(Bland_state::BS_SCREEN)]);
         if (FAILED(hr))return;
     }
     {//BS_LIGHT
         BlendDese.RenderTarget[0].BlendEnable = true;//
         BlendDese.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
         BlendDese.RenderTarget[0].BlendOp = D3D11_BLEND_OP_MAX;
         BlendDese.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
         BlendDese.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
         BlendDese.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MAX;
         BlendDese.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
         BlendDese.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
         hr = _Device->CreateBlendState(&BlendDese, &m_blendState[static_cast<UINT>(Bland_state::BS_LIGHTEN)]);
         if (FAILED(hr))return;
     }
     {//BS_DARK
         BlendDese.RenderTarget[0].BlendEnable = true;//
         BlendDese.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
         BlendDese.RenderTarget[0].BlendOp = D3D11_BLEND_OP_MIN;
         BlendDese.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
         BlendDese.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
         BlendDese.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MIN;
         BlendDese.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
         BlendDese.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
         hr = _Device->CreateBlendState(&BlendDese, &m_blendState[static_cast<UINT>(Bland_state::BS_DARKEN)]);
         if (FAILED(hr))return;
     }
     {//BS_REPLASE
         BlendDese.RenderTarget[0].BlendEnable = true;//
         BlendDese.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
         BlendDese.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
         BlendDese.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
         BlendDese.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
         BlendDese.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
         BlendDese.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
         BlendDese.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
         hr = _Device->CreateBlendState(&BlendDese, &m_blendState[static_cast<UINT>(Bland_state::BS_REPLASE)]);
         if (FAILED(hr))return;
     }
}
