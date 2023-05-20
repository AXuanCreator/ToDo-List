//
// Created by AXuan on 2023/5/19.
//

#include "operation.h"

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
		PAUSE;
		CLS;
	}

	{
		while (true)
		{
			CLS;
			consoleSet.setCursor(5, 0);
			cout << "ToDo-List" << endl;
			cout << "[1]创建今日ToDo-List" << endl;
			cout << "[2]查询今日ToDo-List" << endl;
			cout << "[3]新增今日ToDo-List" << endl;
			cout << "[4]删除今日ToDo-List" << endl;
			cout << "[5]修改今日ToDo-List" << endl;
			cout << "[6]退出ToDo-List" << endl;
			int option;
			cout << "请输入选项: [ ]";
			consoleSet.setCursor(13, 7);
			while (!(cin >> option) || option <= 0 || option > 6)
			{
				cin.clear();    // 清除错误标志
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除缓冲区剩余字符，直到\n
				consoleSet.setCursor(0, 7);
				cout << "请输入选项: [ ]                                     ";
				consoleSet.setCursor(13, 7);
			}

			if (option == 1)
			{
				creatList();
			}
			if (option == 2)
			{
				inquireList();
				PAUSE;
			}


			if (option == 3)
				addList();

			if (option == 4)
			{
				//TODO: 删除今日List，和打勾一个原理，直接用空格替换，输出的时候会跳过空行的
			}
			if (option == 5)
				modifyList();

			if (option == 6)
			{
				return;
			}
		}

	}

}

/*
 * 函数名: creatList
 * In: void
 * Out: void
 * 作用: 创建今日ToDo-List
 */
void Output::creatList()
{
	file.fileCreatList();
	CLS;
	cout << "创建成功，是否新增今天的ToDo-List [y/n]" << endl;
	// TODO:创建之后需要检测昨天的任务是否全部完成，若未完成，则自动添加到今日
	if (judgeYN())
		addList();
}

/*
 * 函数名: inquirelist
 * In: void
 * Out: void
 * 作用: 查询今日ToDo-List
 */
void Output::inquireList()
{
	// TODO:如果没有创建，则应该有提示是否创建
	// TODO:下面这段代码，如果有的话，会导致不能正常输出

	CLS;
	if (!file.checkDateName(file.getDateName(), file.getFileName()))
	{
		cout << "今日还未创建ToDo-List，是否现在创建?[y/n]";
		if (judgeYN())
			creatList();
		else
			return;
	}

	CLS;
	consoleSet.setCursor(5, 0);
	cout << "*" << file.getDateName() << "*" << endl;
	showList(file.fileFindList());
}

/*
 * 函数名: addList
 * In: void
 * Out: void
 * 作用: 新增今日ToDo-List
 */
void Output::addList()
{
	vector<string> list = addList(file.fileFineLevel());
	file.fileAddList(list);
}

/*
 * 函数名: modifyList
 * In: void
 * Out: void
 * 作用: 修改今日ToDo-List
 */
void Output::modifyList()
{
	char level;
	inquireList();
	while (true)
	{
		cout << "[按下已完成项目所对应的数字编号，按q退出]";
		level = static_cast<char>(_getch());
		file.fileModifyList(level);
		inquireList();

		if (level == 'q')
			break;
	}
}

/*
 * 函数名: showList
 * In: const vector<string>&
 * Out: void
 * 作用: 打印列表
 */
void Output::showList(const vector<string>& list)
{
	consoleSet.setCursor(0, 1);
	for (auto& str : list)
	{
		cout << str << endl;
	}
}

/*
 * 函数名: addList
 * In: int [level]已有的事项数
 * Out: vector<string>
 * 作用: 输入并返回待做事项列表
 */
vector<string> Output::addList(int level)
{
	vector<string> list;

	while (true)
	{
		CLS;
		string line;
		consoleSet.setCursor(0, 0);
		cout << "请输入你的代办清单(输入exit退出): ";
		consoleSet.setCursor(33, 0);
		cin >> line;

		if (line == "exit")
			break;

		cout << "确认?[y/n]";
		if (judgeYN())
		{
			consoleSet.setCursor(0, 1);
			cout << "已载入列表                    ";

			stringstream ssline;
			ssline << "[ ]" << ++level << "." << line;
			list.push_back(ssline.str());
		}
	}

	return list;
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
	while (true)
	{
		char r = static_cast<char>(_getch());
		if (r == 'y')
			return true;
		else if (r == 'n')
			return false;
	}
}


