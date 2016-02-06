/**
 kmp
 **/
#include <stdio.h>
#include <string.h>
void getNext(char* t,int* next){
    int length=(int)strlen(t);
    int k=-1;
    int j=0;
    next[0]=-1;
    while(j<length){
        if(k==-1||t[k]==t[j]){
            k++;
            j++;
            next[j]=k;
        }else{
            k=next[k];
        }
    }
}
int main(void){
    char str[1000001];
    int next[1000001];
    int length=0;
    
    while(1){
        scanf("%s",str);
        length=(int)strlen(str);
        
        if((str[0]=='.')&&(length==1)){
            break;
        }
        getNext(str,next);
        if(length%(length-next[length])==0){
            printf("%d\n",length/(length-next[length]));
        }else{
            printf("1\n");
        }
    }
    return 0;
}