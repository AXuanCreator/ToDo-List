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
			if(!line.empty() && line[0]!=' ')  // 填充时可能会存在空格的情况
				++level;
		}
	}
	inFile.close();
	return level;
}


/*
 * 函数名: getDateName
 * In: void / int
 * Out: string
 * 作用: 获取 [当前 / 过去past天] 日期字符串，格式为 2023-5-20
 */
string File::getDateName()
{
	stringstream dateName;
	dateName << 1900 + date->tm_year << "-" << 1 + date->tm_mon << "-" << date->tm_mday;

	return dateName.str();
}

string File::getDateName(int past)
{
	if(date->tm_mday == 1) // TODO: [优化]是否可以读取上个月末尾的那个一天的未做事项
		return "";

	stringstream dateName;
	dateName << 1900 + date->tm_year << "-" << 1+date->tm_mon << "-" << date->tm_mday-past;
	cout << dateName.str();
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
			if(line.empty() || line[0] == ' ') // 当为空字符串或者为空格时，跳过
				continue;
			list.push_back(line);

		}
	}

	inFile.close(); // 关闭文件
	return list;
}


/*
 * 函数名: fileFindUndone
 * In: void
 * Out: vector<string>
 * 作用:返回昨日未做的清单
 */
vector<string> File::fileFindUndone()
{
	streampos startPos = getLinePos(getDateName(1));
	if(startPos==-1)
		return {};

	vector<string> list;
	inFile.open(getFileName(),ios::in|ios::binary);
	if(inFile.is_open())
	{
		string line;
		inFile.seekg(startPos,ios::beg);
		while(getline(inFile,line))
		{
			if(isdigit(line[0]))    // 防止读到日期
				break;
			if(line.empty() || line[0]==' ')    // 遇到空字符串或者空格行时，跳过
				continue;

			if(line[1]==' ')            // 如果未完成，这里是空格
				list.push_back(line);
		}
	}
	inFile.close();
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
			//TODO: [?]这里只能手动计算，用tellg会出问题，why
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


/*
 * 函数名: fileModifyList
 * In: char
 * Out: void
 * 作用: 给今日List的某一事项打勾
 */
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
			if(line[3]==level)
			{
				//startPos+=1;                    // +1换到下一行，不然只是在上一行的换行符后
				line.replace(1,1,"Y");

				ioFile.seekp(startPos,ios::beg);
				ioFile<<setw(line.length())<<setfill(' ')<<' '; // 清除之前的内容
				ioFile.seekp(startPos,ios::beg);
				ioFile<<line<<endl;         // TODO:[?]需要加endl，不然当level是最后一个事项序号时，会无反应
				ioFile.close();             // 小tips:文件的关闭可以立刻刷新文件内容
				break;
			}
			startPos+=line.length()+1;
			cout << startPos << endl;
		}

	}

}


/*
 * 函数名: fileDeleteList
 * In: unsigned char
 * Out: void
 * 作用: 删除某一行事项
 */
void File::fileDeleteList(unsigned char level)
{
	streampos startPos = getLinePos(getDateName());

	if(startPos==-1)
		return;

	ioFile.open(getFileName(),ios::in|ios::out|ios::binary);
	if(ioFile.is_open())
	{
		ioFile.seekg(startPos,ios::beg);
		string line;
		bool sw=false;
		while(getline(ioFile,line))
		{
			if(line.empty())    // 空字符，此时这行没有任何内容，跳过即可
			{
				//startPos+=1;
				continue;
			}
			if(line[0]==' ')    // 空格，为上一次删除时遗留，需要统计长度，+1是因为空格后有换行符(二进制)
			{
				startPos+=line.length()+1;
				continue;
			}

			//TODO:[优化]清空行时将该行换成空字符，而不是用空格替代
			if(sw)  // 在做出删除操作后，对后面的列表序号-1
			{
				line.replace(3,1,to_string((line[3]-'0')-1));
				ioFile.seekp(startPos,ios::beg);
				ioFile<<setw(line.length())<<setfill(' ')<<' '; // 清空改行
				ioFile.seekp(startPos,ios::beg);
				ioFile<<line<<endl;
			}
			if(!sw && line[3]==level)
			{
				ioFile.seekp(startPos,ios::beg);
				ioFile<<setw(line.length())<<setfill(' ')<< ' '; // 清空该行

				sw= true;
			}

			startPos+=line.length()+1;

		}
	}
	ioFile.close();
}








