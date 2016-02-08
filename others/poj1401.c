/**
 可以将N！做个质因子分解，里边肯定有5^x这一项，目标就是求x的值。
 也就是说有多少个5，就有多少个0 。
 **/
#include <stdio.h>

int cal(int num){
    int sum=0;
    int i;
    for(i=5;i<=num;i*=5){
        sum+=(num/i);
    }
    return sum;
}

int main(void){
    int T;
    int num;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&num);
        printf("%d\n",cal(num));
    }
    return 0;
}