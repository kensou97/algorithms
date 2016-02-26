/**
题目大意是给两个串s和t，判断s是不是t的子序列（这个子序列和LCS中子序列的概念是一样的，即s中的字符只要按顺序在t中出现就好了，不一定是连续出现的）。
定义i和j分别是s和t的下标（均从0开始），然后判断s[i]==t[j]吗，如果==，i和j各增1，如果!=，j增1，然后看看s和t哪个先到达串尾'\0'就可以了。
**/
#include <stdio.h>
char s[100001];
char t[100001];
int main(void){
    int i,j;
    while(scanf("%s %s",s,t)!=EOF){
        i=0;
        j=0;
        while(s[i]&&t[j]){
            if(s[i]==t[j]){
                i++;
                j++;
            }else{
                j++;
            }
        }
        if(!s[i]){
            printf("Yes\n");
        }else{
            printf("No\n");
        }
    }
    return 0;
}