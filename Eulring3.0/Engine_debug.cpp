#include "Cboard.h"
int Cboard::satisfy() {
	if (!(move_st[3].x == 8 && move_st[3].y == 10)) return 0;
	if (!(move_st[4].x == 10 && move_st[4].y == 8)) return 0;
	if (!(move_st[5].x == 7 && move_st[5].y == 8)) return 0;
	if (!(move_st[6].x == 8 && move_st[6].y == 7)) return 0;
	if (!(move_st[7].x == 7 && move_st[7].y == 9)) return 0;

	return 1;
}
void Cboard::Debug_func1() {
	Put_piece(7, 7);

	/*Print_board();
	for (int i = 1; i <= 7; i++) {
	CP.Print_t1name(i);
	printf_s(":   %d , %d\n", t1sum[i][0], t1sum[i][1]);
	}*/

	ll t1 = GetTickCount();
	for (int i = 1; i <= 100000; i++) {
		Put_piece(9, 9);
		Get_tlist();
		Revoke();
	}
	ll t2 = GetTickCount();
	cout << t2 - t1 << endl;

	int x, y, z;
	while (true) {
		cin >> x;
		if (x == -1) {
			Revoke();
		}
		else if (x == 0) {
			Print_board(); continue;
		}
		else if (x == -2) {
			for (int i = 1; i <= 3; i++){
				printf_s("%d,%d\n", Wsum[i][0], Wsum[i][1]);
			}
			continue;
		}
		else if (x == -3) {
			Get_tlist(); Print_tlist();
			continue;
		}
		else if (x == -4) {
			for (int i = 1; i <= 7; i++) {
				CP.Print_t1name(i);
				printf_s(":   %d , %d\n", T1sum[i][0], T1sum[i][1]);
			}
		}
		else {
			cin >> y;
			Put_piece(x, y);
		}

	}



}

void Cboard::Print_board() {
	puts("");
	char s[22] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '1', '2', '3', '4', '5', '6' };
	cout << "  ";
	for (int i = 1; i <= size; i++)  cout << " " << s[i % 10];
	puts("");
	for (int i = 1; i <= size; i++){
		printf_s("%c ", s[i]);
		for (int j = 1; j <= size; j++) {
			if (board[i][j] == 2) printf_s("  ");
			else if (board[i][j] == 1) printf(" x");
			else printf(" o");
		}
		puts("");
	}
}

void Cboard::Print_plat_board() {
	char s[22] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '1', '2', '3', '4', '5', '6' };
	cout << "  ";
	for (int i = 0; i < size; i++)  cout << " " << s[i % 10];
	puts("");
	for (int i = 1; i <= size; i++){
		printf_s("%c ", s[i - 1]);
		for (int j = 1; j <= size; j++) {
			if (board[i][j] == 2) printf_s("  ");
			else if (board[i][j] == 1) printf(" x");
			else printf(" o");
		}
		puts("");
	}
}
void Cboard::Print_singletype(int x, int y, int ide) {
	printf_s("(%d,%d)_%d: ", x, y, ide);
	for (int i = 0; i < 4; i++)
		CP.Print_t1name(type[x][y][ide][i]), cout << " ";
	puts("");
}
void Cboard::Print_singletype4(int x, int y, int ide) {
	printf_s("%d %d: ", x, y);
	CP.Print_t4name(type4[x][y][ide]);
	puts("");
}
void Cboard::Print_alltype(){
	for (int i = 1; i <= size; i++)
		for (int j = 1; j <= size; j++)
			for (int k = 0; k < 2; k++) {
				int sum = 0;
				for (int l = 0; l < 4; l++)
					sum += type[i][j][k][l];
				if (sum == 0) continue;
				Print_singletype(i, j, k);
			}
}
void Cboard::Print_tlist() {
	Cpos tmp;
	int cnt = 0;
	for (int i = T4::W0; i <= T4::QN1; i++) {
		CP.Print_t4name(i);  puts(":");  cnt = 0;
		for (int j = 1; j <= tlnum[step][1][i]; j++, cnt++) {
			tmp = tlist[step][1][i][j];
			printf_s(" (%d,%d_x)  : ", tmp.x, tmp.y);
			if (cnt % 5 == 4) puts("");
		}
		for (int j = 1; j <= tlnum[step][0][i]; j++, cnt++) {
			tmp = tlist[step][0][i][j];
			if (cnt % 5 == 4) puts("");
			printf_s(" (%d,%d_o)  : ", tmp.x, tmp.y);
		}
		cout << endl << endl;
	}
}