#pragma once

//delete��p
//�Ȃ񂩂�������if(){delete��nullptr}
//�߂�ǂ������̂ł��ꂷ�邾���ł����悤�ɂ���
#define	DELETEPOINTER( RESOURCE ) \
	if( RESOURCE!=nullptr ) { delete RESOURCE;  RESOURCE = nullptr; }

//	D3D���\�[�X�̈��S�ȊJ���}�N��
//�Ō�̏����@���ꂪ�Ȃ��ƃ������̉���ł��Ȃ��܂�
#define	D3D_SAFE_RELEASE( RESOURCE ) \
	if( RESOURCE ) { RESOURCE->Release(); RESOURCE = nullptr; }