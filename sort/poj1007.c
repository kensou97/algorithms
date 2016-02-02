/*
 归并排序求逆序数
 
 题意是给一堆DNA序列，根据各个DNA序列的逆序数排序。
 这题稍微特殊点，序列的构成元素只有ACGT，因此看到discuss里有人说是可以O（n）求逆序数的（通过统计ACGT的个数），
 但是我因为想练练归并的方法，所以用的归并，复杂度当然是O（nlgn）了，好在也16ms过了。
 
 求逆序数也算是分治法的一个典型了，记得算法导论的习题上有这个。
 比如对某个数组，从中间一分为二变为left和right两部分，那么逆序数就等于下面三个部分的和：
 1.left的逆序数；2.right的逆序数；3.跨越left和right的逆序数。
 
 对于1和2继续递归，因此主要在于求3 。3是可以用线性复杂度求解的，
 主要是要充分利用这个条件：求3的时候（就是merge的时候）left和right两部分已经是各自有序的了。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tDNA{
    char str[101];
    int i;//逆序数
}DNA;

DNA dnas[100];

int n;//串长度
int m;//串的个数

int cmp(const void* x,const void* y){
    return ((DNA*)x)->i-((DNA*)y)->i;
}

int merge(char* str,int low,int mid,int high){
    int count=0;
    if(low<high){
        int i=low;
        int j=mid;
        int k=0;
        
        char* tmp=(char*)malloc(high-low+1);
        
        while(i<mid&&j<=high){
            if(str[i]<=str[j]){
                tmp[k++]=str[i++];
                count+=(j-mid);
            }else{
                tmp[k++]=str[j++];
            }
        }
        while(i<mid){
            tmp[k++]=str[i++];
            count+=(high-mid+1);//这个地方要留意下，一开始漏了这个地方
        }
        while(j<=high){
            tmp[k++]=str[j++];
        }
        
        memcpy(str+low,tmp,high-low+1);
        free(tmp);
    }
    
    return count;
}

/**
 *归并排序的过程中求逆序数
 */
int inversion(char* str,int low,int high){
    int count=0;
    if(low<high){
        int mid=(low+high)/2;
        count+=inversion(str,low,mid);
        count+=inversion(str,mid+1,high);
        count+=merge(str,low,mid+1,high);
    }
    return count;
}

int main(void){
    scanf("%d %d",&n,&m);
    int i;
    char str[101];
    for(i=0;i<m;i++){
        scanf("%s",str);
        strcpy(dnas[i].str,str);
        dnas[i].i=inversion(str,0,n-1);
    }
    
    qsort(dnas,m,sizeof(DNA),cmp);
    
    for(i=0;i<m;i++){
        printf("%s\n",dnas[i].str);
    }
    return 0;
}

