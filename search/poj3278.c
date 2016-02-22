/**
 宽搜
 
 给两个数N和K，每次能对N做三种操作中的一种，N=N+1，N=N-1或N=2*N，求要由N变换到K最少需要多少次这样的操作。
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tPoint{
    int x;
    int steps;
    struct tPoint* next;
}Point;

int visited[100001];

Point* head;
Point* tail;

Point* create_point(int x,int steps){
    Point* p=(Point*)malloc(sizeof(Point));
    p->x=x;
    p->steps=steps;
    p->next=NULL;
    return p;
}

void enqueue(Point* p){
    if(head){
        tail->next=p;
        tail=p;
        p->next=NULL;
    }else{
        head=p;
        tail=p;
    }
}

Point* dequeue(){
    Point* p=head;
    head=head->next;
    return p;
}

int bfs(int N,int K){
    head=create_point(N,0);
    tail=head;
    Point* p;
    int tx;
    int tsteps;
    int nx;
    while(head){
        p=dequeue();
        tx=p->x;
        tsteps=p->steps;
        free(p);
        if(tx==K){
            return tsteps;
        }
        nx=tx+1;
        if(nx>=0&&nx<=100000){
            if(!visited[nx]){
                visited[nx]=1;
                enqueue(create_point(nx,tsteps+1));
            }
        }
        nx=tx-1;
        if(nx>=0&&nx<=100000){
            if(!visited[nx]){
                visited[nx]=1;
                enqueue(create_point(nx,tsteps+1));
            }
        }
        nx=tx*2;
        if(nx>=0&&nx<=100000){
            if(!visited[nx]){
                visited[nx]=1;
                enqueue(create_point(nx,tsteps+1));
            }
        }
    }
    return -1;
}

int main(void){
    memset(visited,0,sizeof(visited));
    int N,K;
    scanf("%d %d",&N,&K);
    printf("%d\n",bfs(N,K));
    return 0;
}