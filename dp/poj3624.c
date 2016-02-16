/**
 01背包
 
 之所以自下而上是因为节省空间...用自上而下会MLE
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N;
int M;

int dp[13000];
int W[3500];
int V[3500];

void zero_one_pack(int value,int weight){
    int j;
    int take;
    for(j=M;j>=weight;j--){
        take=dp[j-weight]+value;
        dp[j]=dp[j]>take?dp[j]:take;
    }
}

int main(void){
    scanf("%d",&N);
    scanf("%d",&M);
    
    int i;
    for(i=0;i<N;i++){
        scanf("%d",W+i);
        scanf("%d",V+i);
    }
    memset(dp,0,sizeof(dp));
    for(i=0;i<N;i++){
        zero_one_pack(V[i],W[i]);
    }
    
    printf("%d\n",dp[M]);
    return 0;
}