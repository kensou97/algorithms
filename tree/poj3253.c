/*
 huffman ＋ 最小堆
 */
#include <stdio.h>

int N;
long long a[20000];

/**
 *沿着堆下沉，直至找到它适合的位置（左右孩子的值都不小于它）
 */
void shiftdown(int i){
    int last_not_leaf=(N-2)/2;//最后一个非叶子节点
    int left;
    while(i<=last_not_leaf){
        left=2*i+1;
        if(left+1<N&&a[left]>a[left+1]){
            left++;
        }
        if(a[i]>a[left]){
            long long tmp=a[i];
            a[i]=a[left];
            a[left]=tmp;
            i=left;
        }else{
            break;
        }
    }
}

/**
 沿着堆上浮，直至找到它适合的位置（左右孩子的值都不小于它）
 */
void shiftup(int i){
    int parent=(i-1)/2;
    while(parent>-1){
        if(a[i]<a[parent]){
            long long tmp=a[i];
            a[i]=a[parent];
            a[parent]=tmp;
            i=parent;
            parent=(i-1)/2;
        }else{
            break;
        }
    }
}

/**
 *最小堆
 */
void initialize_heap(){
    int last_not_leaf=(N-2)/2;
    int i;
    for(i=last_not_leaf;i>-1;i--){//每个非叶子节点执行下沉操作
        shiftdown(i);
    }
}

/*
 *取出最小元素，将最后一个元素放到第一个元素的位置，并下沉
 */
long long heap(){
    long long result=a[0];
    a[0]=a[--N];
    shiftdown(0);
    return result;
}

/*
 *堆插入，插到最后一个元素，然后最后一个元素上浮
 */
void insert(long long value){
    N++;
    a[N-1]=value;
    shiftup(N-1);
}

int main(void){
    scanf("%d",&N);
    int i;
    for(i=0;i<N;i++){
        scanf("%lld",a+i);
    }
    
    initialize_heap();
    
    long long total_sum=0;
    long long sum;
    while(N>=2){
        sum=0;
        sum+=heap();//取出两个最小的
        sum+=heap();
        total_sum+=sum;
        insert(sum);//将他们的和插入回去
    }
    printf("%lld\n",total_sum);	
    return 0;
}