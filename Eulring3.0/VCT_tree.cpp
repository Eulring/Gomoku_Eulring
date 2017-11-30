#include "Cboard.h"

int Cboard::VCT_tree(Cpos &pos, int depth, int atk) {
	Get_tlist();
	/*if (step == 8&&depth==10) {
	Print_board();
	Print_tlist();
	}*/
	vct_counter = 0;
	int def = atk ^ 1;

	Cpos can_st[50], tmp;
	int can_num = 0;

	if (tlnum[step][atk][T4::W0]) {
		can_st[++can_num] = tlist[step][atk][T4::W0][1];
	}
	else if (tlnum[step][def][T4::W0]) {
		can_st[++can_num] = tlist[step][def][T4::W0][1];
	}
	else if (tlnum[step][atk][T4::W1]) {
		can_st[++can_num] = tlist[step][atk][T4::W1][1];
	}
	else if (tlnum[step][def][T4::W1]) {
		for (int i = 1; i <= tlnum[step][def][T4::W1]; i++)
			can_st[++can_num] = tlist[step][def][T4::W1][i];
		for (int i = 1; i <= tlnum[step][def][T4::Q4]; i++)
			can_st[++can_num] = tlist[step][def][T4::Q4][i];
		for (int i = 1; i <= tlnum[step][atk][T4::Q4]; i++)
			can_st[++can_num] = tlist[step][atk][T4::Q4][i];
		for (int i = 1; i <= tlnum[step][atk][T4::W2]; i++)
			can_st[++can_num] = tlist[step][atk][T4::W2][i];

	}
	else if (tlnum[step][atk][T4::W2]) {
		for (int i = 1; i <= tlnum[step][atk][T4::W2]; i++)
			can_st[++can_num] = tlist[step][atk][T4::W2][i];
	}
	else if (tlnum[step][def][T4::W2]) {
		if (tlnum[step][atk][T4::Q4])
			for (int i = 1; i <= tlnum[step][atk][T4::Q4]; i++)
				can_st[++can_num] = tlist[step][atk][T4::Q4][i];
		else {
			for (int i = 1; i <= tlnum[step][atk][T4::Q3F]; i++)
				can_st[++can_num] = tlist[step][atk][T4::Q3F][i];
			for (int i = 1; i <= tlnum[step][def][T4::W2]; i++)
				can_st[++can_num] = tlist[step][def][T4::W2][i];
		}
	}
	else  {
		for (int i = 1; i <= tlnum[step][atk][T4::Q4]; i++)
			can_st[++can_num] = tlist[step][atk][T4::Q4][i];
		for (int i = 1; i <= tlnum[step][atk][T4::Q3F]; i++)
			can_st[++can_num] = tlist[step][atk][T4::Q3F][i];
	}


	if (can_num == 0) return false;
	int res;
	for (int i = 1; i <= can_num; i++) {
		tmp = can_st[i];
		if (tmp.x == 9 && tmp.y == 14) {
			res = 0;
		}
		Put_piece(tmp.x, tmp.y);
		res = VCT_D(depth, atk, def);
		Revoke();

		if (res == true) {
			pos = tmp;
			return true;
		}
		if (GetTickCount() > tend_VCT)
			return false;
	}
	return false;
}
int Cboard::VCT_OPtree(Cpos &pos, Cpos move, int depth, int ide) {
	Put_piece(move.x, move.y);
	Cpos tmp;
	if (VCT_tree(tmp, depth, AIside ^ 1)) {
		Revoke();
		pos = tmp;
		return true;
	}
	Revoke();
	return false;
}
int Cboard::VCT_A(int depth, int atk, int def) {
	Get_tlist();
	vct_counter++;

	if (Wsum[1][def]) return false;

	Cpos can_st[50], tmp;
	int can_num = 0;

	if (tlnum[step][atk][T4::W0]) {
		can_st[++can_num] = tlist[step][atk][T4::W0][1];
	}
	else if (tlnum[step][def][T4::W0]) {
		can_st[++can_num] = tlist[step][def][T4::W0][1];
	}
	else if (tlnum[step][atk][T4::W1]) {
		can_st[++can_num] = tlist[step][atk][T4::W1][1];
	}
	else if (tlnum[step][def][T4::W1]) {
		if (tlnum[step][atk][T4::Q4])
			for (int i = 1; i <= tlnum[step][atk][T4::Q4]; i++)
				can_st[++can_num] = tlist[step][atk][T4::Q4][i];
		else {
			for (int i = 1; i <= tlnum[step][def][T4::W1]; i++)
				can_st[++can_num] = tlist[step][def][T4::W1][i];
			for (int i = 1; i <= tlnum[step][def][T4::Q4]; i++)
				can_st[++can_num] = tlist[step][def][T4::Q4][i];
			for (int i = 1; i <= tlnum[step][atk][T4::W2]; i++)
				can_st[++can_num] = tlist[step][atk][T4::W2][i];
		}

	}
	else if (tlnum[step][atk][T4::W2]) {
		for (int i = 1; i <= tlnum[step][atk][T4::W2]; i++)
			can_st[++can_num] = tlist[step][atk][T4::W2][i];
	}
	else if (tlnum[step][def][T4::W2]) {
		if (tlnum[step][atk][T4::Q4])
			for (int i = 1; i <= tlnum[step][atk][T4::Q4]; i++)
				can_st[++can_num] = tlist[step][atk][T4::Q4][i];
		else {
			for (int i = 1; i <= tlnum[step][atk][T4::Q3F]; i++)
				can_st[++can_num] = tlist[step][atk][T4::Q3F][i];
			for (int i = 1; i <= tlnum[step][def][T4::W2]; i++)
				can_st[++can_num] = tlist[step][def][T4::W2][i];
		}
	}
	else  {
		for (int i = 1; i <= tlnum[step][atk][T4::Q4]; i++)
			can_st[++can_num] = tlist[step][atk][T4::Q4][i];
		for (int i = 1; i <= tlnum[step][atk][T4::Q3F]; i++)
			can_st[++can_num] = tlist[step][atk][T4::Q3F][i];
	}




	if (can_num == 0) return false;
	int res;
	for (int i = 1; i <= can_num; i++) {
		tmp = can_st[i];
		Put_piece(tmp.x, tmp.y);
		res = VCT_D(depth - 1, atk, def);
		Revoke();

		if (res == true) return true;

		if (GetTickCount() > tend_VCT)
			return false;
	}
	return false;
}

