/**
 括号编码
 **/
#include <stdio.h>
#include <string.h>

int N;
int a[40];

void p_to_w(){
    int i;
    int j;
    for(i=0;i<2*N;i++){
        if(a[i]==1){
            j=i-1;
            while(a[j]){
                j--;
            }
            a[j]=1;
            printf("%d ",(i-j+1)/2);
        }
    }
    printf("\n");
}

int main(void){
    int T;
    int i;
    int P;
    scanf("%d",&T);
    while(T--){
        memset(a,0,sizeof(a));
        scanf("%d",&N);
        for(i=0;i<N;i++){
            scanf("%d",&P);
            a[P+i]=1;
        }
        
        p_to_w();
    }
    return 0;
}