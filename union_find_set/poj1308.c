/**
 并查集判断一下是不是连通图，然后数组统计一下顶点的入度信息就好了，
 构成树的条件是：只有一个节点入度为0，其他所有的入度为1。
 **/
#include <stdio.h>
#include <string.h>

int indegree[100];
int treenode[100];
int nc;
int occ[100];
int set[100];

int find(int i){
    int j=i;
    while(i!=set[i]){
        i=set[i];
    }
    set[j]=i;
    return i;
}

void union_set(int i,int j){
    i=find(i);
    j=find(j);
    set[i]=j;
}

void initialize(void){
    nc=0;
    memset(indegree,0,sizeof(indegree));
    memset(occ,0,sizeof(occ));
    int i;
    for(i=0;i<100;i++){
        set[i]=i;
    }
}

int check(void){
    if(nc==0){
        return 1;
    }
    int t=find(treenode[0]);
    int zc=0;
    int oc=0;
    int i,d;
    for(i=0;i<nc;i++){
        if(find(treenode[i])!=t){
            return 0;
        }
        d=indegree[treenode[i]];
        if(d==0){
            zc++;
        }
        if(d==1){
            oc++;
        }
    }
    if(zc==1&&oc==nc-1){
        return 1;
    }
    return 0;
}

int main(void){
    int x,y;
    int i=1;
    while(1){
        scanf("%d %d",&x,&y);
        if(x<0&&y<0){
            break;
        }
        if(x==0&&y==0){
            if(check()){
                printf("Case %d is a tree.\n",i++);
            }else{
                printf("Case %d is not a tree.\n",i++);
            }
            initialize();
            continue;
        }
        
        union_set(x,y);
        if(!occ[x]){
            treenode[nc++]=x;
            occ[x]=1;
        }
        if(!occ[y]){
            treenode[nc++]=y;
            occ[y]=1;
        }
        indegree[y]++;
    }
    return 0;
}