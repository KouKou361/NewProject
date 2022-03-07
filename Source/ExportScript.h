#pragma once
#include <string>
#include <vector>
using namespace std;
class ExportScript
{
private:
	// \•¶‰ğÍ
	vector<string> scripts;
public:
	ExportScript(string fileName);
	~ExportScript() {};


	vector<string>* GetScripts() { return &scripts; }

};