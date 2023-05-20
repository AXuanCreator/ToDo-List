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
	if(!checkDateName(getDateName(), getFileName())) // �������ڵ�ǰ����
	{
		outFile.open(getFileName(),ios::out|ios::app);
		outFile<<endl<<getDateName(); // ��������
		outFile.close();
	}

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
	dateName<<1900+date->tm_year<<"-"<<1+date->tm_mon<<"-"<<date->tm_mday;

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
	fileName<<"../log/"<<1900+date->tm_year<<"-"<<1+date->tm_mon<<"log.txt";

	return fileName.str();
}


/*
 * ������: checkDateName
 * In: const string& [datename,filename]
 * Out: bool
 * ����: ���[filename]���Ƿ��Ѿ���¼[datename]
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


