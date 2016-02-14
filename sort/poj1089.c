/**
 先按照左端点排序，再根据右端点进行合并。
 **/
#include <stdio.h>
#include <stdlib.h>

typedef struct tInterval{
    int a;
    int b;
}Interval;

int N;

Interval ins[50000];
int unioned[50000];

int cmp(const void* x,const void* y){//按左端点排序
    return ((Interval*)x)->a-((Interval*)y)->a;
}

int main(void){
    scanf("%d",&N);
    
    int i;
    for(i=0;i<N;i++){
        scanf("%d %d",&(ins[i].a),&(ins[i].b));
        unioned[i]=0;
    }
    
    qsort(ins,N,sizeof(Interval),cmp);
    
    Interval* current=ins;
    for(i=1;i<N;i++){
        if(ins[i].a>current->b){//两个区间无交集
            current=ins+i;
            continue;
        }
        
        unioned[i]=1;
        if(ins[i].b>current->b){//区间合并，改改右端点就可以了
            current->b=ins[i].b;
        }
    }
    
    for(i=0;i<N;i++){
        if(!unioned[i]){
            printf("%d %d\n",ins[i].a,ins[i].b);
        }
    }
    return 0;
}