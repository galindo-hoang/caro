#include "Picture.h"

char _Picture::menu() {
	int color = 1;
	while (!_kbhit()) {
		_Common::textcolor(color + BackRound_menu * 16);
		gotoxy((Columns - 100) / 2, 0);
		cout << "          _____                   _____                   _____                  _______         ";
		gotoxy((Columns - 100) / 2, 1);
		cout << "         /\\    \\                 /\\    \\                 /\\    \\                /::\\    \\";
		gotoxy((Columns - 100) / 2, 2);
		cout << "        /::\\    \\               /::\\    \\               /::\\    \\              /::::\\    \\";
		gotoxy((Columns - 100) / 2, 3);
		cout << "       /::::\\    \\             /::::\\    \\             /::::\\    \\            /::::::\\    \\";
		gotoxy((Columns - 100) / 2, 4);
		cout << "      /::::::\\    \\           /::::::\\    \\           /::::::\\    \\          /::::::::\\    \\";
		gotoxy((Columns - 100) / 2, 5);
		cout << "     /:::/\\:::\\    \\         /:::/\\:::\\    \\         /:::/\\:::\\    \\        /:::/~~\\:::\\    \\   ";
		gotoxy((Columns - 100) / 2, 6);
		cout << "    /:::/  \\:::\\    \\       /:::/__\\:::\\    \\       /:::/__\\:::\\    \\      /:::/    \\:::\\    \\";
		gotoxy((Columns - 100) / 2, 7);
		cout << "   /:::/    \\:::\\    \\     /::::\\   \\:::\\    \\     /::::\\   \\:::\\    \\    /:::/    / \\:::\\    \\  ";
		gotoxy((Columns - 100) / 2, 8);
		cout << "  /:::/    / \\:::\\    \\   /::::::\\   \\:::\\    \\   /::::::\\   \\:::\\    \\  /:::/____/   \\:::\\____\\ ";
		gotoxy((Columns - 100) / 2, 9);
		cout << " /:::/    /   \\:::\\    \\ /:::/\\:::\\   \\:::\\    \\ /:::/\\:::\\   \\:::\\____\\|:::|    |     |:::|    |";
		gotoxy((Columns - 100) / 2, 10);
		cout << "/:::/____/     \\:::\\____/:::/  \\:::\\   \\:::\\____/:::/  \\:::\\   \\:::|    |:::|____|     |:::|    |";
		gotoxy((Columns - 100) / 2, 11);
		cout << "\\:::\\    \\      \\::/    \\::/    \\:::\\  /:::/    \\::/   |::::\\  /:::|____|\\:::\\    \\   /:::/    / ";
		gotoxy((Columns - 100) / 2, 12);
		cout << " \\:::\\    \\      \\/____/ \\/____/ \\:::\\/:::/    / \\/____|:::::\\/:::/    /  \\:::\\    \\ /:::/    /  ";
		gotoxy((Columns - 100) / 2, 13);
		cout << "  \\:::\\    \\                      \\::::::/    /        |:::::::::/    /    \\:::\\    /:::/    /   ";
		gotoxy((Columns - 100) / 2, 14);
		cout << "   \\:::\\    \\                      \\::::/    /         |::|\\::::/    /      \\:::\\__/:::/    /    ";
		gotoxy((Columns - 100) / 2, 15);
		cout << "    \\:::\\    \\                     /:::/    /          |::| \\::/____/        \\::::::::/    /     ";
		gotoxy((Columns - 100) / 2, 16);
		cout << "     \\:::\\    \\                   /:::/    /           |::|  ~|               \\::::::/    /      ";
		gotoxy((Columns - 100) / 2, 17);
		cout << "      \\:::\\    \\                 /:::/    /            |::|   |                \\::::/    /       ";
		gotoxy((Columns - 100) / 2, 18);
		cout << "       \\:::\\____\\               /:::/    /             \\::|   |                 \\::/____/        ";
		gotoxy((Columns - 100) / 2, 19);
		cout << "        \\::/    /               \\::/    /               \\:|   |                  ~~              ";
		gotoxy((Columns - 100) / 2, 20);
		cout << "         \\/____/                 \\/____/                 \\|___|";
		
		Sleep(100);

		++color;
		if (color > 15) color = 1;
	}
	return _getch();
}

void _Picture::draw_x() {
	_Common::textcolor(2 + BackRound_play * 16);
	for (int i = 0; i < 8; ++i) {
		_Common::gotoxy(left_mid_x_pipeline + 4, top_y_pipeline + i + 1);
		cout << this->x[i];
	}
	_Common::textcolor(0 + BackRound_play * 16);
}

void _Picture::clear_x_o() {
	for (int i = 0; i < 8; ++i) {
		_Common::gotoxy(left_mid_x_pipeline + 2, top_y_pipeline + i + 1);
		cout << "                 ";
	}
}

void _Picture::draw_o() {
	_Common::textcolor(4 + BackRound_play * 16);
	for (int i = 0; i < 8; ++i) {
		_Common::gotoxy(left_mid_x_pipeline + 3, top_y_pipeline + i + 1);
		cout << this->o[i];
	}
	_Common::textcolor(0 + BackRound_play * 16);
}

