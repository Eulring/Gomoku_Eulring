#include "Cboard.h"

int Cboard::FS_AlphaBeta(int depth, int ide, int alpha, int beta) {
	dfs_counter++;
	int res, val, can_num = search_width2;

	if (Wsum[1][AIside]) return INF;
	if (Wsum[1][AIside ^ 1]) return -INF;
	Get_tlist();

	if (depth == 0) return Evaluate();


	Cpos can_st[100], tmp;
	Get_cans(can_st, can_num, ide ^ 1);



	if (ide == AIside ^ 1) {//极大节点
		res = -INF;
		for (int i = 1; i <= can_num; i++){
			tmp = can_st[i];

			Put_piece(tmp.x, tmp.y);
			val = FS_AlphaBeta(depth - 1, ide ^ 1, alpha, beta);
			Revoke();

			if (val >= res) {
				res = val;

				if (val >= alpha) alpha = val;
				if (val >= beta) break;
			}
			if (GetTickCount() > tend_stree) return val;
		}

		return alpha;
	}
	else {
		res = INF;
		for (int i = 1; i <= can_num; i++) {
			tmp = can_st[i];

			Put_piece(tmp.x, tmp.y);
			val = FS_AlphaBeta(depth - 1, ide ^ 1, alpha, beta);
			Revoke();

			if (val <= res) {
				res = val;

				if (val <= beta) beta = val;
				if (val <= alpha) break;
			}
			if (GetTickCount() > tend_stree) return val;
		}

		return beta;
	}

}


int Cboard::AlphaBeta(int depth, int ide, int alpha, int beta) {
	dfs_counter++;
	int hflag, index = hash_val%HASH_SIZE;
	int res, val, can_num = 12;
	/*if ((val = h_tb.ProbeHash(hash_val, base_step, alpha, beta, index)) != val_UNKNOW)
	return val;*/

	if (Wsum[1][AIside]) return INF;
	if (Wsum[1][AIside ^ 1]) return -INF;
	Get_tlist();
	if (depth == 0) return Evaluate();


	Cpos can_st[50], tmp;
	Get_cans(can_st, can_num, ide ^ 1);

	if (ide == AIside ^ 1) {
		hflag = hash_ALPHA;
		for (int i = 1; i <= can_num; i++) {
			tmp = can_st[i];
			Put_piece(tmp.x, tmp.y);
			val = AlphaBeta(depth - 1, ide ^ 1, alpha, beta);
			Revoke();

			if (val > alpha) {
				if (val > beta){
					h_tb.RecordHash(hash_val, beta, base_step, hash_BETA, index);
					return beta;
				}
				else alpha = val, hflag = hash_EXACT;
			}
		}

		h_tb.RecordHash(hash_val, alpha, base_step, hflag, index);
		return alpha;
	}
	else {
		hflag = hash_BETA;
		for (int i = 1; i <= can_num; i++) {
			tmp = can_st[i];
			Put_piece(tmp.x, tmp.y);
			val = AlphaBeta(depth - 1, ide ^ 1, alpha, beta);
			Revoke();

			if (val < beta) {
				if (val < alpha) {
					h_tb.RecordHash(hash_val, alpha, base_step, hash_ALPHA, index);
					return alpha;
				}
				else beta = val, hflag = hash_EXACT;
			}
		}

		h_tb.RecordHash(hash_val, beta, base_step, hflag, index);
		return beta;
	}

}