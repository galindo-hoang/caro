#include "_Board.h"

int _Board::getSize() { return _size; }

int _Board::getXAt(int i, int j) { return _pArr[i][j].getX(); }

int _Board::getYAt(int i, int j) { return _pArr[i][j].getY(); }

_Board::_Board()
{

	_size = 0;
	_pArr = NULL;
}

_Board::_Board(int pSize, int pX, int pY)
{

	_size = pSize;
	_pArr = new _Point * [pSize];
	for (int i = 0; i < pSize; i++) _pArr[i] = new _Point[pSize];
}

_Board::~_Board()
{

	for (int i = 0; i < _size; i++) delete[] _pArr[i];
	delete[] _pArr;
}

void _Board::resetData()
{
	if (_size == 0) return; // Phải gọi constructor trước khi resetData
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			_pArr[i][j].setCheck(0);
		}
	}
}

void _Board::clearpipeline() {
	for (int i = down_y_pipeline + 1; i < _Common::getRows(); ++i) {
		_Common::gotoxy(left_x_pipeline + 1, i);
		cout << "                                       ";
	}
}

ofstream& operator<<(ofstream& inFile, _Board model) {
	for (int i = 0; i < model.getSize(); ++i) {
		for (int j = 0; j < model.getSize(); ++j) {
			inFile << model._pArr[i][j].getCheck() << " ";
		}
		inFile << endl;
	}
	return inFile;
}


ifstream& operator>>(ifstream& outFile, _Board& model) {
	int num;
	for (int i = 0; i < model.getSize(); ++i) {
		for (int j = 0; j < model.getSize(); ++j) {
			outFile >> num;
			model._pArr[i][j].setCheck(num);
		}
	}
	return outFile;
}

void _Board::drawBoard(Player first,Player second) {
	_Common::ClearConsoleToColors(1);
	int size_y = this->_size * 2;
	int size_x = this->_size * 4;

	for (int y = 0; y <= size_y; y++) {
		for (int x = 0; x <= size_x; ++x) {
			_Common::gotoxy(x, y);
			if (y == 0) {
				if (x == 0) {
					putchar(218);
				}
				else if (x == size_x) {
					putchar(191);
				}
				else if ((x % 4) == 0) {
					putchar(194);
				}
				else {
					putchar(196);
				}

			}
			else if (y == size_y) {
				if (x == 0) {
					putchar(192);
				}
				else if (x == size_x) {
					putchar(217);
				}
				else if ((x % 4) == 0) {
					putchar(193);
				}
				else {
					putchar(196);
				}
			}
			else if ((y % 2) == 0) {
				if (x == 0) {
					putchar(195);
				}
				else if (x == size_x) {
					putchar(180);
				}
				else if ((x % 4) == 0) {
					putchar(197);
				}
				else {
					putchar(196);
				}
			}
			else if ((x % 4) == 0) {
				putchar(179);
			}
		}
	}

	// Draw Pipeline

	for (int y = 0; y < top_y_pipeline; y++) {
		_Common::gotoxy(left_x_pipeline, y);
		putchar(186);
		_Common::gotoxy(right_x_pipeline, y);
		putchar(186);
	}

	for (int x = 0; x <= (right_x_pipeline - left_x_pipeline); x++) {
		_Common::gotoxy(left_x_pipeline + x, top_y_pipeline);
		if (x == 0) putchar(200);
		else if (x == (right_x_pipeline - left_x_pipeline)) putchar(188);
		else if ((x + left_x_pipeline) == left_mid_x_pipeline) putchar(187);
		else if ((x + left_x_pipeline) == right_mid_x_pipeline) putchar(201);
		else if (((x + left_x_pipeline) < left_mid_x_pipeline) || ((x + left_x_pipeline) > right_mid_x_pipeline)) putchar(205);
	}

	for (int y = top_y_pipeline + 1; y < down_y_pipeline; y++) {
		_Common::gotoxy(left_mid_x_pipeline, y);
		putchar(186);
		_Common::gotoxy(right_mid_x_pipeline, y);
		putchar(186);
	}

	for (int x = 0; x <= (right_x_pipeline - left_x_pipeline); x++) {
		_Common::gotoxy(left_x_pipeline + x, down_y_pipeline);
		if (x == 0) putchar(201);
		else if (x == (right_x_pipeline - left_x_pipeline)) putchar(187);
		else if ((x + left_x_pipeline) == left_mid_x_pipeline) putchar(188);
		else if ((x + left_x_pipeline) == right_mid_x_pipeline) putchar(200);
		else if (((x + left_x_pipeline) < left_mid_x_pipeline) || ((x + left_x_pipeline) > right_mid_x_pipeline)) putchar(205);
	}

	for (int y = down_y_pipeline + 1; y < _Common::getRows(); y++) {
		_Common::gotoxy(left_x_pipeline, y);
		putchar(186);
		_Common::gotoxy(right_x_pipeline, y);
		putchar(186);
		if ((y > (_Common::getRows() + 3 * down_y_pipeline) / 4) && (y <= (_Common::getRows() * 3 + down_y_pipeline) / 4)) {
			_Common::gotoxy(line_x_pipeline, y);
			putchar(179);
		}
	}
	_Common::gotoxy(0, 30);

	//drawFunc

	int align = (func[0].size() + func[1].size() + func[2].size() + func[3].size()) / (sizeof(func) / sizeof(string));
	for (int i = 0; i < (sizeof(func) / sizeof(string)); ++i) {
		_Common::textcolor(2 + i + BackRound_play * 16);
		_Common::gotoxy(left_x_pipeline + align + 5, 2 + i * 2);
		cout << func[i];
	}


	_Common::textcolor(1 + BackRound_play * 16);

	// draw Player

	//// Name
	_Common::gotoxy(left_x_pipeline + 2, down_y_pipeline + 4);
	cout << "Player X: " << first.getName();
	_Common::gotoxy(line_x_pipeline + 2, down_y_pipeline + 4);
	cout << "Player O: " << second.getName();

	////Status
	_Common::gotoxy(left_x_pipeline + 2, down_y_pipeline + 5);
	cout << "Win     : " << first.getWin();
	_Common::gotoxy(line_x_pipeline + 2, down_y_pipeline + 5);
	cout << "Win     : " << second.getWin();

	_Common::gotoxy(left_x_pipeline + 2, down_y_pipeline + 6);
	cout << "Lose    : " << first.getLose();
	_Common::gotoxy(line_x_pipeline + 2, down_y_pipeline + 6);
	cout << "Lose    : " << second.getLose();

	_Common::gotoxy(left_x_pipeline + 2, down_y_pipeline + 7);
	cout << "Draw    : " << first.getDraw();
	_Common::gotoxy(line_x_pipeline + 2, down_y_pipeline + 7);
	cout << "Draw    : " << second.getDraw();

	////Turn
	drawTurn(first.getID(), second.getID());

	////X_O
	for (int i = 0; i < _size; ++i) {
		for (int j = 0; j < _size; ++j) {
			_Common::gotoxy(j * 4 + 2, i * 2 + 1);
			if (_pArr[i][j].getCheck() > 0) {
				_Common::textcolor(2 + BackRound_play * 16);
				cout << "X";
			}
			else if (_pArr[i][j].getCheck() < 0) {
				_Common::textcolor(4 + BackRound_play * 16);
				cout << "O";
			}
		}
	}
	_Common::textcolor(0 + BackRound_play * 16);

}


