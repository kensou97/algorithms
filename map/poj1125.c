/**
 floyd
 **/
#include <stdio.h>
#include <string.h>

int N;
int d[101][101];

void floyd(void){
    int i,j,k;
    for(k=1;k<=N;k++){
        for(i=1;i<=N;i++){
            if(i==k){
                continue;
            }
            for(j=1;j<=N;j++){
                if((k==j)||(i==j)){
                    continue;
                }
                if((d[i][k]!=-1)&&(d[k][j]!=-1)&&((d[i][j]==-1)||(d[i][j]>d[i][k]+d[k][j]))){
                    d[i][j]=d[i][k]+d[k][j];
                }
            }
        }
    }
}

int main(void){
    int i,j;
    int vcount;
    while(1){
        scanf("%d",&N);
        if(N==0){
            break;
        }
        
        memset(d,-1,sizeof(d));
        
        for(i=1;i<=N;i++){
            scanf("%d",&vcount);
            while(vcount--){
                scanf("%d",&j);
                scanf("%d",&d[i][j]);
            }
        }
        
        floyd();
        
        int min_source=1;
        int result=-1;
        int row_max;
        for(i=1;i<=N;i++){
            row_max=-1;
            for(j=1;j<=N;j++){
                if(i==j){
                    continue;
                }
                if(d[i][j]==-1){//存在该点到达不了的点，因此不能选它做起点
                    row_max=-1;
                    break;
                }
                if(d[i][j]>row_max){
                    row_max=d[i][j];
                }
            }
            if(row_max!=-1&&(result==-1||row_max<result)){
                min_source=i;
                result=row_max;
            }
        }
        if(result==-1){//没有一个点可以到其他各点，图不连通
            printf("disjoint\n");
        }else{
            printf("%d %d\n",min_source,result);
        }
    }
    return 0;
}