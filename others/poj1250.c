/**
 简单模拟
 **/
#include <stdio.h>
#include <string.h>

int N;
int used;
int inbed[26];
char str[55];
int result;

int main(void){
    while(1){
        scanf("%d",&N);
        if(N==0){
            break;
        }
        scanf("%s",str);
        
        used=0;
        memset(inbed,0,sizeof(inbed));
        result=0;
        
        int i=0;
        int j;
        char c;
        while((c=str[i++])!='\0'){
            j=(int)(c-'A');
            if(inbed[j]){
                inbed[j]=0;
                used--;
            }else{
                if(used<N){
                    used++;
                    inbed[j]=1;
                }else{
                    result++;
                }
            }
        }
        if(result){
            printf("%d customer(s) walked away.\n",result/2);
        }else{
            printf("All customers tanned successfully.\n");
        }
    }	
    return 0;
}