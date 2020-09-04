#pragma once
#include <iostream>
#include "_Common.h"
#include "_Player.h"
#include "_Board.h"
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class File {
private:
	string Name, Date;
public:
	void set(string name, string date) {
		this->Name = name;
		this->Date = date;
	}
	string getName() {
		return Name;
	}
	string getDate() {
		return Date;
	}
	~File() {
		Name.clear();
		Date.clear();
	}
};
class _Menu:public _Board
{
public:
	string menu[5] = { "New Game" ,"Load Game" ,"Help", "About" ,"Exit" };

	string AI_PerSon[3] = { "Player with Player","Player with Computer (hard)","Player with Computer (easy)" };

	string Head_Load_Game = "LIST OF GAMES WERE SAVED";

	string Head_Help = "<< Help >>";
	string key_Help[6] = { "W/Top Key", "S/Bottom Key", "D/Right Key", "A/Left Key", "Space/Enter", "ESC" };
	string element_Help[6] = { "Move Top" ,"Move Bottom" , "Move Right" , "Move Left", "Chose", "Exit" };

	string Head_About = "<< About >>";
	string ID_About[4] = { "Phan Nhat Quang","Hoang Minh Huy","Vu Thai Duong","2019" };

	string Exit = " Thank for playing ";

	vector<File> Saved;
	_Menu();
	void show_file(int, int, int);
	void add_to_list(string, string);
	void fixTXT();
	~_Menu();
};

