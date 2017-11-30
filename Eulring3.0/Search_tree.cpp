#include "Cboard.h"

void Cboard::AIgo(int &x, int &y) {
	Init_timecol();
	if (step == 0) {
		x = (size + 1) / 2;
		y = (size + 1) / 2;
	}
	else if (step == 1) {
		x = move_st[0].x + 1;
		y = move_st[0].y;
	}
	else {

		Cpos tmp, tmp1;
		if (Nece_move(tmp)) {
			x = tmp.x;
			y = tmp.y;
			return;
		}
		//Search_tree(tmp, 5); x = tmp.x; y = tmp.y; return;

		//己方VCT
		tend_VCT = tend_VCTA;
		for (int depth = 8; depth <= VCT_depth1; depth += 2) {
			if (VCT_tree(tmp, depth, AIside)) {
				x = tmp.x;
				y = tmp.y;
				return;
			}
			if (tend_VCTA - GetTickCount() < t_remain1)
				break;
		}

		//博弈树搜索
		for (int depth = 6; depth <= search_depth1; depth++) {
			if (Search_tree(tmp, depth)) {
				x = tmp.x;
				y = tmp.y;
			}
			else break;

			if (tend_stree - GetTickCount() < t_remain2)
				break;
		}


		//判对方VCT
		tend_VCT = tend_VCTD;
		for (int depth = 8; depth <= VCT_depth2; depth += 2) {
			//cout << depth << endl;
			if (VCT_OPtree(tmp1, Cpos(x, y), depth, AIside ^ 1)) {
				x = tmp1.x;
				y = tmp1.y;
				//cout << "c" << endl;
				return;
			}
		}

	}
}

int Cboard::Search_tree(Cpos &pos, int depth) {
	dfs_counter = 0;
	Get_tlist();

	t_now = GetTickCount();
	if (t_now > tend_stree) return false;

	int can_num = search_width1;
	Cpos can_st[100], tmp;
	Get_cans(can_st, can_num, AIside);


	int ans = -INF - 1, val;
	//base_step = step+depth;
	//h_tb.InitTable();
	for (int i = 1; i <= can_num; i++) {
		tmp = can_st[i];
		Put_piece(tmp.x, tmp.y);

		val = FS_AlphaBeta(depth, AIside, ans, INF);
		//val = AlphaBeta(depth,AIside,-INF,INF);
		if (val > ans) ans = val, pos = tmp;
		Revoke();
		if (GetTickCount() > tend_stree) return false;
		//printf_s("(%d,%d): %d\n",tmp.x,tmp.y,val);
	}
	return true;
}

int Cboard::Nece_move(Cpos &pos) {
	Get_tlist();
	if (tlnum[step][AIside][T4::W0]){
		pos = tlist[step][AIside][T4::W0][1];
		return 1;
	}
	if (tlnum[step][AIside ^ 1][T4::W0]){
		pos = tlist[step][AIside ^ 1][T4::W0][1];
		return 1;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////
//**************************************************************//
//**************************************************************//
//**************************************************************//
//**************************************************************//
//**************************************************************//
//////////////////////////////////////////////////////////////////
void Cboard::Get_cans(Cpos cans[], int &num, int ide) {
	if (tlnum[step][ide][T4::W0]) {
		cans[1] = tlist[step][ide][T4::W0][1];
		num = 1; return;
	}
	else if (tlnum[step][ide ^ 1][T4::W0]) {
		cans[1] = tlist[step][ide ^ 1][T4::W0][1];
		num = 1; return;
	}
	else if (tlnum[step][ide][T4::W1]) {
		cans[1] = tlist[step][ide][T4::W1][1];
		num = 1; return;
	}
	else if (tlnum[step][ide ^ 1][T4::W1]) {
		int cnt = 0;
		for (int i = 1; i <= tlnum[step][ide ^ 1][T4::W1]; i++)
			cans[++cnt] = tlist[step][ide ^ 1][T4::W1][i];
		for (int i = 1; i <= tlnum[step][ide ^ 1][T4::Q4]; i++)
			cans[++cnt] = tlist[step][ide ^ 1][T4::Q4][i];
		for (int i = 1; i <= tlnum[step][ide][T4::Q4]; i++)
			cans[++cnt] = tlist[step][ide][T4::Q4][i];
		num = cnt; return;
	}
	else if (tlnum[step][ide][T4::W2]) {
		int cnt = 0;
		for (int i = tlnum[step][ide][T4::W2]; i; i--)
			cans[++cnt] = tlist[step][ide][T4::W2][i];
		for (int i = tlnum[step][ide ^ 1][T4::Q4]; i; i--)
			cans[++cnt] = tlist[step][ide ^ 1][T4::Q4][i];
		num = cnt;
		return;
	}
	else if (tlnum[step][ide ^ 1][T4::W2]) {
		int cnt = 0;
		for (int i = tlnum[step][ide ^ 1][T4::W2]; i; i--)
			cans[++cnt] = tlist[step][ide ^ 1][T4::W2][i];
		for (int i = tlnum[step][ide][T4::Q4]; i; i--)
			cans[++cnt] = tlist[step][ide][T4::Q4][i];
		for (int i = tlnum[step][ide][T4::Q3F]; i; i--)
			cans[++cnt] = tlist[step][ide][T4::Q3F][i];
		num = cnt;
		return;
	}
	else  {
		int cnt = 0;
		for (int i = 19; i >= 1 && cnt <= num; i--) {
			for (int j = 1; j <= vlnum[i] && cnt <= num; j++)
				cans[++cnt] = vlist[i][j];
		}
		num = cnt;
	}
}
//////////////////////////////////////////////////////////////////
//**************************************************************//
//**************************************************************//
//**************************************************************//
//**************************************************************//
//**************************************************************//
//////////////////////////////////////////////////////////////////
int Cboard::Evaluate() {
	int sum = 0, opide = AIside ^ 1;
	/*int ide = step % 2;
	if (ide == AIside&&VCT_A(4, AIside, opide)) return INF;
	if (ide == opide&&VCT_A(4, opide, AIside)) return -INF;*/

	if (T1sum[T1::Q5][AIside] == 1) sum += 1 << 11;
	else if (T1sum[T1::Q5][AIside] > 1) sum += (INF >> 1);

	if (T1sum[T1::Q4F][AIside] <= 2) sum += T1sum[T1::Q4F][AIside] << 9;
	else sum += INF >> 4;

	sum += T1sum[T1::Q4][AIside] << 6;
	sum += T1sum[T1::Q3F][AIside] << 5;
	sum += T1sum[T1::Q3][AIside] << 3;
	sum += T1sum[T1::Q2F][AIside];


	/////////////////////////


	if (T1sum[T1::Q5][opide] == 1) sum -= 1 << 11;
	else if (T1sum[T1::Q5][opide] > 1) sum -= (INF >> 1);

	if (T1sum[T1::Q4F][opide] <= 2) sum -= T1sum[T1::Q4F][opide] << 9;
	else sum -= INF >> 4;

	sum -= T1sum[T1::Q4][opide] << 6;
	sum -= T1sum[T1::Q3F][opide] << 5;
	sum -= T1sum[T1::Q3][opide] << 3;
	sum -= T1sum[T1::Q2F][opide];

	////////////////////////////

	/*if (tlnum[step][AIside][T4::W2]==1) sum +=INF >> 6;
	if (tlnum[step][AIside][T4::W2] > 1) sum += INF >> 4;
	if (tlnum[step][opide][T4::W2]==1) sum -= INF >> 6;
	if (tlnum[step][opide][T4::W2] > 1) sum -= INF >> 4;*/
	return sum;
}