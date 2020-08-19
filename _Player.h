#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Player
{
private:
	string name;
	int win, lose, draw, ID;
public:
	Player();
	void setName(string);
	void setID(int);
	void setWin(int);
	void setLose(int);
	void setDraw(int);

	string getName();
	int getWin();
	int getLose();
	int getDraw();
	int getID();

	Player& operator++();

	Player& operator--();

	void increaWin();
	void increaLose();
	void increaDraw();

	~Player();
	friend ofstream& operator<<(ofstream&, Player);
	friend ifstream& operator>>(ifstream&, Player&);
};

