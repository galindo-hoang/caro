#include "Game.h"
_Game::_Game(int pSize, int pLeft, int pTop) {
	_b = new _Board(pSize, pLeft, pTop);
	_loop = _turn = true;
	_command = -1; // Gán lượt và phím mặc định 
	_x = pLeft; _y = pTop;
	MangDiemTanCong = new long[7];
	long mdtc[] = { 0, 3, 24, 192, 1536, 12288, 98304 };
	for (int i = 0; i < 7; i++)
		MangDiemTanCong[i] = mdtc[i];
	MangDiemPhongNgu = new long[7];
	long mdpn[] = { 0, 1, 9, 81,729,6561,59049 };
	for (int i = 0; i < 7; i++)
		MangDiemPhongNgu[i] = mdpn[i];
}

_Game::~_Game() { 
	delete _b;
	delete MangDiemTanCong;
	delete MangDiemPhongNgu;
}

int _Game::getCommand() { return _command; }

bool _Game::isContinue() { return _loop; }

char _Game::waitKeyBoard() {
	if (stdin != NULL)
		fflush(stdin);
	_command = toupper(_getch());
	return _command;
}

char _Game::askContinue() {
	_Common::txtColor(15);
	_Common::gotoXY(BOARD_SIZE * 5, TOP + 24);
	cout << "Press Y to play new game!" << endl;
	_Common::gotoXY(BOARD_SIZE * 5, TOP + 25);
	cout << "Press diffrent key to exit" << endl;
	char a = waitKeyBoard();
	return a;
}

void _Game::startGame() {
	system("cls");
	PlaySound("bgSound", NULL, SND_ASYNC | SND_LOOP);
	// Khởi tạo dữ liệu gốc
	_b->resetData();  
	_Game::CountStep1 = 0;
	_Game::CountStep2 = 0;
	_x = _b->getXAt(0, 0);
	_y = _b->getYAt(0, 0);
	_turn = true;
	_b->drawBoard(); // Vẽ màn hình game 
	// in ra thong so thang thua cua 2 nguoi choi

	_Common::gotoXY(BOARD_SIZE * 5, TOP + 3);
	_Common::txtColor(15);
	cout << "Win:";

	_Common::gotoXY(BOARD_SIZE * 6, TOP + 3);
	_Common::txtColor(11);
	cout << _Game::CountWin1;

	_Common::gotoXY(BOARD_SIZE * 6 + 6, TOP + 3);
	_Common::txtColor(15);
	cout << "--";

	_Common::gotoXY(BOARD_SIZE * 7, TOP + 3);
	_Common::txtColor(12);
	cout << _Game::CountWin2;

	//in so nuoc di cua 2 nguoi choi

	_Common::gotoXY(BOARD_SIZE * 5, TOP + 5);
	_Common::txtColor(15);
	cout << "Step:";

	_Common::gotoXY(BOARD_SIZE * 6, TOP + 5);
	_Common::txtColor(11);
	cout << _Game::CountStep1;

	_Common::gotoXY(BOARD_SIZE * 6 + 6, TOP + 5);
	_Common::txtColor(15);
	cout << "--";

	_Common::gotoXY(BOARD_SIZE * 7, TOP + 5);
	_Common::txtColor(12);
	cout << _Game::CountStep2;
	//in lượt đánh
	_Common::gotoXY(BOARD_SIZE * 5, TOP + 12);
	_Common::txtColor(15);
	cout << "Turn: ";
	_Common::txtColor(11);
	_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 10);
	cout << char(219) << char(219) << "      " << char(219) << char(219);
	_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 11);
	cout << "  " << char(219) << char(219) << "  " << char(219) << char(219) << "  ";
	_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 12);
	cout << "    " << char(219) << char(219) << "    ";
	_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 13);
	cout << "  " << char(219) << char(219) << "  " << char(219) << char(219) << "  ";
	_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 14);
	cout << char(219) << char(219) << "      " << char(219) << char(219);

	//sau khi bắt đầu game mới sẽ reset lại số nước đi
	
	_Common::gotoXY(_x, _y);
}


bool _Game::processCheckBoard() {
	switch (_b->checkBoard(_x, _y, _turn)) {
	case -1:
		_Common::txtColor(11);
		printf("X");
		//in ra số bước đi của người 1
		_Game::CountStep1++;
		_Common::gotoXY(BOARD_SIZE * 6, TOP + 5);
		_Common::txtColor(11);
		cout << _Game::CountStep1;
		//in ra lượt đi của người 2
		_Common::txtColor(12);
		_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 10);
		cout << " " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219)<< " ";
		_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 11);
		cout << char(219) << char(219) << "      " << char(219) << char(219);
		_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 12);
		cout << char(219) << char(219) << "      " << char(219) << char(219);
		_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 13);
		cout << char(219) << char(219) << "      " << char(219) << char(219);
		_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 14);
		cout << " " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << " ";
		break;
	case 1:
		_Common::txtColor(12);
		printf("O");
		//in ra số bước đi của người 2
		_Game::CountStep2++;
		_Common::gotoXY(BOARD_SIZE * 7, TOP + 5);
		_Common::txtColor(12);
		cout << _Game::CountStep2;
		//in ra lượt đi của người 1
		_Common::txtColor(11);
		_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 10);
		cout << char(219) << char(219) << "      " << char(219) << char(219);
		_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 11);
		cout <<"  "<<char(219) << char(219) << "  " << char(219) << char(219)<<"  ";
		_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 12);
		cout << "    " << char(219) << char(219) << "    ";
		_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 13);
		cout << "  " << char(219) << char(219) << "  " << char(219) << char(219) << "  ";
		_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 14);
		cout << char(219) << char(219) << "      " << char(219) << char(219);
		break;
	case 0:
		return false; // Khi đánh vào ô đã đánh rồi 
	}
	return true;
}

