#include "Header.h"


struct Hash_unit {
	ll check_sum;
	int base_dep, val, flag;
};


class Hash_table {
public:
	Hash_unit htable[HASH_SIZE];

	ll zob[MAX_SIZE][MAX_SIZE][3];
	ll llrand();
	ll Initzob(int size);
	int Update(ll check_sum, int val, int base_dep, int index);

	int ProbeHash(ll check_sum, int base_dep, int alpha, int beta, int index);
	void RecordHash(ll check_sum, int val, int base_dep, int flag, int index);

	void InitTable();
};