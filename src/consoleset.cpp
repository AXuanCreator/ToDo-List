//
// Created by AXuan on 2023/5/19.
//

#include "consoleset.h"

/*
 * 函数名: ConsoleSet
 * In: void / short {x,y}
 * Out: void
 * 作用: 设置光标位置
 */
void ConsoleSet::setCursor()
{
	SetConsoleCursorPosition(hConsole,{0,0});
}
void ConsoleSet::setCursor(short x, short y)
{
	SetConsoleCursorPosition(hConsole,{x,y});
}


/*
 * 函数名: setFont
 * In: mul [字体的倍数，默认值为2]
 * Out: void
 * 作用: 按倍数放大或缩小字体(默认两倍放大)
 */
void ConsoleSet::setFont(unsigned short mul)
{
	// 获取字体属性
	CONSOLE_FONT_INFOEX fontInfo;
	fontInfo.cbSize = sizeof(fontInfo);
	GetCurrentConsoleFontEx(hConsole,false,&fontInfo);

	// 设置字体
	fontInfo.dwFontSize.X *= mul;
	fontInfo.dwFontSize.Y *= mul;
	SetCurrentConsoleFontEx(hConsole,false,&fontInfo);
}


/*
 * 函数名： hideCursor
 * In: void
 * Out: void
 * 作用： 隐藏光标
 */
void ConsoleSet::hideCursor()
{
	CONSOLE_CURSOR_INFO consoleCursorInfo;
	consoleCursorInfo.dwSize = 1;       // 将大小设置为1
	consoleCursorInfo.bVisible = false; // 将可见设为false
	SetConsoleCursorInfo(hConsole,&consoleCursorInfo);
}


/*
 * 函数名： getTime
 * In: void
 * Out: tm*  [包含各种时间信息的结构体]
 * 属性: static
 * 作用: 获取当前日期
 */
tm* ConsoleSet::getTime()
{
	// 获取当前系统时间的时间点
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

	// 转换为C风格的时间结构体-以便显示日期
	std::time_t time = std::chrono::system_clock::to_time_t(now);

	// 使用C风格获取日期
	std::tm* date = std::localtime(&time);

	return date;
}


/*
 * 函数名: setMainTittle
 * In: void
 * Out: void
 * 属性: static
 * 作用: 设置CMD主标题
 */
void ConsoleSet::setMainTittle()
{
	SetConsoleTitle("ToDo-List");
}