int _Game::processFinish() { 
	int pWhoWin = _b->testBoard(_x, _y);
	if (_Game::CountStep1 + _Game::CountStep2 == BOARD_SIZE * BOARD_SIZE && pWhoWin == 2)
		pWhoWin = 0; // nếu số nước đi của 2 bên cộng lại  = 13*13 và chưa thắng thì hòa
	switch (pWhoWin) {
	case WIN1:
		PlaySound("winSound", NULL, SND_ASYNC);
		//in ra x win
		for (int i = 14; i > 9; i--)
		{
			_Common::txtColor(i);
			_Common::gotoXY(BOARD_SIZE * 5, TOP + 17);
			cout << char(219) << char(219) << char(187) << "  " << char(219) << char(219) << char(187) <<
				"    " << char(219) << char(219) << char(187) << "    " << char(219) << char(219) << char(187) <<
				char(219) << char(219) << char(187) << char(219) << char(219) << char(219) << char(187) << "   " <<
				char(219) << char(219) << char(187);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 18);
			cout << char(200) << char(219) << char(219) << char(187) << char(219) << char(219) << char(201) << char(188) << "    " <<
				char(219) << char(219) << char(186) << "    " << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) <<
				char(219) << char(219) << char(219) << char(219) << char(187) << "  " << char(219) << char(219) << char(186);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 19);
			cout<<" " << char(200) << char(219) << char(219)<<char(219) << char(201) << char(188) << "     " << char(219) << char(219) << char(186) <<
				" " << char(219) << char(187) << " " << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) <<
				char(219) << char(219) << char(201) << char(219) << char(219) << char(187) << " "<<char(219) << char(219) << char(186);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 20);
			cout << " " << char(219) << char(219) << char(201) << char(219) << char(219) << char(187) << "     " << char(219) << char(219) << char(186) <<
				char(219) << char(219) << char(219) << char(187) << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) <<
				char(219) << char(219) << char(186) << char(200) << char(219) << char(219) << char(187) << char(219) << char(219) << char(186);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 21);
			cout << char(219) << char(219) << char(201) << char(188) << " " << char(219) << char(219) << char(187) << "    " << char(200) << char(219) << char(219) << char(219) <<
				char(201) << char(219) << char(219) << char(219) << char(201)<<char(188) << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) << " " <<
				char(200) << char(219) << char(219) << char(219) << char(219) << char(186);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 22);
			cout << char(200) << char(205) << char(188) << "  " << char(200) << char(205) << char(188) << "     " << char(200) << char(205) << char(205) << char(188) <<
				char(200) << char(205) << char(205) << char(188) << " " << char(200) << char(205) << char(188) << char(200) << char(205) << char(188) << "  " <<
				char(200) << char(205) << char(205) << char(205) << char(188);
			Sleep(800);
		}
		_Game::CountWin1++;
		break;
	case WIN2:
		PlaySound("winSound", NULL, SND_ASYNC);
		//in ra o win
		for (int i = 14; i > 9; i--)
		{
			_Common::txtColor(i);
			_Common::gotoXY(BOARD_SIZE * 5, TOP + 17);
			cout <<" " << char(219) << char(219) << char(219) << char(219)<<char(219)<<char(219) << char(187) <<
				"     " << char(219) << char(219) << char(187) << "    " << char(219) << char(219) << char(187) <<
				char(219) << char(219) << char(187) << char(219) << char(219) << char(219) << char(187) << "   " <<
				char(219) << char(219) << char(187);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 18);
			cout << char(219) << char(219) << char(201) << char(205) << char(205) << char(205) << char(219)<<char(219) << char(187) << "    " <<
				char(219) << char(219) << char(186) << "    " << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) <<
				char(219) << char(219) << char(219) << char(219) << char(187) << "  " << char(219) << char(219) << char(186);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 19);
			cout << char(219) << char(219) << char(186)<<"   " << char(219) << char(219) << char(186) << "    " << char(219) << char(219) << char(186) <<
				" " << char(219) << char(187) << " " << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) <<
				char(219) << char(219) << char(201) << char(219) << char(219) << char(187) << " " << char(219) << char(219) << char(186);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 20);
			cout << char(219) << char(219) << char(186) << "   " << char(219) << char(219) << char(186) << "    " << char(219) << char(219) << char(186) <<
				char(219) << char(219) << char(219) << char(187) << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) <<
				char(219) << char(219) << char(186) << char(200) << char(219) << char(219) << char(187) << char(219) << char(219) << char(186);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 21);
			cout << char(200) << char(219)<< char(219) << char(219) << char(219) << char(219) << char(219)<<char(201)<<char(188) << "    " << char(200) << char(219) << char(219) << char(219) <<
				char(201) << char(219) << char(219) << char(219) << char(201) << char(188) << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) << " " <<
				char(200) << char(219) << char(219) << char(219) << char(219) << char(186);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 22);
			cout <<" "<<char(200)<<char(205)<< char(205) << char(205) << char(205) << char(205) <<char(188)<< "      " << char(200) << char(205) << char(205) << char(188) <<
				char(200) << char(205) << char(205) << char(188) << " " << char(200) << char(205) << char(188) << char(200) << char(205) << char(188) << "  " <<
				char(200) << char(205) << char(205) << char(205) << char(188);
			Sleep(800);
		}
		_Game::CountWin2++;
		break;
	case DRAW:
		PlaySound("winSound", NULL, SND_ASYNC);
		for (int i = 14; i > 9; i--)
		{
			_Common::txtColor(i);
			_Common::gotoXY(BOARD_SIZE * 5, TOP + 17);
			cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << " " << char(219) << char(219) <<
				char(219) << char(219) << char(219) << char(219) << char(187) << "  " << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) <<
				" " << char(219) << char(219) << char(187) << "    " << char(219) << char(219) << char(187);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 18);
			cout << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(187) << char(219) << char(219) << char(201) << char(205) << char(205) <<
				char(219) << char(219) << char(187) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(187) << char(219) << char(219) <<
				char(186) << "    " << char(219) << char(219) << char(186);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 19);
			cout << char(219) << char(219) << char(186) << "  " << char(219) << char(219) << char(186) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) <<
				char(201) << char(188) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(186) << char(219) << char(219) <<
				char(186) << " " << char(219) << char(187) << " " << char(219) << char(219) << char(186);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 20);
			cout << char(219) << char(219) << char(186) << "  " << char(219) << char(219) << char(186) << char(219) << char(219) << char(201) << char(205) << char(205) <<
				char(219) << char(219) << char(187) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) <<
				char(219) << char(219) << char(219) << char(187) << char(219) << char(219) << char(186);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 21);
			cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(201) << char(188) << char(219) << char(219) << char(186) << "  " <<
				char(219) << char(219) << char(186) << char(219) << char(219) << char(186) << "  " << char(219) << char(219) << char(186) << char(200) << char(219) << char(219) << char(219) <<
				char(201) << char(219) << char(219) << char(219) << char(201) << char(188);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 22);
			cout << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << " " << char(200) << char(205) << char(188) << "  " << char(200) << char(205) << char(188) <<
				char(200) << char(205) << char(188) << "  " << char(200) << char(205) << char(188)<<" " << char(200) << char(205) << char(205) << char(188) <<
				char(200) << char(205) << char(205) << char(188);

			Sleep(800);
		}
		break;
	case CONTINUE:
		_turn = !_turn;// Đổi lượt nếu không có gì xảy ra
		_Common::gotoXY(_x, _y);// Trả về vị trí hiện hành của con trỏ màn hình bàn cờ
	}
	return pWhoWin;
}
void _Game::moveRight() {
	if (_x < _b->getXAt(_b->getSize() - 1, _b->getSize() - 1)) {
		_x += 4;
		_Common::gotoXY(_x, _y);
	}
}
void _Game::moveLeft() {
	if (_x > _b->getXAt(0, 0)) {
		_x -= 4;
		_Common::gotoXY(_x, _y);
	}
}
void _Game::moveDown() {
	if (_y < _b->getYAt(_b->getSize() - 1, _b->getSize() - 1)) {
		_y += 2;
		_Common::gotoXY(_x, _y);
	}
}
void _Game::moveUp() {
	if (_y > _b->getYAt(0, 0)) {
		_y -= 2;
		_Common::gotoXY(_x, _y);
	}
}

