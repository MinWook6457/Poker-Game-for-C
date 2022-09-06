/*
	comment : ī�� 5���� �̿��ϴ� ��Ŀ����(������ ������Ŀ�� ����)
	������ : SCH CSE 20194024 ��ο�(with ������)
*/
#include <time.h>//������ ���
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>//system ���
#include <conio.h> //getch ���
#pragma warning(disable:4996)
void rules()
{
	printf("�⺻���� ��Ŀ���� ������ �����Դϴ� ");
	printf("�� 5���� ī�带 ������ ������ �մϴ�.");
	printf("�⺻ ���� �ڱ��� 50000�� �Դϴ� ");
	printf("�÷��̾�� ������ ī�� 2���� ���� �Ǵ��� �Ͽ� ������ �����մϴ�.");
	printf("���ӿ��� �̱�ٸ� ���� �ڱݿ� ������ �ݾ��� 2�踸ŭ�� �߰��˴ϴ�. ");
	printf("���ӿ��� ���ٸ� ���� �ڱݿ� ������ �ݾ��� ���ϴ� ");
}

void red()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
}
void white()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void blue()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
}
int flag = 1;
int game_result;
int bet;

void gotoxy(int x, int y);
void display();
void card_screen(int x);
void cal(int a, int b, int c);
int num_check(int a[5][2], int b[5][2]);
void level_check1(void);
void level_check2(void);

int sum; // ���þ�
int money = 50000;
int count_bet = 1;
int show_bet = 66;
int k = 1; // ���� Ŀ�� ����

int com[5][2], ply[5][2], com_row, ply_row;//cal�Լ�, levelüũ �Լ� (����,�׸�����, �׸�����)
char num[13][3] = { "2","3","4","5","6","7","8","9","10","J","Q","K","A" }; // ��� ǥ���ϱ� ���� �ʿ�
int count1 = 0, count2 = 0, pair1[2], pair2[2], triple1 = 0, triple2 = 0, temp1, temp2; //level1,2üũ �Լ�
int fourcard1 = 0, fourcard2 = 0, flash1, flash2, strat1, strat2;//cal�Լ�, levelüũ �Լ�
float point1 = 0, point2 = 0; //levelüũ �Լ�,numüũ �Լ�
char shape[4][3] = { "��","��","��","��" }; //main�Լ�, cal �Լ�
void menu();