void _Board::drawTurn(int first, int second) {

	_Common::textcolor(1 + BackRound_play * 16);
	_Common::gotoxy(left_x_pipeline + 2, down_y_pipeline + 8);
	cout << "Turn    : " << "   ";
	_Common::gotoxy(line_x_pipeline + 2, down_y_pipeline + 8);
	cout << "Turn    : " << "   ";

	_Common::gotoxy(left_x_pipeline + 2, down_y_pipeline + 8);
	cout << "Turn    : ";
	_Common::textcolor(0 + BackRound_play * 16);
	cout << first;
	_Common::textcolor(1 + BackRound_play * 16);
	_Common::gotoxy(line_x_pipeline + 2, down_y_pipeline + 8);
	cout << "Turn    : ";
	_Common::textcolor(0 + BackRound_play * 16);
	cout << second;

}


int _Board::checkTurn(int j, int i, int turn)
{
	if (_pArr[i][j].getCheck() == 0) {
		if (turn % 2 == 0) {
			_pArr[i][j].setCheck(turn + 1);
			return 1;
		}
		else {
			_pArr[i][j].setCheck(-1 * (turn + 1));
			return -1;
		}
	}
	else return 0;
}

int _Board::check(int i, int j) {
	if (check_Row(i, j) || check_Col(i, j) || check_Diagonal_2(i, j) || check_Diagonal_1(i, j)) {

		if (_pArr[i][j].getCheck() > 0) return 1;
		else return -1;
	}
	else if (abs(_pArr[i][j].getCheck()) == (_size * _size)) {
		return 2;
	}
	else {
		return 0;
	}

}

bool _Board::check_Row(int i, int j) {
	int pivot = _pArr[i][j].getCheck();
	int count = 1;
	int block_top = -1, block_down = this->_size;
	int count_top = 0, count_down = 1;
	bool check_top = true, check_down = true;
	while (count < 6 && (check_top || check_down)) {
		if ((i - count) > -1 && check_top) {
			if ((_pArr[i - count][j].getCheck() * pivot) > 0) {
				++count_top;
			}
			else {
				if ((_pArr[i - count][j].getCheck() * pivot) < 0) block_top = i - count;

				check_top = false;
			}
		}

		if ((i + count) < this->_size && check_down) {
			if ((_pArr[i + count][j].getCheck() * pivot) > 0) {
				++count_down;
			}
			else {
				if ((_pArr[i + count][j].getCheck() * pivot) < 0) block_down = i + count;

				check_down = false;
			}
		}
		++count;
	}

	if ((count_down + count_top) == 5) {
		if (block_down != this->_size && block_top != -1 && (block_down - block_top) == 6) {
			return false;
		}
		else {
			return true;
		}
	}
	else {
		return false;
	}
}