void _Game::loadGame(string a) {
	ifstream fin;
	char ch;
	fin.open(a, ios::in);
	startGame();
	fin >> CountWin1;
	fin >> CountWin2;
	fin >> CountStep1;
	fin >> CountStep2;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			fin >> ch;
			if (int(ch) - 48 == 2) _b->setPointcheck(i, j, -1);
			else
			{
				_b->setPointcheck(i, j, int(ch) - 48);
			}
			_Common::gotoXY(_b->getXAt(i, j), _b->getYAt(i, j));
			switch (int(ch) - 48) {
			case 2:
				_Common::txtColor(11);
				printf("X");
				break;
			case 1:
				_Common::txtColor(12);
				printf("O");
				break;
			case 0:
				break;//khi đọc số 0 
			}
		}
	}
	fin.close();
	//in lại số nước đi của 2 người chơi
	_Common::gotoXY(BOARD_SIZE * 6, TOP + 5);
	_Common::txtColor(11);
	cout << _Game::CountStep1;

	_Common::gotoXY(BOARD_SIZE * 7, TOP + 5);
	_Common::txtColor(12);
	cout << _Game::CountStep2;
	//xét lượt đi
	if (CountStep1 == CountStep2) _turn = true;
	else
	{
		_turn = false;
		//in ra lượt đi của người thứ 2
		_Common::txtColor(12);
		_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 10);
		cout << " " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << " ";
		_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 11);
		cout << char(219) << char(219) << "      " << char(219) << char(219);
		_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 12);
		cout << char(219) << char(219) << "      " << char(219) << char(219);
		_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 13);
		cout << char(219) << char(219) << "      " << char(219) << char(219);
		_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 14);
		cout << " " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << " ";
	}
	_Common::gotoXY(_b->getXAt(0, 0), _b->getYAt(0, 0));//di chuyển vào ô đầu
}