void main()
{
	menu();
	int card[4][13] = { 0 }, x;
	int column, row, count, i = 8, j = 8;

	while (1)
	{
		for (i = 0; i < 4; i++) // �ʱ�ȭ
		{
			for (j = 0; j < 13; j++)
			{
				card[i][j] = 0;
			}
		}
		for (i = 0; i < 5; i++)
		{
			for (j = 0; j < 2; j++)
			{
				com[i][j] = 0;
				ply[i][j] = 0;
			}
		}

		x = 0;   i = 8;   j = 8;
		count1 = 0;    count2 = 0;    triple1 = 0;    triple2 = 0;
		fourcard1 = 0;    fourcard2 = 0;
		strat1 = 0;   strat2 = 0;   temp1 = 1;
		point1 = 0;   point2 = 0;   flash1 = 0;   flash2 = 0;


		// �ʱ�ȭ ��--------------------------------
		system("cls");
		display();


		srand(time(NULL));

		for (count = 0; count < 52; count++)   // ���� ī�� 52�� �̱�
		{
			do
			{
				row = rand() % 4;
				column = rand() % 13;
			} while (card[row][column] != 0);

			card[row][column] = count; // card[4][13] �迭�� ����
		}

		for (count = 0; count < 10; count++)
		{
			for (row = 0; row < 4; row++)
			{
				for (column = 0; column < 13; column++)
				{
					if (card[row][column] == count) //row �׸�, column ����
					{
						if (card[row][column] % 2 == 0)// ��ǻ��
						{
							if (i >= 24 && i <= 60)
							{
								getch();
								gotoxy(show_bet, 12 + k);
								printf("%d�� ���� ", count_bet);
								scanf("%d", &bet);

								sum += bet;
								money -= bet;
								gotoxy(show_bet, 11);
								printf("����=%d ���� ", sum);
								gotoxy(59, 10);
								printf("���� ���� �ڱ� %d��", money);
								printf("\n");

								count_bet++;
								k++;
							}
							x++;
							card_screen(x);
							if (i <= 24)
							{
								gotoxy(i - 2, 4);   printf("?"); //ù��° ���� ī�� ���� ���
								gotoxy(i + 1, 6);   printf("?");
								gotoxy(i + 4, 8);   printf("?");
								i += 12;
								cal(row, column, x);
							}
							else
							{
								gotoxy(i - 2, 4);   printf("%2s", num[column]); //����° ���� ī�� ���� ���
								gotoxy(i + 1, 6);   printf("%s", shape[row]);
								gotoxy(i + 4, 8);   printf("%2s", num[column]);
								i += 12;
								cal(row, column, x);
							}//a, b, c

							Sleep(100);
						}
						else   //�÷��̾�
						{
							x++;
							card_screen(x);

							gotoxy(j - 2, 18);   printf("%2s", num[column]);
							gotoxy(j + 1, 20);   printf("%s", shape[row]);
							gotoxy(j + 4, 22);   printf("%2s", num[column]);
							j += 12;
							cal(row, column, x);

							Sleep(100);
						}
					}
				}
			}

		}
		k = 0;//���� Ŀ�� �ʱ�ȭ
		gotoxy(64, 16); printf("�� ���þ� : %d ", sum);
		count_bet = 1;
		if (game_result == 0)
			money = money - bet;
		else
			money = money + (2 * sum);
		sum = 0;// �ʱ�ȭ
		getch();
	}
}
void menu()
{
	int i, j, y = 16, key = 0;
	system("cls");
	system("mode con cols=80 lines=25");
	white();
	gotoxy(26, 5); printf("Develop By MinWook");
	gotoxy(21, 7); printf("������������������������������������������������������");
	gotoxy(23, 9); red(); printf("     ��        Ŀ  ");
	gotoxy(23, 11); blue(); printf("                 G a m e");
	gotoxy(21, 13); white(); printf("������������������������������������������������������");


	gotoxy(27, 15);
	printf("������������������������������������������������");
	gotoxy(27, 16);
	printf("��                      ��");
	gotoxy(27, 17);
	printf("��                      ��");
	gotoxy(27, 18);
	printf("��                      ��");
	gotoxy(27, 19);
	printf("������������������������������������������������");
	gotoxy(27, 14);
	printf(" ");
	gotoxy(35, 16); printf("S t a r t ");
	gotoxy(35, 17); printf("R u l e s");
	gotoxy(35, 18); printf(" E x i t ");
	gotoxy(31, y); printf("��");
	while (1) {
		//up 72 down 80 enter 13
		key = getch();
		if (key == 72 && flag == 0) {
			gotoxy(31, y); printf("��");
			y--;
			gotoxy(31, y); printf("��");
			flag = 1;
		}
		else if (key == 80 && flag == 1) {
			gotoxy(31, y); printf("��");
			y++;
			gotoxy(31, y); printf("��");
			flag = 0;
		}
		else if (key == 13) {
			break;
		}
	}
}
	void cal(int a, int b, int c) //a�� row, b�� column (����),c�� ī��Ʈ
{
	int i, j;


	if (c % 2 == 1)   //��ǻ�� 1,3,5...
	{
		com[c / 2][0] = b;   //0 ~ 12 ���ڸ� ����, ���ڸ� �׸�
		com[c / 2][1] = a;   //�׸� ��� (0=��,1=��,2=��,3=ũ)                 
	}
	if (c % 2 == 0) //�÷��̾� 2,4,6....
	{
		ply[c / 2 - 1][0] = b;   //����
		ply[c / 2 - 1][1] = a;   //�׸�           
	}
	// ���� ���� ������ �׸��� ��� �ؾ��Ѵ�.


	if (c == 10)
	{
		for (i = 0; i < 4; i++) //ī�� �����ϱ� ���� for��-------------------
		{
			for (j = i + 1; j < 5; j++)
			{
				if (com[i][0] < com[j][0])// ���� �� ���� ���� ---------------��ǻ��----------
				{
					temp1 = com[i][0];
					temp2 = com[i][1];   // �׸��� ���� ����
					com[i][0] = com[j][0];
					com[i][1] = com[j][1];
					com[j][0] = temp1;
					com[j][1] = temp2;
				}
				else if (com[i][0] == com[j][0]) //���ڰ� ������
				{
					if (com[i][1] > com[j][1])   // �׸��� ���� ������(�׸��� �������ڰ� ���� ����)
					{
						temp1 = com[i][0];
						temp2 = com[i][1];   // �׸��� ���� ����
						com[i][0] = com[j][0];
						com[i][1] = com[j][1];
						com[j][0] = temp1;
						com[j][1] = temp2;
					}
				}   //-----------------------------------------------------------------------

				if (ply[i][0] < ply[j][0])// ���� �� ���� ���� ---------------�÷��̾�----------
				{
					temp1 = ply[i][0];
					temp2 = ply[i][1];
					ply[i][0] = ply[j][0];
					ply[i][1] = ply[j][1];
					ply[j][0] = temp1;
					ply[j][1] = temp2;
				}
				else if (ply[i][0] == ply[j][0]) //���ڰ� ������
				{
					if (ply[i][1] > ply[j][1])   // �׸��� ���� ������
					{
						temp1 = ply[i][0];
						temp2 = ply[i][1];
						ply[i][0] = ply[j][0];
						ply[i][1] = ply[j][1];
						ply[j][0] = temp1;
						ply[j][1] = temp2;
					}
				}   //----------------------------------------------------------------------
			}
		} //-----------------------------------------------���� for�� ����

		for (i = 0; i < 4; i++)   // ���, ��Ʈ����Ʈ�� ã������ for��----------------��ǻ��------------------
		{            // ���ڰ� ������ �Ǿ� �־ �� �ڸ� �� �ص� �ȴ�.        
			if (i < 3)
			{
				if (com[i][0] == com[i + 2][0])   //��ǻ�� Ʈ����(ó�� ī��� ����° ī�尡 ������)
				{
					triple1 = com[i][0];
					i += 2;
				}   //��ǻ�� Ʈ����
			}// Ʈ���� äũ�� ���,��ī äũ ǥ��
			if (com[i][0] == com[i + 1][0]) //��ǻ�� ��� (���� ���ڰ� ������)
			{
				pair1[count1] = com[i][0]; //(��� ���� ���)
				count1++;   // ��,�� ��� ����(0=�����orǮ�Ͽ콺, 1=�����)
				i++;
			}
			if (com[i][0] - com[i + 1][0] == 1 || com[1][0] == 3 && com[0][0] == 12) //��Ʈ����Ʈ ����� ���ؼ�(��)
			{
				strat1++;
			}
		}// for �� ����--------------------------------------------------------------------------
		if (com[0][0] == com[3][0]) //���� 4���� ������ ��ī��
			fourcard1 = com[0][0];
		if (com[1][0] == com[4][0])
			fourcard1 = com[1][0];

		for (i = 0; i < 4; i++)   // ���, ��Ʈ����Ʈ�� ã������ for��-----------------�÷��̾�---------------
		{            // ���ڰ� ������ �Ǿ� �־ �� �ڸ� �� �ص� �ȴ�.        
			if (i < 3)
			{
				if (ply[i][0] == ply[i + 2][0])   //�÷��̾� Ʈ����(ó�� ī��� ����° ī�尡 ������)
				{
					triple2 = ply[i][0];
					i += 2;
				}   //�÷��̾� Ʈ����
			}// Ʈ���� äũ�� ���,��ī äũ ǥ��
			if (ply[i][0] == ply[i + 1][0]) //��ǻ�� ��� (���� ���ڰ� ������)
			{
				pair2[count2] = ply[i][0]; //(��� ���� ���)
				count2++;   // ��,�� ��� ����(0=�����orǮ�Ͽ콺, 1=�����)
				i++;
			}
			if (ply[i][0] - ply[i + 1][0] == 1 || ply[1][0] == 3 && ply[0][0] == 12) //��Ʈ����Ʈ ����� ���ؼ�(��)
			{
				strat2++;
			}
		}// for �� ����--------------------------------------------------------------------------
		if (ply[0][0] == ply[3][0]) //���� 4���� ������ ��ī��
			fourcard2 = ply[0][0];
		if (ply[1][0] == ply[4][0])
			fourcard2 = ply[1][0];

		for (i = 0; i < 4; i++)// flash üũ for��------------------------------
		{
			if (com[i][1] == com[i + 1][1])   //��ǻ��
			{
				flash1++;
			}
			if (ply[i][1] == ply[i + 1][1])   //�÷��̾�
			{
				flash2++;
			}
		}// for �� ���� ---------------------------------------------------

		level_check1();

	}
}         //-------------------------------------cal �Լ� ��

