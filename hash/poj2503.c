/*
 hash（线性开型）
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 100000
typedef struct tNode{
    char f[11];
    char e[11];
    struct tNode* next;
}Node;

Node* node[N];

unsigned int BKDRHash(char *str){
    unsigned int seed = 131;
    unsigned int hash = 0;
    while (*str){
        hash = hash * seed + (*str++);
    }
    return (hash & 0x7FFFFFFF);
}

Node* create_node(char* f,char* e){
    Node* n=(Node*)malloc(sizeof(Node));
    n->next=NULL;
    strcpy(n->f,f);
    strcpy(n->e,e);
    return n;
}

void insert(char* f,char* e){
    int i=BKDRHash(f)%N;
    Node* cn=node[i];
    if(!cn){
        node[i]=create_node(f,e);
        return;
    }
    while(cn){
        if(strcmp(cn->f,f)==0){
            return;
        }
        cn=cn->next;
    }
    cn=create_node(f,e);
    cn->next=node[i];
    node[i]=cn;
}

Node* search(char* f){
    int i=BKDRHash(f)%N;
    Node* cn=node[i];
    if(!cn){
        return NULL;
    }
    while(cn){
        if(strcmp(cn->f,f)==0){
            return cn;
        }
        cn=cn->next;
    }
    return NULL;
}

int main(void){
    memset(node,0,sizeof(node));
    char str[30];
    char e[11];
    char f[11];
    while(gets(str)&&str[0]!='\0'){
        sscanf(str,"%s %s",e,f);
        insert(f,e);
    }
    Node* nc;
    while(gets(f)&&f[0]!='\0'){
        nc=search(f);
        if(nc){
            printf("%s\n",nc->e);
            continue;
        }
        printf("eh\n");
    }
    return 0;
}