void _Game::exitGame() {
	////////////Có thể lưu game trước khi exit////////////////////////////////////////
	if (_b->testBoard(_x,_y) == CONTINUE)
	{
		_Common::txtColor(15);
		_Common::gotoXY(BOARD_SIZE * 5, TOP + 20);
		cout << "Do you want to save game?";
		_Common::gotoXY(BOARD_SIZE * 5, TOP + 21);
		cout << "Yes: Press L\tNo: Press diffrent key";
		char a = waitKeyBoard();
		if (a == 'L') {
			_Common::gotoXY(BOARD_SIZE * 5, TOP + 22);
			cout << "Nhap ten tap tin de luu: " << endl;
			_Common::gotoXY(BOARD_SIZE * 5, TOP + 23);
			string a;
			getline(cin, a);
			ofstream f;
			f.open(a, ios::out);
			f << CountWin1 << endl;
			f << CountWin2 << endl;
			f << CountStep1 << endl;
			f << CountStep2 << endl;
			for (int i = 0; i < BOARD_SIZE; i++) {
				for (int j = 0; j < BOARD_SIZE; j++) {
					if (_b->getPoint(i, j).getCheck() == -1)
						f << 2;
					else {
						f << _b->getPoint(i, j).getCheck();
					}
				}
			}
			f.close();
		}
	}
	system("cls");
	_loop = false;
}
//danh voi may trung binh

bool _Game::processCheckBoardWithMachine() {
	switch (_b->checkBoardWithMachine(_x, _y)) {
	case -1:
		_Common::txtColor(11);
		printf("X");
		//in ra số bước đi của người 1
		_Game::CountStep1++;
		_Common::gotoXY(BOARD_SIZE * 6, TOP + 5);
		_Common::txtColor(11);
		cout << _Game::CountStep1;
		//in ra lượt đi của máy
		_Common::txtColor(12);
		_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 10);
		cout << " " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << " ";
		_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 11);
		cout << char(219) << char(219) << "      " << char(219) << char(219);
		_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 12);
		cout << char(219) << char(219) << "      " << char(219) << char(219);
		_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 13);
		cout << char(219) << char(219) << "      " << char(219) << char(219);
		_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 14);
		cout << " " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << " ";
		_Common::gotoXY(_x, _y);
		break;
	case 0:
		return false; // Khi đánh vào ô đã đánh rồi 
	}
	return true;
}