void level_check1(void)
{
	//--------------------------��ǻ��--------------------------------
	if (strat1 == 4 && flash1 == 4) // ��Ʈ��Ʈ �÷���
	{
		point1 = 1.5f;
	}
	else if (fourcard1 != 0)   //��ǻ�� ��ī��
	{
		gotoxy(6, 11);   printf("%s ��ī�� �Դϴ�. ", num[fourcard1]);
		point1 = 2;
	}
	else if (count1 == 1 && triple1 != 0) // Ǯ�Ͽ콺 (��ǻ��)
	{
		gotoxy(6, 11);   printf("%s,%s Ǯ�Ͽ콺 �Դϴ�. ", num[triple1], num[pair1[0]]);
		point1 = 3;
	}
	else if (flash1 == 4) //��ǻ�� �÷���
	{
		gotoxy(6, 11);   printf("%s%s �÷��� �Դϴ�. ", shape[com[0][1]], num[com[0][0]]);
		point1 = 4;
	}
	else if (strat1 == 4)   // ��Ʈ����Ʈ �϶� ����Ʈ �ֱ�
		point1 = 6;
	else if (triple1 != 0 && count1 == 0) // Ʈ���� (��ǻ��)
	{
		gotoxy(6, 11);   printf("%s Ʈ���� �Դϴ�. ", num[triple1]);
		point1 = 7;
	}
	else if (count1 == 2) // ����� (��ǻ��)
	{
		gotoxy(6, 11);   printf("%s, %s ����� �Դϴ�. ", num[pair1[0]], num[pair1[1]]);
		point1 = 8;
	}
	else if (count1 == 1 && triple1 == 0) // ����� (��ǻ��)
	{
		gotoxy(6, 11);   printf("%s ����� �Դϴ�.", num[pair1[0]]);
		point1 = 9;
	}
	else if (count1 == 0 && triple1 == 0 && flash1 != 4) // �� ���(ž) (��ǻ��)
	{
		gotoxy(6, 11);   printf("%s%s ž �Դϴ�.", shape[com[0][1]], num[com[0][0]]);
		point1 = 10;   // ��Ŀ ���� ����(1~9)
	}

	//----------------------�÷��̾�------------------------------------
	if (strat2 == 4 && flash2 == 4) // ��Ʈ��Ʈ �÷���
	{
		point2 = 1.5f;
	}
	else if (fourcard2 != 0)   //�÷��̾� ��ī��
	{
		gotoxy(6, 25);   printf("%s ��ī�� �Դϴ�. ", num[fourcard2]);
		point2 = 2;
	}
	else if (count2 == 1 && triple2 != 0)   // Ǯ�Ͽ콺 (�÷��̾�)
	{
		gotoxy(6, 25);   printf("%s,%s Ǯ�Ͽ콺 �Դϴ�. ", num[triple2], num[pair2[0]]);
		point2 = 3;
	}
	else if (flash2 == 4) //�÷��̾� �÷���
	{
		gotoxy(6, 25);   printf("%s%s �÷��� �Դϴ�. ", shape[ply[0][1]], num[ply[0][0]]);
		point2 = 4;
	}
	else if (strat2 == 4) //��Ʈ����Ʈ �϶� ����Ʈ �ֱ�
		point2 = 6;
	else if (triple2 != 0 && count2 == 0) // Ʈ���� (�÷��̾�)
	{
		gotoxy(6, 25);   printf("%s Ʈ���� �Դϴ�. ", num[triple2]);
		point2 = 7;
	}
	else if (count2 == 2) // ����� (�÷��̾�)
	{
		gotoxy(6, 25);   printf("%s, %s ����� �Դϴ�. ", num[pair2[0]], num[pair2[1]]);
		point2 = 8;
	}
	else if (count2 == 1 && triple2 == 0) // ����� (�÷��̾�)
	{
		gotoxy(6, 25);   printf("%s ����� �Դϴ�.", num[pair2[0]]);
		point2 = 9;
	}
	else if (count2 == 0 && triple2 == 0 && flash2 != 4)   // �����(ž) (�÷��̾�)
	{
		gotoxy(6, 25);   printf("%s%s ž �Դϴ�.", shape[ply[0][1]], num[ply[0][0]]);
		point2 = 10;
	}
	level_check2();
}
void level_check2(void)//-------------------------------------------------------------------------
{
	if (point1 == 10 && point2 == 10) // ž �϶� ī�� ��
	{
		if (com[0][0] > ply[0][0])   // ù��° ���� ��
		{
			point2 = 10.2f;
		}
		else if (com[0][0] < ply[0][0])
		{
			point1 = 10.2f;
		}
	}
	if (point1 == 9 && point2 == 9) //�� ��� �϶� ī�� ��
	{
		if (pair1[0] > pair2[0])
		{
			point2 = 9.2f;
		}
		else if (pair1[0] < pair2[0])
		{
			point1 = 9.2f;
		}
	}
	if (point1 == 8 && point2 == 8)   //����� �϶� ��
	{
		if (pair1[0] > pair2[0])
		{
			point2 = 8.2f;
		}
		else if (pair1[0] < pair2[0])
		{
			point1 = 8.2f;
		}
		if (pair1[0] == pair2[0] && pair1[1] > pair2[1])
		{
			point2 = 8.2f;
		}
		else if (pair1[0] == pair2[0] && pair1[1] < pair2[1])
		{
			point1 = 8.2f;
		}
	}
	if (point1 == 1.5f || point2 == 1.5f)   //�� ��Ʈ����Ʈ �÷��� �� �ξ� ��Ʈ����Ʈ �� (���� ��Ʈ����Ʈ�϶�)
	{
		if (com[0][0] == 12 && com[1][0] == 11)
			point1 = 1.1f;
		if (com[0][0] == 12 && com[1][0] == 3)
			point1 = 1.2f;
		if (ply[0][0] == 12 && ply[1][0] == 11)
			point2 = 1.1f;
		if (ply[0][0] == 12 && ply[1][0] == 3)
			point2 = 1.2f;
	}
	if (point1 == 1.5)   //��ǻ�� ��Ʈ����Ʈ �÷���
	{
		gotoxy(6, 11);   printf("%s%s ��Ʈ����Ʈ �÷��� �Դϴ�. ", shape[com[0][1]], num[com[0][0]]);
	}
	if (point1 == 1.1f)
	{
		gotoxy(6, 11);   printf("%s%s �ξ� ��Ʈ����Ʈ �Դϴ�. ", shape[com[0][1]], num[com[0][0]]);
	}
	if (point1 == 1.2f)
	{
		gotoxy(6, 11);   printf("%s%s �齺Ʈ����Ʈ �÷��� �Դϴ�. ", shape[com[0][1]], num[com[0][0]]);
	}//----------------------------------------------------------------------  
	if (point2 == 1.5)   //�÷��̾� ��Ʈ����Ʈ �÷���
	{
		gotoxy(6, 25);   printf("%s%s ��Ʈ����Ʈ �÷��� �Դϴ�. ", shape[ply[0][1]], num[ply[0][0]]);
	}
	if (point2 == 1.1f)
	{
		gotoxy(6, 25);   printf("%s%s �ξ� ��Ʈ����Ʈ �÷��� �Դϴ�. ", shape[ply[0][1]], num[ply[0][0]]);
	}
	if (point2 == 1.2f)
	{
		gotoxy(6, 25);   printf("%s%s �齺Ʈ����Ʈ �÷��� �Դϴ�. ", shape[ply[0][1]], num[ply[0][0]]);
	}//----------------------------------------------------------------------


	if (point1 == 6 || point2 == 6)   //�� ��Ʈ����Ʈ �� ����ƾ �� (���� ��Ʈ����Ʈ�϶�)
	{
		if (com[0][0] == 12 && com[1][0] == 11)// ����ƾ
			point1 = 5.1f;
		if (com[0][0] == 12 && com[1][0] == 3)
			point1 = 5.2f;
		if (ply[0][0] == 12 && ply[1][0] == 11)
			point2 = 5.1f;
		if (ply[0][0] == 12 && ply[1][0] == 3)
			point2 = 5.2f;
	}//---------------------------
	if (point1 == 6)   //��ǻ�� ��Ʈ����Ʈ
	{
		gotoxy(6, 11);   printf("%s ��Ʈ����Ʈ �Դϴ�. ", num[com[0][0]]);
	}
	if (point1 == 5.1f)
	{
		gotoxy(6, 11);   printf("%s ����ƾ �Դϴ�. ", num[com[0][0]]);
	}
	if (point1 == 5.2f)
	{
		gotoxy(6, 11);   printf("%s �齺Ʈ����Ʈ �Դϴ�. ", num[com[0][0]]);
	}//----------------------------------------------------------------------  
	if (point2 == 6)   //�÷��̾� ��Ʈ����Ʈ
	{
		gotoxy(6, 25);   printf("%s ��Ʈ����Ʈ �Դϴ�. ", num[ply[0][0]]);
	}
	if (point2 == 5.1f)
	{
		gotoxy(6, 25);   printf("%s ����ƾ �Դϴ�. ", num[ply[0][0]]);
	}
	if (point2 == 5.2f)
	{
		gotoxy(6, 25);   printf("%s �齺Ʈ����Ʈ �Դϴ�. ", num[ply[0][0]]);
	}//----------------------------------------------------------------------

	temp1 = 0;
	if (point1 == 4 && point2 == 4)//���� �� ---�÷���
	{
		temp1 = num_check(com, ply);   //���ĵ� ���ڹ迭 �Է�
	}
	if (point1 == 7 && point2 == 7)   // Ʈ���� ��
	{
		if (triple1 > triple2)
			point2++;
		if (triple1 < triple2)
			point1++;
	}
	//�׸� �� ---------------------  
	if (point1 == point2 && point1 != 4 && point1 != 7 || temp1 == 1)// ���� ����Ʈ �̰�, �÷���,Ʈ������ �ƴҶ�
	{
		if (com[0][1] < ply[0][1])   //��ǻ���� �׸� ������ ������
			point2 += 0.1f;   // �÷��̾� ����Ʈ�� �� ������
		else if (com[0][1] > ply[0][1])
			point1 += 0.1f;
	}
	//-------------------------------------

	if (point1 < point2) // ����Ʈ�� ���� ���� �̱�
	{
		gotoxy(68, 7); printf("Computer WIN!!");
		game_result = 0;
	}
	else if (point1 > point2)
	{
		gotoxy(68, 21); printf("Player WIN!!");
		game_result = 1;
	}
}