int Cboard::VCT_D(int depth, int atk, int def) {
	Get_tlist();
	vct_counter++;
	if (Wsum[1][atk]) return true;
	if (depth == 0) return false;

	Cpos can_st[50], tmp;
	int can_num = 0;



	if (tlnum[step][def][T4::W0])
		can_st[++can_num] = tlist[step][def][T4::W0][1];
	else if (tlnum[step][atk][T4::W0])
		can_st[++can_num] = tlist[step][atk][T4::W0][1];
	else if (tlnum[step][def][T4::W1])
		can_st[++can_num] = tlist[step][def][T4::W1][1];
	else if (tlnum[step][atk][T4::W1]) {
		for (int i = 1; i <= tlnum[step][atk][T4::W1]; i++)
			can_st[++can_num] = tlist[step][atk][T4::W1][i];
		for (int i = 1; i <= tlnum[step][atk][T4::Q4]; i++)
			can_st[++can_num] = tlist[step][atk][T4::Q4][i];
		for (int i = 1; i <= tlnum[step][def][T4::Q4]; i++)
			can_st[++can_num] = tlist[step][def][T4::Q4][i];
		for (int i = 1; i <= tlnum[step][def][T4::W2]; i++)
			can_st[++can_num] = tlist[step][def][T4::W2][i];
	}
	else {
		for (int i = 1; i <= tlnum[step][atk][T4::W2]; i++)
			can_st[++can_num] = tlist[step][atk][T4::W2][i];
		if (can_num){
			for (int i = 1; i <= tlnum[step][def][T4::Q4]; i++)
				can_st[++can_num] = tlist[step][def][T4::Q4][i];
		}
	}



	if (can_num == 0) return false;
	int res;
	for (int i = 1; i <= can_num; i++) {
		tmp = can_st[i];
		Put_piece(tmp.x, tmp.y);
		res = VCT_A(depth - 1, atk, def);
		Revoke();
		if (res == false) return false;


		if (GetTickCount() > tend_VCT)
			return false;
	}
	return true;
}