int _Game::processFinishWithMachine() {
	// Nhảy tới vị trí thích hợp để in chuỗi thắng/thua/hòa   
	int pWhoWin = _b->testBoard(_x,_y);
	if (_Game::CountStep1 + _Game::CountStep2 == BOARD_SIZE * BOARD_SIZE && pWhoWin == 2)
		pWhoWin = 0; // nếu số nước đi của 2 bên cộng lại  = 13*13 và chưa thắng thì hòa
	switch (pWhoWin) {
	case WIN1:
		PlaySound("winSound", NULL, SND_ASYNC);
		//in ra x win
		for (int i = 14; i > 9; i--)
		{
			_Common::txtColor(i);
			_Common::gotoXY(BOARD_SIZE * 5, TOP + 17);
			cout << char(219) << char(219) << char(187) << "  " << char(219) << char(219) << char(187) <<
				"    " << char(219) << char(219) << char(187) << "    " << char(219) << char(219) << char(187) <<
				char(219) << char(219) << char(187) << char(219) << char(219) << char(219) << char(187) << "   " <<
				char(219) << char(219) << char(187);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 18);
			cout << char(200) << char(219) << char(219) << char(187) << char(219) << char(219) << char(201) << char(188) << "    " <<
				char(219) << char(219) << char(186) << "    " << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) <<
				char(219) << char(219) << char(219) << char(219) << char(187) << "  " << char(219) << char(219) << char(186);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 19);
			cout << " " << char(200) << char(219) << char(219) << char(219) << char(201) << char(188) << "     " << char(219) << char(219) << char(186) <<
				" " << char(219) << char(187) << " " << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) <<
				char(219) << char(219) << char(201) << char(219) << char(219) << char(187) << " " << char(219) << char(219) << char(186);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 20);
			cout << " " << char(219) << char(219) << char(201) << char(219) << char(219) << char(187) << "     " << char(219) << char(219) << char(186) <<
				char(219) << char(219) << char(219) << char(187) << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) <<
				char(219) << char(219) << char(186) << char(200) << char(219) << char(219) << char(187) << char(219) << char(219) << char(186);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 21);
			cout << char(219) << char(219) << char(201) << char(188) << " " << char(219) << char(219) << char(187) << "    " << char(200) << char(219) << char(219) << char(219) <<
				char(201) << char(219) << char(219) << char(219) << char(201) << char(188) << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) << " " <<
				char(200) << char(219) << char(219) << char(219) << char(219) << char(186);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 22);
			cout << char(200) << char(205) << char(188) << "  " << char(200) << char(205) << char(188) << "     " << char(200) << char(205) << char(205) << char(188) <<
				char(200) << char(205) << char(205) << char(188) << " " << char(200) << char(205) << char(188) << char(200) << char(205) << char(188) << "  " <<
				char(200) << char(205) << char(205) << char(205) << char(188);
			Sleep(800);
		}
		_Game::CountWin1++;
		break;
	case WIN2:
		PlaySound("winSound", NULL, SND_ASYNC);
		//in ra o win
		for (int i = 14; i > 9; i--)
		{
			_Common::txtColor(i);
			_Common::txtColor(i);
			_Common::gotoXY(BOARD_SIZE * 5, TOP + 17);
			cout << " " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) <<
				"     " << char(219) << char(219) << char(187) << "    " << char(219) << char(219) << char(187) <<
				char(219) << char(219) << char(187) << char(219) << char(219) << char(219) << char(187) << "   " <<
				char(219) << char(219) << char(187);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 18);
			cout << char(219) << char(219) << char(201) << char(205) << char(205) << char(205) << char(219) << char(219) << char(187) << "    " <<
				char(219) << char(219) << char(186) << "    " << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) <<
				char(219) << char(219) << char(219) << char(219) << char(187) << "  " << char(219) << char(219) << char(186);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 19);
			cout << char(219) << char(219) << char(186) << "   " << char(219) << char(219) << char(186) << "    " << char(219) << char(219) << char(186) <<
				" " << char(219) << char(187) << " " << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) <<
				char(219) << char(219) << char(201) << char(219) << char(219) << char(187) << " " << char(219) << char(219) << char(186);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 20);
			cout << char(219) << char(219) << char(186) << "   " << char(219) << char(219) << char(186) << "    " << char(219) << char(219) << char(186) <<
				char(219) << char(219) << char(219) << char(187) << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) <<
				char(219) << char(219) << char(186) << char(200) << char(219) << char(219) << char(187) << char(219) << char(219) << char(186);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 21);
			cout << char(200) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(201) << char(188) << "    " << char(200) << char(219) << char(219) << char(219) <<
				char(201) << char(219) << char(219) << char(219) << char(201) << char(188) << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) << " " <<
				char(200) << char(219) << char(219) << char(219) << char(219) << char(186);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 22);
			cout << " " << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << "      " << char(200) << char(205) << char(205) << char(188) <<
				char(200) << char(205) << char(205) << char(188) << " " << char(200) << char(205) << char(188) << char(200) << char(205) << char(188) << "  " <<
				char(200) << char(205) << char(205) << char(205) << char(188);
			Sleep(800);
		}
		_Game::CountWin2++;
		break;
	case DRAW:
		PlaySound("winSound", NULL, SND_ASYNC);
		//in ra hòa
		for (int i = 14; i > 9; i--)
		{
			_Common::txtColor(i);
			_Common::gotoXY(BOARD_SIZE * 5, TOP + 17);
			cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << " " << char(219) << char(219) <<
				char(219) << char(219) << char(219) << char(219) << char(187) << "  " << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) <<
				" " << char(219) << char(219) << char(187) << "    " << char(219) << char(219) << char(187);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 18);
			cout << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(187) << char(219) << char(219) << char(201) << char(205) << char(205) <<
				char(219) << char(219) << char(187) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(187) << char(219) << char(219) <<
				char(186) << "    " << char(219) << char(219) << char(186);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 19);
			cout << char(219) << char(219) << char(186) << "  " << char(219) << char(219) << char(186) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) <<
				char(201) << char(188) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(186) << char(219) << char(219) <<
				char(186) << " " << char(219) << char(187) << " " << char(219) << char(219) << char(186);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 20);
			cout << char(219) << char(219) << char(186) << "  " << char(219) << char(219) << char(186) << char(219) << char(219) << char(201) << char(205) << char(205) <<
				char(219) << char(219) << char(187) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) <<
				char(219) << char(219) << char(219) << char(187) << char(219) << char(219) << char(186);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 21);
			cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(201) << char(188) << char(219) << char(219) << char(186) << "  " <<
				char(219) << char(219) << char(186) << char(219) << char(219) << char(186) << "  " << char(219) << char(219) << char(186) << char(200) << char(219) << char(219) << char(219) <<
				char(201) << char(219) << char(219) << char(219) << char(201) << char(188);

			_Common::gotoXY(BOARD_SIZE * 5, TOP + 22);
			cout << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << " " << char(200) << char(205) << char(188) << "  " << char(200) << char(205) << char(188) <<
				char(200) << char(205) << char(188) << "  " << char(200) << char(205) << char(188) << " " << char(200) << char(205) << char(205) << char(188) <<
				char(200) << char(205) << char(205) << char(188);

			Sleep(800);
		}
		break;
	case CONTINUE:
		//xu ly danh voi may
		_Point* oco = TimKiemNuocDi();
		_x = oco->getX();
		_y = oco->getY();
		_b->setPointcheck((_y - 2) / 2, (_x - 3) / 4, 1);
		_Common::gotoXY(_x,_y);
		_Common::txtColor(12);
		printf("O");
		//in ra số bước đi của máy
		_Game::CountStep2++;
		_Common::gotoXY(BOARD_SIZE * 7, TOP + 5);
		_Common::txtColor(12);
		cout << _Game::CountStep2;
		//in ra lượt đi của người 1
		_Common::txtColor(11);
		_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 10);
		cout << char(219) << char(219) << "      " << char(219) << char(219);
		_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 11);
		cout << "  " << char(219) << char(219) << "  " << char(219) << char(219) << "  ";
		_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 12);
		cout << "    " << char(219) << char(219) << "    ";
		_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 13);
		cout << "  " << char(219) << char(219) << "  " << char(219) << char(219) << "  ";
		_Common::gotoXY(BOARD_SIZE * 6 + 2, TOP + 14);
		cout << char(219) << char(219) << "      " << char(219) << char(219);
		//xu ly in ra man hinh neu may thang hoac hoa
		int kq = _b->testBoard(_x,_y);
		if (kq != CONTINUE)
		{
			switch (kq) {
			case WIN2:
				PlaySound("winSound", NULL, SND_ASYNC);
				//in ra o win
				for (int i = 14; i > 9; i--)
				{
					_Common::txtColor(i);
					_Common::gotoXY(BOARD_SIZE * 5, TOP + 17);
					cout << " " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) <<
						"     " << char(219) << char(219) << char(187) << "    " << char(219) << char(219) << char(187) <<
						char(219) << char(219) << char(187) << char(219) << char(219) << char(219) << char(187) << "   " <<
						char(219) << char(219) << char(187);

					_Common::gotoXY(BOARD_SIZE * 5, TOP + 18);
					cout << char(219) << char(219) << char(201) << char(205) << char(205) << char(205) << char(219) << char(219) << char(187) << "    " <<
						char(219) << char(219) << char(186) << "    " << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) <<
						char(219) << char(219) << char(219) << char(219) << char(187) << "  " << char(219) << char(219) << char(186);

					_Common::gotoXY(BOARD_SIZE * 5, TOP + 19);
					cout << char(219) << char(219) << char(186) << "   " << char(219) << char(219) << char(186) << "    " << char(219) << char(219) << char(186) <<
						" " << char(219) << char(187) << " " << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) <<
						char(219) << char(219) << char(201) << char(219) << char(219) << char(187) << " " << char(219) << char(219) << char(186);

					_Common::gotoXY(BOARD_SIZE * 5, TOP + 20);
					cout << char(219) << char(219) << char(186) << "   " << char(219) << char(219) << char(186) << "    " << char(219) << char(219) << char(186) <<
						char(219) << char(219) << char(219) << char(187) << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) <<
						char(219) << char(219) << char(186) << char(200) << char(219) << char(219) << char(187) << char(219) << char(219) << char(186);

					_Common::gotoXY(BOARD_SIZE * 5, TOP + 21);
					cout << char(200) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(201) << char(188) << "    " << char(200) << char(219) << char(219) << char(219) <<
						char(201) << char(219) << char(219) << char(219) << char(201) << char(188) << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) << " " <<
						char(200) << char(219) << char(219) << char(219) << char(219) << char(186);

					_Common::gotoXY(BOARD_SIZE * 5, TOP + 22);
					cout << " " << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << "      " << char(200) << char(205) << char(205) << char(188) <<
						char(200) << char(205) << char(205) << char(188) << " " << char(200) << char(205) << char(188) << char(200) << char(205) << char(188) << "  " <<
						char(200) << char(205) << char(205) << char(205) << char(188);
					Sleep(800);
				}
				_Game::CountWin2++;
				break;
			case DRAW:
				//in ra hòa
				PlaySound("winSound", NULL, SND_ASYNC);
				for (int i = 14; i > 9; i--)
				{
					_Common::txtColor(i);
					_Common::gotoXY(BOARD_SIZE * 5, TOP + 17);
					cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) << " " << char(219) << char(219) <<
						char(219) << char(219) << char(219) << char(219) << char(187) << "  " << char(219) << char(219) << char(219) << char(219) << char(219) << char(187) <<
						" " << char(219) << char(219) << char(187) << "    " << char(219) << char(219) << char(187);

					_Common::gotoXY(BOARD_SIZE * 5, TOP + 18);
					cout << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(187) << char(219) << char(219) << char(201) << char(205) << char(205) <<
						char(219) << char(219) << char(187) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(187) << char(219) << char(219) <<
						char(186) << "    " << char(219) << char(219) << char(186);

					_Common::gotoXY(BOARD_SIZE * 5, TOP + 19);
					cout << char(219) << char(219) << char(186) << "  " << char(219) << char(219) << char(186) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) <<
						char(201) << char(188) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(186) << char(219) << char(219) <<
						char(186) << " " << char(219) << char(187) << " " << char(219) << char(219) << char(186);

					_Common::gotoXY(BOARD_SIZE * 5, TOP + 20);
					cout << char(219) << char(219) << char(186) << "  " << char(219) << char(219) << char(186) << char(219) << char(219) << char(201) << char(205) << char(205) <<
						char(219) << char(219) << char(187) << char(219) << char(219) << char(201) << char(205) << char(205) << char(219) << char(219) << char(186) << char(219) << char(219) << char(186) <<
						char(219) << char(219) << char(219) << char(187) << char(219) << char(219) << char(186);

					_Common::gotoXY(BOARD_SIZE * 5, TOP + 21);
					cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(201) << char(188) << char(219) << char(219) << char(186) << "  " <<
						char(219) << char(219) << char(186) << char(219) << char(219) << char(186) << "  " << char(219) << char(219) << char(186) << char(200) << char(219) << char(219) << char(219) <<
						char(201) << char(219) << char(219) << char(219) << char(201) << char(188);

					_Common::gotoXY(BOARD_SIZE * 5, TOP + 22);
					cout << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << " " << char(200) << char(205) << char(188) << "  " << char(200) << char(205) << char(188) <<
						char(200) << char(205) << char(188) << "  " << char(200) << char(205) << char(188) << " " << char(200) << char(205) << char(205) << char(188) <<
						char(200) << char(205) << char(205) << char(188);
					Sleep(800);
				}
				break;
			}
			return kq;
		}
		else
		{
			_turn = !_turn;// Đổi lượt sau khi đánh xong
		}
		_Common::gotoXY(_x, _y);// Trả về vị trí vừa đánh của máy
	}
	return pWhoWin;
}

