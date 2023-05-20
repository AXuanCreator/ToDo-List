//
// Created by AXuan on 2023/5/19.
//

/*
 * 此类用于控制所有操作
 * ALL
 */
#ifndef OPERATION_H
#define OPERATION_H

#include "consoleset.h"
#include "file.h"
#include <iostream>
#include <conio.h>

#define CLS system("cls")
#define PAUSE system("pause>nul")
using namespace std;

class Output
{
private:
	ConsoleSet consoleSet;
	File file;
public:

	void startInit();
	void creatList();
	void inquireList();
	void addList();
	void modifyList();
	void showList(const vector<string>& list);

	vector<string> addList(int level);

	static bool judgeYN();


};


#endif //OPERATION_H
