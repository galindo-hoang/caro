#include "_Game.h"

_Game::_Game(Player& first, Player& second, int pSize, int pLeft, int pTop)
{
	_b = new _Board(pSize, pLeft, pTop);
	_command = -1; // Gán lượt và phím mặc định
	_x = pLeft; _y = pTop;
	first.setLose(0);
	first.setWin(0);
	first.setDraw(0);
	second.setLose(0);
	second.setWin(0);
	second.setDraw(0);
}

_Game::~_Game() { delete _b; }

int _Game::getCommand() { return _command; }

void _Game::SetLoop(bool loop) { this->_loop = loop; }

void _Game::setXY(int x, int y) {
	_x = x;
	_y = y;
}

char _Game::waitKeyBoard()
{
	if (_kbhit()) _command = toupper(_getch());

	return _command;
}

char _Game::askContinue()
{
	return _command;
}

void _Game::startGame(Player& first, Player& second)
{
	bool played = PlaySound(L"ting.wav", NULL, SND_ASYNC && SND_LOOP && SND_NOSTOP);
	_Common::Show_Cursor();
	_Picture::clear_x_o();
	if (_loop) {
		first.setID(0);
		second.setID(0);
		_b->resetData();
	}
	else _loop = true;

	_b->drawBoard(first, second);
	_x = 2;
	_y = 1;
	_b->drawTurn(first.getID(), second.getID());
	if ((first.getID() + second.getID()) % 2 == 0) _Picture::draw_x();
	else _Picture::draw_o();

	_Common::gotoxy(_x, _y);
}

void _Game::exitGame()
{
	_loop = false;
	_Common::ClearConsoleToColors(0);
	_b->resetData();
	_Common::Hidden_Cursor();
	bool play = PlaySound(L"verystrong.wav", NULL, SND_LOOP && SND_ASYNC);
}

bool _Game::processCheckBoard(Player& first, Player& second)
{
	switch (_b->checkTurn(_x / 4, _y / 2, first.getID() + second.getID()))
	{
	case 1:
		_Common::textcolor(2 + BackRound_play * 16);
		_Common::gotoxy(_x, _y);
		++first;
		printf("X");
		_Picture::clear_x_o();
		_Picture::draw_o();
		break;
	case -1:
		_Common::textcolor(4 + BackRound_play * 16);
		_Common::gotoxy(_x, _y);
		++second;
		printf("O");
		_Picture::clear_x_o();
		_Picture::draw_x();
		break;
	case 0:
		return false;
	}
	bool played = PlaySound(L"press.wav", NULL, SND_ASYNC);
	_b->drawTurn(first.getID(), second.getID());
	_Common::gotoxy(_x, _y);
	return true;
}

char _Game::processFinish(Player& first, Player& second) {
	bool run = false;
	switch (_b->check(_y / 2, _x / 4)) {
	case 1:
		run = true;
		first.increaWin();
		second.increaLose();
		_b->clearpipeline();
		_Picture::clear_x_o();
		_Picture::draw_x();
		_Common::textcolor(2 + BackRound_play * 16);
		_Picture::show_win();
		break;
	case -1:
		run = true;
		second.increaWin();
		first.increaLose();
		_b->clearpipeline();
		_Picture::clear_x_o();
		_Picture::draw_o();
		_Common::textcolor(4 + BackRound_play * 16);
		_Picture::show_win();
		break;
	case 2:
		run = true;
		second.increaDraw();
		first.increaDraw();
		_Picture::clear_x_o();
		_b->clearpipeline();
		_Picture::show_draw();
		break;
	}

	string result;
	_Common::textcolor(0 + BackRound_play * 16);
	if (run) bool played = PlaySound(L"glory.wav", NULL, SND_ASYNC);
	while (run) {
		_Common::gotoxy(left_x_pipeline + 1, _Common::getRows() - 3);
		cout << "   Do you want to play continue Y/N";
		_Common::gotoxy(left_x_pipeline + 1, _Common::getRows() - 2);
		cout << "              (yes/no): ";
		getline(cin, result);
		_Common::gotoxy(left_x_pipeline + 1, _Common::getRows() - 3);
		cout << "   Do you want to play continue Y/N";
		_Common::gotoxy(left_x_pipeline + 1, _Common::getRows() - 2);
		cout << "              (yes/no): ";
		cout << "    ";
		if (result[0] == 'y' || result[0] == 'Y' || result[0] == 'n' || result[0] == 'N') {
			char mod = result[0];
			result.clear();
			return mod;
		}
		result.clear();
	}
	
	return '\0';
}

