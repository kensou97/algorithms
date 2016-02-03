/*
 花店（dp）
 
 比较简单的动态规划，基本和背包差不多，需要注意的地方是初始化，还有就是花必须要保证原来的顺序。
 */
#include <stdio.h>
#define INF -999999
int F,V;
int A[100][100];
int d[100][100];

int dp(int f,int v){
    if(d[f][v]!=INF){
        return d[f][v];
    }
    if(f>v){//花瓶不够
        return INF;
    }
    if(f==v){//花瓶恰好够，按顺序放过来
        int i;
        int result=0;
        for(i=0;i<=v;i++){
            result+=A[i][i];
        }
        d[f][v]=result;
        return result;
    }
    int x=dp(f-1,v-1)+A[f][v];//f放入v
    int y=dp(f,v-1);//f不放入v
    x=x>y?x:y;
    d[f][v]=x;
    return x;
}

int main(void){
    scanf("%d %d",&F,&V);
    int i,j;
    for(i=0;i<F;i++){
        for(j=0;j<V;j++){
            scanf("%d",&A[i][j]);
            d[i][j]=INF;
        }
    }
    printf("%d\n",dp(F-1,V-1));
    return 0;
}