/**
 好像编译原理里边东西的简化版，
 只有一个产生式S->CSS|DSS|ESS|ISS|NS|p-z（CDEIN都是终结符）
 **/
#include <stdio.h>
#include <string.h>

char str[257];

char* legal(char* str){//str开头的字符串是否合法，如果合法，返回合法语句的下一个位置
    char c=str[0];
    if(c>='p'&&c<='z'){
        return str+1;
    }
    char* s1;
    char* s2;
    if(c=='N'){
        s1=legal(str+1);
        return s1;
    }
    if(c=='C'||c=='D'||c=='E'||c=='I'){
        s1=legal(str+1);
        if(s1){
            s2=legal(s1);
            return s2;
        }
        return NULL;
    }
    return NULL;
}

int main(void){
    int len;
    while(scanf("%s",str)!=EOF){
        len=(int)strlen(str);
        if(str+len==legal(str)){
            printf("YES\n");
        }else{
            printf("NO\n");
        }
    }
    return 0;
}