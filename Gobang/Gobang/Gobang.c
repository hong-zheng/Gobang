#define _CRT_SECURE_NO_WARNINGS 1
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define MAX_ROW 14
#define MAX_COL 14
#define EOR 5
#define YU 10
int menu(){
	printf("********************\n");
	printf("***   1、游戏    ***\n");
	printf("***   0、退出    ***\n");
	printf("********************\n");
	printf("给出你的选择:>");
	int choice = 0;
	scanf("%d",&choice);
	return choice;
}
int CHIOCE(){
	printf("*********************\n");
	printf("**** 0、人机对战 ****\n");
	printf("**** 1、人人对战 ****\n");
	printf("*********************\n");
	int choice = 0;
	printf("请做出你的选择:>\n");
	scanf("%d", &choice);
	return choice;
}
void Init(char chessBoard[MAX_ROW][MAX_COL]){
	srand((unsigned int)time(NULL));
	memset(chessBoard, ' ', MAX_ROW*MAX_COL*sizeof(char));
}
void Print(char chessBoard[MAX_ROW][MAX_COL]){
	printf("    ");
	for (int col = 0; col < MAX_COL; col++){
		if (col + 1<10){
			printf(" 0%d ", col + 1);
		}
		else{
			if ((MAX_COL - 1) == col){
				printf(" %d\n", col + 1);
				break;
			}
			printf(" %d ", col + 1);
		}
	}
	for (int row = 0; row < MAX_ROW; row++){
		printf("    ");
		for (int col = 0; col <= MAX_COL; col++){
			if (MAX_COL == col){
				printf("+\n");
				break;
			}
			printf("+---");
		}
		if (row + 1<10){
			printf(" 0%d ", row + 1);
		}
		else{
			printf(" %d ", row + 1);
		}

		for (int col = 0; col <= MAX_COL; col++){
			if (MAX_COL == col){
				printf("|\n");
				break;
			}
			printf("| %c ", chessBoard[row][col]);
		}
	}
	printf("    ");
	for (int col = 0; col <= MAX_COL; col++){
		if (MAX_COL == col){
			printf("+\n");
			break;
		}
		printf("+---");
	}
}

void ComputerMove(char chessBoard[MAX_ROW][MAX_COL]){
	int row = 0;
	int col = 0;
	while (1){
		row = rand() % MAX_ROW;
		col = rand() % MAX_COL;
		if (' ' != chessBoard[row][col]){
			continue;
		}
		break;
	}
	chessBoard[row][col] = 'O';
	Print(chessBoard);
	printf("电脑已走!\n");
	printf("电脑走的位置为(%d,%d)\n",row+1,col+1);
}
char isFull(char chessBoard[MAX_ROW][MAX_COL]){
	for (size_t row = 0; row < MAX_ROW;row++){
		for (size_t col = 0; col < MAX_COL;col++){
			if (' ' == chessBoard[row][col]){
				return ' ';
			}
		}
	}
}
char isWin(char chessBoard[MAX_ROW][MAX_COL]){
	// 以一个子为例
	// 1、检验行
	// 2、检验列
	// 3、检验对角线

	// 先判断一行
	// 以一行的一个元素作为标准，
	// 一个一个向右比对，相邻一样则记录
	// 然后count++,如果为5，则记录为胜
	for (int row = 0; row < MAX_ROW;row++){
		//              0 --> 13  7 8 9 10 11 12 13
		//                 10 
		for (int col = 0; col < MAX_COL;col++){
			int ccol = col; // 10
			char cur = chessBoard[row][col];
			if (' ' != cur){
				int count = 0;
				//              1 2 3 4 5 6
				// 9 10 11 12 13      9+5=14
				for (int curj = ccol; curj<ccol + EOR; curj++){
					if (chessBoard[row][curj] == cur){
						count++;
					}
					if (EOR == count){
						return cur;
					}
				}
			}
		}
	}

	// 检验列赢
	for (int col = 0; col < MAX_COL;col++){
		for (int row = 0; row < MAX_ROW;row++){
			int crow = row; // 10
			char cur = chessBoard[crow][col];
			if (' ' != cur){
				int count = 0;
				//              1 2 3 4 5 6
				// 9 10 11 12 13      9+5=14
				for (int curi = crow; curi<crow + EOR; curi++){
					if (chessBoard[curi][col] == cur){
						count++;
					}
					if (EOR == count){
						return cur;
					}
				}
			}
		}
	}

	// 判断对角线
	for (int row = 0; row < MAX_ROW;row++){
		for (int col = 0; col < MAX_COL;col++){
			int crow = row;
			int ccol = col;
			int cur = chessBoard[row][col];
			int count = 0;
			if (' ' != cur){
				for (int curij = 0; curij < EOR;curij++){
					if (chessBoard[crow+curij][ccol+curij] == cur){
						count++;
					}
					if (EOR == count){
						return cur;
					}
				}
			}
		}
	}
	//判断' ' 为继续游戏
	if (' ' == isFull(chessBoard)){
		return ' ';
	}
	return 'Q';
}
char Role(){
	printf("您好，请选择你需要充当的角色(X,O):>\n");
	//char role = ' ';
	//scanf("%c",&role);
	char ch = ' ';
	//gets(&ch);
	////ch = getchar();

	// scanf 的运行机制是先判断缓冲区是否有内容再读入键入，因此可以选择fflush(stdin)
	//setbuf(stdin,NULL)
	//setbuf(stdin, NULL); (这个windows和linux下都可以)
    fflush(stdin); //(这个只能windows)；
	//setbuf(stdin, NULL);
	scanf("%c", &ch);
	int role1 = rand() % YU;
	int role2 = rand() % YU;
	//printf("%d %d\n",role1,role2);
	char winner = role1 > role2 ? 'X' : 'O';
	printf("请玩家%c先下子!\n", winner);
	return winner;
}


