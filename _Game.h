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
	_Board* _b;
	int _x, _y; 
	int _command; 
	bool _loop = false; 
	long long attack[7] = { 0, 3, 24, 192, 1536, 12288, 98304 };
	long long defense[7] = { 0, 1, 9, 81, 729, 6561, 59049 };
public:
	_Game(Player&, Player&, int, int, int);
	~_Game();

	char waitKeyBoard(); 
	int getCommand();
	char askContinue();

	void SetLoop(bool loop = false);
	void startGame(Player&, Player&); 
	void exitGame(); 
	char processFinish(Player&, Player&);
	bool processCheckBoard(Player&, Player&);

	void Undo(Player&, Player&);
	void Save(Player, Player, _Menu&);

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

	vector<int> alpha_beta();
	vector<int> easy();
};

