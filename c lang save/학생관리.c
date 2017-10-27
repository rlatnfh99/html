#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int id;
	char name[32];
	int kor,eng,math,sum;
	float avg;
	char grade;
	int rank;
	student *link
}student;


int get_id(int index){
	int id=1000;

	return id+index;

}

int get_index(student *ST, int n){
	int i;

	if(ST == NULL){
		return 0;
	}
	for(i=0;i<n;i++){
		if(ST[i].id != 1000+i){
			return i;
		}
	}

	return -1;
}

int get_sum(student *ST, int index){
	int sum = ST[index].math+ST[index].kor+ST[index].eng;

	return sum;
}
float get_avg(student *ST, int index){
	float avg = (float)(get_sum(ST,index))/3;

	return avg;
}

char get_grade(student *ST, int index){
	if(ST[index].avg >= 90){
		return 'A';
	}else if(ST[index].avg >= 80){
		return 'B';
	}else if(ST[index].avg >= 70){
		return 'C';
	}else if(ST[index].avg >= 60){
		return 'D';
	}else if(ST[index].avg >= 50){
		return 'E';
	}else{
		return 'F';
	}
}

void make_rank(student *ST, int n){
	int i,j,rank;

	for(i=0;i<n;i++){
		rank = 1;
		for(j=0;j<n;j++){
			if(ST[j].id && ST[i].avg<ST[j].avg){
				rank++;
			}
		}
		ST[i].rank = rank;
	}
}
void insert_use_index(student *ST,int n, int index){
	char buf[32];

	ST[index].id = get_id(index);
	printf("insert\n");

	printf(" 이름 : ");
	fflush(stdin);
	scanf("%s",buf);

	strcpy(ST[index].name,buf);

	printf(" 국어 성적 : ");
	scanf("%d",&ST[index].kor);

	printf(" 영어 성적 : ");
	scanf("%d",&ST[index].eng);

	printf(" 수학 성적 : ");
	scanf("%d",&ST[index].math);

	ST[index].sum = get_sum(ST,index);
	ST[index].avg = get_avg(ST,index);
	ST[index].grade = get_grade(ST,index);
	make_rank(ST,n);
}

int insert(student *ST, int n){

	int index;

	index = get_index(ST,n);
	if(index < 0){
		return -1;
	}

	insert_use_index(ST,n,index);


	return 0;
}
void output(student *ST, int n){
	int i;
	printf("output\n");

	printf("|%4s|%10s|국어|영어|수학|합계|%10s|등급|등수|\n","ID","이름","평균");
	for(i=0;i<n;i++){
		if(ST[i].id){
			printf("|%4d|%10s|%4d|%4d|%4d|%4d| %6.2f| %2c | %2d |\n",ST[i].id,ST[i].name,ST[i].kor,ST[i].eng,ST[i].math,ST[i].sum,ST[i].avg,ST[i].grade,ST[i].rank);
		}
	}
}
int get_index_use_id(student *ST, int n,int id){
	int i;

	for(i=0;i<n;i++){
		if(ST[i].id==id){
			return i;
		}
	}
	return -1;
}
int modify_st(student *ST, int n){
	int input_id;
	char index;

	while(1){
		printf("ID를 입력하세요 : ");
		scanf("%d",&input_id);
		if(input_id == 0){
			return 0;
		}
		index = get_index_use_id(ST,n,input_id);
		if(index<0){
			printf("잘못된 ID입니다.\n");
			continue;
		}
		insert_use_index(ST,n,index);

		return 1;
	}
}

void delete_st(student *ST, int n){
	int input_id;
	char index;

	while(1){
		printf("ID를 입력하세요 : ");
		scanf("%d",&input_id);
		if(input_id == 0){
			return;
		}
		index = get_index_use_id(ST,n,input_id);

		if(index<0){
			printf("잘못된 ID입니다.\n");
			continue;
		}
		ST[index].id = 0;
		make_rank(ST,n);
		return;
	}
}

void modify_delete(student *ST, int n){
	int select;

	printf("modify&delete\n");
	printf("  1 : 수정\n");
	printf("  2 : 삭제\n");
	printf("   > ");
	scanf("%d",&select);

	switch(select){
	case 1 :
		modify_st(ST,n);
		break;
	case 2 :
		delete_st(ST,n);
		break;

	default :
		break;
	}
}

void load(student *ST, int n){
	FILE *f = fopen("save.txt","r");
	int i=0;
	int fcnt=0;
	char y_n=0;

	if(f==NULL){
		printf("파일이 없습니다.\n");
		return;
	}
	fscanf(f,"%d",fcnt);
	if(fcnt!=n){
		printf("데이터는 %d명의 데이터 입니다.\n");
		printf("현재 학생수는 %d 입니다. 학생수를 변경하시겠습니까?(y,n)");
		scanf("%c",y_n);
		if(y_n=='y'){
			printf("변경하실 학생수를 입력해주세요");
			scanf("%c",y_n);
		}
	}
	for(i=0;i<n;i++){
		fscanf(f,"%d %s %d %d %d %d %f %c %d\n",&ST[i].id,ST[i].name,&ST[i].kor,&ST[i].eng,&ST[i].math,&ST[i].sum,&ST[i].avg,&ST[i].grade,&ST[i].rank);
	}
	fclose(f);
}

void save(student *ST){
	int i;
	FILE *f = fopen("save.txt","w");

	fprintf(f,"%d\n",n);
	for(i=0;i<n;i++){
		if(ST[i].id){
			fprintf(f,"%d %s %d %d %d %d %f %c %d\n",ST[i].id,ST[i].name,ST[i].kor,ST[i].eng,ST[i].math,ST[i].sum,ST[i].avg,ST[i].grade,ST[i].rank);
		}else{
			fprintf(f,"0\n");
		}
	}
	fclose(f);
}
int choose_menu(student *ST){
	char select;
	int insert_ret;
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
		insert_ret=insert(ST);
		if(insert_ret<0){
			printf("더 이상 추가 할수 없습니다.\n");
		}
		break;

	case '2' :
		output(ST);
		break;

	case '3' :
		modify_delete(ST);
		break;

	case '4' :
		save(ST,n);
		break;
	case '5' :
		load(ST,n);
		break;

	case '0' :
		ret = 1;
		break;

	default :
		break;
	}

	return ret;
}

void make_st(student **ST){
	student tmp;

	return;
}


int main(){
	int ret = 0;
	student *ST;


	make_st(&ST);
	while(1){
		if(ret=choose_menu(ST)){
			break;
		}
	}
	return 0;
}
