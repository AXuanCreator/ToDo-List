//
// Created by AXuan on 2023/5/19.
//

/*
 * 此类，用于控制所有与终端有关的操作
 * 光标坐标
 * 光标隐藏
 * 时间获取
 *
 * 所有的函数在.cpp中均有介绍
 */

#ifndef CONSOLESET_H
#define CONSOLESET_H

#include <windows.h>
#include <chrono>
#include <ctime>
#include <iomanip>

class ConsoleSet
{
private:
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
public:
	void setCursor();
	void setCursor(short x,short y);
	void setFont(unsigned short mul=2);

	void hideCursor();


	static tm* getTime();
	static void setMainTittle();
};


#endif //CONSOLESET_H
