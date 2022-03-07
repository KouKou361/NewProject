#pragma once

#include <memory>
#include <vector>
#include <dsound.h>
#include <map>

using namespace std;

// ����
class SoundSource
{
public:
	SoundSource(IDirectSound8* ds, const char* filename);//���[�h
	~SoundSource();//���

	void Play(bool loop);//�X�^�[�g
	void Stop();//�X�g�b�v
	void SetVolume(float volume);	// 0.0 �` 1.0
	void SetPan(float pan);			// -1.0[L] �` 1.0[R]

private:
	IDirectSoundBuffer*		soundBuffer = nullptr;
};

// �T�E���h�}�l�[�W���[
class SoundManager
{
public:
	// ��DirectXTK��WICTextureLoader����x�ł��g�p�������
	// �@�T�E���h�̏�����������ƈȌ�AWICTextureLoader��
	// �@�g�p�ł��Ȃ��Ȃ�̂ŁASoundManager�̓Q�[���N������ɐ������邱�ƁB
	// �@Framework�̍ŏ��̏�����������ł���Ƃ悢�B
	SoundManager(HWND hWnd);
	~SoundManager();

	//���O����T�E���h���擾
	SoundSource* GetSound(const char* KeyName);
	//�T�E���h�̓o�^
	void RegisterSound(const char* fileName,const char* RegisterName);
	//�T�E���h�쐬
	SoundSource* CreateSoundSource(const char* filename);
	//�o�^����Ă���T�E���h��S�č폜
	void SoundClear();

private:
	map<const char*, SoundSource*> Sounds;
	
	IDirectSound8*			directSound = nullptr;
	IDirectSoundBuffer*		primaryBuffer = nullptr;
};

// WAVE�f�[�^
struct Wave
{
	Wave(const char* filename);

	// RIFF�w�b�_
	struct Riff
	{
		UINT32				tag;			// RIFF�`���̎��ʎq 'RIFF'
		UINT32				size;			// ����ȍ~�̃t�@�C���T�C�Y(�t�@�C���T�C�Y - 8)
		UINT32				type;			// RIFF�̎�ނ�\�����ʎq 'WAVE'
	};

	// �`�����N
	struct Chunk
	{
		UINT32				tag;			// �`�����N�`���̎��ʎq 'fmt ' 'data'
		UINT32				size;			// �f�[�^�T�C�Y('fmt '���j�APCM�Ȃ��16 'data'�g�`�f�[�^�T�C�Y)
	};

	// fmt �`�����N
	struct Fmt
	{
		UINT16				fmtId;			// �t�H�[�}�b�gID(���j�APCM�Ȃ��1)
		UINT16				channel;		// �`�����l����(���m����:1 �X�e���I:2)
		UINT32				sampleRate;		// �T���v�����O���[�g(44.1kHz�Ȃ�44100)
		UINT32				transRate;		// �f�[�^���x(Byte/sec) [ 44.1kHz 16bit �X�e���I 44100�~2�~2 ]
		UINT16				blockSize;		// �u���b�N�T�C�Y(Byte/sample�~�`�����l����)
		UINT16				quantumBits;	// �T���v��������̃r�b�g��(bit/sample)
	};

	Riff					riff;
	Fmt						fmt;
	std::vector<char>		data;
};