void _Game::moveRight()
{
	_x += 4;
	if (_x > (_b->getSize() * 4)) _x = 2;
	_Common::gotoxy(_x, _y);
	bool played = PlaySound(L"move1.wav", NULL, SND_ASYNC);
}

void _Game::moveLeft()
{
	_x -= 4;
	if (_x < 2) _x = (_b->getSize() * 4) - 2;
	_Common::gotoxy(_x, _y);
	bool played = PlaySound(L"move1.wav", NULL, SND_ASYNC);
}

void _Game::moveDown()
{
	_y += 2;
	if (_y > (_b->getSize() * 2)) _y = 1;
	_Common::gotoxy(_x, _y);
	bool played = PlaySound(L"move1.wav", NULL, SND_ASYNC);
}

void _Game::moveUp()
{
	_y -= 2;
	if (_y < 1) _y = (_b->getSize() * 2) - 1;
	_Common::gotoxy(_x, _y);
	bool played = PlaySound(L"move1.wav", NULL, SND_ASYNC);
}


void _Game::Undo(Player& first, Player& second) {
	if ((first.getID() + second.getID()) <= 0) { return; }
	for (int i = 0; i < _b->getSize(); ++i) {
		for (int j = 0; j < _b->getSize(); ++j) {
			if ((first.getID() + second.getID()) == abs(_b->getIJ(i, j))) {
				if ((first.getID() + second.getID()) % 2 == 0) {
					--second;
				}
				else --first;

				_b->drawTurn(first.getID(), second.getID());

				_b->setIJ(i, j, 0);
				_x = j * 4 + 2;
				_y = i * 2 + 1;
				
				
				_Picture::clear_x_o();
				if ((first.getID() + second.getID()) % 2 == 0) _Picture::draw_x();
				else _Picture::draw_o();
				_Common::textcolor(0 + BackRound_play * 16);


				_Common::gotoxy(_x, _y);
				cout << " ";
				_Common::gotoxy(_x, _y);
				bool played = PlaySound(L"undo.wav", NULL, SND_ASYNC);
				return;
			}
		}
	}
}



string Time() {
	time_t current_time;
	struct tm  local_time;
	time(&current_time);
	localtime_s(&local_time, &current_time);

	string Year = to_string(local_time.tm_year + 1900);
	string Month = to_string(local_time.tm_mon + 1);
	string Day = to_string(local_time.tm_mday);

	string Hour = to_string(local_time.tm_hour);
	string Min = to_string(local_time.tm_min);
	string Sec = to_string(local_time.tm_sec);
	return  Day + "-" + Month + "-" + Year + " (" + Hour + ":" + Min + ":" + Sec + ")";
}

void _Game::Save(Player first, Player second, _Menu& Menu) {
	string file;
	ofstream write;
	_Common::gotoxy(left_mid_x_pipeline - 2, down_y_pipeline + 1);
	cout << "nhap ten: ";
	getline(cin, file);

	_Common::gotoxy(left_mid_x_pipeline - 2, down_y_pipeline + 1);
	cout << "                           ";
	write.open(file + ".txt", ios::out);
	write << first;
	write << second;
	for (int i = 0; i < _b->getSize(); ++i) {
		for (int j = 0; j < _b->getSize(); ++j) {
			write << _b->getIJ(i, j) << " ";
		} 
		write << endl;
	}


	Menu.add_to_list(file, Time());

	_Common::gotoxy(_x, _y);
	write.close();
	Menu.fixTXT();
	bool played = PlaySound(L"save.wav", NULL, SND_ASYNC);
}

void _Game::loading(Player& first, Player& second, _Menu Menu, int chose) {
	ifstream read;
	int n;
	read.open(Menu.Saved[chose].getName() + ".txt");
	read >> first;
	read >> second; 
	for (int i = 0; i < _b->getSize(); ++i) {
		for (int j = 0; j < _b->getSize(); ++j) {
			read >> n;
			_b->setIJ(i, j, n);
		}
	}
	read.close();
}


