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
	if (!checkDateName(getDateName(), getFileName())) // 若不存在当前日期
	{
		outFile.open(getFileName(), ios::out |ios::binary |ios::app);
		outFile << getDateName() << endl; // 创建日期
		outFile.close();
	}

}

/*
 * 函数名: fileAddList
 * In : vector<string>&
 * Out : void
 * 作用 : 将vector里的内容输出到文件
 */
void File::fileAddList(vector<string>& list)
{
	outFile.open(getFileName(), ios::in |ios::binary| ios::app);
	//outFile << endl;        // 换到下一行
	if (outFile.is_open())
	{
		for (auto& line : list)
		{
			outFile << line << endl;
		}
	}
	outFile.close();
}

/*
 * 函数名: fileFineLevel
 * In: void
 * Out: int
 * 作用: 返回list中已存在的待办事项个数
 */
int File::fileFineLevel()
{
	streampos startPos = getLinePos(getDateName());
	if (startPos == -1)
		return 0;

	int level = 0;
	inFile.open(getFileName(), ios::in|ios::binary);
	if(inFile.is_open())
	{
		inFile.seekg(startPos);
		string line;
		while(getline(inFile,line))
		{
			if(!line.empty())
				++level;
		}
	}
	inFile.close();
	return level;
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
	dateName << 1900 + date->tm_year << "-" << 1 + date->tm_mon << "-" << date->tm_mday;

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
	fileName << "../log/" << 1900 + date->tm_year << "-" << 1 + date->tm_mon << "log.txt";

	return fileName.str();
}


/*
 * 函数名: fileFineList
 * In: void
 * Out: vector<string>
 * 作用: 返回列表清单
 */
vector<string> File::fileFindList()
{
	streampos startPos = getLinePos(getDateName());
	if (startPos == -1)
		return {};

	vector<string> list;
	inFile.open(getFileName(), ios::in|ios::binary);
	if (inFile.is_open())
	{
		//inFile.clear();
		inFile.seekg(startPos,ios::beg); // 寻找当前日期所在的行

		string line;
		while (getline(inFile, line))
		{
			if (isdigit(line[0]))
				break;
			if(line.empty())
				continue;
			list.push_back(line);

		}
	}

	inFile.close(); // 关闭文件
	return list;
}

/*
 * 函数名: checkDateName
 * In: const string& [datename,filename]
 * Out: bool
 * 作用: 检查[filename]中是否已经记录[datename]
 */
bool File::checkDateName(const string& datename, const string& filename)
{
	inFile.open(filename, ios::in|ios::binary);
	if (inFile.is_open())
	{
		string line;
		while (getline(inFile, line))
		{
			if (line == datename)
			{
				inFile.close();
				return true;
			}

		}
	}
	inFile.close();
	return false;
}

/*
 * 函数名: getLinePos
 * In: const string& [pattern]
 * Out: streampos
 * 作用: 返回文件中指定字符串所在的位置
 */
streampos File::getLinePos(const string& pattern)
{
	string line;
	streampos startPos = 0;
	inFile.open(getFileName(), ios::in|ios::binary);
	if (inFile.is_open())
	{
		while (getline(inFile, line))
		{
			//TODO：这里只能手动计算，用tellg会出问题，why
			startPos+=line.length() + 1;  // 统计每一行字符的长度和换行符
			if (line == pattern)
			{
				inFile.close();
				return startPos; // +1换行
			}
		}
	}
	inFile.close();

	return -1;
}


// test
void File::fileModifyList(char level)
{
	streampos startPos = getLinePos(getDateName());
	if(startPos==-1)
		return;

	ioFile.open(getFileName(),ios::in|ios::out|ios::binary);

	if(ioFile.is_open())
	{
		ioFile.seekg(startPos,ios::beg);
		string line;

		while(getline(ioFile,line))
		{
			//if(level=='1')
				//startPos-=1;                    // 特性，需要-1，不然会多走一格(因为getLinePos返回时已经+1)
			if(line[3]==level)
			{
				//startPos+=1;                    // +1换到下一行，不然只是在上一行的换行符后
				line.replace(1,1,"Y");

				ioFile.seekp(startPos,ios::beg);
				ioFile<<setw(line.length())<<setfill(' '); // 清除之前的内容
				ioFile.seekp(startPos,ios::beg);
				ioFile<<line;
				ioFile.close(); // 小tips:文件的关闭可以立刻刷新文件内容
				break;
			}
			startPos+=line.length()+1;
		}

	}

}




