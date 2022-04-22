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


//文字コードの変換機構（日本語に対応させるため）
std::wstring utf8_to_wide_cppapi(std::string const& src)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(src);
}

//wstringからstringに変換
std::string WStringToString(std::wstring oWString)
{
	// wstring → SJIS
	int iBufferSize = WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str()
		, -1, (char*)NULL, 0, NULL, NULL);

	// バッファの取得
	CHAR* cpMultiByte = new CHAR[iBufferSize];

	// wstring → SJIS
	WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str(), -1, cpMultiByte
		, iBufferSize, NULL, NULL);

	// stringの生成
	std::string oRet(cpMultiByte, cpMultiByte + iBufferSize - 1);

	// バッファの破棄
	delete[] cpMultiByte;

	// 変換結果を返す
	return(oRet);
}



ExportText::ExportText(string fileName)
{
	//初期化
	scripts.clear();

	//メモ帳を開く
	std::ifstream ifs(fileName.c_str());
	assert(!ifs.fail());
	if (ifs.fail())
		return;

	//構文解析
	string str;

	while (getline(ifs, str))
	{
		if (str.size() == 0)
			continue;

		//文字変換
		{
			std::wstring wStr = utf8_to_wide_cppapi(str);
			str = WStringToString(wStr);
		}

		//ここで「　//　」があるなら登録しない
		if (str.find("/") == 0)
		{
			if (str.find("/",1) == 1)
			{
				continue;
			}
		}
	
		//ここで改行コードがあるなら変換する
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
