
#include "Cboard.h"

void Cboard::Init(int _size) {
	turn_lim = TIME_TURN;
	Init_timecol();
	size = _size;
	memset(board, -1, sizeof(board));
	for (int i = 1; i <= size; i++)
		for (int j = 1; j <= size; j++)
			board[i][j] = EMPTY;
	memset(Wsum, 0, sizeof(Wsum));
	memset(type, 0, sizeof(type));
	memset(type4, 0, sizeof(type4));
	memset(T1sum, 0, sizeof(T1sum));
	memset(bug_flag, 0, sizeof(bug_flag));
	//hash_val = h_tb.Initzob(_size);
	//h_tb.InitTable();
	CP.Init();
	//Debug_func1();
}
void Cboard::Set_side() {
	AIside = step % 2;
}

/*
type[][][][4]中的四个方向
0: 向下
1: 向右下
2: 向右
3: 向右上

*/
void Cboard::Put_piece(int x, int y) {
	int ide = step % 2;
	int opide = ide ^ 1;
	board[x][y] = ide;
	int v;
	v = type4[x][y][ide];
	if (v < 3) Wsum[v][ide]++;
	else v = 0;
	move_st[step] = Cvpos(x, y, v);
	t_rec_num[step] = 0;

	for (int i = 1; i <= 7; i++)
		T1sum_rec[step][i][0] = T1sum[i][0], T1sum_rec[step][i][1] = T1sum[i][1];
	/*hash_val ^= h_tb.zob[x][y][ide];
	hash_val ^= h_tb.zob[x][y][EMPTY];*/



	int dx, dy;//方向向量
	int sx, sy, ex, ey;//窗口起始坐标末坐标
	int side, hash, len;
	int tmp;
	for (int dir = 0; dir < 4; dir++) {
		//当前点的T1棋型消失，也要计入计算
		T1sum[type[x][y][opide][dir]][opide] --;
		T1sum[type[x][y][ide][dir]][ide] --;

		if (dir == 0) dx = 1, dy = 0;
		else if (dir == 1) dx = 1, dy = 1;
		else if (dir == 2) dx = 0, dy = 1;
		else dx = -1, dy = 1;

		sx = ex = x;
		sy = ey = y;
		side = 0, hash = 0, len = -1;
		for (int i = 0; i < 5; i++) {
			if (board[sx][sy] == opide || board[sx][sy] == -1) break;
			sx -= dx, sy -= dy, len++;
		}
		for (int i = 0; i < 5; i++) {
			if (board[ex][ey] == opide || board[ex][ey] == -1) break;
			ex += dx, ey += dy, len++;
		}//**如果len小于5直接goto
		if (board[sx][sy] == opide || board[sx][sy] == -1)
			side = 2;
		if (board[ex][ey] == opide || board[ex][ey] == -1)
			side ^= 1;

		for (int xx = sx + dx, yy = sy + dy; xx != ex || yy != ey; xx += dx, yy += dy)
			hash <<= 1, hash += (board[xx][yy] == ide);
		for (int xx = sx + dx, yy = sy + dy, cnt = 1; xx != ex || yy != ey; xx += dx, yy += dy, cnt++)
			if (board[xx][yy] == 2) {
				tmp = type[xx][yy][ide][dir];
				t_rec[step][++t_rec_num[step]] = Type_rec(xx, yy, dir, ide, tmp);
				if (CP.lptn[hash][len][side][cnt]>tmp) {
					T1sum[type[xx][yy][ide][dir]][ide]--;
					type[xx][yy][ide][dir] = CP.lptn[hash][len][side][cnt];
					T1sum[type[xx][yy][ide][dir]][ide]++;
					Update_T4(xx, yy, ide);
				}
			}

		//正方向一侧对方棋型更新
		if (step == 3 && dir == 2)
			dir = 2;
		sx = x - dx;
		sy = y - dy;
		side = 1; len = 0; hash = 0;
		for (int i = 0; i < 9; i++) {
			if (board[sx][sy] == ide || board[sx][sy] == -1) break;
			hash += (board[sx][sy] == opide) << i;
			sx -= dx, sy -= dy, len++;
		}

		if (board[sx][sy] == ide || board[sx][sy] == -1)
			side ^= 2;
		for (int xx = x - dx, yy = y - dy, cnt = 0; xx != sx || yy != sy; xx -= dx, yy -= dy, cnt++)
			if (board[xx][yy] == 2 && cnt < 4) {
				t_rec[step][++t_rec_num[step]] = Type_rec(xx, yy, dir, opide, type[xx][yy][opide][dir]);
				T1sum[type[xx][yy][opide][dir]][opide]--;
				type[xx][yy][opide][dir] = CP.lptn[hash][len][side][len - cnt];
				T1sum[type[xx][yy][opide][dir]][opide]++;
				Update_T4(xx, yy, opide);
			}

		//负方向一侧对方棋型更新
		ex = x + dx;
		ey = y + dy;
		side = 1; len = 0; hash = 0;
		for (int i = 0; i < 9; i++) {
			if (board[ex][ey] == ide || board[ex][ey] == -1) break;
			hash += (board[ex][ey] == opide) << i;
			ex += dx; ey += dy; len++;
		}
		if (board[ex][ey] == ide || board[ex][ey] == -1)
			side ^= 2;
		for (int xx = x + dx, yy = y + dy, cnt = 0; xx != ex || yy != ey; xx += dx, yy += dy, cnt++)
			if (board[xx][yy] == 2 && cnt < 4) {
				t_rec[step][++t_rec_num[step]] = Type_rec(xx, yy, dir, opide, type[xx][yy][opide][dir]);
				T1sum[type[xx][yy][opide][dir]][opide]--;
				type[xx][yy][opide][dir] = CP.lptn[hash][len][side][len - cnt];
				T1sum[type[xx][yy][opide][dir]][opide]++;
				Update_T4(xx, yy, opide);
			}

	}
	/*if (x == 5 && y == 6) {
	cout << 4;
	for (int i = 1; i <= t_rec_num[step]; i++)
	t_rec[step][i].print();
	}*/

	step++;

}
void Cboard::Revoke() {
	Cvpos pos = move_st[step - 1];
	if (pos.v < 3) {
		Wsum[pos.v][board[pos.x][pos.y]]--;
	}
	/*hash_val ^= h_tb.zob[pos.x][pos.y][board[pos.x][pos.y]];
	hash_val ^= h_tb.zob[pos.x][pos.y][EMPTY];*/

	board[pos.x][pos.y] = EMPTY;
	step--;
	for (int i = t_rec_num[step]; i; i--) {
		Type_rec tmp = t_rec[step][i];
		type[tmp.x][tmp.y][tmp.ide][tmp.d] = tmp.v;
		Update_T4(tmp.x, tmp.y, tmp.ide);
	}
	for (int i = 1; i <= 7; i++)
		T1sum[i][0] = T1sum_rec[step][i][0], T1sum[i][1] = T1sum_rec[step][i][1];
}
void Cboard::Update_T4(int x, int y, int ide) {
	/*int ti[4];
	for (int j = 0; j < 4; j++)
	ti[j] = type[x][y][ide][j];
	type4[x][y][ide] = CP.T4hash[ti[0]][ti[1]][ti[2]][ti[3]];*/
	type4[x][y][ide] = CP.T4hash[type[x][y][ide][0]][type[x][y][ide][1]][type[x][y][ide][2]][type[x][y][ide][3]];
}
void Cboard::Get_tlist() {
	for (int i = 0; i <= T4::QN1; i++)
		tlnum[step][0][i] = tlnum[step][1][i] = 0;
	memset(vlnum, 0, sizeof(vlnum));
	for (int i = 1, x; i <= size; i++)
		for (int j = 1; j <= size; j++) if (board[i][j] == 2){
			x = 0;
			if (type4[i][j][0])
				tlist[step][0][type4[i][j][0]][++tlnum[step][0][type4[i][j][0]]] = Cpos(i, j), x += (10 - type4[i][j][0]);
			if (type4[i][j][1])
				tlist[step][1][type4[i][j][1]][++tlnum[step][1][type4[i][j][1]]] = Cpos(i, j), x += (10 - type4[i][j][1]);
			if (x) vlist[x][++vlnum[x]] = Cpos(i, j);
		}
	/*for (int i = 1; i <= T4SIZE * 2; i++)
	printf_s("%d: %d\n",i,vlnum[i]);*/
}

//////////////////////////////////////////////////////////////////
//**************************************************************//
//**************************************************************//
//**************************************************************//
//**************************************************************//
//**************************************************************//
//////////////////////////////////////////////////////////////////
void Cboard::Init_timecol(){
	t_start = GetTickCount();
	t_pre = t_start;
	tend_VCTA = (turn_lim * 37) / 100 + t_start;
	tend_stree = (turn_lim * 72) / 100 + t_start;
	tend_VCTD = (turn_lim * 95) / 100 + t_start;

	t_remain1 = turn_lim * 15 / 100;
	t_remain2 = turn_lim * 15 / 100;


	t_end = t_start + turn_lim;
}
void Cboard::Time_pass() {
	cout << GetTickCount() - t_pre << endl;
	t_pre = GetTickCount();
}