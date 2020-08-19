#include "_Point.h"

_Point::_Point() { _x = _y = _check = 0; }

_Point::_Point(int pX, int pY)
{
	_x = pX; _y = pY;
	_check = 0;
}

_Point::~_Point() { this->_x = this->_y = this->_check = 0; }

int _Point::getX() { return _x; }

int _Point::getY() { return _y; }

int _Point::getCheck() { return _check; }

void _Point::setX(int pX) { _x = pX; }

void _Point::setY(int pY) { _y = pY; }

void _Point::setCheck(int pCheck)
{

	_check = pCheck;
}