_Point* _Game::TimKiemNuocDi()
{
	_Point* oCoResult = new _Point();
	long DiemMax = 0;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (_b->getPoint(i, j).getCheck() == 0)
			{
				long DiemTC = DiemTC_DuyetDoc(i, j) + DiemTC_DuyetNgang(i, j) + DiemTC_DuyetCheoPhai(i, j) + DiemTC_DuyetCheoTrai(i, j);
				long DiemPN = DiemPN_DuyetDoc(i, j) + DiemPN_DuyetNgang(i, j) + DiemPN_DuyetCheoPhai(i, j) + DiemPN_DuyetCheoTrai(i, j);
				long DiemTam = DiemTC > DiemPN ? DiemTC : DiemPN;
				if (DiemMax < DiemTam)
				{
					DiemMax = DiemTam;
					oCoResult->setX(_b->getPoint(i, j).getX());
					oCoResult->setY(_b->getPoint(i, j).getY());
				}
			}
		}
	}
	return oCoResult;
}

//tấn công
long _Game::DiemTC_DuyetDoc(int dong, int cot)
{
	int diemtru = 0;
	if (dong == BOARD_SIZE || dong * cot == 0 || cot == BOARD_SIZE) diemtru = 9;
	int SoQuanTa = 0;
	int SoQuanDich = 0;
	//duyệt trên xuống
	for (int Dem = 1; Dem < 6 && dong + Dem < BOARD_SIZE; Dem++)
	{
		int check = _b->getPoint(dong + Dem, cot).getCheck();
		if (check == 1) SoQuanTa++;
		else if (check == -1)
		{
			SoQuanDich++;
			break;
		}
		else break;//gặp ô trống
	}
	//duyệt dưới lên
	for (int Dem = 1; Dem < 6 && dong - Dem >=0 ; Dem++)
	{
		int check = _b->getPoint(dong - Dem, cot).getCheck();
		if (check == 1)	SoQuanTa++;
		else if (check == -1)
		{
			SoQuanDich++;
			break;
		}
		else break;//gặp ô trống
	}
	//Bị chặn 2 đầu
	if (SoQuanDich == 2) return 0;
	return MangDiemTanCong[SoQuanTa] - MangDiemPhongNgu[SoQuanDich + 1] - diemtru;
}

