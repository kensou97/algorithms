/*
 题目是求中位数。其实可以归结为求第K大的数，中位数其实就是（length/2+1）大的数。
 算法导论上有讲过，当时那章好像叫顺序统计量。
 
 大体思路就是快排的一个改动，快排每次会选一个元素pivot，根据pivot将原数据分为左中右三部分（即partition操作），
 左边的元素不大于pivot，右边的元素不小于pivot。因此要找第K大的数的话，首先关心下右边那一部分的长度，
 因为右边的都是大数。
 
 不妨用right_length表示右侧的长度。
 1.如果right_length恰好等于K-1，那么pivot就是要找的元素了；
 2.如果right_length大于K-1，那么递归调用该过程在右侧继续找第K大的数；
 3.如果right_length小于K-1，那么递归调用该过程在左侧找第（K-（right_lengh+1））大的数。
 */
#include <stdio.h>
int num[10000];

/**
 找第k大的数
 */
int find(int k,int low,int high){
    int pivot=num[low];
    int i=low;
    int j=high;
    while(i<j){
        while(i<j&&num[j]>=pivot){
            j--;
        }
        while(i<j&&num[i]<=pivot){
            i++;
        }
        int temp=num[i];
        num[i]=num[j];
        num[j]=temp;
    }
    num[low]=num[j];
    num[j]=pivot;
    
    //下标很讨厌，可得算清楚了
    int right_length=high-j;
    if(right_length==k-1){
        return pivot;
    }else if(right_length<k-1){
        return find(k-(right_length+1),low,j-1);
    }else{
        return find(k,j+1,high);
    }
}

int main(void){
    int N;
    scanf("%d",&N);
    int i;
    for(i=0;i<N;i++){
        scanf("%d",num+i);
    }
    printf("%d\n",find(N/2+1,0,N-1));
    return 0;
}