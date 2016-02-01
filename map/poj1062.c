/*
 题意说的比较复杂，不过大体是个稍微有点改动的dijkstra算法，为什么说是稍有改动呢，
 因为多了一个等级的限制，也就是说有向图G中所有的边在不同的等级限制下只能出现一部分，
 这个限制就是顶点之间的等级（level）之差要小于等于M。
 */
#include <stdio.h>
#include <string.h>
int M;//等级差距
int N;//物品总数

int L[101];//主人等级
int X[101];//替代品总数

int d[101][101];//替代关系的权值
int dcopy[101][101];

int visited[101];

int level_list[101];
int level_list_size;

void init_dcopy(int level){
    int i,j;
    for(i=0;i<=N;i++){
        for(j=0;j<=N;j++){
            if(i==0||j==0){
                dcopy[i][j]=d[i][j];
            }else{
                if(L[i]<level||L[j]<level||L[i]-level>M||L[j]-level>M){
                    dcopy[i][j]=-1;
                }else{
                    dcopy[i][j]=d[i][j];
                }
            }
        }
    }
}

/**
 *目标是找0到1（酋长）的最短路
 */
int dijkstra(){
    memset(visited,0,sizeof(visited));
    
    int step=N-1;
    int i;
    int min_v;
    int min_i=0;
    while(step--){//最多进行N-1次
        min_v=d[0][1]+1;
        for(i=1;i<=N;i++){//找到未访问的权值最小的顶点
            if(!visited[i]){
                if(dcopy[0][i]<min_v){
                    min_i=i;
                    min_v=dcopy[0][i];
                }
            }
        }
        
        if(min_i==1){//找到到1（酋长）的最短路了，不用继续了
            return min_v;
        }
        
        visited[min_i]=1;
        
        for(i=1;i<=N;i++){
            if(visited[i]){//用找到的顶点松弛未访问的顶点
                continue;
            }
            if(dcopy[min_i][i]!=-1&&min_v+dcopy[min_i][i]<dcopy[0][i]){//松弛
                dcopy[0][i]=min_v+dcopy[min_i][i];
            }
        }
    }
    return dcopy[0][1];
    
}

int findlevel(int level){
    int i;
    for(i=0;i<level_list_size;i++){
        if(level_list[i]==level){
            return 1;
        }
    }
    return 0;
}



int main(void){
    memset(d,-1,sizeof(d));
    level_list_size=0;
    
    scanf("%d %d",&M,&N);
    int i,j;
    int P,T,V;
    for(i=1;i<=N;i++){
        scanf("%d %d %d",&P,&L[i],&X[i]);
        d[0][i]=P;
        d[i][0]=P;
        for(j=0;j<X[i];j++){
            scanf("%d %d",&T,&V);
            d[T][i]=V;//这地方是有向图，刚开始当成无向图了，WA的蛋疼菊紧.....
        }
    }
    
    int min_cost=d[0][1];
    int cost;
    for(i=1;i<=N;i++){
        if(!findlevel(L[i])){
            level_list[level_list_size++]=L[i];
            init_dcopy(L[i]);
            cost=dijkstra();
            if(cost<min_cost){
                min_cost=cost;
            }
        }
    }
    
    printf("%d\n",min_cost);
    return 0;
}