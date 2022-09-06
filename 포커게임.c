/*
	comment : 카드 5개를 이용하는 포커게임(로직은 세븐포커와 같음)
	제작자 : SCH CSE 20194024 김민욱(with 구민주)
*/
#include <time.h>//랜덤값 사용
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>//system 사용
#include <conio.h> //getch 사용
#pragma warning(disable:4996)
void rules()
{
	printf("기본적인 포커룰을 따르는 게임입니다 ");
	printf("총 5장의 카드를 가지고 게임을 합니다.");
	printf("기본 보유 자금은 50000원 입니다 ");
	printf("플레이어는 본인의 카드 2장을 보고 판단을 하여 베팅을 진행합니다.");
	printf("게임에서 이긴다면 보유 자금에 베팅한 금액의 2배만큼이 추가됩니다. ");
	printf("게임에서 진다면 보유 자금에 베팅한 금액을 뺍니다 ");
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

int sum; // 베팅액
int money = 50000;
int count_bet = 1;
int show_bet = 66;
int k = 1; // 베팅 커서 변수

int com[5][2], ply[5][2], com_row, ply_row;//cal함수, level체크 함수 (숫자,그림저장, 그림저장)
char num[13][3] = { "2","3","4","5","6","7","8","9","10","J","Q","K","A" }; // 영어를 표시하기 위해 필요
int count1 = 0, count2 = 0, pair1[2], pair2[2], triple1 = 0, triple2 = 0, temp1, temp2; //level1,2체크 함수
int fourcard1 = 0, fourcard2 = 0, flash1, flash2, strat1, strat2;//cal함수, level체크 함수
float point1 = 0, point2 = 0; //level체크 함수,num체크 함수
char shape[4][3] = { "♠","◇","♡","♣" }; //main함수, cal 함수
void menu();

void main()
{
	menu();
	int card[4][13] = { 0 }, x;
	int column, row, count, i = 8, j = 8;

	while (1)
	{
		for (i = 0; i < 4; i++) // 초기화
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


		// 초기화 끝--------------------------------
		system("cls");
		display();


		srand(time(NULL));

		for (count = 0; count < 52; count++)   // 랜덤 카드 52장 뽑기
		{
			do
			{
				row = rand() % 4;
				column = rand() % 13;
			} while (card[row][column] != 0);

			card[row][column] = count; // card[4][13] 배열에 저장
		}

		for (count = 0; count < 10; count++)
		{
			for (row = 0; row < 4; row++)
			{
				for (column = 0; column < 13; column++)
				{
					if (card[row][column] == count) //row 그림, column 숫자
					{
						if (card[row][column] % 2 == 0)// 컴퓨터
						{
							if (i >= 24 && i <= 60)
							{
								getch();
								gotoxy(show_bet, 12 + k);
								printf("%d차 베팅 ", count_bet);
								scanf("%d", &bet);

								sum += bet;
								money -= bet;
								gotoxy(show_bet, 11);
								printf("현재=%d 베팅 ", sum);
								gotoxy(59, 10);
								printf("현재 보유 자금 %d원", money);
								printf("\n");

								count_bet++;
								k++;
							}
							x++;
							card_screen(x);
							if (i <= 24)
							{
								gotoxy(i - 2, 4);   printf("?"); //첫번째 뽑힌 카드 부터 출력
								gotoxy(i + 1, 6);   printf("?");
								gotoxy(i + 4, 8);   printf("?");
								i += 12;
								cal(row, column, x);
							}
							else
							{
								gotoxy(i - 2, 4);   printf("%2s", num[column]); //세번째 뽑힌 카드 부터 출력
								gotoxy(i + 1, 6);   printf("%s", shape[row]);
								gotoxy(i + 4, 8);   printf("%2s", num[column]);
								i += 12;
								cal(row, column, x);
							}//a, b, c

							Sleep(100);
						}
						else   //플래이어
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
		k = 0;//베팅 커서 초기화
		gotoxy(64, 16); printf("총 베팅액 : %d ", sum);
		count_bet = 1;
		if (game_result == 0)
			money = money - bet;
		else
			money = money + (2 * sum);
		sum = 0;// 초기화
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
	gotoxy(21, 7); printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━");
	gotoxy(23, 9); red(); printf("     포        커  ");
	gotoxy(23, 11); blue(); printf("                 G a m e");
	gotoxy(21, 13); white(); printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━");


	gotoxy(27, 15);
	printf("┏━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(27, 16);
	printf("┃                      ┃");
	gotoxy(27, 17);
	printf("┃                      ┃");
	gotoxy(27, 18);
	printf("┃                      ┃");
	gotoxy(27, 19);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━┛");
	gotoxy(27, 14);
	printf(" ");
	gotoxy(35, 16); printf("S t a r t ");
	gotoxy(35, 17); printf("R u l e s");
	gotoxy(35, 18); printf(" E x i t ");
	gotoxy(31, y); printf("☞");
	while (1) {
		//up 72 down 80 enter 13
		key = getch();
		if (key == 72 && flag == 0) {
			gotoxy(31, y); printf("　");
			y--;
			gotoxy(31, y); printf("☞");
			flag = 1;
		}
		else if (key == 80 && flag == 1) {
			gotoxy(31, y); printf("　");
			y++;
			gotoxy(31, y); printf("☞");
			flag = 0;
		}
		else if (key == 13) {
			break;
		}
	}
}
	void cal(int a, int b, int c) //a는 row, b는 column (숫자),c는 카운트
{
	int i, j;


	if (c % 2 == 1)   //컴퓨터 1,3,5...
	{
		com[c / 2][0] = b;   //0 ~ 12 앞자리 숫자, 뒷자리 그림
		com[c / 2][1] = a;   //그림 기억 (0=스,1=다,2=하,3=크)                 
	}
	if (c % 2 == 0) //플레이어 2,4,6....
	{
		ply[c / 2 - 1][0] = b;   //숫자
		ply[c / 2 - 1][1] = a;   //그림           
	}
	// 제일 높은 숫자의 그림을 기억 해야한다.


	if (c == 10)
	{
		for (i = 0; i < 4; i++) //카드 정렬하기 위한 for문-------------------
		{
			for (j = i + 1; j < 5; j++)
			{
				if (com[i][0] < com[j][0])// 높은 수 부터 정렬 ---------------컴퓨터----------
				{
					temp1 = com[i][0];
					temp2 = com[i][1];   // 그림도 같이 정렬
					com[i][0] = com[j][0];
					com[i][1] = com[j][1];
					com[j][0] = temp1;
					com[j][1] = temp2;
				}
				else if (com[i][0] == com[j][0]) //숫자가 같을때
				{
					if (com[i][1] > com[j][1])   // 그림이 높은 순으로(그림은 낮은숫자가 높은 것임)
					{
						temp1 = com[i][0];
						temp2 = com[i][1];   // 그림도 같이 정렬
						com[i][0] = com[j][0];
						com[i][1] = com[j][1];
						com[j][0] = temp1;
						com[j][1] = temp2;
					}
				}   //-----------------------------------------------------------------------

				if (ply[i][0] < ply[j][0])// 높은 수 부터 정렬 ---------------플레이어----------
				{
					temp1 = ply[i][0];
					temp2 = ply[i][1];
					ply[i][0] = ply[j][0];
					ply[i][1] = ply[j][1];
					ply[j][0] = temp1;
					ply[j][1] = temp2;
				}
				else if (ply[i][0] == ply[j][0]) //숫자가 같을때
				{
					if (ply[i][1] > ply[j][1])   // 그림이 높은 순으로
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
		} //-----------------------------------------------이중 for문 종료

		for (i = 0; i < 4; i++)   // 페어, 스트레이트를 찾기위한 for문----------------컴퓨터------------------
		{            // 숫자가 정렬이 되어 있어서 앞 뒤만 비교 해도 된다.        
			if (i < 3)
			{
				if (com[i][0] == com[i + 2][0])   //컴퓨터 트리플(처음 카드와 세번째 카드가 같으면)
				{
					triple1 = com[i][0];
					i += 2;
				}   //컴퓨터 트리플
			}// 트리플 채크후 페어,포카 채크 표시
			if (com[i][0] == com[i + 1][0]) //컴퓨터 페어 (같은 숫자가 있으면)
			{
				pair1[count1] = com[i][0]; //(페어 숫자 기억)
				count1++;   // 원,투 페어 구분(0=원페어or풀하우스, 1=투페어)
				i++;
			}
			if (com[i][0] - com[i + 1][0] == 1 || com[1][0] == 3 && com[0][0] == 12) //스트레이트 계산을 위해서(플)
			{
				strat1++;
			}
		}// for 문 종료--------------------------------------------------------------------------
		if (com[0][0] == com[3][0]) //숫자 4개가 같으면 포카드
			fourcard1 = com[0][0];
		if (com[1][0] == com[4][0])
			fourcard1 = com[1][0];

		for (i = 0; i < 4; i++)   // 페어, 스트레이트를 찾기위한 for문-----------------플레이어---------------
		{            // 숫자가 정렬이 되어 있어서 앞 뒤만 비교 해도 된다.        
			if (i < 3)
			{
				if (ply[i][0] == ply[i + 2][0])   //플레이어 트리플(처음 카드와 세번째 카드가 같으면)
				{
					triple2 = ply[i][0];
					i += 2;
				}   //플레이어 트리플
			}// 트리플 채크후 페어,포카 채크 표시
			if (ply[i][0] == ply[i + 1][0]) //컴퓨터 페어 (같은 숫자가 있으면)
			{
				pair2[count2] = ply[i][0]; //(페어 숫자 기억)
				count2++;   // 원,투 페어 구분(0=원페어or풀하우스, 1=투페어)
				i++;
			}
			if (ply[i][0] - ply[i + 1][0] == 1 || ply[1][0] == 3 && ply[0][0] == 12) //스트레이트 계산을 위해서(컴)
			{
				strat2++;
			}
		}// for 문 종료--------------------------------------------------------------------------
		if (ply[0][0] == ply[3][0]) //숫자 4개가 같으면 포카드
			fourcard2 = ply[0][0];
		if (ply[1][0] == ply[4][0])
			fourcard2 = ply[1][0];

		for (i = 0; i < 4; i++)// flash 체크 for문------------------------------
		{
			if (com[i][1] == com[i + 1][1])   //컴퓨터
			{
				flash1++;
			}
			if (ply[i][1] == ply[i + 1][1])   //플레이어
			{
				flash2++;
			}
		}// for 문 종료 ---------------------------------------------------

		level_check1();

	}
}         //-------------------------------------cal 함수 끝

void level_check1(void)
{
	//--------------------------컴퓨터--------------------------------
	if (strat1 == 4 && flash1 == 4) // 스트리트 플래쉬
	{
		point1 = 1.5f;
	}
	else if (fourcard1 != 0)   //컴퓨터 포카드
	{
		gotoxy(6, 11);   printf("%s 포카드 입니다. ", num[fourcard1]);
		point1 = 2;
	}
	else if (count1 == 1 && triple1 != 0) // 풀하우스 (컴퓨터)
	{
		gotoxy(6, 11);   printf("%s,%s 풀하우스 입니다. ", num[triple1], num[pair1[0]]);
		point1 = 3;
	}
	else if (flash1 == 4) //컴퓨터 플래쉬
	{
		gotoxy(6, 11);   printf("%s%s 플래쉬 입니다. ", shape[com[0][1]], num[com[0][0]]);
		point1 = 4;
	}
	else if (strat1 == 4)   // 스트레이트 일때 포인트 주기
		point1 = 6;
	else if (triple1 != 0 && count1 == 0) // 트리플 (컴퓨터)
	{
		gotoxy(6, 11);   printf("%s 트리플 입니다. ", num[triple1]);
		point1 = 7;
	}
	else if (count1 == 2) // 투페어 (컴퓨터)
	{
		gotoxy(6, 11);   printf("%s, %s 투페어 입니다. ", num[pair1[0]], num[pair1[1]]);
		point1 = 8;
	}
	else if (count1 == 1 && triple1 == 0) // 원페어 (컴퓨터)
	{
		gotoxy(6, 11);   printf("%s 원페어 입니다.", num[pair1[0]]);
		point1 = 9;
	}
	else if (count1 == 0 && triple1 == 0 && flash1 != 4) // 노 페어(탑) (컴퓨터)
	{
		gotoxy(6, 11);   printf("%s%s 탑 입니다.", shape[com[0][1]], num[com[0][0]]);
		point1 = 10;   // 포커 족보 순위(1~9)
	}

	//----------------------플레이어------------------------------------
	if (strat2 == 4 && flash2 == 4) // 스트리트 플래쉬
	{
		point2 = 1.5f;
	}
	else if (fourcard2 != 0)   //플레이어 포카드
	{
		gotoxy(6, 25);   printf("%s 포카드 입니다. ", num[fourcard2]);
		point2 = 2;
	}
	else if (count2 == 1 && triple2 != 0)   // 풀하우스 (플레이어)
	{
		gotoxy(6, 25);   printf("%s,%s 풀하우스 입니다. ", num[triple2], num[pair2[0]]);
		point2 = 3;
	}
	else if (flash2 == 4) //플레이어 플래쉬
	{
		gotoxy(6, 25);   printf("%s%s 플래쉬 입니다. ", shape[ply[0][1]], num[ply[0][0]]);
		point2 = 4;
	}
	else if (strat2 == 4) //스트레이트 일때 포인트 주기
		point2 = 6;
	else if (triple2 != 0 && count2 == 0) // 트리플 (플레이어)
	{
		gotoxy(6, 25);   printf("%s 트리플 입니다. ", num[triple2]);
		point2 = 7;
	}
	else if (count2 == 2) // 투페어 (플레이어)
	{
		gotoxy(6, 25);   printf("%s, %s 투페어 입니다. ", num[pair2[0]], num[pair2[1]]);
		point2 = 8;
	}
	else if (count2 == 1 && triple2 == 0) // 원페어 (플레이어)
	{
		gotoxy(6, 25);   printf("%s 원페어 입니다.", num[pair2[0]]);
		point2 = 9;
	}
	else if (count2 == 0 && triple2 == 0 && flash2 != 4)   // 노페어(탑) (플레이어)
	{
		gotoxy(6, 25);   printf("%s%s 탑 입니다.", shape[ply[0][1]], num[ply[0][0]]);
		point2 = 10;
	}
	level_check2();
}
void level_check2(void)//-------------------------------------------------------------------------
{
	if (point1 == 10 && point2 == 10) // 탑 일때 카드 비교
	{
		if (com[0][0] > ply[0][0])   // 첫번째 숫자 비교
		{
			point2 = 10.2f;
		}
		else if (com[0][0] < ply[0][0])
		{
			point1 = 10.2f;
		}
	}
	if (point1 == 9 && point2 == 9) //원 페어 일때 카드 비교
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
	if (point1 == 8 && point2 == 8)   //투페어 일때 비교
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
	if (point1 == 1.5f || point2 == 1.5f)   //백 스트레이트 플래쉬 와 로얄 스트레이트 비교 (같은 스트레이트일때)
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
	if (point1 == 1.5)   //컴퓨터 스트레이트 플래쉬
	{
		gotoxy(6, 11);   printf("%s%s 스트레이트 플래쉬 입니다. ", shape[com[0][1]], num[com[0][0]]);
	}
	if (point1 == 1.1f)
	{
		gotoxy(6, 11);   printf("%s%s 로얄 스트레이트 입니다. ", shape[com[0][1]], num[com[0][0]]);
	}
	if (point1 == 1.2f)
	{
		gotoxy(6, 11);   printf("%s%s 백스트레이트 플래쉬 입니다. ", shape[com[0][1]], num[com[0][0]]);
	}//----------------------------------------------------------------------  
	if (point2 == 1.5)   //플레이어 스트레이트 플래쉬
	{
		gotoxy(6, 25);   printf("%s%s 스트레이트 플래쉬 입니다. ", shape[ply[0][1]], num[ply[0][0]]);
	}
	if (point2 == 1.1f)
	{
		gotoxy(6, 25);   printf("%s%s 로얄 스트레이트 플래쉬 입니다. ", shape[ply[0][1]], num[ply[0][0]]);
	}
	if (point2 == 1.2f)
	{
		gotoxy(6, 25);   printf("%s%s 백스트레이트 플래쉬 입니다. ", shape[ply[0][1]], num[ply[0][0]]);
	}//----------------------------------------------------------------------


	if (point1 == 6 || point2 == 6)   //백 스트레이트 와 마운틴 비교 (같은 스트레이트일때)
	{
		if (com[0][0] == 12 && com[1][0] == 11)// 마운틴
			point1 = 5.1f;
		if (com[0][0] == 12 && com[1][0] == 3)
			point1 = 5.2f;
		if (ply[0][0] == 12 && ply[1][0] == 11)
			point2 = 5.1f;
		if (ply[0][0] == 12 && ply[1][0] == 3)
			point2 = 5.2f;
	}//---------------------------
	if (point1 == 6)   //컴퓨터 스트레이트
	{
		gotoxy(6, 11);   printf("%s 스트레이트 입니다. ", num[com[0][0]]);
	}
	if (point1 == 5.1f)
	{
		gotoxy(6, 11);   printf("%s 마운틴 입니다. ", num[com[0][0]]);
	}
	if (point1 == 5.2f)
	{
		gotoxy(6, 11);   printf("%s 백스트레이트 입니다. ", num[com[0][0]]);
	}//----------------------------------------------------------------------  
	if (point2 == 6)   //플레이어 스트레이트
	{
		gotoxy(6, 25);   printf("%s 스트레이트 입니다. ", num[ply[0][0]]);
	}
	if (point2 == 5.1f)
	{
		gotoxy(6, 25);   printf("%s 마운틴 입니다. ", num[ply[0][0]]);
	}
	if (point2 == 5.2f)
	{
		gotoxy(6, 25);   printf("%s 백스트레이트 입니다. ", num[ply[0][0]]);
	}//----------------------------------------------------------------------

	temp1 = 0;
	if (point1 == 4 && point2 == 4)//숫자 비교 ---플래쉬
	{
		temp1 = num_check(com, ply);   //정렬된 숫자배열 입력
	}
	if (point1 == 7 && point2 == 7)   // 트리플 비교
	{
		if (triple1 > triple2)
			point2++;
		if (triple1 < triple2)
			point1++;
	}
	//그림 비교 ---------------------  
	if (point1 == point2 && point1 != 4 && point1 != 7 || temp1 == 1)// 같은 포인트 이고, 플래쉬,트리플은 아닐때
	{
		if (com[0][1] < ply[0][1])   //컴퓨터의 그림 레벨이 낮으면
			point2 += 0.1f;   // 플레이어 포인트가 더 높아짐
		else if (com[0][1] > ply[0][1])
			point1 += 0.1f;
	}
	//-------------------------------------

	if (point1 < point2) // 포인트가 낮을 수록 이김
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

int num_check(int a[5][2], int b[5][2]) //플래쉬 일때 숫자 비교 함수
{
	int i = 0;
	float save1, save2;
	save1 = point1;
	save2 = point2;
	for (i = 0; i < 5; i++)   // 스트레이트 빼고 순위 정함
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
	gotoxy(2, 2);    printf("┌───────────────────────────────────────────────────────────────────────────────┐");
	gotoxy(2, 3);    printf("│                                                                               │");
	gotoxy(2, 4);    printf("│                                                                               │");
	gotoxy(2, 5);    printf("│                                                                               │");
	gotoxy(2, 6);    printf("│                                                                               │");
	gotoxy(2, 7);    printf("│                                                                               │");
	gotoxy(2, 8);    printf("│                                                                               │");
	gotoxy(2, 9);    printf("│                                                                               │");
	gotoxy(2, 9);    printf("│                                                                               │");
	gotoxy(2, 10);   printf("│                                                                               │");
	gotoxy(2, 11);   printf("│                                                                               │");
	gotoxy(2, 12);   printf("│                                                                               │");
	gotoxy(2, 13);   printf("│                                                                               │");
	gotoxy(2, 14);   printf("│                                                                               │");
	gotoxy(2, 15);   printf("│                                                                               │");
	gotoxy(2, 16);   printf("│                                                                               │");
	gotoxy(2, 17);   printf("│                                                                               │");
	gotoxy(2, 18);   printf("│                                                                               │");
	gotoxy(2, 19);   printf("│                                                                               │");
	gotoxy(2, 20);   printf("│                                                                               │");
	gotoxy(2, 21);   printf("│                                                                               │");
	gotoxy(2, 22);   printf("│                                                                               │");
	gotoxy(2, 23);   printf("│                                                                               │");
	gotoxy(2, 24);   printf("│                                                                               │");
	gotoxy(2, 25);   printf("│                                                                               │");
	gotoxy(2, 26);   printf("└───────────────────────────────────────────────────────────────────────────────┘");

}
void card_screen(int x)
{

	if (x % 2 == 1) {
		gotoxy(4 * temp1, 3);   printf("┌─────────┐"); //컴퓨터 1
		gotoxy(4 * temp1, 4);   printf("│         │");
		gotoxy(4 * temp1, 5);   printf("│         │");
		gotoxy(4 * temp1, 6);   printf("│         │ ");
		gotoxy(4 * temp1, 7);   printf("│         │");
		gotoxy(4 * temp1, 8);   printf("│         │");
		gotoxy(4 * temp1, 9);   printf("└─────────┘");
	}
	if (x % 2 == 0) {
		gotoxy(4 * temp1, 17);   printf("┌─────────┐"); //사람 1
		gotoxy(4 * temp1, 18);   printf("│         │");
		gotoxy(4 * temp1, 19);   printf("│         │");
		gotoxy(4 * temp1, 20);   printf("│         │");
		gotoxy(4 * temp1, 21);   printf("│         │");
		gotoxy(4 * temp1, 22);   printf("│         │");
		gotoxy(4 * temp1, 23);   printf("└─────────┘");
		temp1 += 3;
	}
}