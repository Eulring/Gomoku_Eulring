
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <Windows.h>
#include <queue>
using namespace std;

#define MAX_SIZE 33
#define BLACK 0
#define WHITE 1
#define EMPTY 2
#define INF 0x00010000


#define search_depth1 13
#define VCT_depth1 18
#define VCT_depth2 18

//HASH置换表相关
#define hash_EXACT 0
#define hash_ALPHA 1
#define hash_BETA 2
#define HASH_SIZE 1000007
#define val_UNKNOW 0x00100000

//棋型HASH表相关
#define XX 0x60
#define XO 0x40
#define OX 0x20
#define OO 0x00
#define T4SIZE 11
#define T1SIZE 10

//时间控制
#define TIME_TURN 5000
typedef unsigned long long ll;
