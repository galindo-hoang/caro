#pragma once
#include <iostream>
#include "_Board.h"
#include "_Common.h"
#include "_Player.h"
#include "Picture.h"
#include "_Menu.h"
#include <conio.h>
#include <ctime>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

class _Game: public _Picture
{
private:
	_Board* _b;// một bàn cờ
	int _x, _y; // Tọa độ hiện hành của nháy chuột
	int _command; // phím gõ từ người dùng
	bool _loop = false; // Biến quyết định thoát game hay 60hông
	long long attack[7] = { 0, 3, 24, 192, 1536, 12288, 98304 };
	long long defense[7] = { 0, 1, 9, 81, 729, 6561, 59049 };
public:
	_Game(Player&, Player&, int, int, int);
	~_Game();

	int getCommand();
	bool isContinue();
	char waitKeyBoard(); // Hàm nhận phím từ người dùng
	char askContinue();
	void startGame(Player&, Player&); // Hàm bắt đầu game
	void exitGame(); // Hàm thoát game
	char processFinish(Player&, Player&);
	bool processCheckBoard(Player&, Player&);

	void Undo(Player&, Player&);
	void Save(Player, Player, _Menu&);

//	void dele(_Menu&, int);
	void loading(Player&, Player&, _Menu, int);

	void moveRight();
	void setXY(int, int);
	void moveLeft();
	void moveUp();
	void moveDown();

	// may

	bool bad_trip_1(int, int, int);
	bool bad_trip_2(int, int, int);

	long long attack_Cot(int, int);
	long long attack_dong(int, int);
	long long attack_Cheo_1(int, int);
	long long attack_Cheo_2(int, int);

	long long defen_Dong(int, int);
	long long defen_Cot(int, int);
	long long defen_Cheo_1(int, int);
	long long defen_Cheo_2(int, int);

	vector<int> minimax();
};

