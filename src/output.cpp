//
// Created by AXuan on 2023/5/19.
//

#include "output.h"

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
		system("pause>nul");
		system("cls");
	}

	{
		while(true)
		{
			system("cls");
			consoleSet.setCursor(5, 0);
			cout << "ToDo-List" << endl;
			cout << "[1]��������ToDo-List" << endl;
			cout << "[2]��ѯ����ToDo-List" << endl;
			cout << "[3]�޸Ľ���ToDo-List" << endl;
			cout << "[4]�˳�ToDo-List" << endl;
			int option;
			cout << "������ѡ��: [ ]";
			consoleSet.setCursor(13, 5);
			while (!(cin >> option) || option <= 0 || option > 4)
			{
				cin.clear();    // ��������־
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���������ʣ���ַ���ֱ��\n
				consoleSet.setCursor(0, 5);
				cout << "������ѡ��: [ ]                                     ";
				consoleSet.setCursor(13, 5);
			}

			if (option == 1)
			{
				op.creatList();
				cout << "�����ɹ����Ƿ�򿪽����ToDo-List [y/n]"<<endl;
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
 * ������: judgeYN
 * In: void
 * Out: bool
 * ����: static
 * ����: �û�����y/nʱ����boolֵ
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
