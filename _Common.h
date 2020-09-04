#pragma once
#include <iostream>
#include <Windows.h>
#define Width  1000
#define Height  550
#define Columns 119
#define Rows 31
#define BackRound_menu 0
#define BackRound_play 7

using namespace std;
class _Common
{
public:
	_Common();
	static void fixConsoleWindow();
	static void gotoxy(int, int);
	static void ClearConsoleToColors(int);
	static void resizeConsole();

	static int getColumns();
	static int getRows();
	static void textcolor(int);
	static void Hidden_Cursor();
	static void Show_Cursor();
};
