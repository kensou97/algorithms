/*
 二分查找
 */
#include <stdio.h>
#include <stdlib.h>

int N,C;
int a[100000];

int cmp(const void* x,const void* y){
    return *((int*)x)-*((int*)y);
}

int can_put(int x){
    int i;
    int count=1;
    int t=a[0];
    for(i=0;i<N;i++){
        if(a[i]-t>=x){
            t=a[i];
            count++;
            if(count>=C){
                return 1;
            }
        }
    }
    return 0;
}

int main(void){
    int i,low,mid,high,re;
    scanf("%d %d",&N,&C);
    for(i=0;i<N;i++){
        scanf("%d",a+i);
    }
    qsort(a,N,sizeof(int),cmp);
    
    low=0;
    high=(a[N-1]-a[0])/(C-1);
    re=0;
    
    while(low<=high){
        mid=(low+high)/2;
        if(can_put(mid)){
            re=mid>re?mid:re;
            low=mid+1;
        }else{
            high=mid-1;
        }
    }
    printf("%d\n",re);
    return 0;
}