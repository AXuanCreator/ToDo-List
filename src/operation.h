//
// Created by AXuan on 2023/5/19.
//

/*
 * 此类，用于控制所有用户操作有关的操作
 * 选择新建ToDo
 * 选择删除ToDo
 * 选择显示指定日期ToDo
 * 选择显示当前日期ToDo
 */
#ifndef OPERATION_H
#define OPERATION_H

#include <sstream>
#include "file.h"
#include "consoleset.h"

using namespace std;

static tm* date = ConsoleSet::getTime();

class Operation
{
private:
	File fileCtr;
public:
	void creatList();
};


#endif //OPERATION_H
