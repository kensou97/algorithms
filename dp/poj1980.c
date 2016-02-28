/**
 从最后一位匹配，要么是字母配字母，要么是字母配空格，要么是空格配字母，在三种方案里选择一个较大的就可以了。
 **/
#include <stdio.h>
#define INF -999999
char a[101];
char b[101];
int score[5][5]={{5,-1,-2,-1,-3},{-1,5,-3,-2,-4},{-2,-3,5,-2,-2},{-1,-2,-2,5,-1},{-3,-4,-2,-1,0}};
char dna[]="ACGT-";
int dp[101][101];

int calscore(char x,char y){//算分
    if(x==y){
        return 5;
    }
    int i,j;
    for(i=0;i<5;i++){
        if(dna[i]==x){
            break;
        }
    }
    for(j=0;j<5;j++){
        if(dna[j]==y){
            break;
        }
    }
    return score[i][j];
}

int lcs(int x,int y){
    if(dp[x][y]!=INF){
        return dp[x][y];
    }
    if(x==0||y==0){
        char* tc=x==0?b:a;
        int tl=x==0?y:x;
        int re=0;
        int i;
        for(i=0;i<tl;i++){
            re+=calscore(tc[i],'-');
        }
        dp[x][y]=re;
        return re;
    }
    int n1=lcs(x-1,y-1)+calscore(a[x-1],b[y-1]);//三种可行方案
    int n2=lcs(x-1,y)+calscore(a[x-1],'-');
    int n3=lcs(x,y-1)+calscore(b[y-1],'-');
    n1=n1>n2?n1:n2;
    n1=n1>n3?n1:n3;
    dp[x][y]=n1;
    return n1;
}

int main(void){
    int T,la,lb,i,j;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&la);
        scanf("%s",a);
        scanf("%d",&lb);
        scanf("%s",b);
        for(i=0;i<=la;i++){
            for(j=0;j<=lb;j++){
                dp[i][j]=INF;
            }
        }
        printf("%d\n",lcs(la,lb));
    }
    return 0;	
}