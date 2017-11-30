#include "Hashitem.h"

ll Hash_table::llrand() {
	//rand();
	return rand() ^ ((ll)rand() << 15) ^ ((ll)rand() << 30) ^ ((ll)rand() << 45) ^ ((ll)rand() << 60);
}
ll Hash_table::Initzob(int size){
	ll hash_val = 0;
	for (int i = 1; i <= size; i++) for (int j = 1; j <= size; j++)
		for (int k = 0; k < 3; k++) {
			zob[i][j][k] = llrand(); //cout << zob[i][j][k] << endl;;
			if (k == 2) hash_val^zob[i][j][2];
		}
	return hash_val;
}
int Hash_table::Update(ll check_sum, int val, int base_dep, int index){
	/*ll tmp = (ll)bugnum;
	if (check_sum == tmp)
	tmp++, tmp--;*/
	if (base_dep == 3 && val == 18 && check_sum == (ll)5649018687047615704){
		index = 1;
	}
	htable[check_sum%HASH_SIZE].val = val;
	htable[check_sum%HASH_SIZE].check_sum = check_sum;
	htable[check_sum%HASH_SIZE].base_dep = base_dep;
	return val;
}
void Hash_table::InitTable() {
	for (int i = 0; i < HASH_SIZE; i++)
		htable[i].check_sum = 0;
}

int Hash_table::ProbeHash(ll check_sum, int base_dep, int alpha, int beta, int index){
	Hash_unit *tmp = &htable[index];
	if (tmp->check_sum == check_sum) if (tmp->base_dep == base_dep){
		if (tmp->flag == hash_EXACT)
			return tmp->val;
		if ((tmp->flag == hash_ALPHA) && (tmp->val <= alpha))
			return alpha;
		if ((tmp->flag == hash_BETA) && (tmp->val >= beta))
			return beta;
	}
	return val_UNKNOW;
}

void Hash_table::RecordHash(ll check_sum, int val, int base_dep, int flag, int index){
	Hash_unit *tmp = &htable[index];
	tmp->check_sum = check_sum;
	tmp->val = val;
	tmp->flag = flag;
	tmp->base_dep = base_dep;
}