// 设置悔棋模式，如果键入(0 0)就悔棋
void Regret(char chessBoard[MAX_ROW][MAX_COL], int row, int col){
	chessBoard[row][col] = ' ';
}
static int last_row = 0;
static int last_col = 0;
char PlayerMove(char chessBoard[MAX_ROW][MAX_COL], char role){
	if ('H' == role){
		printf("轮到你下子:>\n");
	}else{
		if (last_row <= MAX_ROW && last_row > 0 && last_col <= MAX_COL && last_col > 0){
			printf("对手%c落子为(%d,%d)\n", 'X' == role ? 'O' : 'X', last_row, last_col);
		}
		printf("轮到%c下子:>\n", role);
	}
	int row = 0;
	int col = 0;
	while (1){
		setbuf(stdin, NULL);
		scanf("%d %d", &row, &col);
		//if (0 == row && 0 == col){
		//	role = 'X' == role ? 'O' : 'X';
		//	printf("准许玩家%c悔棋,请%c重新落子:>\n", role, role);
		//	//                2 4 
		//	Regret(chessBoard, last_row, last_col);
		//	continue;
		//}
		if (col <= 0 || col > MAX_ROW || row <= 0 || row > MAX_COL){
			printf("输入不合法，重新输入:>\n");
			continue;
		}
		if (' ' != chessBoard[row - 1][col - 1]){
			printf("此处已有址，请重新输入:>\n");
			continue;
		}
		break;
	}
	last_row = row ;
	last_col = col ;
	chessBoard[row - 1][col - 1] = role;
	return role;
}
int main(){
	char chessBoard[MAX_ROW][MAX_COL];
	while (1){
		int choice = menu();
		if (1 == choice){
			char ret = ' ';
			Init(chessBoard);
			int inside_chioce = CHIOCE();
			// 人机对战
			if (0 == inside_chioce){
				char role = 'H';
				Print(chessBoard);
				while (1){
					PlayerMove(chessBoard,role);
					ret = isWin(chessBoard);
					if (' ' != ret){
						break;
					}
					ComputerMove(chessBoard);
					ret = isWin(chessBoard);
					if (' ' != ret){
						break;
					}
				}
				Print(chessBoard);
				if ('X' == ret){
					printf("恭喜，你赢了！\n");
				}
				else if ('O' == ret){
					printf("憨憨，电脑赢\n");
				}
				else{
					printf("憨憨，平局！\n");
				}
			// 人人对战
			}else if (1 == inside_chioce){
				//1、 选择角色，'X' 'O',一人选择X，另外一人默认为O，反之亦然,系统会根据你的角色判断你先走还是后走
				//2、 X 走
				//3、 判断X是否已赢
				//4、 O 走

				//5、 判断O是否已赢
				//6、 回到2，继续循环

				// 选角色
				char role=Role();
				Print(chessBoard);
				int flag = 0; // flag 为0 时是在选角色，刚进入游戏 
				while (1){
					PlayerMove(chessBoard, role);
					ret = isWin(chessBoard);
					if (' ' != ret){
						break;
					}
					Print(chessBoard);
					role = ('X' == role) ? 'O' : 'X';
				    PlayerMove(chessBoard,role);
					ret = isWin(chessBoard);
					if (' ' != ret){
						break;
					}
					Print(chessBoard);
					role = ('X' == role) ? 'O' : 'X';
				}
				Print(chessBoard);
				if ('X' == ret){
					printf("恭喜玩家'X'赢得此场比赛！\n");
				}
				else if ('O' == ret){
					printf("恭喜玩家'O'赢得此场比赛！\n");
				}else{
					printf("两位憨憨，平局！\n");
				}
			}
		}else if(0 == choice){
			printf("退出游戏！\n");
			break;
		}
	}
	// 初始化
	// 打印
	// 玩家走
	// 判断玩家是否获胜
	// 电脑走
	// 判断电脑是否获胜
	// 重复以上步骤
	system("pause");
	return 0;
}
//
//// 测试
//#define _CRT_SECURE_NO_WARNINGS 1
//#include<stdlib.h>
//#include<stdio.h>
//void Role(){
//	char ch = ' ';
//	//scanf("%c", &ch);
//	gets(&ch);
//	puts(&ch);
//}
//int main(){
//	Role();
//	system("pause");
//	return 0;
//}