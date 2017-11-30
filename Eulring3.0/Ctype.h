#include "Header.h"

class Cpos{
public:
	Cpos(){};
	int x;
	int y;
	Cpos(int _x, int _y) :x(_x), y(_y){}

};
class Cvpos {
public:
	Cvpos(){};
	int x, y, v;
	Cvpos(int _x, int _y, int _v) :x(_x), y(_y), v(_v){}
};
class Type_rec {
public:
	Type_rec(){};
	int x, y, d, ide, v;
	Type_rec(int _x, int _y, int _d, int _ide, int _v)
		:x(_x), y(_y), d(_d), ide(_ide), v(_v) {}
	void print() {
		printf_s("%d %d %d %d  \n", x, y, ide, v);
	}
};