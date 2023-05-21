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
#include "operation.h"


using namespace std;
int main()
{
	Output output;
	output.startInit();

	//File fl;
	//fl.fileModifyList('3');


	system("pause>nul");
	return 0;
}

// TODO:[优化]开始菜单的输入可以使用_getch，提高效率
// TODO:[优化]file.cpp在检测日期所在的streampos时，推荐使用find()，以免日期前有空格或者其他东西导致检测失败
// TODO:[优化]完成和删除时可以先检测今日的ToDo-List是否为空