void _Picture::show_win() {
	string win[6];
	win[0] = win[0] + (char)219 + (char)219 + (char)187 + "    " + (char)219 + (char)219 + (char)187 + (char)219 + (char)219 + (char)187 + (char)219 + (char)219 + (char)219 + (char)187 + "   " + (char)219 + (char)219 + (char)187;
	win[1] = win[1] + (char)219 + (char)219 + (char)186 + "    " + (char)219 + (char)219 + (char)186 + (char)219 + (char)219 + (char)186 + (char)219 + (char)219 + (char)219 + (char)219 + (char)187 + "  " + (char)219 + (char)219 + (char)186;
	win[2] = win[2] + (char)219 + (char)219 + (char)186 + " " + (char)219 + (char)187 + " " + (char)219 + (char)219 + (char)186 + (char)219 + (char)219 + (char)186 + (char)219 + (char)219 + (char)201 + (char)219 + (char)219 + (char)187 + " " + (char)219 + (char)219 + (char)186;
	win[3] = win[3] + (char)219 + (char)219 + (char)186 + (char)219 + (char)219 + (char)219 + (char)187 + (char)219 + (char)219 + (char)186 + (char)219 + (char)219 + (char)186 + (char)219 + (char)219 + (char)186 + (char)200 + (char)219 + (char)219 + (char)187 + (char)219 + (char)219 + (char)186;
	win[4] = win[4] + (char)200 + (char)219 + (char)219 + (char)219 + (char)201 + (char)219 + (char)219 + (char)219 + (char)201 + (char)188 + (char)219 + (char)219 + (char)186 + (char)219 + (char)219 + (char)186 + " " + (char)200 + (char)219 + (char)219 + (char)219 + (char)219 + (char)186;
	win[5] = win[5] + " " + (char)200 + (char)205 + (char)205 + (char)188 + (char)200 + (char)205 + (char)205 + (char)188 + " " + (char)200 + (char)205 + (char)188 + (char)200 + (char)205 + (char)188 + "  " + (char)200 + (char)205 + (char)205 + (char)205 + (char)188;


	for (int i = 0; i < 6; i++) {
		_Common::gotoxy(left_mid_x_pipeline - 1, down_y_pipeline + 2 + i);
		cout << win[i];
	}

}


void _Picture::show_draw() {
	string draw[6];
	draw[0] = draw[0] + (char)219 + (char)219 + (char)219 + (char)219 + (char)219 + (char)219 + (char)187 + " " + (char)219 + (char)219 + (char)219 + (char)219 + (char)219 + (char)219 + (char)187 + "  " + (char)219 + (char)219 + (char)219 + (char)219 + (char)219 + (char)187 + " " + (char)219 + (char)219 + (char)187 + "    " + (char)219 + (char)219 + (char)187;
	draw[1] = draw[1] + (char)219 + (char)219 + (char)201 + (char)205 + (char)205 + (char)219 + (char)219 + (char)187 + (char)219 + (char)219 + (char)201 + (char)205 + (char)205 + (char)219 + (char)219 + (char)187 + (char)219 + (char)219 + (char)201 + (char)205 + (char)205 + (char)219 + (char)219 + (char)187 + (char)219 + (char)219 + (char)186 + "    " + (char)219 + (char)219 + (char)186;
	draw[2] = draw[2] + (char)219 + (char)219 + (char)186 + "  " + (char)219 + (char)219 + (char)186 + (char)219 + (char)219 + (char)219 + (char)219 + (char)219 + (char)219 + (char)201 + (char)188 + (char)219 + (char)219 + (char)219 + (char)219 + (char)219 + (char)219 + (char)219 + (char)186 + (char)219 + (char)219 + (char)186 + " " + (char)219 + (char)187 + " " + (char)219 + (char)219 + (char)186;
	draw[3] = draw[3] + (char)219 + (char)219 + (char)186 + "  " + (char)219 + (char)219 + (char)186 + (char)219 + (char)219 + (char)201 + (char)205 + (char)205 + (char)219 + (char)219 + (char)187 + (char)219 + (char)219 + (char)201 + (char)205 + (char)205 + (char)219 + (char)219 + (char)186 + (char)219 + (char)219 + (char)186 + (char)219 + (char)219 + (char)219 + (char)187 + (char)219 + (char)219 + (char)186;
	draw[4] = draw[4] + (char)219 + (char)219 + (char)219 + (char)219 + (char)219 + (char)219 + (char)201 + (char)188 + (char)219 + (char)219 + (char)186 + "  " + (char)219 + (char)219 + (char)186 + (char)219 + (char)219 + (char)186 + "  " + (char)219 + (char)219 + (char)186 + (char)200 + (char)219 + (char)219 + (char)219 + (char)201 + (char)219 + (char)219 + (char)219 + (char)201 + (char)188;
	draw[5] = draw[5] + (char)200 + (char)205 + (char)205 + (char)205 + (char)205 + (char)205 + (char)188 + " " + (char)200 + (char)205 + (char)188 + "  " + (char)200 + (char)205 + (char)188 + (char)200 + (char)205 + (char)188 + "  " + (char)200 + (char)205 + (char)188 + " " + (char)200 + (char)205 + (char)205 + (char)188 + (char)200 + (char)205 + (char)205 + (char)188;

	for (int i = 0; i < 6; i++) {
		_Common::gotoxy(left_mid_x_pipeline - 6, down_y_pipeline + 2 + i);
		cout << draw[i];
	}
}
