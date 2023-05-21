//
// Created by AXuan on 2023/5/19.
//

#include "operation.h"

/*
 * ������: startInit
 * In: void
 * Out: void
 * ����: CMD�н����ʼ��
 */
void Output::startInit()
{
	consoleSet.hideCursor();        // ���ع��
	ConsoleSet::setMainTittle();    // ����������

	{
		cout << "��ʼ���У����Ե�..." << endl;
		Sleep(300);
		cout << "��ʼ����ɣ������������ToDo-List";
		PAUSE;
		CLS;
	}

	{
		while (true)
		{
			CLS;
			consoleSet.setCursor(5, 0);
			cout << "ToDo-List" << endl;
			cout << "[1]��������ToDo-List" << endl;
			cout << "[2]��ѯ����ToDo-List" << endl;
			cout << "[3]��������ToDo-List" << endl;
			cout << "[4]ɾ������ToDo-List" << endl;
			cout << "[5]��ɽ���ToDo-List" << endl;
			cout << "[6]�˳�ToDo-List" << endl;
			int option;
			cout << "������ѡ��: [ ]";
			consoleSet.setCursor(13, 7);
			while (!(cin >> option) || option <= 0 || option > 6)
			{
				cin.clear();    // ��������־
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���������ʣ���ַ���ֱ��\n
				consoleSet.setCursor(0, 7);
				cout << "������ѡ��: [ ]                                     ";
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
 * ������: creatList
 * In: void
 * Out: void
 * ����: ��������ToDo-List
 */
void Output::creatList()
{
	if(file.checkDateName(file.getDateName(),file.getFileName()))
	{
		CLS;
		cout << "���Ѵ�������ToDo-List�������ظ�������";
		PAUSE;
		return;
	}

	file.fileCreatList();
	CLS;
	cout << "�����ɹ������ڼ������δ�������..." << endl;
	Sleep(500);
	cout << "�����ɣ�����������δ�������Ƿ���Ҫ���ӵ������ToDo-List? [y/n]" << endl;
	vector<string> list = file.fileFindUndone();
	showList(list);
	if(judgeYN())
	{
		CLS;
		addList(list);
		cout << "�����ɹ�!" << endl;
	}

	cout << "�Ƿ����������ToDo-List [y/n]" << endl;
	if (judgeYN())
		addList();
}

/*
 * ������: inquirelist
 * In: void
 * Out: void
 * ����: ��ѯ����ToDo-List
 */
void Output::inquireList()
{
	CLS;
	if (!file.checkDateName(file.getDateName(), file.getFileName()))
	{
		cout << "���ջ�δ����ToDo-List���Ƿ����ڴ���?[y/n]";
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
 * ������: inputList
 * In: void / vector<string>&
 * Out: void
 * ����: ��������ToDo-List [�ֶ�/�б�]
 */
void Output::addList()
{
	vector<string> list = inputList(file.fileFineLevel());
	file.fileAddList(list);
}
void Output::addList(vector<string>& list)
{
	// ��list��������
	int level = file.fileFineLevel() + 1; // +1����Ϊ���û���κ����ݣ��᷵��0
	for(auto& line : list)
	{
		line.replace(3,1,to_string(level));
		++level;
	}

	// ���
	file.fileAddList(list);
}


/*
 * ������: modifyList
 * In: void
 * Out: void
 * ����: �޸Ľ���ToDo-List
 */
void Output::modifyList()
{
	char level;
	inquireList();
	while (true)
	{
		cout << "\n[�����������Ŀ����Ӧ�����ֱ�ţ���q�˳�]";
		level = static_cast<char>(_getch());
		file.fileModifyList(level);
		inquireList();

		if (level == 'q')
			break;
	}
}

/*
 * ������: deleteList
 * In:void
 * Out:void
 * ����:ɾ������ToDo-List
 */
void Output::deleteList()
{
	char level;
	inquireList();
	while (true)
	{
		cout << "\n[������Ҫɾ����Ŀ������Ӧ�����ֱ�ţ���q�˳�]";
		level = static_cast<char>(_getch());
		file.fileDeleteList(level);
		inquireList();

		if (level == 'q')
			break;
	}
}


/*
 * ������: showList
 * In: const vector<string>&
 * Out: void
 * ����: ��ӡ�б�
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
 * ������: inputList
 * In: int [level]���е�������
 * Out: vector<string>
 * ����: ���벢���ش��������б�
 */
vector<string> Output::inputList(int level)
{
	vector<string> list;

	while (true)
	{
		CLS;
		string line;
		consoleSet.setCursor(0, 0);
		cout << "��������Ĵ����嵥(����exit�˳�): ";
		consoleSet.setCursor(33, 0);
		cin >> line;

		if (line == "exit")
			break;

		cout << "ȷ��?[y/n]";
		if (judgeYN())
		{
			consoleSet.setCursor(0, 1);
			cout << "�������б�                    ";

			stringstream ssline;
			ssline << "[ ]" << ++level << "." << line;
			list.push_back(ssline.str());
		}
	}

	return list;
}

/*
 * ������: judgeYN
 * In: void
 * Out: bool
 * ����: static
 * ����: �û�����y/nʱ����boolֵ
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


