//
// Created by AXuan on 2023/5/19.
//

/*
 * 此类用于控制所有输出
 * 输出
 */
#ifndef OUTPUT_H
#define OUTPUT_H

#include "consoleset.h"
#include "operation.h"
#include <iostream>
#include <conio.h>

using namespace std;

class Output
{
private:
	ConsoleSet consoleSet;
	Operation op;
public:

	void startInit();

	static bool judgeYN();
};


#endif //OUTPUT_H