long _Game::DiemTC_DuyetNgang(int dong, int cot)
{
	int diemtru = 0;
	if (dong == BOARD_SIZE || dong * cot == 0 || cot == BOARD_SIZE) diemtru = 9;
	int SoQuanTa = 0;
	int SoQuanDich = 0;
	//duyệt bên phải
	for (int Dem = 1; Dem < 6 && cot + Dem < BOARD_SIZE; Dem++)
	{
		int check = _b->getPoint(dong, cot + Dem).getCheck();
		if (check == 1) SoQuanTa++;
		else if (check == -1)
		{
			SoQuanDich++;
			break;
		}
		else break; // gặp ô trống
	}
	//duyệt bên trái
	for (int Dem = 1; Dem < 6 && cot - Dem >= 0; Dem++)
	{
		int check = _b->getPoint(dong, cot - Dem).getCheck();
		if (check == 1) SoQuanTa++;
		else if (check == -1)
		{
			SoQuanDich++;
			break;
		}
		else break;//gặp ô trống
	}
	//Bị chặn 2 đầu
	if (SoQuanDich == 2) return 0;

	return MangDiemTanCong[SoQuanTa] - MangDiemPhongNgu[SoQuanDich + 1] - diemtru;
}

long _Game::DiemTC_DuyetCheoPhai(int dong, int cot)
{
	int diemtru = 0;
	if (dong == BOARD_SIZE || dong * cot == 0 || cot == BOARD_SIZE) diemtru = 9;
	int SoQuanTa = 0;
	int SoQuanDich = 0;
	//duyệt chéo xuống dưới
	for (int Dem = 1; Dem < 6 && dong + Dem < BOARD_SIZE && cot + Dem < BOARD_SIZE; Dem++)
	{
		int check = _b->getPoint(dong + Dem, cot + Dem).getCheck();
		if (check == 1) SoQuanTa++;
		else if (check == -1)
		{
			SoQuanDich++;
			break;
		}
		else break;//gặp ô trống
	}
	//duyệt chéo lên trên
	for (int Dem = 1; Dem < 6 && dong - Dem >= 0 && cot - Dem >= 0; Dem++)
	{
		int check = _b->getPoint(dong - Dem, cot - Dem).getCheck();
		if (check == 1) SoQuanTa++;
		else if (check == -1)
		{
			SoQuanDich++;
			break;
		}
		else break;//gặp ô trống
	}
	//Bị chặn 2 đầu
	if (SoQuanDich == 2) return 0;
	return MangDiemTanCong[SoQuanTa] - MangDiemPhongNgu[SoQuanDich + 1] - diemtru;
}

