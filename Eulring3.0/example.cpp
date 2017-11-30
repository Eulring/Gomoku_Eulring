#include "pisqpipe.h"
#include <windows.h>
#include "AIengine.h"
#include <string.h>

const char *infotext = "name=\"Eulring\", author=\"Bian JunYi\", version=\"3.0\", country=\"China\" ,email=\"593729914@qq.com\"";

#define MAX_BOARD 100
int board[MAX_BOARD][MAX_BOARD];
static unsigned seed;
AIengine AI;

void brain_init()
{
	//pipeOut("DEBUG init area");
	if (width<5 || width>MAX_BOARD || height<5 || height>MAX_BOARD){
		pipeOut("ERROR size of the board");
		return;
	}
	//clearlog();
	//------------------
	AI.Api_init(width);

	seed = start_time;
	pipeOut("OK");
}

void brain_restart()
{
	//pipeOut("DEBUG restart area");
	//clearlog();
	int x, y;
	for (x = 0; x<width; x++){
		for (y = 0; y<height; y++){
			board[x][y] = 0;
		}
	}
	//------------------
	AI.Api_init(width);
	pipeOut("OK");
}

int isFree(int x, int y)
{
	return x >= 0 && y >= 0 && x<width && y<height && board[x][y] == 0;
}

void brain_my(int x, int y)
{
	//pipeOut("DEBUG mymove area");
	if (isFree(x, y)){
		board[x][y] = 1;
		//------------------
		AI.Api_mymove(x, y);
	}
	else{
		pipeOut("ERROR my move [%d,%d]", x, y);
	}

}

void brain_opponents(int x, int y)
{
	//pipeOut("DEBUG oppomove area");
	if (isFree(x, y)){
		board[x][y] = 2;
		//------------------
		AI.Api_oppomove(x, y);
	}
	else{
		pipeOut("ERROR opponents's move [%d,%d]", x, y);
	}
}

void brain_block(int x, int y)
{
	if (isFree(x, y)){
		board[x][y] = 3;
	}
	else{
		pipeOut("ERROR winning move [%d,%d]", x, y);
	}
}

int brain_takeback(int x, int y)
{
	if (x >= 0 && y >= 0 && x<width && y<height && board[x][y] != 0){
		board[x][y] = 0;
		AI.Api_takeback();
		return 0;
	}
	return 2;
}

unsigned rnd(unsigned n)
{
	seed = seed * 367413989 + 174680251;
	return (unsigned)(UInt32x32To64(n, seed) >> 32);
}

void brain_turn()
{
	//pipeOut("DEBUG makemove area");
	int x, y, i;
	if (terminated) return;


	AI.Api_makemove(x, y);
	do_mymove(x, y);
}
void brain_print() {
	AI.Api_printboard();

}
void brain_debug() {
	AI.Api_debug();
}
void brain_info(int flag, int val) {
	if (flag == 0) {
		AI.Api_set_turntime(val);
	}
}
void brain_end()
{
}

#ifdef DEBUG_EVAL
#include <windows.h>

void brain_eval(int x, int y)
{
	HDC dc;
	HWND wnd;
	RECT rc;
	char c;
	wnd = GetForegroundWindow();
	dc = GetDC(wnd);
	GetClientRect(wnd, &rc);
	c = (char)(board[x][y] + '0');
	TextOut(dc, rc.right - 15, 3, &c, 1);
	ReleaseDC(wnd, dc);
}

#endif


