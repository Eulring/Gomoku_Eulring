#include "Header.h"
#include "Cpattern.h"


void Cpattern::Init(){
	Get_bptn();
	Get_ptn();
	Get_lptn();
	Get_T4hash();
	//Print_lptn();
	//Debug_print();
}
void Cpattern::Get_bptn() {
	int hash, v;

	//Q5
	v = Q5;
	hash = 1 << 5; hash--;
	bptn[hash^OO] = v;
	bptn[hash^XO] = v;
	bptn[hash^OX] = v;
	bptn[hash^XX] = v;

	//Q4F
	v = Q4F;
	hash = 1 << 4; hash--;  //_oooo
	bptn[hash^OO] = v;
	bptn[hash^XO] = v;
	hash <<= 1;   //oooo_
	bptn[hash^OO] = v;
	bptn[hash^OX] = v;

	//Q4
	v = Q4;
	for (int i = 0; i < (1 << 7); i++) if (bptn[i] == Q5){
		for (int j = 0; j < 5; j++) {
			hash = i - (1 << j);
			if (bptn[hash] == Q4F) continue;
			bptn[hash] = v;
		}
	}

	//Q3F
	v = Q3F;
	for (int i = 0; i < (1 << 7); i++) if (bptn[i] == Q4F) {
		for (int j = 0; j < 5; j++) if (i&(1 << j)) {
			hash = i - (1 << j);
			if (bptn[hash]) continue;
			bptn[hash] = v;
		}
	}
	//
	//Q3
	v = Q3;
	for (int i = 0; i < (1 << 7); i++) if (bptn[i] == Q4) {
		for (int j = 0; j < 5; j++) if (i&(1 << j)) {
			hash = i - (1 << j);
			if (bptn[hash]) continue;
			bptn[hash] = v;
		}
	}

	//Q2F
	v = Q2F;
	for (int i = 0; i < (1 << 7); i++) if (bptn[i] == Q3F) {
		for (int j = 0; j < 5; j++) if (i&(1 << j)) {
			hash = i - (1 << j);
			if (bptn[hash]) continue;
			bptn[hash] = v;
		}
	}

	//Q2
	v = Q2;
	for (int i = 0; i < (1 << 7); i++) if (bptn[i] == Q3) {
		for (int j = 0; j < 5; j++) if (i&(1 << j)) {
			hash = i - (1 << j);
			if (bptn[hash]) continue;
			bptn[hash] = v;
		}
	}

}
void Cpattern::Get_ptn() {
	for (int i = 0; i < (1 << 7); i++) {
		for (int j = 0; j < 5; j++) if (i&(1 << j))
			ptn[i - (1 << j)][5 - j] = bptn[i];
	}
}


//lptn[hash][len][side][pos]
//对于side，左边高位，右边低位 如： xo=2+0  ox=0+1
//对于hash 如果从左至右为 oo_o_ 直接以二进制11010的值26表示
void Cpattern::Get_lptn() {
	int line[22];
	int hash_mid, hash_side, hash;
	memset(lptn, 0, sizeof(lptn));
	for (int len = 5; len < 10; len++) for (int lside = 0; lside < 4; lside++){
		line[0] = lside / 2; line[len + 1] = lside % 2;
		for (int lhash = (1 << len) - 1; lhash; lhash--) {
			int tmp = lhash;
			for (int l = 0; l < len; l++)
				line[len - l] = tmp % 2, tmp >>= 1;
			hash_mid = hash_side = 0;

			for (int i = 1; i <= 5; i++)
				hash_mid <<= 1, hash_mid += line[i];

			for (int i = 0; i <= len - 5; i++){
				hash_side = 0;
				if (i == 0 && line[i] == 1) hash_side = 2;
				/*if (len == 7 && lside == 1&&i==len-5)
				lside = 1;*/
				if (i == len - 5 && line[i + 6] == 1)  hash_side++;
				hash_side <<= 5;
				hash = hash_side + hash_mid;
				for (int j = 1; j <= 5; j++) if (line[i + j] == 0)
					if (ptn[hash][j]>lptn[lhash][len][lside][j + i])
						lptn[lhash][len][lside][j + i] = ptn[hash][j];
				hash_mid <<= 1;
				hash_mid += line[i + 6];
				hash_mid %= (1 << 5);
			}
		}
	}
}
//*****************************************************************************//
//*****************************************************************************//
//*****************************************************************************//
//*****************************************************************************//
//*****************************************************************************//
void Cpattern::Debug_print() {
	ll t1, t2;
	int d[11], sum = 0;
	t1 = GetTickCount();

	t2 = GetTickCount();
	cout << t2 - t1 << endl;

	t1 = GetTickCount();

	t2 = GetTickCount();
	cout << t2 - t1 << endl;
}
void Cpattern::Print_ptn() {
	for (int i = 0; i < (1 << 7); i++) {
		int x = i >> 5; x <<= 5;
		Print_Q(i, x, 5);
		for (int j = 1; j <= 5; j++)
			Print_t1name(ptn[i][j]);
		puts("");
	}
}
void Cpattern::Print_lptn() {
	for (int len = 7; len <= 7; len++) {
		for (int hash = (1 << len); hash; hash--) {
			Print_Q(hash, XX, len);
			for (int i = 1; i <= len; i++)
				Print_t1name(lptn[hash][len][3][i]);
			puts("");
		}
	}
}
void Cpattern::Print_bptn() {
	int hash;
	for (int i = 0; i < (1 << 5); i++) {
		hash = i^OO;
		Print_Q(i, OO, 5); Print_t1name(bptn[hash]); puts("");
		hash = i^OX;
		Print_Q(i, OX, 5); Print_t1name(bptn[hash]); puts("");
		hash = i^XO;
		Print_Q(i, XO, 5); Print_t1name(bptn[hash]); puts("");
		hash = i^XX;
		Print_Q(i, XX, 5); Print_t1name(bptn[hash]); puts("");
	}
}
void Cpattern::Print_Q(int mid, int side, int len) {
	if (side == XO || side == XX) cout << "x ";
	else cout << "_ ";
	for (int i = len - 1; i >= 0; i--) {
		if (mid&(1 << i)) cout << "o";
		else cout << "_";
	}
	if (side == XX || side == OX) cout << " x";
	else cout << " _";
	cout << " : ";
}
void Cpattern::Print_t1name(int val) {
	if (val == T1::Q2) cout << " Q2 ";
	else if (val == T1::Q2F) cout << " Q2F";
	else if (val == T1::Q3) cout << " Q3 ";
	else if (val == T1::Q3F) cout << " Q3F";
	else if (val == T1::Q4) cout << " Q4 ";
	else if (val == T1::Q4F) cout << " Q4F";
	else if (val == T1::Q5) cout << " Q5 ";
	else if (val == T1::Qn) cout << " Qn ";
	else cout << " __ ";
}
void Cpattern::Print_t4name(int val) {
	if (val == T4::QN1) cout << " QN1";
	else if (val == T4::QN2) cout << " QN2";
	else if (val == T4::QN3) cout << " QN3";
	else if (val == T4::QN4) cout << " QN4";
	else if (val == T4::Q3F) cout << " Q3F";
	else if (val == T4::Q4) cout << " Q4 ";
	else if (val == T4::W0) cout << " W0 ";
	else if (val == T4::W1) cout << " W1 ";
	else if (val == T4::W2) cout << " W2 ";
	else cout << " __ ";
}


