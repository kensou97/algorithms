/*
 每个节点需要记录其与父节点的偏移，判断x和y吃与被吃的关系时，可以根据x、y与他们共同的祖先的偏移来判断。
 */

#include <stdio.h>
int N;
int p[50001];
int offset[50001];//与父节点之间的偏移

int find(int x){
    int o=0;
    int y=x;
    while(x!=p[x]){//找祖先，顺便计算和该祖先的偏移
        o+=offset[x];
        x=p[x];
    }
    p[y]=x;
    offset[y]=o%3;
    return x;
}

void union_set(int off,int i,int j){
    p[j]=i;
    offset[j]=off;
}

int check(int t,int x,int y){
    if(t==2&&x==y){
        return 1;
    }
    if(x>N||y>N){
        return 1;
    }
    int rx=find(x);
    int ry=find(y);
    if(rx!=ry){
        int off=offset[x]-offset[y]+t-1;//根据x与rx的偏移、y与ry的偏移、x与y的偏移，计算rx与ry之间的偏移
        off=off<0?off+3:off;
        off%=3;
        union_set(off,rx,ry);
        return 0;
    }
    //rx==ry
    if(t==1&&offset[x]==offset[y]){
        return 0;
    }
    if(t==2&&(offset[x]+1)%3==offset[y]){
        return 0;
    }
    return 1;
}

int main(void){
    int K;
    int t,x,y;
    int result=0;
    scanf("%d %d",&N,&K);
    for(t=1;t<=N;t++){
        p[t]=t;
    }
    while(K--){
        scanf("%d %d %d",&t,&x,&y);
        result+=check(t,x,y);
    }
    printf("%d\n",result);
    return 0;
}