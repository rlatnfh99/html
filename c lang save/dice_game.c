#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct score{
	int win;
	int draw;
	int lose;
};

int money = 1000;//2-1. 초기금액은 100원으로 한다.
struct score score;

int throw_dice(int *dice){
	static n=0;
	int i;

	n++;
	srand(time(NULL));
	for(i=0;i<(n%4+1);i++){
		rand();rand();rand();rand();rand();
		srand(rand());
	}

	*dice += rand()%6+1;
	return *dice;
}
void print_score(){//6. 메뉴 2번 승률 누적 기능을 구현하라
	printf("=====================\n");
	printf("이긴 경기수 : %d\n",score.win);
	printf("비긴 경기수 : %d\n",score.draw);
	printf(" 진  경기수 : %d\n",score.lose);
	printf("=====================\n");
	printf("계속 하려면 아무 키나 누르십시오 . . .");
	fflush(stdin);
	scanf("%c");
	system("cls");
}

void start(){
	int bet_m = 0;
	int user_dice = 0;
	int com_dice = 0;

	char y_n;

	money -= 10;//2-2.게임 시작시마다 10원씩 감소되도록 구현한다.

	throw_dice(&user_dice);//8.사용자와 컴퓨터의 Random값 갱성시 3번생성한 랜덤값을 합산하라.
	throw_dice(&user_dice);
	throw_dice(&user_dice);

	throw_dice(&com_dice);
	throw_dice(&com_dice);
	throw_dice(&com_dice);

	printf("== DICE GAME START! ==\n");
	printf(" 나의 주사위의 합 : %d\n",user_dice);
	printf("배팅하시겠습니까?<y/n> ");
	fflush(stdin);
	scanf("%c",&y_n);

	switch(y_n){
    case 'y' :
		while(1){
			printf("배팅금액을 입력해주세요<1~%d>: ",money);
			scanf("%d",&bet_m);
			if(bet_m<1 || bet_m>money){//5-2. 1~사용자금액 범위가 아닐시 잘못 입력이라는 예외 처리를 한다.
				printf("잘못 입력하셨습니다.\n");
				fflush(stdin);
				continue;
			}
			break;
		}
		break;

    case 'n' :
		printf("배팅 NO !\n");
		break;

    default :
		printf("배팅 NO !\n"); //5-1. Y나 N이 아닌 값은 전부 N으로 처리한다.
		break;
	}
	printf("=====================\n");
	printf("Player  : %d\n",user_dice);
	printf("Compuer : %d\n",com_dice);
	printf("=====================\n");

	if(user_dice>com_dice){//7-1. 사용자 승리시 배팅금액만큼 사용자 금액 증가.
		printf("당신이 이겼습니다.\n");
		score.win++;
		money += bet_m+10;
	} else if(user_dice<com_dice){//7-2. 패배시 판돈(10)을 제외한 금액
		printf("당신이 졌습니다.^^\n");
		score.lose++;
		money -= bet_m;
	}else {//7-3. 무승부시 배팅전 사용자 금액
		printf("우린 비겼습니다.\n");
		score.draw++;
		money += 10;
	}
		printf("계속 하려면 아무 키나 누르십시오 . . .");
	fflush(stdin);
	scanf("%c");
	system("cls");	//9.화면의 출력이 누적되지 않도록 판당 화면을 정리하시오
}
void intro(){
	int sel;
	printf("=====================\n");
	printf("= = = DICE GAME = = =\n");
	printf("\n");
	printf("   Money = %d\n",money);
	printf("\n");
	printf("   1. GameStart\n");
	printf("   2. Game Score\n");
	printf("   3. End Game\n");
	printf("=====================\n");

	while(1){
		printf(" > ");
		scanf("%d",&sel);
		if(sel<1 || sel>3){
			printf("잘못 입력하셨습니다.(1~3)\n");
			fflush(stdin);
			continue;
		}
		break;
	}

	switch(sel){
	case 1:
		start();
		break;
	case 2:
		print_score();
		break;
	case 3:
		printf("게임을 종료하겠습니다.\n");//3-2. 메뉴 3번 입력시 프로그램 종료
		exit(0);
		break;
	default :
		printf("잘못 입력하셨습니다.\n");
		break;
	}
}
void no_money(){
	printf("===============================\n");
	printf("10원 갖고, 돈 갖고 오세요 ^^!!\n");
	printf("===============================\n");
	printf("프로그램을 종료 하겠습니다.\n");
	system("pause");
	exit(0);
}
void main(){
	while(1){
		if(money>=10){
			intro();
		}else{
			no_money();//3-1.사용자 금액이 10원 미만일경우 프로그램종료
		}
	}
}
