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
	printf("***   1����Ϸ    ***\n");
	printf("***   0���˳�    ***\n");
	printf("********************\n");
	printf("�������ѡ��:>");
	int choice = 0;
	scanf("%d",&choice);
	return choice;
}
int CHIOCE(){
	printf("*********************\n");
	printf("**** 0���˻���ս ****\n");
	printf("**** 1�����˶�ս ****\n");
	printf("*********************\n");
	int choice = 0;
	printf("���������ѡ��:>\n");
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
	printf("��������!\n");
	printf("�����ߵ�λ��Ϊ(%d,%d)\n",row+1,col+1);
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
	// ��һ����Ϊ��
	// 1��������
	// 2��������
	// 3������Խ���

	// ���ж�һ��
	// ��һ�е�һ��Ԫ����Ϊ��׼��
	// һ��һ�����ұȶԣ�����һ�����¼
	// Ȼ��count++,���Ϊ5�����¼Ϊʤ
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

	// ������Ӯ
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

	// �ж϶Խ���
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
	//�ж�' ' Ϊ������Ϸ
	if (' ' == isFull(chessBoard)){
		return ' ';
	}
	return 'Q';
}
char Role(){
	printf("���ã���ѡ������Ҫ�䵱�Ľ�ɫ(X,O):>\n");
	//char role = ' ';
	//scanf("%c",&role);
	char ch = ' ';
	//gets(&ch);
	////ch = getchar();

	// scanf �����л��������жϻ������Ƿ��������ٶ�����룬��˿���ѡ��fflush(stdin)
	//setbuf(stdin,NULL)
	//setbuf(stdin, NULL); (���windows��linux�¶�����)
    fflush(stdin); //(���ֻ��windows)��
	//setbuf(stdin, NULL);
	scanf("%c", &ch);
	int role1 = rand() % YU;
	int role2 = rand() % YU;
	//printf("%d %d\n",role1,role2);
	char winner = role1 > role2 ? 'X' : 'O';
	printf("�����%c������!\n", winner);
	return winner;
}


// ���û���ģʽ���������(0 0)�ͻ���
void Regret(char chessBoard[MAX_ROW][MAX_COL], int row, int col){
	chessBoard[row][col] = ' ';
}
static int last_row = 0;
static int last_col = 0;
char PlayerMove(char chessBoard[MAX_ROW][MAX_COL], char role){
	if ('H' == role){
		printf("�ֵ�������:>\n");
	}else{
		if (last_row <= MAX_ROW && last_row > 0 && last_col <= MAX_COL && last_col > 0){
			printf("����%c����Ϊ(%d,%d)\n", 'X' == role ? 'O' : 'X', last_row, last_col);
		}
		printf("�ֵ�%c����:>\n", role);
	}
	int row = 0;
	int col = 0;
	while (1){
		setbuf(stdin, NULL);
		scanf("%d %d", &row, &col);
		//if (0 == row && 0 == col){
		//	role = 'X' == role ? 'O' : 'X';
		//	printf("׼�����%c����,��%c��������:>\n", role, role);
		//	//                2 4 
		//	Regret(chessBoard, last_row, last_col);
		//	continue;
		//}
		if (col <= 0 || col > MAX_ROW || row <= 0 || row > MAX_COL){
			printf("���벻�Ϸ�����������:>\n");
			continue;
		}
		if (' ' != chessBoard[row - 1][col - 1]){
			printf("�˴�����ַ������������:>\n");
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
			// �˻���ս
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
					printf("��ϲ����Ӯ�ˣ�\n");
				}
				else if ('O' == ret){
					printf("����������Ӯ\n");
				}
				else{
					printf("������ƽ�֣�\n");
				}
			// ���˶�ս
			}else if (1 == inside_chioce){
				//1�� ѡ���ɫ��'X' 'O',һ��ѡ��X������һ��Ĭ��ΪO����֮��Ȼ,ϵͳ�������Ľ�ɫ�ж������߻��Ǻ���
				//2�� X ��
				//3�� �ж�X�Ƿ���Ӯ
				//4�� O ��

				//5�� �ж�O�Ƿ���Ӯ
				//6�� �ص�2������ѭ��

				// ѡ��ɫ
				char role=Role();
				Print(chessBoard);
				int flag = 0; // flag Ϊ0 ʱ����ѡ��ɫ���ս�����Ϸ 
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
					printf("��ϲ���'X'Ӯ�ô˳�������\n");
				}
				else if ('O' == ret){
					printf("��ϲ���'O'Ӯ�ô˳�������\n");
				}else{
					printf("��λ������ƽ�֣�\n");
				}
			}
		}else if(0 == choice){
			printf("�˳���Ϸ��\n");
			break;
		}
	}
	// ��ʼ��
	// ��ӡ
	// �����
	// �ж�����Ƿ��ʤ
	// ������
	// �жϵ����Ƿ��ʤ
	// �ظ����ϲ���
	system("pause");
	return 0;
}
//
//// ����
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