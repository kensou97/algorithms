/**
 堆
 **/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int T,m,n;
int a[2010];
int b[2010];
int hs;

int cmp(const void* x,const void* y){
    return *((int*)x)-*((int*)y);
}

void shiftdown(int i){
    int last_not_leaf=(hs-2)/2;//最后一个非叶子节点
    int left;
    while(i<=last_not_leaf){
        left=2*i+1;
        if(left+1<hs&&a[left]<a[left+1]){
            left++;
        }
        if(a[i]<a[left]){
            int tmp=a[i];
            a[i]=a[left];
            a[left]=tmp;
            i=left;
        }else{
            break;
        }
    }
}

void shiftup(int i){
    int parent=(i-1)/2;
    while(parent>-1){
        if(a[i]>a[parent]){
            int tmp=a[i];
            a[i]=a[parent];
            a[parent]=tmp;
            i=parent;
            parent=(i-1)/2;
        }else{
            break;
        }
    }
}

void initialize_heap(){
    int i;
    for(i=0;i<n;i++){
        a[i]=1000001;
    }
}

int heap(){
    int result=a[0];
    a[0]=a[--hs];
    shiftdown(0);
    return result;
}

int look_heap(){
    return a[0];
}

void insert(int value){
    hs++;
    a[hs-1]=value;
    shiftup(hs-1);
}

int main(void){
    int i,j,k,c;
    int sum;
    scanf("%d",&T);
    while(T--){
        scanf("%d %d",&m,&n);
        hs=n;
        for(i=0;i<n;i++){
            scanf("%d",b+i);
        }
        for(i=1;i<m;i++){
            initialize_heap();
            for(j=0;j<n;j++){
                scanf("%d",&c);
                for(k=0;k<n;k++){
                    sum=b[k]+c;
                    if(sum<look_heap()){
                        heap();
                        insert(sum);
                    }
                }
            }
            memcpy(b,a,n*sizeof(int));
        }
        if(m>=2){
            for(i=n-1;i>=0;i--){
                b[i]=heap();
            }
        }else{
            qsort(b,n,sizeof(int),cmp);
        }
        for(i=0;i<n;i++){
            printf("%d ",b[i]);
        }
        printf("\n");
    }
    return 0;
}