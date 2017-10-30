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

int get_id(struct student **ST){
	struct student *tmp;
	int id=1000;
	int i=0;

	if(*ST==NULL){
		return id;
	}

	tmp = *ST;
	while(tmp){
		i++;
		if(tmp->link==NULL){
			return id+i;
		}
		tmp = tmp->link;

	}

	return id+i;
}


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

void insert_detail(struct student **ST){
	char buf[32];

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
}

void insert_use_link(struct student **root, struct student **ST){
	(*ST)->id = get_id(root);
	(*ST)->link = NULL;
	insert_detail(ST);
	return;
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

	insert_use_link(ST, &tmp);

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

int delete_link_use_id(struct student **ST,int input_id){
	struct student *tmp;
	struct student *search;
	if(*ST==NULL){
		printf("등록된 학생이 없습니다.\n");
		return 0;
	}


	if((*ST)->id == input_id){
		if((*ST)->link == NULL){
			free((*ST));
		} else {
			tmp = (*ST)->link;
			free((*ST));
			(*ST) = tmp;
		}
		return 1;
	}

	search = *ST;
	while(search){
		if(search->link == NULL){
			return -1;
		}
		if(search->link->id == input_id){
			tmp = search->link->link;
			free(search->link);
			search->link = tmp;
			return 1;
		}

		search = search->link;
	}
	return -1;
}
struct student* get_link_use_id(struct student **ST,int input_id){
	struct student *tmp;

	if(*ST==NULL){
		printf("등록된 학생이 없습니다.\n");
		return NULL;
	}

	tmp = *ST;

	while(tmp){
		if(tmp->id == input_id){
			return tmp;
		}
		if(tmp->link == NULL){
			return NULL;
		}
		tmp = tmp->link;
	}

	return NULL;
}

void delete_st(struct student **ST){
	int input_id,ret;

	while(1){
		printf("ID를 입력하세요 : ");
		scanf("%d",&input_id);
		if(input_id == 0){
			return;
		}
		ret = delete_link_use_id(ST,input_id);
		if(ret==0){
			break;
		}else if(ret== -1){
			printf("잘못된 ID를 입력하셨습니다.\n");
			continue;
		}else{
			printf("성공적으로 삭제되었습니다.\n");
		}
		return;
	}
}

void modify_st(struct student **ST){
	int input_id;
	struct student *tmp;

	while(1){
		printf("ID를 입력하세요 : ");
		scanf("%d",&input_id);
		if(input_id == 0){
			return;
		}
		tmp = get_link_use_id(ST,input_id);
		if(tmp==NULL){
			printf("잘못된 ID를 입력하셨습니다. 다시 입력해주세요.\n");
			continue;
		}
		insert_detail(&tmp);

		return;
	}
}

void modify_delete(struct student **ST){
	int select;

	printf("modify&delete\n");
	printf("  1 : 수정\n");
	printf("  2 : 삭제\n");
	printf("   > ");
	scanf("%d",&select);

	switch(select){
	case 1 :
		modify_st(ST);
		break;

	case 2 :
		delete_st(ST);
		break;

	default :
		break;
	}
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
		make_rank(ST);
		output(*ST);
		break;

	case '3' :
		modify_delete(ST);
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
