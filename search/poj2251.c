/*
 三维的迷宫找最短路，当然是宽搜了。不好估计队列会膨胀到多大时，用链表好些.....
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tPoint{
    int level;
    int row;
    int col;
    int steps;//步数
    struct tPoint* next;
}Point;

int L;
int R;
int C;
char ch[30][30][31];
int visited[30][30][30];

int directions[6][3]={{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};

Point* head;
Point* tail;

int target_level;
int target_row;
int target_col;

Point* create_point(int level,int row,int col,int steps){
    Point* p=(Point*)malloc(sizeof(Point));
    p->level=level;
    p->row=row;
    p->col=col;
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

int bfs(void){
    Point* p;
    int tl,nl;
    int tr,nr;
    int tc,nc;
    int tsteps;
    int i;
    while(head){
        p=dequeue();
        tl=p->level;
        tr=p->row;
        tc=p->col;
        tsteps=p->steps;
        free(p);
        if(tl==target_level&&tr==target_row&&tc==target_col){
            return tsteps;
        }
        for(i=0;i<6;i++){
            nl=tl+directions[i][0];
            nr=tr+directions[i][1];
            nc=tc+directions[i][2];
            if(nl>=0&&nl<L&&nr>=0&&nr<R&&nc>=0&&nc<C){//是否越界
                if((ch[nl][nr][nc]=='.')&&(!visited[nl][nr][nc])){//是否有墙，是否访问过
                    visited[nl][nr][nc]=1;
                    enqueue(create_point(nl,nr,nc,tsteps+1));
                }
            }
        }
    }
    //队列空，说明找不到
    return -1;
}

int main(void){
    int i,j,k;
    int result;
    while(1){
        scanf("%d %d %d",&L,&R,&C);
        if(L==0&&R==0&&C==0){
            break;
        }
        
        head=NULL;
        tail=NULL;
        memset(visited,0,sizeof(visited));
        int nos=1;
        int noe=1;
        for(i=0;i<L;i++){
            for(j=0;j<R;j++){
                scanf("%s",ch[i][j]);
                if(nos){
                    k=0;
                    while(ch[i][j][k]){
                        if(ch[i][j][k]=='S'){
                            head=create_point(i,j,k,0);
                            tail=head;
                            nos=0;
                            break;
                        }
                        k++;
                    }
                }
                if(noe){
                    k=0;
                    while(ch[i][j][k]){
                        if(ch[i][j][k]=='E'){
                            ch[i][j][k]='.';
                            target_level=i;
                            target_row=j;
                            target_col=k;
                            noe=0;
                            break;
                        }
                        k++;
                    }
                }
            }
        }
        result=bfs();
        if(result==-1){
            printf("Trapped!\n");
        }else{
            printf("Escaped in %d minute(s).\n",result);
        }
    }
    return 0;
}