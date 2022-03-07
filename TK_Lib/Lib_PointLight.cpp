#include "Lib_PointLight.h"
void Lib_PointLight::SetIndex(const int index)
{
	this->index = static_cast<float>(index);
}
//データを元に戻す
void Lib_PointLight::Clear()
{
	index = -1;
}
int Lib_PointLight::GetIndex()
{
	return static_cast<int>(index);
}
//位置の取得
VECTOR4 Lib_PointLight::GetPos()
{
	return pos;
}
//データの設定
void Lib_PointLight::Set(VECTOR4 pos, VECTOR4 color, float range)
{
	this->pos = pos;
	this->color = color;
	this->range= range;//光の届く範囲
}