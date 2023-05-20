//
// Created by AXuan on 2023/5/19.
//

#include "output.h"

/*
 * 函数名: startInit
 * In: void
 * Out: void
 * 作用: CMD中界面初始化
 */
void Output::startInit()
{
	consoleSet.hideCursor();        // 隐藏光标
	ConsoleSet::setMainTittle();    // 设置主标题

	{
		cout << "初始化中，请稍等..." << endl;
		Sleep(300);
		cout << "初始化完成，按任意键进入ToDo-List";
		system("pause>nul");
		system("cls");
	}

	{
		while(true)
		{
			system("cls");
			consoleSet.setCursor(5, 0);
			cout << "ToDo-List" << endl;
			cout << "[1]创建今日ToDo-List" << endl;
			cout << "[2]查询今日ToDo-List" << endl;
			cout << "[3]修改今日ToDo-List" << endl;
			cout << "[4]退出ToDo-List" << endl;
			int option;
			cout << "请输入选项: [ ]";
			consoleSet.setCursor(13, 5);
			while (!(cin >> option) || option <= 0 || option > 4)
			{
				cin.clear();    // 清除错误标志
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除缓冲区剩余字符，直到\n
				consoleSet.setCursor(0, 5);
				cout << "请输入选项: [ ]                                     ";
				consoleSet.setCursor(13, 5);
			}

			if (option == 1)
			{
				op.creatList();
				cout << "创建成功，是否打开今天的ToDo-List [y/n]"<<endl;
				if(judgeYN())
					option=2;
				else
					continue;
			}
			if (option == 2)
			{
				cout << "here";
			}
			if (option == 3)
			{

			}
			if(option == 4)
			{
				system("cls");
				return;
			}
		}

	}

}


/*
 * 函数名: judgeYN
 * In: void
 * Out: bool
 * 属性: static
 * 作用: 用户键入y/n时返回bool值
 */
bool Output::judgeYN()
{
	while(true)
	{
		char r = static_cast<char>(_getch());
		if(r=='y')
			return true;
		else if(r=='n')
			return false;
	}
}
