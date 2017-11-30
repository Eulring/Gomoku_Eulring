#include "Header.h"
#include "Cpattern.h"
#include "Hashitem.h"
#include "Ctype.h"

/*
*/
class Cboard {
public:
	Cboard(){};

	//基础变量
	int size; //棋盘大小
	int step; //落子时前的步数
	int AIside; //AI所代表一方
	int dfs_counter; //搜索节点计数
	int board[MAX_SIZE][MAX_SIZE];
	int search_width1 = 15, search_width2 = 11;

	//时间控制模块
	ll t_start;
	ll t_end;
	ll t_now;
	ll t_remain1, t_remain2, t_remain3;
	ll turn_lim = TIME_TURN, TURN_LIM = TIME_TURN;
	ll tot_lim;
	ll tend_stree;
	ll tend_VCTA;
	ll tend_VCTD;
	ll tend_VCT;
	void Init_timecol();
	ll t_pre;
	void Time_pass();

	//基础函数
	void Init(int _size);
	void Set_side();
	void Put_piece(int x, int y);
	void Revoke();


	//置换表
	Hash_table h_tb;
	ll hash_val;
	int base_step;

	//棋型模块
	Cpattern CP;

	Cvpos move_st[400];                 //按顺序每一步落子的位置及是否是威胁棋型
	Type_rec t_rec[400][100];           //单点单行估值还原缓存
	int t_rec_num[400];                 //各棋层缓存数量

	int type[MAX_SIZE][MAX_SIZE][2][4]; //[..][..][ide][dir] 单点定向棋型 
	int type4[MAX_SIZE][MAX_SIZE][2];   // 单点综合棋型
	int T1sum[T1SIZE][2];
	int T1sum_rec[400][T1SIZE][2];
	int Wsum[3][2];                     //制胜棋型W0,W1统计
	Cpos tlist[400][2][T4SIZE][80];     //棋型到点的映射
	int tlnum[400][2][T4SIZE];          //各个棋型点的数量
	Cpos vlist[T4SIZE * 2][80];                //棋型价值到点的映射
	int vlnum[T4SIZE * 2];                     //棋型价值点的数量

	void Update_T4(int x, int y, int ide);
	void Get_tlist();

	//博弈树

	void AIgo(int &x, int &y);
	int Nece_move(Cpos &pos);
	int Search_tree(Cpos &pos, int depth);
	int FS_AlphaBeta(int depth, int ide, int alpha, int beta);
	int AlphaBeta(int depth, int ide, int alpha, int beta);
	void Get_cans(Cpos cans[], int &num, int ide);
	int eva_type = 3;
	int Evaluate();
	////VCT树
	int VCT_tree(Cpos &pos, int depth, int atk);
	int VCT_OPtree(Cpos &pos, Cpos move, int depth, int atk);
	int VCT_A(int depth, int atk, int def);
	int VCT_D(int depth, int atk, int def);
	int vct_counter;
	Cpos vct_pos;



	//debug 模块
	int bug_flag[10];
	void Print_board();
	void Print_plat_board();
	void Print_singletype(int x, int y, int ide);
	void Print_singletype4(int x, int y, int ide);
	void Print_alltype();
	void Print_tlist();

	void Debug_func1();
	int satisfy();



};