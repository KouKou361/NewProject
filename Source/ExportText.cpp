#include <fstream>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include "ExportScript.h"

#include <windows.h>
#include <crtdbg.h>

#include <string>

#include <iostream>
#include <string>
#include <locale>
#include <codecvt>


//�����R�[�h�̕ϊ��@�\�i���{��ɑΉ������邽�߁j
std::wstring utf8_to_wide_cppapi(std::string const& src)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(src);
}

//wstring����string�ɕϊ�
std::string WStringToString(std::wstring oWString)
{
	// wstring �� SJIS
	int iBufferSize = WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str()
		, -1, (char*)NULL, 0, NULL, NULL);

	// �o�b�t�@�̎擾
	CHAR* cpMultiByte = new CHAR[iBufferSize];

	// wstring �� SJIS
	WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str(), -1, cpMultiByte
		, iBufferSize, NULL, NULL);

	// string�̐���
	std::string oRet(cpMultiByte, cpMultiByte + iBufferSize - 1);

	// �o�b�t�@�̔j��
	delete[] cpMultiByte;

	// �ϊ����ʂ�Ԃ�
	return(oRet);
}



ExportText::ExportText(string fileName)
{
	//������
	scripts.clear();

	//���������J��
	std::ifstream ifs(fileName.c_str());
	assert(!ifs.fail());
	if (ifs.fail())
		return;

	//�\�����
	string str;

	while (getline(ifs, str))
	{
		if (str.size() == 0)
			continue;

		//�����ϊ�
		{
			std::wstring wStr = utf8_to_wide_cppapi(str);
			str = WStringToString(wStr);
		}

		//�����Łu�@//�@�v������Ȃ�o�^���Ȃ�
		if (str.find("/") == 0)
		{
			if (str.find("/",1) == 1)
			{
				continue;
			}
		}
	
		//�����ŉ��s�R�[�h������Ȃ�ϊ�����
		int Index = str.find('\\', 0);
		if (Index != -1)
		{
			if (str.find("n", 1) != -1)
			{
				str.erase(Index, 2);
				str.insert(Index, "\n");
			}


				
			
		}
		

		
		

		scripts.push_back(str);
	}
}
