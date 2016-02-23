/**
 稍微有点变化的深搜，基础的深搜是每个顶点访问一次后涂黑，这里是有的顶点可能允许访问多次，比如题目中给的acba，
 这里的a最多可以访问两次，两次才涂黑，其它依次类推。
 注意题目中的字典序是这个顺序：'A'<'a'<'B'<'b'<...<'Z'<'z'。
 **/
#include <stdio.h>
#include <string.h>

int lower[26];//记录每个小写字母的次数
int upper[26];//大写

char str[100];

char print_str[100];
int myindex;

void dfs(int j,int isupper){
    int i;
    if(j==-1){
        for(i=0;i<26;i++){
            if(upper[i]){
                dfs(i,1);
            }
            if(lower[i]){
                dfs(i,0);
            }
        }
    }else{
        if(isupper){
            upper[j]--;
            print_str[myindex++]=(char)(j+'A');
        }else{
            lower[j]--;
            print_str[myindex++]=(char)(j+'a');
        }
        
        for(i=0;i<26;i++){
            if(upper[i]){
                dfs(i,1);
            }
            if(lower[i]){
                dfs(i,0);
            }
        }
        if(!str[myindex]){//一个排列形成
            printf("%s\n",print_str);
        }
        myindex--;
        
        if(isupper){
            upper[j]++;
        }else{
            lower[j]++;
        }
    }
}

int main(void){
    myindex=0;
    
    int N;
    scanf("%d",&N);
    while(N--){
        scanf("%s",str);
        memset(lower,0,sizeof(lower));
        memset(upper,0,sizeof(upper));
        
        int i=0;
        char c;
        while((c=str[i])!='\0'){
            if(c>='a'&&c<='z'){
                lower[(int)(c-'a')]++;
            }else{
                upper[(int)(c-'A')]++;
            }
            i++;
        }
        print_str[i]='\0';
        dfs(-1,0);
    }
    return 0;
}