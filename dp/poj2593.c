/**
给一个数组，求两段子序列，使他们的和最大。
对某个位置i，先求出以它为终点（也就是左侧）的最大和的子串，保存到l[i]，再求出以它为起点（也就是右侧）的最大和的子串，保存到r[i]。
然后根据r[i]计算出i右侧的最大和的子串（这里不一定是以i为起点的，只要起点在i右侧的就可以，这是和r[i]的区别），r[i]可以复用，直接存到r[i]里就可以了。
然后枚举下i的位置，计算出最大的。
 **/
#include <stdio.h>
#define INF -999999999

int n;
int a[100000];
int l[100000];
int r[100000];

int main(void){
    int i,result,t;
    while(1){
        scanf("%d",&n);
        if(!n){
            break;
        }
        for(i=0;i<n;i++){
            scanf("%d",a+i);
        }
        
        l[0]=a[0];
        for(i=1;i<n;i++){//i为终点
            t=l[i-1]+a[i];
            l[i]=t>a[i]?t:a[i];
        }
        
        r[n-1]=a[n-1];
        for(i=n-2;i>-1;i--){//i为起点
            t=r[i+1]+a[i];
            r[i]=t>a[i]?t:a[i];
        }
        
        for(i=n-2;i>-1;i--){//i右侧
            r[i]=r[i]>r[i+1]?r[i]:r[i+1];
        }
        
        result=INF;
        for(i=0;i<n-1;i++){
            t=l[i]+r[i+1];
            result=t>result?t:result;
        }
        printf("%d\n",result);
    }
    return 0;
}