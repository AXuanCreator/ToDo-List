//
// Created by AXuan on 2023/5/19.
//

#include "file.h"


/*
 * 函数名: fileCreatList
 * In:
 * Out: void
 * 作用: 创建今日TodoList
 */
void File::fileCreatList()
{
	if(!checkDateName(getDateName(), getFileName())) // 若不存在当前日期
	{
		outFile.open(getFileName(),ios::out|ios::app);
		outFile<<endl<<getDateName(); // 创建日期
		outFile.close();
	}

}


/*
 * 函数名: getDateName
 * In: void
 * Out: string
 * 作用: 获取当前日期字符串，格式为 2023-5-20
 */
string File::getDateName()
{
	stringstream dateName;
	dateName<<1900+date->tm_year<<"-"<<1+date->tm_mon<<"-"<<date->tm_mday;

	return dateName.str();
}


/*
 * 函数名: getFileName
 * In: void
 * Out: string
 * 作用: 获取当月文件名，格式为 ../log/2023-5log.txt
 */
string File::getFileName()
{
	stringstream fileName;
	fileName<<"../log/"<<1900+date->tm_year<<"-"<<1+date->tm_mon<<"log.txt";

	return fileName.str();
}


/*
 * 函数名: checkDateName
 * In: const string& [datename,filename]
 * Out: bool
 * 作用: 检查[filename]中是否已经记录[datename]
 */
bool File::checkDateName(const string& datename, const string& filename)
{
	inFile.open(filename,ios::in);
	if(inFile.is_open())
	{
		string line;
		while(getline(inFile,line))
		{
			if(line==datename)
				return true;
		}
	}
	inFile.close();
	return false;
}


