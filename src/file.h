//
// Created by AXuan on 2023/5/19.
//

/*
 * 此类，用于控制所有与文件读写有关的操作
 * 写入
 * 读取
 * 删除
 * 创建
 * 查找
 */

#pragma once

#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "consoleset.h"

using namespace std;

class File
{
private:
	tm* date = ConsoleSet::getTime();
	ifstream inFile;
	ofstream outFile;
	fstream  ioFile;
public:

	void fileCreatList();
	void fileAddList(vector<string>& list);
	void fileModifyList(char level);
	void fileDeleteList(unsigned char level);

	int fileFineLevel();

	string getDateName();
	string getDateName(int past);
	string getFileName();

	vector<string> fileFindList();
	vector<string> fileFindUndone();

	streampos getLinePos(const string& pattern);


	bool checkDateName(const string& datename, const string& filename);

};


#endif //FILE_H
