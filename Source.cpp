#include <iostream>
#include "_Board.h"
#include "_Common.h"
#include "_Player.h"
#include "_Menu.h"
#include "_Game.h"
#include "Picture.h"
#include <conio.h>
#include <cmath>
#include <cstdlib>
#include <stdio.h>
#define one_third_Columns 39
#define two_thirds_Columns 79
#define one_ninth_Rows 3
#define eight_ninths_Rows 27
#define half_Columns 59

using namespace std;

Player first, second;
_Picture Picture;
_Menu Menu;
_Game Game(first, second,15, 0, 0);
_Board board(15, 0, 0);

int y_menu_up = (2 * _Common::getRows() / 3) + 2;
int y_menu_down = (2 * _Common::getRows() / 3) + 10;

void Load_Game();



void Play() {
	ofstream write;
	string file = "";
	vector<int> bestMove(2);
	_Common::ClearConsoleToColors(1);
	char ar;
	bool ha = false;

	Game.startGame(first, second);

	while (true) {

		if (second.getName() == "computer" && (first.getID() + second.getID()) % 2 == 1) {
			bestMove = Game.minimax();
			Game.setXY(bestMove[1] * 4 + 2, bestMove[0] * 2 + 1);
			
			if (Game.processCheckBoard(first, second)) {

				if (Game.processFinish(first, second)) {
					_Common::gotoxy(0, _Common::getRows());
					return;
				}
			}

		}
		
		ar = _getch();

		switch (ar) {
		case 'w': case 'W': case 72:
			Game.moveUp();
			break;
		case 's': case 'S': case 80:
			Game.moveDown();
			break;
		case 'a': case 'A': case 75:
			Game.moveLeft();
			break;
		case 'd': case 'D': case 77:
			Game.moveRight();
			break;
		case '1':
			_Common::ClearConsoleToColors(1);
			Game.startGame(first, second);
			break;
		case '2':
			Game.exitGame();
			Load_Game();
			_Common::ClearConsoleToColors(1);
			Game.startGame(first, second);
			break;
		case '3':
			Game.Save(first, second, Menu);
			break;
		case '4':
			Game.Undo(first, second);
			if (second.getName() == "computer") Game.Undo(first, second);
			break;
		case 32:
			if (Game.processCheckBoard(first, second)) {
				switch (Game.processFinish(first, second)) {
				case 'y':case'Y':
					_Common::ClearConsoleToColors(1);
					Game.startGame(first, second);
					break;
				case 'n': case'N':
					first.~Player();
					second.~Player();
					Game.exitGame();
					return;
				}
			}
			break;
		case 27:
			first.~Player();
			second.~Player();
			Game.exitGame();
			return;
		}
	}
}

void Load_Game() {
	_Common::ClearConsoleToColors(0);
	string Head = "LIST OF GAMES WERE SAVED";
	int Head_y = _Common::getRows() / 4;
	int start_x = (_Common::getColumns() - Head.size()) / 2;
	int start_y = Head_y + 3;
	int end_y = start_y + (Menu.Saved.size() - 1) * 2;
	int current = start_y;
	char pointer;
	int chose;
	for (int i = 0; i < _Common::getColumns(); ++i) {
		_Common::gotoxy(i, Head_y);
		putchar(205);
	}
	

	_Common::gotoxy(start_x, Head_y);
	_Common::textcolor(11 + BackRound_menu * 16);
	cout << Head;

	Menu.show_file(start_x, start_y, current);
	_Common::gotoxy(start_x, current);


	while (true) {
		pointer = _getch();

		switch (pointer) {
		case 's': case 80:
			current += 2;
			if (current > end_y) current = start_y;
			Menu.show_file(start_x, start_y, current);
			break;
		case 'w': case 72:
			current -= 2;
			if (current < start_y) current = end_y;
			Menu.show_file(start_x, start_y, current);
			break;
		case 27:
			_Common::ClearConsoleToColors(0);
			return;
		case 83:
			chose = (current - start_y) / 2;
			_Common::gotoxy(start_x, current);
			cout << "                                                      ";
			Menu.Saved.erase(Menu.Saved.begin() + chose);
			if (chose != 0) current -= 2;

			_Common::gotoxy(start_x, end_y);
			cout << "                                                      ";

			if (Menu.Saved.size() > 0) end_y -= 2;
			Menu.show_file(start_x, start_y, current);
			break;
		case 13: case 32:
			if (Menu.Saved.size() != 0) {
				chose = (current - start_y) / 2;
				Game.loading(first, second, Menu, chose);
				return;
			}
		}
	}
}