//// may

// easy

vector<int> _Game::easy() {
	srand(time(NULL));
	vector<int> stipud(2);
	stipud[0] = rand() % 15;
	stipud[1] = rand() % 15;
	while (this->_b->getIJ(stipud[0], stipud[1]) != 0) {
		stipud[0] = rand() % 15;
		stipud[1] = rand() % 15;
	}
	return stipud;
}

// hrad
bool _Game::bad_trip_1(int count, int i, int j) {
	for (int x = 0; x < 5; ++x) {
		for (int y = 10 + x; y < _b->getSize(); ++y) {
			if ((x == j && y == i) || (x == i && y == j)) {
				if (y == (10 + x)) {
					++count;
				}
				else return true;
			}
		}
	}
	if (count == 2) return true;
	else return false;
}

bool _Game::bad_trip_2(int count, int i, int j) {
	for (int x = 0; x < 5; ++x) {
		for (int y = 0; y < (5 - x); ++y) {
			if ((x == j && y == i)) {
				if (y == (4 - x)) {
					++count;
					break;//3 1
				}
				else return true;
			}
		}
	}

	int alpha = 0;

	for (int x = 10; x < _b->getSize(); ++x) {
		for (int y = 14 - alpha; y < _b->getSize(); ++y) {
			if (x == j && y == i) {
				if (y == (14 - alpha)) {
					++count;
					break;
				}
				else return true;
			}
		}
		++alpha;
	}

	if (count == 2) return true;
	else return false;
}

long long _Game::attack_Cot(int i, int j) {
	long long local_bad = 0, total = 0;
	if (i == 0 || i == (_b->getSize() - 1)) local_bad = 9;
	int count = 1;
	int computer = 0;
	int player = 0;
	bool flag_left = true, flag_right = true;
	bool align = false;
	while (count < 6 && (flag_left || flag_right)) {
		if ((i - count) > -1 && flag_left) {
			if (_b->getIJ(i - count, j) < 0) {
				++computer;
			}
			else {
				if (_b->getIJ(i - count, j) > 0) {
					++player;
				}
				flag_left = false;
			}
		}
		else if (!align && flag_left) {
			flag_left = false;
			align = true;
		}

		if ((i + count) < _b->getSize() && flag_right) {
			if (_b->getIJ(i + count, j) < 0) {
				++computer;
			}
			else {
				if (_b->getIJ(i + count, j) > 0) {
					++player;
				}
				flag_right = false;
			}
		}
		else if (!align && flag_right) {
			flag_right = false;
			align = true;
		}
		++count;
	}

	if (player == 2 || computer >= 5 || (align && player == 1 && computer != 4)) return total;
	else total = attack[computer] - defense[player + 1] - local_bad;

	return total;
}

long long _Game::attack_dong(int i, int j) {
	long long local_bad = 0, total = 0;
	if (j == 0 || j == (_b->getSize() - 1)) local_bad = 9;
	int count = 1;
	int computer = 0;
	int player = 0;
	bool flag_top = true, flag_down = true;
	bool align = false;
	while (count < 6 && (flag_top || flag_down)) {
		if ((j - count) > -1 && flag_top) {
			if (_b->getIJ(i, j - count) < 0) {
				++computer;
			}
			else {
				if (_b->getIJ(i, j - count) > 0) {
					++player;
				}
				flag_top = false;
			}
		}
		else if (!align && flag_top) {
			flag_top = false;
			align = true;
		}

		if ((j + count) < _b->getSize() && flag_down) {
			if (_b->getIJ(i, j + count) < 0) {
				++computer;
			}
			else {
				if (_b->getIJ(i, j + count) > 0) {
					++player;
				}
				flag_down = false;
			}
		}
		else if (!align && flag_down) {
			flag_down = false;
			align = true;
		}
		++count;
	}

	if (player == 2 || computer >= 5 || (align && player == 1 && computer != 4)) return total;
	else total = attack[computer] - defense[player + 1] - local_bad;

	return total;
}