long _Game::DiemTC_DuyetCheoTrai(int dong, int cot)
{
	int diemtru = 0;
	if (dong == BOARD_SIZE || dong * cot == 0 || cot == BOARD_SIZE) diemtru = 9;
	int SoQuanTa = 0;
	int SoQuanDich = 0;
	//duyệt chéo xuống dưới
	for (int Dem = 1; Dem < 6 && dong + Dem < BOARD_SIZE && cot - Dem >= 0; Dem++)
	{
		int check = _b->getPoint(dong + Dem, cot - Dem).getCheck();
		if (check == 1) SoQuanTa++;
		else if (check == -1)
		{
			SoQuanDich++;
			break;
		}
		else break;//gặp ô trống
	}
	//duyệt chéo lên trên
	for (int Dem = 1; Dem < 6 && dong - Dem >= 0 && cot + Dem < BOARD_SIZE; Dem++)
	{
		int check = _b->getPoint(dong - Dem, cot + Dem).getCheck();
		if (check == 1) SoQuanTa++;
		else if (check == -1)
		{
			SoQuanDich++;
			break;
		}
		else break;//gặp ô trống
	}
	//Bị chặn 2 đầu
	if (SoQuanDich == 2) return 0;
	return MangDiemTanCong[SoQuanTa] - MangDiemPhongNgu[SoQuanDich + 1] - diemtru;
}

//phòng ngự

long _Game::DiemPN_DuyetDoc(int dong, int cot)
{
	int SoQuanTa = 0;
	int SoQuanDich = 0;
	//duyệt trên xuống
	for (int Dem = 1; Dem < 6 && dong + Dem < BOARD_SIZE; Dem++)
	{
		int check = _b->getPoint(dong + Dem, cot).getCheck();
		if (check == 1)
		{
			SoQuanTa++;
			break;
		}
		else if (check == -1) SoQuanDich++;
		else break;//gặp ô trống
	}
	//duyệt dưới lên
	for (int Dem = 1; Dem < 6 && dong - Dem >= 0; Dem++)
	{
		int check = _b->getPoint(dong - Dem, cot).getCheck();
		if (check == 1)
		{
			SoQuanTa++;
			break;
		}
		else if (check == -1) SoQuanDich++;
		else break;
	}
	//Đã chặn 2 đầu
	if (SoQuanTa == 2) return 0;
	return MangDiemPhongNgu[SoQuanDich];
}

long _Game::DiemPN_DuyetNgang(int dong, int cot)
{
	int SoQuanTa = 0;
	int SoQuanDich = 0;
	//duyệt bên phải
	for (int Dem = 1; Dem < 6 && cot + Dem < BOARD_SIZE; Dem++)
	{
		int check = _b->getPoint(dong, cot + Dem).getCheck();
		if (check == 1)
		{
			SoQuanTa++;
			break;
		}
		else if (check == -1) SoQuanDich++;
		else break;//gặp ô trống
	}
	//duyệt bên trái
	for (int Dem = 1; Dem < 6 && cot - Dem >= 0; Dem++)
	{
		int check = _b->getPoint(dong, cot - Dem).getCheck();
		if (check == 1)
		{
			SoQuanTa++;
			break;
		}
		else if (check == -1) SoQuanDich++;
		else break;//gặp ô trống
	}
	//Đã chặn 2 đầu
	if (SoQuanTa == 2) return 0;

	return MangDiemPhongNgu[SoQuanDich];
}

long _Game::DiemPN_DuyetCheoPhai(int dong, int cot)
{
	int SoQuanTa = 0;
	int SoQuanDich = 0;
	//duyệt chéo xuống dưới
	for (int Dem = 1; Dem < 6 && dong + Dem < BOARD_SIZE && cot + Dem < BOARD_SIZE; Dem++)
	{
		int check = _b->getPoint(dong + Dem, cot + Dem).getCheck();
		if (check == 1)
		{
			SoQuanTa++;
			break;
		}
		else if (check == -1) SoQuanDich++;
		else break;//gặp ô trống
	}
	//duyệt chéo lên trên
	for (int Dem = 1; Dem < 6 && dong - Dem >= 0 && cot - Dem >= 0; Dem++)
	{
		int check = _b->getPoint(dong - Dem, cot - Dem).getCheck();
		if (check == 1)
		{
			SoQuanTa++;
			break;
		}
		else if (check == -1) SoQuanDich++;
		else break;//gặp ô trống
	}
	//Đã chặn 2 đầu
	if (SoQuanTa == 2) return 0;
	return MangDiemPhongNgu[SoQuanDich];
}

long _Game::DiemPN_DuyetCheoTrai(int dong, int cot)
{
	int SoQuanTa = 0;
	int SoQuanDich = 0;
	//duyệt chéo xuống dưới
	for (int Dem = 1; Dem < 6 && dong + Dem < BOARD_SIZE && cot - Dem >= 0; Dem++)
	{
		int check = _b->getPoint(dong + Dem, cot - Dem).getCheck();
		if (check == 1)
		{
			SoQuanTa++;
			break;
		}
		else if (check == -1) SoQuanDich++;
		else break; //gặp ô trống
	}
	//duyệt chéo lên trên
	for (int Dem = 1; Dem < 6 && dong - Dem >= 0 && cot + Dem < BOARD_SIZE; Dem++)
	{
		int check = _b->getPoint(dong - Dem, cot + Dem).getCheck();
		if (check == 1)
		{
			SoQuanTa++;
			break;
		}
		else if (check == -1) SoQuanDich++;
		else break;//gặp ô trống
	}
	//Đã chặn 2 đầu
	if (SoQuanTa == 2) return 0;
	return MangDiemPhongNgu[SoQuanDich];
}
