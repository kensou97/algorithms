#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int N;
int stick[64];
int used[64];

int cmp(const void* x,const void* y){
    return *((int*)y)-*((int*)x);
}

/**
 start:从这根小棍开始试
 sticks_left:还没使用的小棍的数目
 length:要拼凑的目标长度
 initlength:原始长度
 */
int combine(int start,int sticks_left,int length,int initlength){
    if(sticks_left==0&&length==0){
        return 1;
    }
    
    if(length==0){//目标长度变0了，说明拼出了完整的一根，继续拼下一根
        return combine(0,sticks_left,initlength,initlength);
    }
    
    int i;
    int fail_stick_length=-1;//记录上一次失败的小棍
    for(i=start;i<N;i++){
        if((!used[i])&&(stick[i]<=length)&&(stick[i]!=fail_stick_length)){
            used[i]=1;
            if(combine(i+1,sticks_left-1,length-stick[i],initlength)){
                return 1;
            }
            used[i]=0;
            fail_stick_length=stick[i];
            if(length==initlength||stick[i]==length){
                return 0;
            }
        }
    }
    
    return 0;
}

int main(void){
    int i;
    int sum;
    while(1){
        scanf("%d",&N);
        if(N==0){
            break;
        }
        
        sum=0;
        for(i=0;i<N;i++){
            scanf("%d",stick+i);
            sum+=stick[i];
        }
        
        memset(used,0,sizeof(used));
        qsort(stick,N,sizeof(int),cmp);
        
        for(i=stick[0];i<=sum;i++){
            if(sum%i){
                continue;
            }
            
            if(combine(0,N,0,i)){
                printf("%d\n",i);
            }
        }
    }
    
    return 0;
}