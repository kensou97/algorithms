/**
 flip game
 
 题意是4*4的棋盘，所有的格子都摆上棋子（棋子一面是黑色，另一面是白色），
 每次可以选择一个棋子翻过来（即白变黑或黑变白），不过翻的同时要同时将其上下左右相邻的棋子也一同翻过来。
 问最少多少次能翻到全黑或全白。
 
 棋子的状态可以用01表示，4*4棋盘的所有状态最多只用一个short就能表示了，状态一共有65536个。
 实际上如果考虑到黑白对称，以及棋盘的旋转对称，可能的状态数还会少得多。
 对这些状态枚举就可以了，因为要找最少的翻转次数，所以用宽搜逐步的找
 （先找翻一步可以到达的状态，再找二步可以到达的状态），直到找到目标状态为止。
 **/
#include<stdio.h>
#include<stdlib.h>
#define QUES_SIZE 65536

/**
 判断第i位的值，i（0-15）
 **/
int getBit(unsigned short value,int i){
    unsigned short mask=0x0001<<i;
    return (value&mask)==0?0:1;
}

/**
 设置第i位为j
 **/
void setBit(unsigned short *value,int i,int j){
    unsigned short mask=0x0001<<i;
    if(j==0){
        mask=~mask;
        *value=(*value)&mask;
    }else{
        *value=(*value)|mask;
    }
}

int flip(unsigned short value, int i){
    int tmp=value;
    
    setBit(&value,i,1-getBit(tmp,i));
    int j;
    if(i%4!=0){
        j=i-1;
        if(j>-1){
            setBit(&value,j,1-getBit(tmp,j));
        }
    }
    if(i%4!=3){
        j=i+1;
        if(j<16){
            setBit(&value,j,1-getBit(tmp,j));
        }
    }
    j=i-4;
    if(j>-1){
        setBit(&value,j,1-getBit(tmp,j));
    }
    j=i+4;
    if(j<16){
        setBit(&value,j,1-getBit(tmp,j));
    }
    return value;
}

int main(void){
    unsigned short input_value=0x0400;
    int j;
    for(j=0;j<4;j++){
        char str[4];
        scanf("%s",str);
        int p=0;
        for(p=0;p<4;p++){
            if(str[p]=='b'){
                setBit(&input_value,15-4*j-p,0);
            }else{
                setBit(&input_value,15-4*j-p,1);
            }
        }
    }
    
    char contains[QUES_SIZE];
    unsigned short queue[QUES_SIZE];
    int steps[QUES_SIZE];
    
    int i=0;
    for(i=0;i<QUES_SIZE;i++){
        contains[i]='n';
    }
    
    int head=0;
    int tail=1;
    queue[head]=input_value;
    steps[input_value]=0;
    int flip_result;
    int head_value;
    int current_step;
    while(head<tail){
        head_value=queue[head];
        current_step=steps[head_value];
        if(head_value==0x0000||head_value==0xffff){
            printf("%d\n",0);
            return 0;
        }
        for(i=0;i<16;i++){
            flip_result=flip(head_value,i);
            if(contains[flip_result]=='n'){
                contains[flip_result]='y';
                queue[tail++]=flip_result;
                steps[flip_result]=current_step+1;
            }
            if(flip_result==0x0000||flip_result==0xffff){
                printf("%d\n",steps[flip_result]);
                return 0;
            }
        }
        head++;
    }
    printf("Impossible\n");
    return 0;	
}

