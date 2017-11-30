#include "Header.h"
#include "Cpattern.h"
#include "Hashitem.h"
#include "Ctype.h"

/*
*/
class Cboard {
public:
	Cboard(){};

	//��������
	int size; //���̴�С
	int step; //����ʱǰ�Ĳ���
	int AIside; //AI������һ��
	int dfs_counter; //�����ڵ����
	int board[MAX_SIZE][MAX_SIZE];
	int search_width1 = 15, search_width2 = 11;

	//ʱ�����ģ��
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

	//��������
	void Init(int _size);
	void Set_side();
	void Put_piece(int x, int y);
	void Revoke();


	//�û���
	Hash_table h_tb;
	ll hash_val;
	int base_step;

	//����ģ��
	Cpattern CP;

	Cvpos move_st[400];                 //��˳��ÿһ�����ӵ�λ�ü��Ƿ�����в����
	Type_rec t_rec[400][100];           //���㵥�й�ֵ��ԭ����
	int t_rec_num[400];                 //����㻺������

	int type[MAX_SIZE][MAX_SIZE][2][4]; //[..][..][ide][dir] ���㶨������ 
	int type4[MAX_SIZE][MAX_SIZE][2];   // �����ۺ�����
	int T1sum[T1SIZE][2];
	int T1sum_rec[400][T1SIZE][2];
	int Wsum[3][2];                     //��ʤ����W0,W1ͳ��
	Cpos tlist[400][2][T4SIZE][80];     //���͵����ӳ��
	int tlnum[400][2][T4SIZE];          //�������͵������
	Cpos vlist[T4SIZE * 2][80];                //���ͼ�ֵ�����ӳ��
	int vlnum[T4SIZE * 2];                     //���ͼ�ֵ�������

	void Update_T4(int x, int y, int ide);
	void Get_tlist();

	//������

	void AIgo(int &x, int &y);
	int Nece_move(Cpos &pos);
	int Search_tree(Cpos &pos, int depth);
	int FS_AlphaBeta(int depth, int ide, int alpha, int beta);
	int AlphaBeta(int depth, int ide, int alpha, int beta);
	void Get_cans(Cpos cans[], int &num, int ide);
	int eva_type = 3;
	int Evaluate();
	////VCT��
	int VCT_tree(Cpos &pos, int depth, int atk);
	int VCT_OPtree(Cpos &pos, Cpos move, int depth, int atk);
	int VCT_A(int depth, int atk, int def);
	int VCT_D(int depth, int atk, int def);
	int vct_counter;
	Cpos vct_pos;



	//debug ģ��
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