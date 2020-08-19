#include "_Player.h"

Player::Player() {
	name = "";
	this->ID = 0;
	this->lose = 0;
	this->win = 0;
	this->draw = 0;
}

Player::~Player() {
	name.clear();
	win = lose = draw = ID = 0;
}

void Player::setName(string name) {
	this->name = name;
}

void Player::setID(int id) {
	this->ID = id;
}

void Player::setWin(int win) {
	this->win = win;
}
void Player::setLose(int lose) {
	this->lose = lose;
}
void Player::setDraw(int draw) {
	this->draw = draw;
}


string Player::getName() {
	return this->name;
}
int Player::getID() {
	return this->ID;
}

int Player::getLose() {
	return this->lose;
}

int Player::getWin() {
	return this->win;
}

int Player::getDraw() {
	return this->draw;
}

Player& Player::operator++() {
	++this->ID;
	return *this;
}

Player& Player::operator--() {
	--this->ID;
	return *this;
}

void Player::increaDraw() { ++draw; }
void Player::increaLose() { ++lose; }
void Player::increaWin() { ++win; }

ofstream& operator<<(ofstream& inFile, Player model) {
	inFile << model.getName() << endl;
	inFile << model.getID() << endl;
	inFile << model.getWin() << endl;
	inFile << model.getLose() << endl;
	inFile << model.getDraw() << endl;
	return inFile;
}

ifstream& operator>>(ifstream& outFile, Player& model) {
	string name;
	int num, ID, win, lose, draw;
	getline(outFile, name, '\n');
	model.setName(name);
	outFile >> ID; model.setID(ID);
	outFile >> num; model.setWin(num);
	outFile >> num; model.setLose(num);
	outFile >> num; model.setDraw(num);
	outFile.ignore();
	return outFile;
}