int num_check(int a[5][2], int b[5][2]) //�÷��� �϶� ���� �� �Լ�
{
	int i = 0;
	float save1, save2;
	save1 = point1;
	save2 = point2;
	for (i = 0; i < 5; i++)   // ��Ʈ����Ʈ ���� ���� ����
	{
		if (a[i][0] > b[i][0])
		{
			point2 += 0.1f;
		}
		if (a[i][0] < b[i][0])
		{
			point1 += 0.1f;
		}
		if (point1 >= 9)
		{
			if (point1 > point2 || point1 < point2)
				break;
		}
	}

	if (point1 == point2)
	{
		i = 1;
		point1 = save1 + 0.1f;
		point2 = save2 + 0.1f;
	}
	else i = 0;

	return i;
}



void gotoxy(int x, int y)
{
	COORD XY = { x,y };
	HANDLE hHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hHandle, XY);
}

void display()
{
	system("mode con cols=94 lines=30");
	system("cls");
	gotoxy(2, 2);    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������");
	gotoxy(2, 3);    printf("��                                                                               ��");
	gotoxy(2, 4);    printf("��                                                                               ��");
	gotoxy(2, 5);    printf("��                                                                               ��");
	gotoxy(2, 6);    printf("��                                                                               ��");
	gotoxy(2, 7);    printf("��                                                                               ��");
	gotoxy(2, 8);    printf("��                                                                               ��");
	gotoxy(2, 9);    printf("��                                                                               ��");
	gotoxy(2, 9);    printf("��                                                                               ��");
	gotoxy(2, 10);   printf("��                                                                               ��");
	gotoxy(2, 11);   printf("��                                                                               ��");
	gotoxy(2, 12);   printf("��                                                                               ��");
	gotoxy(2, 13);   printf("��                                                                               ��");
	gotoxy(2, 14);   printf("��                                                                               ��");
	gotoxy(2, 15);   printf("��                                                                               ��");
	gotoxy(2, 16);   printf("��                                                                               ��");
	gotoxy(2, 17);   printf("��                                                                               ��");
	gotoxy(2, 18);   printf("��                                                                               ��");
	gotoxy(2, 19);   printf("��                                                                               ��");
	gotoxy(2, 20);   printf("��                                                                               ��");
	gotoxy(2, 21);   printf("��                                                                               ��");
	gotoxy(2, 22);   printf("��                                                                               ��");
	gotoxy(2, 23);   printf("��                                                                               ��");
	gotoxy(2, 24);   printf("��                                                                               ��");
	gotoxy(2, 25);   printf("��                                                                               ��");
	gotoxy(2, 26);   printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������");

}
void card_screen(int x)
{

	if (x % 2 == 1) {
		gotoxy(4 * temp1, 3);   printf("����������������������"); //��ǻ�� 1
		gotoxy(4 * temp1, 4);   printf("��         ��");
		gotoxy(4 * temp1, 5);   printf("��         ��");
		gotoxy(4 * temp1, 6);   printf("��         �� ");
		gotoxy(4 * temp1, 7);   printf("��         ��");
		gotoxy(4 * temp1, 8);   printf("��         ��");
		gotoxy(4 * temp1, 9);   printf("����������������������");
	}
	if (x % 2 == 0) {
		gotoxy(4 * temp1, 17);   printf("����������������������"); //��� 1
		gotoxy(4 * temp1, 18);   printf("��         ��");
		gotoxy(4 * temp1, 19);   printf("��         ��");
		gotoxy(4 * temp1, 20);   printf("��         ��");
		gotoxy(4 * temp1, 21);   printf("��         ��");
		gotoxy(4 * temp1, 22);   printf("��         ��");
		gotoxy(4 * temp1, 23);   printf("����������������������");
		temp1 += 3;
	}
}