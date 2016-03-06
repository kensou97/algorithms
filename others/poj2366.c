/**
 一个升序数组A，一个降序数组B，给一个sum，问是否存在i和j，使sum=A[i]+B[j]。
 可以考虑用hash，将Ahash之后，遍历B，查找sum-B[j]。
 
 这里我用的是另一种方法。初始化i和j为0，那么此时A[i]是A中最小的元素，B[j]是B中最大的元素，计算t=A[i]+B[j]，
 如果t==sum，那么找到结果了。
 如果t>sum，说明B[j]太大了，因为用A中能用的最小的元素它相加，结果都超过了sum，那么A中剩下的其他元素和B[j]相加就更大了，因此可以直接拿掉B[j]了，j++。
 如果t<sum，同理，可以拿掉A[i]。可以看出，该过程是线性复杂度。
 
 小扩展下，求某个数组中是否存在两个元素，其和是sum。如果直接遍历的话，是N^2复杂度，如果先排序，再利用上述方法，从数组两端点往中间找，是NlgN+N，要更优一些。
 **/
#include <stdio.h>
int na;
int nb;
int a[50000];
int b[50000];

int find(void){
    int i=0;
    int j=0;
    int sum;
    while(i<na&&j<nb){
        sum=a[i]+b[j];
        if(sum==10000){
            return 1;
        }
        if(sum<10000){
            i++;
        }else{
            j++;
        }
    }
    return 0;
}

int main(void){
    int i;
    scanf("%d",&na);
    for(i=0;i<na;i++){
        scanf("%d",a+i);
    }
    scanf("%d",&nb);
    for(i=0;i<nb;i++){
        scanf("%d",b+i);
    }
    if(find()){
        printf("YES\n");
    }else{
        printf("NO\n");
    }
    
    return 0;
}