/**
 尝试用了随机算法，随机算法真的是很强大，可以将复杂的问题瞬间变为极其简单的问题，
 不过代价就是rp不好的时候结果可能会有误差，不过如果随机的次数足够多，这种误差几乎可以消除。
 
 我提交的时候随机200000次的时候会WA，700000次的时候就AC了。
 总之，重要的是这种问题转化的思想，如果一个问题正面很难攻克，不妨可以用随机算法做下近似，然后用巨大的随机次数弥补随机算法带来的不确定性。
 **/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int N;
int d[20][20];
int result;
int group[20];

void random_change(){
    int times=700000;
    int j;
    int sum=0;
    int choice;
    while(times--){
        choice=rand()%N;
        group[choice]=1-group[choice];//把该节点拿到另一个集合去，看结果会不会变大
        for(j=0;j<N;j++){
            if(group[j]==group[choice]){
                sum-=d[j][choice];
            }else{
                sum+=d[j][choice];
            }
        }
        result=sum>result?sum:result;
    }
}

int main(void){
    scanf("%d",&N);
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            scanf("%d",&d[i][j]);
        }
    }
    
    memset(group,0,sizeof(group));
    result=0;
    random_change();
    printf("%d\n",result);
    return 0;
}