long long _Game::attack_Cheo_1(int i, int j) {
	long long local_bad = 0, total = 0;
	if (i * j == 0 || i == (_b->getSize() - 1) || j == (_b->getSize() - 1)) local_bad = 9;
	int count = 1;
	int computer = 0;
	int player = 0;
	bool flag_top = true, flag_down = true;
	bool align = false;
	while (count < 6 && (flag_top || flag_down)) {
		if ((i - count) > -1 && (j - count) > -1 && flag_top) {

			if ((_b->getIJ(i - count, j - count) < 0)) {
				++computer;
			}
			else {
				if ((_b->getIJ(i - count, j - count) > 0)) {
					++player;
				}
				flag_top = false;
			}
		}
		else if (!align && flag_top) {
			flag_top = false;
			align = true;
		}

		if ((i + count) < _b->getSize() && (j + count) < _b->getSize() && flag_down) {
			if ((_b->getIJ(i + count, j + count) < 0)) {
				++computer;
			}
			else {
				if ((_b->getIJ(i + count, j + count) > 0)) {
					++player;
				}
				flag_down = false;
			}
		}
		else if (!align && flag_down) {
			flag_down = false;
			align = true;
		}
		++count;
	}

	if (player == 2 || computer >= 5 || bad_trip_1(player, i, j) || (align && player == 1 && computer != 4)) return total;
	else total = attack[computer] - defense[player + 1] - local_bad;

	return total;
}

long long _Game::attack_Cheo_2(int i, int j) {
	long long local_bad = 0, total = 0;
	if (i * j == 0 || i == (_b->getSize() - 1) || j == (_b->getSize() - 1)) local_bad = 9;
	int count = 1;
	int computer = 0;
	int player = 0;
	bool flag_top = true, flag_down = true;
	bool align = false;
	while (count < 6 && (flag_top || flag_down)) {
		if ((i - count) > -1 && (j + count) < _b->getSize() && flag_top) {

			if (_b->getIJ(i - count, j + count) < 0) {
				++computer;
			}
			else {
				if (_b->getIJ(i - count, j + count) > 0) {
					++player;
				}
				flag_top = false;
			}
		}
		else if (!align && flag_top) {
			flag_top = false;
			align = true;
		}

		if ((i + count) < _b->getSize() && (j - count) > -1 && flag_down) {
			if (_b->getIJ(i + count, j - count) < 0) {
				++computer;
			}
			else {
				if (_b->getIJ(i + count, j - count) > 0) {
					++player;
				}
				flag_down = false;
			}
		}
		else if (!align && flag_down) {
			flag_down = false;
			align = true;
		}
		++count;
	}
	if (player == 2 || computer >= 5 || bad_trip_2(player, i, j) || (align && player == 1 && computer != 4)) return total;
	else total = attack[computer] - defense[player + 1] - local_bad;

	return total;
}

long long _Game::defen_Dong(int i, int j) {
	long long total = 0;
	int count = 1;
	int computer = 0, player = 0;
	bool flag_left = true, flag_right = true;
	bool align = false;
	while (count < 6 && (flag_left || flag_right)) {
		if ((i - count) > -1 && flag_left) {
			if (_b->getIJ(i - count, j) > 0) {
				++player;
			}
			else {
				if (_b->getIJ(i - count, j) < 0) ++computer;
				flag_left = false;
			}
		}
		else if (!align && flag_left) {
			align = true;
			flag_left = false;
		}

		if ((i + count) < _b->getSize() && flag_right) {
			if (_b->getIJ(i + count, j) > 0) {
				++player;
			}
			else {
				if (_b->getIJ(i + count, j) < 0) ++computer;
				flag_right = false;
			}
		}
		else if (!align && flag_right) {
			align = true;
			flag_right = false;
		}
		++count;
	}
	if (computer == 2 || player >= 5 || (computer == 1 && align && player < 4)) return total;
	total = defense[player];
	if (player > 0) total -= attack[computer] * 2;
	return total;
}

