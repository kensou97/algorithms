/**
 排列组合的问题，算出当前串前面的串共有多少个。
 **/
#include <stdio.h>
#include <string.h>

int c[27][27];

int cal(char* str){//vwxyz
    char ch='a'-1;
    int i=0,j,k;
    while(str[i]){//字符串是否严格升序，顺便求长度
        if(str[i]<=ch){
            return 0;
        }
        ch=str[i];
        i++;
    }
    
    int len=i;
    
    int index=0;
    for(i=1;i<len;i++){//长度小于当前串长度的个数，比如对于串vwxyz，那么此处就是c(26,1)+c(26,2)+c(26,3)+c(26,4)
        index+=c[26][i];
    }
    
    j=str[0]-'a';
    for(i=0;i<j;i++){//当前串第一个字母前有多少个，此处就是a-u开头的len为5的串的数目
        index+=c[25-i][len-1];
    }
    
    i=1;//剩下的字母（只有第一位是比较特殊的，从第二位开始都一样）
    while(i<len){//wxyz
        k=(int)(str[i]-'a');
        for(j=(int)(str[i-1]-'a')+1;j<k;j++){
            index+=c[25-j][len-1-i];
        }
        i++;
    }
    return index+1;
}

int main(void){
    int i;
    int j;
    for(i=0;i<27;i++){
        for(j=0;j<=i;j++){
            if(j==0||i==j){
                c[i][j]=1;
            }else{
                c[i][j]=c[i-1][j]+c[i-1][j-1];
            }
        }
    }
    
    char str[11];	
    while(scanf("%s",str)!=EOF){
        printf("%d\n",cal(str));
    }
    return 0;
}