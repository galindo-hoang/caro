#pragma once
#include "_Common.h"
#include "_Board.h"
#include <conio.h>
#include <iostream>

using namespace std;
class _Picture : public _Common {
private:
	string x[8] = { "xxxxx    xxxxx", " x:::x  x:::x", "  x:::xx:::x", "   x::::::x", "   x::::::x", "  x:::xx:::x", " x:::x  x:::x", "xxxxx    xxxxx" };
	string o[8] = { "    0000000","  00:::::::00"," 0::::000::::0","0::::0   0::::0","0::::0   0::::0"," 0::::000::::0","  00:::::::00","    0000000" };
public:
	char menu();
	void draw_x();
	void clear_x_o();
	void draw_o();
	void show_win();
	void show_draw();
};
