//
// Created by AXuan on 2023/5/19.
//

#include "file.h"


/*
 * ������: fileCreatList
 * In:
 * Out: void
 * ����: ��������TodoList
 */
void File::fileCreatList()
{
	if (!checkDateName(getDateName(), getFileName())) // �������ڵ�ǰ����
	{
		outFile.open(getFileName(), ios::out |ios::binary |ios::app);
		outFile << getDateName() << endl; // ��������
		outFile.close();
	}

}

/*
 * ������: fileAddList
 * In : vector<string>&
 * Out : void
 * ���� : ��vector�������������ļ�
 */
void File::fileAddList(vector<string>& list)
{
	outFile.open(getFileName(), ios::in |ios::binary| ios::app);
	//outFile << endl;        // ������һ��
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
 * ������: fileFineLevel
 * In: void
 * Out: int
 * ����: ����list���Ѵ��ڵĴ����������
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
 * ������: getDateName
 * In: void
 * Out: string
 * ����: ��ȡ��ǰ�����ַ�������ʽΪ 2023-5-20
 */
string File::getDateName()
{
	stringstream dateName;
	dateName << 1900 + date->tm_year << "-" << 1 + date->tm_mon << "-" << date->tm_mday;

	return dateName.str();
}


/*
 * ������: getFileName
 * In: void
 * Out: string
 * ����: ��ȡ�����ļ�������ʽΪ ../log/2023-5log.txt
 */
string File::getFileName()
{
	stringstream fileName;
	fileName << "../log/" << 1900 + date->tm_year << "-" << 1 + date->tm_mon << "log.txt";

	return fileName.str();
}


/*
 * ������: fileFineList
 * In: void
 * Out: vector<string>
 * ����: �����б��嵥
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
		inFile.seekg(startPos,ios::beg); // Ѱ�ҵ�ǰ�������ڵ���

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

	inFile.close(); // �ر��ļ�
	return list;
}

/*
 * ������: checkDateName
 * In: const string& [datename,filename]
 * Out: bool
 * ����: ���[filename]���Ƿ��Ѿ���¼[datename]
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
 * ������: getLinePos
 * In: const string& [pattern]
 * Out: streampos
 * ����: �����ļ���ָ���ַ������ڵ�λ��
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
			//TODO������ֻ���ֶ����㣬��tellg������⣬why
			startPos+=line.length() + 1;  // ͳ��ÿһ���ַ��ĳ��Ⱥͻ��з�
			if (line == pattern)
			{
				inFile.close();
				return startPos; // +1����
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
				//startPos-=1;                    // ���ԣ���Ҫ-1����Ȼ�����һ��(��ΪgetLinePos����ʱ�Ѿ�+1)
			if(line[3]==level)
			{
				//startPos+=1;                    // +1������һ�У���Ȼֻ������һ�еĻ��з���
				line.replace(1,1,"Y");

				ioFile.seekp(startPos,ios::beg);
				ioFile<<setw(line.length())<<setfill(' '); // ���֮ǰ������
				ioFile.seekp(startPos,ios::beg);
				ioFile<<line;
				ioFile.close(); // Сtips:�ļ��Ĺرտ�������ˢ���ļ�����
				break;
			}
			startPos+=line.length()+1;
		}

	}

}




