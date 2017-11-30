#include "Header.h"
//五子棋棋型相关类

//单点四线综合棋型
class T4 {
public:
	enum {

		QX = 0x00000000,
		//胜负点
		W0 = 0x00000001, //落子后成五
		W1 = 0x00000002, //落子后差一个子必定成五
		W2 = 0x00000003, //落子后差两个子必定成五
		//VCT有效
		Q4 = 0x00000004, //落子后冲四
		Q3F = 0x00000005, //落子后活三
		//VCT无效 Q2F或Q3叠加棋型
		QN4 = 0x00000006, //4次叠加
		QN3 = 0x00000007, //3次叠加
		QN2 = 0x00000008, //2次叠加
		QN1 = 0x00000009, //单次叠加

	};
};

//单点单线棋型
class T1 {
public:
	enum{
		QX = 0x00000000,
		Q2 = 0x00000001, //眠二：再走一着能够形成眠三
		Q2F = 0x00000002, //活二：再走一着能够形成活三
		Q3 = 0x00000003, //眠三：再走一着能够形成冲四
		Q3F = 0x00000004, //活三：再走一着能够形成活四
		Q4 = 0x00000005, //冲四：只有一个点能够成五
		Q4F = 0x00000006, //活四：有两个点能够成五
		Q5 = 0x00000007, //成五
		Qn = 0x00000008  //长连
	};
};
//class VT1{
//public:
//	enum{
//		VX  = 0x00000000,
//		V2  = 0x00000001, //眠二：再走一着能够形成眠三
//		V2F = 0x00000102, //活二：再走一着能够形成活三
//		V3  = 0x00000103, //眠三：再走一着能够形成冲四
//		V3F = 0x00010004, //活三：再走一着能够形成活四
//		V4  = 0x00010005, //冲四：只有一个点能够成五
//		V4F = 0x01000006, //活四：有两个点能够成五
//		V5  = 0x01000007, //成五
//		Vn  = 0x00000008  //长连
//	};
//};


class Cpattern {
public:
	enum{
		QX = 0x00000000,
		Q2 = 0x00000001,
		Q2F = 0x00000002,
		Q3 = 0x00000003,
		Q3F = 0x00000004,
		Q4 = 0x00000005,
		Q4F = 0x00000006,
		Q5 = 0x00000007,
		Qn = 0x00000008
	};
	//最高两位为边界两侧的棋型，末五位为中间五个基础棋型
	int bptn[(1 << 7)];
	//若此点为空，当落完子后形成的棋型值
	int ptn[(1 << 7)][6];
	//lptn[hash][len][side][position]
	int lptn[512][10][4][10];
	int T4hash[T1SIZE][T1SIZE][T1SIZE][T1SIZE];


	void Get_bptn();
	void Get_ptn();
	void Get_lptn();
	void Get_T4hash();
	void Init();

	//debug相关

	void Print_t1name(int val);
	void Print_t4name(int val);
	void Print_Q(int mid, int side, int len);
	void Print_bptn();
	void Print_lptn();
	void Print_ptn();
	void Debug_print();
};