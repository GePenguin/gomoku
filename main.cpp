//设计五子棋小游戏
//以二维数组作为棋盘，+代表空，X代表黑方，O代表白方

#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

#define PII pair<int,int>

const int N=22;//棋盘的长宽为N-2，即去掉两个边后的长度

class panel {
public:
	char size[N][N];

	void initial() {
		memset(size, '+', sizeof size);
		memset(size[0], '-', sizeof size[0]);
		memset(size[N-1],'-',sizeof size[N-1]);
		for(int i=1;i<N-1;i++){
			size[i][0]='|';
			size[i][N-1]='|';
		}
	}//初始化棋盘

	void print() {
		printf("    ");
		for (int i = 1; i <= 20; i++)
			printf("%c ", i + 96);
		printf("\n");
		for (int i = 0; i < N; i++) {
			if (i >= 1 && i <= 9) printf("%c ", i + 96);
			else if (i > 9 && i <= 20) printf("%c ", i + 96);
			else printf("  ");
			for (int j = 0; j < N; j++) {
				printf("%c ", size[i][j]);
			}
			printf("\n");
		}
	}//打印棋盘

};//定义棋盘类

class player {
public:
		string name;
		panel* p;
		char type;//X:代表黑方，O：代表白方
		vector<PII> q;//存储已经下过的棋的坐标；
		bool judgment() {//判胜原理：遍历已经下过的点，每个点都判断是否垂线、水平线、正对角线、反对角线有连续的5个相同色的棋
			for (int i = 0; i < this->q.size(); i++) {
				
				int stx[] = { 0,0,1,-1,1,-1,-1,1 }, sty[] = { 1,-1,0,0,1,-1,1,-1 };//右，左，下，上，右下，左上，右上，左下；
				PII t = this->q[i];
				int x = t.first, y = t.second;
				int sum_T = 1, sum_P = 1, sum_Z = 1, sum_F = 1;//记录每条线上的连续同色棋个数
				int x_S = x, y_S = y, x_X= x, y_X = y, x_Z = x, y_Z = y, x_Y = x, y_Y = y;
				int x_ZS = x, y_ZS = y, x_ZX = x, y_ZX = y, x_YS = x, y_YS = y, x_YX = x, y_YX = y;
				while (this->p->size[x_S + stx[3]][y_S + sty[3]] == this->type) {
					sum_T++;
					x_S += stx[3];
					y_S += sty[3];
				}//该棋上方的棋有多少个连续的同色棋
				while (this->p->size[x_X + stx[2]][y_X + sty[2]] == this->type) {
					sum_T++;
					x_X += stx[2];
					y_X += sty[2];
				}//该棋下方的棋有多少个连续的同色棋
				if (sum_T >= 5) return 1;
				while (this->p->size[x_Z + stx[1]][y_Z + sty[1]] == this->type) {
					sum_P++;
					x_Z += stx[1];
					y_Z += sty[1];
				}//该棋左方的棋有多少个连续的同色棋
				while (this->p->size[x_Y + stx[0]][y_Y + sty[0]] == this->type) {
					sum_P++;
					x_Y += stx[0];
					y_Y += sty[0];
				}//该棋右方的棋有多少个连续的同色棋
				if (sum_P >= 5) return 1;
				while (this->p->size[x_ZS + stx[5]][y_ZS + sty[5]] == this->type) {
					sum_F++;
					x_ZS += stx[5];
					y_ZS += sty[5];
				}//该棋左上方的棋有多少个连续的同色棋
				while (this->p->size[x_YX + stx[4]][y_YX + sty[4]] == this->type) {
					sum_F++;
					x_YX += stx[4];
					y_YX += sty[4];
				}//该棋右下方的棋有多少个连续的同色棋
				if (sum_F >= 5) return 1;
				while (this->p->size[x_ZX + stx[7]][y_ZX + sty[7]] == this->type) {
					sum_Z++;
					x_ZX += stx[7];
					y_ZX += sty[7];
				}//该棋左下方的棋有多少个连续的同色棋
				while (this->p->size[x_YS + stx[6]][y_YS + sty[6]] == this->type) {
					sum_Z++;
					x_YS += stx[6];
					y_YS += sty[6];
				}//该棋右上方的棋有多少个连续的同色棋
				if (sum_Z >= 5) return 1;
			}
			return 0;//所有点都遍历一遍后，没有连成5个的返回0
		}

		void set(panel* p) {
			while (1) {
				char x, y;//x是行坐标（纵坐标），y是列坐标（横坐标）
				cout << "输入棋子的横纵坐标：";
				cin >> y >> x;
				if (x >= 'a' && x <= N - 2+96 && y >= 'a' && y <= N - 2+96 && p->size[x-96][y-96] == '+') {
					p->size[x-96][y-96] = this->type;
					int a = x - 96, b = y - 96;
					this->q.push_back({ a,b });
					break;
				}
				else {
					cout << "该坐标不合法或已有棋子" << endl;
					continue;
				}
			}
		}

		void initial() {
			this->q.clear();
		}
};//定义玩家类

int main() {
	panel p1;
	p1.size[0][0] = {'+'};
	player a,b;
	
	a.q = { {0,0} };
	a.name = "Li_he";
	a.p=&p1;
	a.type = 'X';
	b.q = { {0,0} };
	b.name = "Zhang_yuntian";
	b.p =&p1;
	b.type = 'O';

	while (1) {
		int sum = 0;//判断和棋，即当下棋数等于400时，仍未出胜负即为和棋；
		a.initial();
		b.initial();
		p1.initial();
		p1.print();
		while (1) {
			cout << "黑方选手请出手下棋：";
			a.set(a.p);
			sum++;
			p1.print();
			if (a.judgment()) {
				cout << "黑方选手" << a.name << "胜出，比赛结束!" << endl;
				break;
			}
			cout << "白方选手请出手下棋：";
			b.set(b.p);
			sum++;
			p1.print();
			if (b.judgment()) {
				cout << "白方选手" << b.name << "胜出，比赛结束！" << endl;
				break;
			}
			if (sum == 400) {
				cout << "两位势均力敌，和棋了！" << endl;
				break;
			}
		}
		
		cout << "退出游戏，请输入\'T\'；继续游戏,输入任意其它字符。\n";
		char out ;
		cin >> out;
		if (out == 'T') {
			break;
		}
		else continue;
	}
	return 0;
}
