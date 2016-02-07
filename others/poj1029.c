/**
 称硬币，三种考虑：
 1.如果天平平衡，那天平上的都是正常的。
 2.如果不平衡，那么不在天平上的都是正常的。
 3.如果一个硬币在某次称重时出现在了较轻的一端，某次称重时又出现在了较重的一端，那么它也是正常的。
 **/
#include <stdio.h>
#include <string.h>

int N,pi;
int coin[1001];
int left[501];
int right[501];
int left_o[1001];
int right_o[1001];

void setothers(){
    int i;
    for(i=1;i<=N;i++){
        if(left_o[i]||right_o[i]){
            continue;
        }
        coin[i]=1;
    }
}

int main(void){
    int i,j,K;
    char c[2];
    scanf("%d",&N);
    scanf("%d",&K);
    for(i=0;i<K;i++){
        memset(left_o,0,sizeof(left_o));
        memset(right_o,0,sizeof(right_o));
        scanf("%d",&pi);
        for(j=0;j<pi;j++){
            scanf("%d",left+j);
            left_o[left[j]]=1;
        }
        for(j=0;j<pi;j++){
            scanf("%d",right+j);
            right_o[right[j]]=1;
        }
        scanf("%s",c);
        if(c[0]=='='){
            for(j=0;j<pi;j++){
                coin[left[j]]=1;
                coin[right[j]]=1;
            }
        }
        if(c[0]=='>'){
            setothers();
            for(j=0;j<pi;j++){//left:-2,right:-1
                if(coin[left[j]]==1){
                    continue;
                }
                if(coin[left[j]]==-1){
                    coin[left[j]]=1;
                    continue;
                }
                coin[left[j]]=-2;
            }
            for(j=0;j<pi;j++){//left:-2,right:-1
                if(coin[right[j]]==1){
                    continue;
                }
                if(coin[right[j]]==-2){
                    coin[right[j]]=1;
                    continue;
                }
                coin[right[j]]=-1;
            }
        }
        if(c[0]=='<'){
            setothers();
            for(j=0;j<pi;j++){//left:-1,right:-2
                if(coin[right[j]]==1){
                    continue;
                }
                if(coin[right[j]]==-1){
                    coin[right[j]]=1;
                    continue;
                }
                coin[right[j]]=-2;
            }
            for(j=0;j<pi;j++){//left:-2,right:-1
                if(coin[left[j]]==1){
                    continue;
                }
                if(coin[left[j]]==-2){
                    coin[left[j]]=1;
                    continue;
                }
                coin[left[j]]=-1;
            }
        }
    }
    j=0;
    for(i=1;i<=N;i++){
        if(coin[i]==1){
            j++;
        }else{
            K=i;
        }
    }
    if(j==N-1){
        printf("%d\n",K);
    }else{
        printf("0\n");
    }
    return 0;
}