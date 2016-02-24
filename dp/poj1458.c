/**
 最长公共子序列
 **/
#include <stdio.h>
#include <string.h>
int dp[500][500];
int lcs(char* str1,char* str2,int len1,int len2){
    if(dp[len1][len2]!=-1){
        return dp[len1][len2];
    }
    if(len1==0||len2==0){
        dp[len1][len2]=0;
        return 0;
    }
    if(str1[len1-1]==str2[len2-1]){//最后一个字符相等，那该字符肯定是lcs的一部分
        dp[len1][len2]=lcs(str1,str2,len1-1,len2-1)+1;
        return dp[len1][len2];
    }else{//最后一个字符不等
        dp[len1-1][len2]=lcs(str1,str2,len1-1,len2);
        dp[len1][len2-1]=lcs(str1,str2,len1,len2-1);
        dp[len1][len2]=dp[len1-1][len2]>dp[len1][len2-1]?dp[len1-1][len2]:dp[len1][len2-1];//挑一个大的
        return dp[len1][len2];
    }
}
int main(void){
    char str1[500];
    char str2[500];
    int len1=0;
    int len2=0;
    
    while(scanf("%s %s",str1,str2)!=EOF){
        memset(dp,-1,sizeof(dp));
        len1=(int)strlen(str1);
        len2=(int)strlen(str2);
        printf("%d\n",lcs(str1,str2,len1,len2));
    }
    return 0;
}

