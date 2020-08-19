#pragma once
#include <iostream>
#include "_Point.h"
#include "_Common.h"
#include "_Player.h"
#define left_x_pipeline 70
#define right_x_pipeline 110
#define left_mid_x_pipeline 80
#define right_mid_x_pipeline 100
#define top_y_pipeline 10
#define down_y_pipeline 20
#define line_x_pipeline 90

using namespace std;
class _Board
{
private:
	string func[4] = { "1: New Game","2: Load Game","3: Save Game","4: Undo" };
	int _size;
//	int _left, _top;
	_Point** _pArr;


public:
	_Board();
	_Board(int, int, int);
	~_Board();
	int getSize();
//	int getLeft();
//	int getTop();
	int getXAt(int, int);
	int getYAt(int, int);

	void setIJ(int, int, int);
	int getIJ(int, int);
	void resetData();
	void drawBoard(Player, Player);
	void drawTurn(int, int);
	int checkTurn(int, int, int);
	void clearpipeline();

	int check(int, int);
	bool check_Row(int, int);
	bool check_Col(int, int);
	bool check_Diagonal_1(int, int);
	bool check_Diagonal_2(int, int);

	friend ofstream& operator<<(ofstream&, _Board);
	friend ifstream& operator>>(ifstream&, _Board&);
};


