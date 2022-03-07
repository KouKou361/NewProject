#pragma once

//delete専用
//なんかいちいちif(){deleteとnullptr}
//めんどくさいのでこれするだけでいいようにする
#define	DELETEPOINTER( RESOURCE ) \
	if( RESOURCE!=nullptr ) { delete RESOURCE;  RESOURCE = nullptr; }

//	D3Dリソースの安全な開放マクロ
//最後の処理　これがないとメモリの解放できないまま
#define	D3D_SAFE_RELEASE( RESOURCE ) \
	if( RESOURCE ) { RESOURCE->Release(); RESOURCE = nullptr; }