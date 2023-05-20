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
			cout << "[5]�޸Ľ���ToDo-List" << endl;
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
				//TODO: ɾ������List���ʹ�һ��ԭ��ֱ���ÿո��滻�������ʱ����������е�
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
 * ������: creatList
 * In: void
 * Out: void
 * ����: ��������ToDo-List
 */
void Output::creatList()
{
	file.fileCreatList();
	CLS;
	cout << "�����ɹ����Ƿ����������ToDo-List [y/n]" << endl;
	// TODO:����֮����Ҫ�������������Ƿ�ȫ����ɣ���δ��ɣ����Զ���ӵ�����
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
	// TODO:���û�д�������Ӧ������ʾ�Ƿ񴴽�
	// TODO:������δ��룬����еĻ����ᵼ�²����������

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
 * ������: addList
 * In: void
 * Out: void
 * ����: ��������ToDo-List
 */
void Output::addList()
{
	vector<string> list = addList(file.fileFineLevel());
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
		cout << "[�����������Ŀ����Ӧ�����ֱ�ţ���q�˳�]";
		level = static_cast<char>(_getch());
		file.fileModifyList(level);
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
	consoleSet.setCursor(0, 1);
	for (auto& str : list)
	{
		cout << str << endl;
	}
}

/*
 * ������: addList
 * In: int [level]���е�������
 * Out: vector<string>
 * ����: ���벢���ش��������б�
 */
vector<string> Output::addList(int level)
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


