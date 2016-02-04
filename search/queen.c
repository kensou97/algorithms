/*
 八皇后
 */
#include <stdio.h>
#define N 8

int row[N];
int myindex;
int count;

int can_put(int r,int c){
    int i;
    for(i=0;i<myindex;i++){//(row[i],i) and (r,c)
        if(row[i]==r){//同行
            return 0;
        }
        if(row[i]-i==r-c){//y=x+b
            return 0;
        }
        if(row[i]+i==r+c){//y=-x+b
            return 0;
        }
    }
    return 1;
}

void print_result(){
    int i;
    int j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if(row[j]==i){
                printf("*");
            }else{
                printf("O");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void try(int left_count){
    int current_col=N-left_count;
    int i;
    for(i=0;i<N;i++){//i,current_col
        if(can_put(i,current_col)){
            row[myindex++]=i;
            if(left_count!=1){
                try(left_count-1);
            }else{
                print_result();//找到可行解，输出结果
                count++;
            }
            myindex--;//回溯
        }
    }
}

int main(void){
    count=0;
    myindex=0;
    try(N);
    printf("%d\n",count);
    return 0;
}