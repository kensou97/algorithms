/*
 雪花（经典hash...）
 
 先根据雪花特征hash到不同的小集合，再在小集合范围内遍历比较。
 直接遍历的话会超时。
 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define HASH_SIZE 10000000

typedef struct tSnow{
    int a[6];
    struct tSnow* next;
}Snow;

int N;
Snow* snows[HASH_SIZE];

int equal(Snow* x,Snow* y){
    int* a=x->a;
    int* b=y->a;
    int i,j;
    for(i=0;i<6;i++){
        if(a[0]==b[i]){
            for(j=1;j<6;j++){
                if(a[j]!=b[(j+i)%6]){
                    break;
                }
            }
            if(j==6){
                return 1;
            }
            
            for(j=1;j<6;j++){
                if(a[6-j]!=b[(i+j)%6]){
                    break;
                }
           	}
            if(j==6){
                return 1;
            }
        }
    }
    return 0;
}

int hash(Snow* x){
    int sum=0;
    int* a=x->a;
    int i;
    for(i=0;i<6;i++){
        sum+=a[i];
    }
    return sum%HASH_SIZE;
}

int insert(Snow* x){
    int index=hash(x);
    Snow* current=snows[index];
    if(current){
        while(current){
            if(equal(current,x)){
                return 0;
            }
            current=current->next;
        }
        x->next=snows[index];
        snows[index]=x;
    }else{
        snows[index]=x;
    }
    return 1;
}


int main(void){
    memset(snows,0,sizeof(snows));
    scanf("%d",&N);
    int i,j;
    for(i=0;i<N;i++){
        Snow* snow=(Snow*)malloc(sizeof(Snow));
        snow->next=NULL;
        int* a=snow->a;
        for(j=0;j<6;j++){
            scanf("%d",a+j);
        }
        if(!insert(snow)){
            printf("Twin snowflakes found.\n");
            break;
        }
    }
    if(i==N){
        printf("No two snowflakes are alike.\n");	
    }
    return 0;
}