bool _Board::check_Col(int i, int j) {
	int pivot = _pArr[i][j].getCheck();
	int count = 1;
	int block_left = -1, block_right = this->_size;
	int count_left = 0, count_right = 1;
	bool check_left = true, check_right = true;
	while (count < 6 && (check_left || check_right)) {
		if ((j - count) > -1 && check_left) {
			if ((_pArr[i][j - count].getCheck() * pivot) > 0) {
				++count_left;
			}
			else {
				if ((_pArr[i][j - count].getCheck() * pivot) < 0) block_left = j - count;

				check_left = false;
			}
		}

		if ((j + count) < this->_size && check_right) {
			if ((_pArr[i][j + count].getCheck() * pivot) > 0) {
				++count_right;
			}
			else {
				if ((_pArr[i][j + count].getCheck() * pivot) < 0) block_right = j + count;

				check_right = false;
			}
		}
		++count;
	}

	if ((count_right + count_left) == 5) {
		if (block_right != this->_size && block_left != -1 && (block_right - block_left) == 6) {
			return false;
		}
		else {
			return true;
		}
	}
	else {
		return false;
	}
}

bool _Board::check_Diagonal_1(int i, int j) {
	int pivot = _pArr[i][j].getCheck();
	int count = 1;
	int count_diagonal_top = 0, count_diagonal_down = 1;
	int block_diagonal_top_x = -1, block_diagonal_down_x = this->_size;
	int block_diagonal_top_y = -1, block_diagonal_down_y = this->_size;
	bool check_diagonal_top = true, check_diagonal_down = true;

	while (count < 6 && (check_diagonal_top || check_diagonal_down)) {
		if ((i - count) > -1 && (j - count) > -1 && check_diagonal_top) {

			if ((_pArr[i - count][j - count].getCheck() * pivot) > 0) {
				++count_diagonal_top;
			}
			else {
				if ((_pArr[i - count][j - count].getCheck() * pivot) < 0) {
					block_diagonal_top_x = i - count;
					block_diagonal_top_y = j - count;
				}
				check_diagonal_top = false;
			}
		}

		if ((i + count) < this->_size && (j + count) < this->_size && check_diagonal_down) {
			if ((_pArr[i + count][j + count].getCheck() * pivot) > 0) {
				++count_diagonal_down;
			}
			else {
				if ((_pArr[i + count][j + count].getCheck() * pivot) < 0) {
					block_diagonal_down_x = i + count;
					block_diagonal_down_y = j + count;
				}
				check_diagonal_down = false;
			}
		}
		++count;
	}

	if ((count_diagonal_down + count_diagonal_top) == 5) {
		if (block_diagonal_down_x != this->_size && block_diagonal_down_y != this->_size && block_diagonal_top_x != -1 && block_diagonal_top_y != -1 && (block_diagonal_down_x - block_diagonal_top_x) == 6) {
			return false;
		}
		else {
			return true;
		}
	}
	else {
		return false;
	}
}

bool _Board::check_Diagonal_2(int i, int j) {
	int pivot = _pArr[i][j].getCheck();
	int count = 1;
	int count_diagonal_top = 0, count_diagonal_down = 1;
	int block_diagonal_top_x = -1, block_diagonal_down_x = this->_size;
	int block_diagonal_top_y = this->_size, block_diagonal_down_y = -1;
	bool check_diagonal_top = true, check_diagonal_down = true;

	while (count < 6 && (check_diagonal_top || check_diagonal_down)) {
		if ((i - count) > -1 && (j + count) < this->_size && check_diagonal_top) {

			if ((_pArr[i - count][j + count].getCheck() * pivot) > 0) {
				++count_diagonal_top;
			}
			else {
				if ((_pArr[i - count][j + count].getCheck() * pivot) < 0) {
					block_diagonal_top_x = i - count;
					block_diagonal_top_y = j + count;
				}
				check_diagonal_top = false;
			}
		}

		if ((i + count) < this->_size && (j - count) > -1 && check_diagonal_down) {
			if ((_pArr[i + count][j - count].getCheck() * pivot) > 0) {
				++count_diagonal_down;
			}
			else {
				if ((_pArr[i + count][j - count].getCheck() * pivot) < 0) {
					block_diagonal_down_x = i + count;
					block_diagonal_down_y = j - count;
				}
				check_diagonal_down = false;
			}
		}
		++count;
	}

	if ((count_diagonal_down + count_diagonal_top) == 5) {
		if (block_diagonal_down_x != this->_size && block_diagonal_down_y != -1 && block_diagonal_top_x != -1 && block_diagonal_top_y != this->_size && (block_diagonal_down_x - block_diagonal_top_x) == 6) {
			return false;
		}
		else {
			return true;
		}
	}
	else {
		return false;
	}
}

int _Board::getIJ(int i, int j) { return _pArr[i][j].getCheck(); }
void _Board::setIJ(int i, int j, int num) { _pArr[i][j].setCheck(num); }
