/**
 求最大生成树中权值最小的边，构造树的时候要注意只要1和n通了就可以结束了，也就是说可能不用构造出完整的n-1条边。
 **/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tEdge{
    int x;
    int y;
    int w;
}Edge;

Edge e[500000];
int n,m;
int set[1001];

int cmp(const void* x,const void* y){
    return ((Edge*)y)->w-((Edge*)x)->w;
}

int find(int i){
    int j=i;
    while(i!=set[i]){
        i=set[i];
    }
    set[j]=i;
    return i;
}

int kruskal(void){
    qsort(e,m,sizeof(Edge),cmp);
    int i=0;
    int x,y;
    int min=1000001;
    while(1){
        x=find(e[i].x);
        y=find(e[i].y);
        if(x==y){
            i++;
            continue;
        }
        set[x]=y;
        min=e[i].w<min?e[i].w:min;
        if(find(n)==find(1)){
            return min;
        }
        i++;
    }
    return min;
}

int main(void){
    int T,i,j,x,y,w;
    scanf("%d",&T);
    for(i=1;i<=T;i++){
        scanf("%d %d",&n,&m);
        for(j=1;j<=n;j++){
            set[j]=j;
        }
        for(j=0;j<m;j++){
            scanf("%d %d %d",&x,&y,&w);
            e[j].x=x;
            e[j].y=y;
            e[j].w=w;
        }
        printf("Scenario #%d:\n",i);
        printf("%d\n\n",kruskal());
    }
    return 0;
}