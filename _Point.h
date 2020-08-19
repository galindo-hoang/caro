#pragma once
class _Point
{
	int _x, _y, _check;

public:
	_Point();
	_Point(int, int);
	~_Point();
	void setCheck(int);
	int getX();
	int getY();
	int getCheck();
	void setX(int);
	void setY(int);
};