long long _Game::defen_Cot(int i, int j) {
	long long total = 0;
	int count = 1;
	int computer = 0, player = 0;
	bool flag_up = true, flag_down = true;
	bool align = false;
	while (count < 6 && (flag_up || flag_down)) {
		if ((j - count) > -1 && flag_up) {
			if (_b->getIJ(i, j - count) > 0) {
				++player;
			}
			else {
				if (_b->getIJ(i, j - count) < 0) ++computer;
				flag_up = false;
			}
		}
		else if (!align && flag_up) {
			align = true;
			flag_up = false;
		}

		if ((j + count) < _b->getSize() && flag_down) {
			if (_b->getIJ(i, j + count) > 0) {
				++player;
			}
			else {
				if (_b->getIJ(i, j + count) < 0) ++computer;
				flag_down = false;
			}
		}
		else if (!align && flag_down) {
			align = true;
			flag_down = false;
		}
		++count;
	}
	if (computer == 2 || player >= 5 || (computer == 1 && align && player < 4)) return total;
	total = defense[player];
	if (player > 0) total -= attack[computer] * 2;
	return total;
}

long long _Game::defen_Cheo_1(int i, int j) {
	long long total = 0;
	int count = 1;
	int computer = 0, player = 0;
	bool flag_up = true, flag_down = true;
	bool align = false;
	while (count < 6 && (flag_down || flag_up)) {
		if ((i - count) > -1 && (j - count) > -1 && flag_up) {
			if (_b->getIJ(i - count, j - count) > 0) ++player;
			else {
				if (_b->getIJ(i - count, j - count) < 0) ++computer;
				flag_up = false;
			}
		}
		else if (!align && flag_up) {
			align = true;
			flag_up = false;
		}

		if ((i + count) < _b->getSize() && (j + count) < _b->getSize() && flag_down) {
			if (_b->getIJ(i + count, j + count) > 0) ++player;
			else {
				if (_b->getIJ(i + count, j + count) < 0) ++computer;
				flag_down = false;
			}
		}
		else if (!align && flag_down) {
			align = true;
			flag_down = false;
		}
		++count;
	}
	if (computer == 2 || player >= 5 || bad_trip_1(computer, i, j) || (computer == 1 && align && player < 4)) return total;
	total = defense[player];
	if (player > 0) total -= attack[computer] * 2;
	return total;
}

long long _Game::defen_Cheo_2(int i, int j) {
	long long total = 0;
	int count = 1;
	int computer = 0, player = 0;
	bool flag_up = true, flag_down = true;
	bool align = false;
	while (count < 6 && (flag_up || flag_down)) {
		if ((i - count) > -1 && (j + count) < _b->getSize() && flag_up) {
			if (_b->getIJ(i - count, j + count) > 0) ++player;
			else {
				if (_b->getIJ(i - count, j + count) < 0) ++computer;
				flag_up = false;
			}
		}
		else if (!align && flag_up) {
			align = true;
			flag_up = false;
		}

		if ((i + count) < _b->getSize() && (j - count) > -1 && flag_down) {
			if (_b->getIJ(i + count, j - count) > 0) ++player;
			else {
				if (_b->getIJ(i + count, j - count) < 0) ++computer;
				flag_down = false;
			}
		}
		else if (!align && flag_down) {
			align = true;
			flag_down = false;
		}
		++count;
	}
	if (computer == 2 || player >= 5 || bad_trip_2(computer, i, j) || (computer == 1 && align && player < 4)) return total;
	total = defense[player];
	if (player > 0) total -= attack[computer] * 2;
	return total;
}

vector<int> _Game::alpha_beta() {
	vector<int> bestMove(2);//0 row   -----  1 col
	long long max = 0;
	for (int i = 0; i < _b->getSize(); ++i) {
		for (int j = 0; j < _b->getSize(); ++j) {
			if (_b->getIJ(i, j) == 0) {
				long long attack = attack_dong(i, j) + attack_Cot(i, j) + attack_Cheo_1(i, j) + attack_Cheo_2(i, j);
				long long defen = defen_Cot(i, j) + defen_Dong(i, j) + defen_Cheo_1(i, j) + defen_Cheo_2(i, j);
				long long model = max(attack, defen);
				if (max < model) {
					max = model;
					bestMove[0] = i;
					bestMove[1] = j;
				}
			}
		}
	}
	return bestMove;
}
