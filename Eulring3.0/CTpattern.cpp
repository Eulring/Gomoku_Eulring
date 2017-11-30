#include "Cpattern.h"

void Cpattern::Get_T4hash() {
	int cnt[11];
	memset(T4hash, 0, sizeof(T4hash));
	for (int a = 0; a <= T1::Q5; a++)
		for (int b = 0; b <= T1::Q5; b++)
			for (int c = 0; c <= T1::Q5; c++)
				for (int d = 0; d <= T1::Q5; d++) {
					memset(cnt, 0, sizeof(cnt));
					cnt[a]++; cnt[b]++; cnt[c]++; cnt[d]++;
					if (cnt[T1::Q5]) {
						T4hash[a][b][c][d] = T4::W0;
					}
					else if (cnt[T1::Q4F] || cnt[T1::Q4]>1) {
						T4hash[a][b][c][d] = T4::W1;
					}
					else if (cnt[T1::Q3F] && (cnt[T1::Q4] || cnt[T1::Q3F]>1)) {
						T4hash[a][b][c][d] = T4::W2;
					}
					else if (cnt[T1::Q4]){
						T4hash[a][b][c][d] = T4::Q4;
					}
					else if (cnt[T1::Q3F]) {
						T4hash[a][b][c][d] = T4::Q3F;
					}
					else {
						int nsum = cnt[T1::Q3] + cnt[T1::Q2F];
						if (nsum == 1) T4hash[a][b][c][d] = T4::QN1;
						if (nsum == 2) T4hash[a][b][c][d] = T4::QN2;
						if (nsum == 3) T4hash[a][b][c][d] = T4::QN3;
						if (nsum == 4) T4hash[a][b][c][d] = T4::QN4;
					}
				}


}