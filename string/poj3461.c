/**
 kmp
 **/
#include <stdio.h>
#include <string.h>

char W[10010];
char T[1000010];
int next[11111];

void getNext(void){
    int length=(int)strlen(W);
    int k=-1;
    int j=0;
    next[0]=-1;
    while(j<length){
        if(k==-1||W[k]==W[j]){
            k++;
            j++;
            next[j]=k;
        }else{
            k=next[k];
        }
    }
}

int kmp(void){
    int i=0;
    int j=0;
    int wlength=(int)strlen(W);
    int length=(int)strlen(T);
    int count=0;
    
    while(i<length){
        if(j==-1||T[i]==W[j]){
            i++;
            j++;
        }else{
            j=next[j];
        }
        if(j==wlength){
            count++;
            j=next[wlength];
        }
    }
    return count;
}

int main(void){
    int N;
    scanf("%d",&N);
    while(N--){
        scanf("%s",W);
        scanf("%s",T);
        getNext();
        printf("%d\n",kmp());		
    }
    return 0;
}