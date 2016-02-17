/**
 hash
 **/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define HASH_SIZE 9999

typedef struct tTrain{
    char str[100];
    struct tTrain* next;
}Train;

Train* train[HASH_SIZE];
char str[100];

unsigned int BKDRHash(char *str){//网上找的
    unsigned int seed = 131;
    unsigned int hash = 0;
    while (*str){
        hash = hash * seed + (*str++);
    }
    return (hash & 0x7FFFFFFF);
}

Train* create_train(char* str){
    Train* t=(Train*)malloc(sizeof(Train));
    strcpy(t->str,str);
    t->next=NULL;
    return t;
}

void reverse(char *word){//字符串反转
    int first, last;
    first = 0;
    last = (int)strlen(word);
    char c;
    while ((first != last) && (first != --last)){
        c=word[first];
        word[first]=word[last];
        word[last]=c;
        first++;
    }
}

int insert(char* str){
    unsigned int index=BKDRHash(str)%HASH_SIZE;
    Train* current=train[index];
    if(current){
        while(current){
            if(strcmp(current->str,str)==0){
                return 0;
            }
            current=current->next;
        }
        Train* t=create_train(str);
        t->next=train[index];
        train[index]=t;
        return 1;
    }
    train[index]=create_train(str);
    return 1;
}

int cal(){
    int count=0;
    int len=(int)strlen(str);
    int i,j;
    for(i=0;i<len-1;i++){
        for(j=0;j<2;j++){
            reverse(str+i+1);//每个字符串转成8个串
            count+=insert(str);
            reverse(str);
            count+=insert(str);
            reverse(str+len-i-1);
            count+=insert(str);
            reverse(str);
            count+=insert(str);
        }
    }
    return count;
}

void free_mem(){
    int i;
    Train* tmp;
    Train* t;
    for(i=0;i<HASH_SIZE;i++){
        t=train[i];
        while(t){
            tmp=t;
            t=t->next;
            free(tmp);
        }
    }
}

int main(void){
    int N;
    scanf("%d",&N);
    while(N--){
        memset(train,0,sizeof(train));
        scanf("%s",str);
        printf("%d\n",cal());
        free_mem();
    }
    return 0;
}