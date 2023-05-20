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
#include "consoleset.h"

using namespace std;

class File
{
private:
	tm* date = ConsoleSet::getTime();
	ifstream inFile;
	ofstream outFile;
public:

	void fileCreat();
	void fileCreatList();

	string getDateName();
	string getFileName();

	bool checkDateName(const string& datename, const string& filename);

};


#endif //FILE_H
