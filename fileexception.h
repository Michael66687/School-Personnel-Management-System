#pragma once
/*文件异常类的声明*/
#include<string>
using std::string;

class FileException
{
public:
	string filename;
	string type;
	string mode;
	FileException(string inputFilename, string inputType, string inputMode)
	{
		filename = inputFilename;
		type = inputType;
		mode = inputMode;
	};
	virtual ~FileException() {};
};