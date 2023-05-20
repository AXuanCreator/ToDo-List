//
// Created by AXuan on 2023/5/19.
//

/*
 * 程序的入口
 *
 * 项目名： ToDo记录程序
 * 作用： 记录需要ToDo的事情，并支持通过日期快速搜索
 * 限制： 最大支持记录30天内的ToDo，超过30天会在运行程序时自动删除最早的天
 * 拓展： 支持读写.md文件
 */

#include <iostream>
#include <fstream>

#include "consoleset.h"
#include "file.h"
#include "output.h"


using namespace std;
int main()
{
	Output output;
	output.startInit();



	system("pause>nul");
	return 0;
}