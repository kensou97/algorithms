/**
 位操作
 **/
#include <stdio.h>

int main(void){
    unsigned int R;
    int x;
    int y;
    
    scanf("%x,%d,%d",&R,&x,&y);
    
    R&=(~(1<<x));
    R|=(1<<y--);
    R|=(1<<y--);
    R&=(~(1<<y));
    
    printf("%x\n",R);
    return 0;
}