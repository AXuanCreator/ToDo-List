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
			cout << "[5]完成今日ToDo-List" << endl;
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
				creatList();

			if (option == 2)
				inquireList();
				PAUSE;

			if (option == 3)
				addList();

			if (option == 4)
				deleteList();

			if (option == 5)
				modifyList();

			if (option == 6)
				return;

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
	if(file.checkDateName(file.getDateName(),file.getFileName()))
	{
		CLS;
		cout << "你已创建今日ToDo-List，请勿重复创建。";
		PAUSE;
		return;
	}

	file.fileCreatList();
	CLS;
	cout << "创建成功，正在检测昨日未完成事项..." << endl;
	Sleep(500);
	cout << "检测完成，以下是昨日未完成事项，是否需要增加到今天的ToDo-List? [y/n]" << endl;
	vector<string> list = file.fileFindUndone();
	showList(list);
	if(judgeYN())
	{
		CLS;
		addList(list);
		cout << "新增成功!" << endl;
	}

	cout << "是否新增今天的ToDo-List [y/n]" << endl;
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
 * 函数名: inputList
 * In: void / vector<string>&
 * Out: void
 * 作用: 新增今日ToDo-List [手动/列表]
 */
void Output::addList()
{
	vector<string> list = inputList(file.fileFineLevel());
	file.fileAddList(list);
}
void Output::addList(vector<string>& list)
{
	// 对list进行排序
	int level = file.fileFineLevel() + 1; // +1是因为如果没有任何内容，会返回0
	for(auto& line : list)
	{
		line.replace(3,1,to_string(level));
		++level;
	}

	// 添加
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
		cout << "\n[按下已完成项目所对应的数字编号，按q退出]";
		level = static_cast<char>(_getch());
		file.fileModifyList(level);
		inquireList();

		if (level == 'q')
			break;
	}
}

/*
 * 函数名: deleteList
 * In:void
 * Out:void
 * 作用:删除今日ToDo-List
 */
void Output::deleteList()
{
	char level;
	inquireList();
	while (true)
	{
		cout << "\n[按下需要删除项目的所对应的数字编号，按q退出]";
		level = static_cast<char>(_getch());
		file.fileDeleteList(level);
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
	//consoleSet.setCursor(0, 1);
	cout << endl;
	for (auto& str : list)
	{
		if(str.empty())
			continue;
		cout << str << endl;
	}
}

/*
 * 函数名: inputList
 * In: int [level]已有的事项数
 * Out: vector<string>
 * 作用: 输入并返回待做事项列表
 */
vector<string> Output::inputList(int level)
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