void Help() {
	_Common::ClearConsoleToColors(0);
	int start_x = one_third_Columns + 5;
	int end_x = two_thirds_Columns - 2;
	int start_y = one_ninth_Rows;
	int end_y = eight_ninths_Rows;
	int mid_y = start_y + 4;


	for (int y = start_y; y <= end_y; y++) {
		for (int x = start_x; x <= end_x; x++) {

			if (y == start_y) {
				if (x == start_x) {
					_Common::gotoxy(x, y);
					putchar(201);
				}
				else if (x == end_x) {
					_Common::gotoxy(x, y);
					putchar(187);
				}
				else {
					_Common::gotoxy(x, y);
					putchar(205);
				}

			}
			else if (y == mid_y) {
				if (x == start_x) {
					_Common::gotoxy(x, y);
					putchar(204);
				}
				else if (x == end_x) {
					_Common::gotoxy(x, y);
					putchar(185);
				}
				else {
					_Common::gotoxy(x, y);
					putchar(205);
				}

			}
			else if (y == end_y) {
				if (x == start_x) {
					_Common::gotoxy(x, y);
					putchar(200);
				}
				else if (x == end_x) {
					_Common::gotoxy(x, y);
					putchar(188);
				}
				else {
					_Common::gotoxy(x, y);
					putchar(205);
				}

			}
			else if (x == start_x || x == end_x) {
				_Common::gotoxy(x, y);
				putchar(186);

			}
		}
	}
	_Common::gotoxy((end_x + start_x - Menu.Head_Help.size() + 2) / 2, (start_y + mid_y) / 2);
	cout << Menu.Head_Help;

	for (int i = 0; i < sizeof(Menu.key_Help) / sizeof(string); i++) {
		_Common::gotoxy(start_x + 2, mid_y + i * 3 + 1);
		cout << Menu.key_Help[i];
		_Common::gotoxy(start_x + 15, mid_y + i * 3 + 1); cout << "  :  " << Menu.element_Help[i];
	}

	_Common::gotoxy(start_x + 1, end_y - 1);
	system("pause");
	_Common::ClearConsoleToColors(0);
}

void About() {
	_Common::ClearConsoleToColors(0);
	int start_x = one_third_Columns + 5;
	int end_x = two_thirds_Columns - 2;
	int start_y = one_ninth_Rows;
	int end_y = eight_ninths_Rows;
	int mid_y = start_y + 2;

	for (int y = start_y; y <= end_y; y++) {
		for (int x = start_x; x <= end_x; x++) {

			if (y == start_y) {
				if (x == start_x) {
					_Common::gotoxy(x, y);
					putchar(201);
				}
				else if (x == end_x) {
					_Common::gotoxy(x, y);
					putchar(187);
				}
				else {
					_Common::gotoxy(x, y);
					putchar(205);
				}
				//				Sleep(20);
			}
			else if (y == mid_y) {
				if (x == start_x) {
					_Common::gotoxy(x, y);
					putchar(204);
				}
				else if (x == end_x) {
					_Common::gotoxy(x, y);
					putchar(185);
				}
				else {
					_Common::gotoxy(x, y);
					putchar(205);
				}
				//				Sleep(20);
			}
			else if (y == end_y) {
				if (x == start_x) {
					_Common::gotoxy(x, y);
					putchar(200);
				}
				else if (x == end_x) {
					_Common::gotoxy(x, y);
					putchar(188);
				}
				else {
					_Common::gotoxy(x, y);
					putchar(205);
				}
				//				Sleep(20);
			}
			else if (x == start_x || x == end_x) {
				_Common::gotoxy(x, y);
				putchar(186);
				//				Sleep(20);
			}
		}
	}
	
	_Common::gotoxy((end_x + start_x - Menu.Head_About.size() + 2) / 2, (start_y + mid_y) / 2);
	cout << Menu.Head_About;

	for (int y = 1; y < 5; y++) {
		if (y == 1) {
			_Common::gotoxy(start_x + 2, mid_y + y * 2);
			cout << "design : ";
		}
		else if (y == 4) {
			_Common::gotoxy(start_x + 2, mid_y + y * 2);
			cout << "year   : ";
		}

		_Common::gotoxy(start_x + 2 * 7, mid_y + y * 2);
		cout << Menu.ID_About[y - 1];
	}

	_Common::gotoxy(start_x + 1, end_y - 1);
	system("pause");
	_Common::ClearConsoleToColors(0);
}

void Exit() {
	_Common::ClearConsoleToColors(0);

	_Common::gotoxy((_Common::getColumns() / 2) - Menu.Exit.size() / 2, _Common::getRows() / 2);
	cout << Menu.Exit;
}

