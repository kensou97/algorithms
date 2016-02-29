/**
 挺好的字符串动态规划，比较好想，状态方程也比较好写。
 **/
#include <stdio.h>
#include <string.h>

char first[201];
char second[201];
char str[401];

int d[201][201];

int dp(int i,int j){
    if(d[i][j]!=-1){
        return d[i][j];
    }
    if(i==0){//first用完，比较剩下的second和str
        if(strncmp(second,str,j)==0){
            d[i][j]=1;
            return 1;
        }
        d[i][j]=0;
        return 0;
    }
    if(j==0){
        if(strncmp(first,str,i)==0){
            d[i][j]=1;
            return 1;
        }
        d[i][j]=0;
        return 0;
    }
    char a=first[i-1];
    char b=second[j-1];
    char c=str[i+j-1];
    if(c!=a&&c!=b){//都不等，false
        d[i][j]=0;
        return 0;
    }
    if(c==a&&c!=b){//只等于a，消耗first一个字符
        d[i][j]=dp(i-1,j);
        return d[i][j];
    }
    if(c!=a&&c==b){
        d[i][j]=dp(i,j-1);
        return d[i][j];
    }
    //a==b==c
    if(dp(i-1,j)||dp(i,j-1)){
        d[i][j]=1;
        return 1;
    }
    d[i][j]=0;
    return 0;
}

int main(void){
    int N,i;
    scanf("%d",&N);
    for(i=1;i<=N;i++){
        memset(d,-1,sizeof(d));
        scanf("%s %s %s",first,second,str);
        if(dp((int)strlen(first),(int)strlen(second))){
            printf("Data set %d: yes\n",i);
        }else{
            printf("Data set %d: no\n",i);
        }	
    }
    return 0;
}