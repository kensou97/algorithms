/*
 丑数就是可以写成(2^x)*(3^y)*(5^z)这种形式的数字，其中xyz均为非负整数。
 可以看出，下一个丑数总是当前已计算的某个丑数或乘2或乘3或乘5得到。
 因此可以为2、3、5各维护一个指针（或者说游标吧），根据他们来生成下一个丑数，同时更新指针。
 比如，初始时三个指针均指向1，这时1*2和1*3和1*5三个数中，最小的是1*2，因此下一个丑数是2，
 同时2的指针指向下一个丑数，也就是2 。
 下一步比较2*2和1*3和1*5，发现1*3最小，因此下一个丑数是3，3的指针指向下一个丑数，也指向了2 。
 下一步比较2*2和2*3和1*5，发现2*2最小，因此2*2是下一个丑数，2的指针指向下一个丑数，也就是3 。
 然后是比较3*2和2*3和1*5..........依次类推
 */
#include <stdio.h>

int ugly[1500];

int main(void){
    ugly[0]=1;
    int index_2=0;
    int index_3=0;
    int index_5=0;
    
    int i;
    int multi_2=1;
    int multi_3=1;
    int multi_5=1;
    for(i=1;i<1500;i++){
        multi_2=ugly[index_2]*2;
        multi_3=ugly[index_3]*3;
        multi_5=ugly[index_5]*5;
        if(multi_2<=multi_3&&multi_2<=multi_5){
            ugly[i]=multi_2;
            index_2++;
        }
        if(multi_3<=multi_2&&multi_3<=multi_5){
            ugly[i]=multi_3;
            index_3++;
        }
        if(multi_5<=multi_2&&multi_5<=multi_3){
            ugly[i]=multi_5;
            index_5++;
        }
    }
    
    while(1){
        scanf("%d",&i);
        if(i==0){
            break;
        }
        printf("%d\n",ugly[i-1]);
    }
    
    return 0;
}