void show_play_with(int x, int y, int cursor) {
	for (int i = 0; i < sizeof(Menu.AI_PerSon) / sizeof(string); ++i) {
		_Common::textcolor(15 + BackRound_menu * 16);
		if ((y + i * 2) == cursor) _Common::textcolor(2 + BackRound_menu * 16);

		_Common::gotoxy(x, y + i * 2);
		cout << Menu.AI_PerSon[i];
	}
	_Common::gotoxy(x, cursor);
}

void play_with() {
	_Common::ClearConsoleToColors(0);

	string Head = "<<New Game>>";
	int start_x = (_Common::getColumns() - Head.size()) / 2;
	_Common::gotoxy(start_x, _Common::getRows() / 3);
	cout << Head;
	char cur;
	int x = start_x - 4;
	int y = (_Common::getRows() + 9) / 3;
	int current = y;
	show_play_with(x, y, current);
	while (true) {
		cur = _getch();
		switch (cur) {
		case 'W': case 'w': case 72:
			current -= 2;
			if (current < y) current = y + 2;
			show_play_with(x, y, current);
			break;
		case 'S': case's': case 80:
			current += 2;
			if (current > (y + 2)) current = y;
			show_play_with(x, y, current);
			break;
		case 13: case 32:
			if (current == (y + 2)) second.setName("computer");
			else second.setName("");
			return;
		}
	}
}

void trans_to_new_play() {
	play_with();
	_Common::ClearConsoleToColors(0);
	string Head = "<<New Game>>";
	int start_x = (_Common::getColumns() - Head.size()) / 2;
	_Common::gotoxy(start_x, _Common::getRows() / 3);
	cout << Head;

	_Common::gotoxy(start_x - 5, (_Common::getRows() + 9) / 3);
	cout << "Name Player 1: "; getline(cin, Head);
	while (Head == "") {
		_Common::gotoxy(start_x - 5, (_Common::getRows() + 9) / 3);
		cout << "Name Player 1: "; getline(cin, Head);
	}
	first.setName(Head);

	if (second.getName() == "") {
		_Common::gotoxy(start_x - 5, (_Common::getRows() + 18) / 3);
		cout << "Name Player 2: "; getline(cin, Head);
		while (Head == first.getName()) {
			_Common::gotoxy(start_x - 5, (_Common::getRows() + 18) / 3);
			cout << "                                                      ";
			_Common::gotoxy(start_x - 5, (_Common::getRows() + 18) / 3);
			cout << "Name Player 2: "; getline(cin, Head);
		}
		second.setName(Head);
	}
}


void show_function_menu(int curSor) {
	int average = (Menu.menu[0].size() + Menu.menu[1].size() + Menu.menu[2].size() + Menu.menu[3].size() + Menu.menu[4].size()) / 5;
	for (int i = 0; i < 5; ++i) {
		_Common::gotoxy(half_Columns - average, y_menu_up + i * 2);
		_Common::textcolor(15 + BackRound_menu * 16);

		if (curSor == (y_menu_up + i * 2)) {
			_Common::textcolor(2 + BackRound_menu * 16);
		}
		cout << Menu.menu[i];
	}

	_Common::gotoxy(half_Columns, curSor);
}


void show_menu() {
	int current = 0, chose;
	show_function_menu(current);
	char pointer;
	while (true) {
		if (current == 0) {
			pointer = Picture.menu();
			current = y_menu_up;
			_Common::gotoxy(half_Columns, current);
			show_function_menu(current);
		}
		else pointer = _getch();
		switch (pointer) {
		case 'w': case 'W': case 72:
			current -= 2;

			if (current < y_menu_up) current = y_menu_down;
			show_function_menu(current);
			_Common::gotoxy(half_Columns, current);
			break;
		case 's': case 'S': case 80:
			current += 2;
			if (current > y_menu_down) current = y_menu_up;
			show_function_menu(current);
			_Common::gotoxy(half_Columns, current);
			break;
		case 27:
			current = y_menu_down;
			_Common::gotoxy(half_Columns, current);
			show_function_menu(current);
			break;
		case 13: case 32:
			chose = (current - y_menu_up) / 2;
			switch (chose) {
			case 4:
				Exit();
				return;
			case 3:
				About();
				show_function_menu(current);
				Picture.menu();
				break;
			case 2:
				Help();
				show_function_menu(current);
				Picture.menu();
				break;
			case 1:
				Load_Game();
				Play();
				_Common::ClearConsoleToColors(0);
				_Common::gotoxy(half_Columns, current);
				show_function_menu(current);
				Picture.menu();
				break;
			case 0:
				trans_to_new_play();
				Play();
				_Common::ClearConsoleToColors(0);
				show_function_menu(current);
				Picture.menu();
				break;
			}
			break;
		}
	}
}




int main() {
	_Common q;
	show_menu();
}
