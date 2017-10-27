#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct student {
	int id;
	char name[32];
	int kor,eng,math,sum;
	float avg;
	char grade;
	int rank;
	struct student *link;
};

char get_grade(float avg){
	if(avg >= 90){
		return 'A';
	}else if(avg >= 80){
		return 'B';
	}else if(avg >= 70){
		return 'C';
	}else if(avg >= 60){
		return 'D';
	}else if(avg >= 50){
		return 'E';
	}else{
		return 'F';
	}
}

void make_rank(struct student **ST){
	struct student *cur;
	struct student *cmp;
	int rank;


	if((*ST)->link == NULL){
		(*ST)->rank = 1;
	}
	cur = *ST;
	while(cur){
		rank = 1;
		cmp = *ST;
		while(cmp){
			if(cur->avg < cmp->avg){
				rank++;
			}
			cmp = cmp->link;
		}
		cur->rank = rank;
		cur = cur->link;
	}
}
void insert_use_link(struct student **ST){
	char buf[32];

	(*ST)->id = 1000;
	printf("insert\n");

	printf(" 이름 : ");
	fflush(stdin);
	scanf("%s",buf);

	strcpy((*ST)->name,buf);

	printf(" 국어 성적 : ");
	scanf("%d",&(*ST)->kor);

	printf(" 영어 성적 : ");
	scanf("%d",&(*ST)->eng);

	printf(" 수학 성적 : ");
	scanf("%d",&(*ST)->math);

	(*ST)->sum = (*ST)->kor+(*ST)->eng+(*ST)->math;
	(*ST)->avg = (float)(*ST)->sum/3;
	(*ST)->grade = get_grade((*ST)->avg);
	(*ST)->link = NULL;
	make_rank(ST);
}

void output(struct student *ST){
	printf("|%4s|%10s|국어|영어|수학|합계|%7s|등급|등수|\n","ID","이름","평균");
	while(ST){
			printf("|%4d|%10s|%4d|%4d|%4d|%4d| %6.2f| %2c |%4d|\n",
			(*ST).id,(*ST).name,(*ST).kor,(*ST).eng,(*ST).math,(*ST).sum,(*ST).avg,(*ST).grade,(*ST).rank);
			ST = (*ST).link;
	}
}

int insert(struct student **ST){
	struct student *tmp;
	struct student *search;

	tmp = (struct student*)malloc(sizeof(struct student));

	insert_use_link(&tmp);
	if(*ST==NULL){
		*ST = tmp;
	}else{
		search = *ST;
		while(search){
			if(search->link == NULL){
				search->link = tmp;
				break;
			}
			search = search->link;
		}
	}
	return 0;
}

int choose_menu(struct student **ST){
	char select;
	int ret=0;


	printf("<< 학생 성적 관리 프로그램 >>\n");
	printf(" 1. 입력\n");
	printf(" 2. 출력\n");
	printf(" 3. 수정 / 삭제\n");
	printf(" 4. save\n");
	printf(" 5. load\n");
	printf(" 0. 종료\n\n");
	printf(" > ");
	fflush(stdin);
	scanf("%c",&select);

	switch(select){
	case '1':
		insert(ST);
		break;

	case '2' :
		output(*ST);
		break;

	case '3' :
	//	modify_delete(ST);
		break;

	case '4' :
	//	save(ST);
		break;
	case '5' :
	//	load(ST);
		break;

	case '0' :
		ret = 1;
		break;

	default :
		break;
	}

	return ret;
}

int main(){
	int ret = 0;
	struct student *ST = NULL;

	while(1){
		if(ret=choose_menu(&ST)){
			break;
		}
	}
	return 0;
}
