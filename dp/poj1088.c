/**
 假设用f（i，j）表示以（i，j）为起点的最长区域的长度，用g上，g下 ，g左，g右表示通过上下左右四个方向递推过来的长度，
 那么f（i，j）=max{g上，g下，g左，g右}。那么每一个g又是如何得来的呢？以g上为例，如果矩阵（i，j）处的高度大于（i-1，j）的高度，
 那么g上=f（i-1，j）+1，否则g上=1。需要注意的是递推的时候要注意一下边界啊，不是每个点都有上下左右四个分量的。
 **/
#include <stdio.h>
#include <string.h>
int dp[100][100];
int height[100][100];
int R=0;
int C=0;
int main(void){
    scanf("%d %d",&R,&C);
    
    int i;
    int j;
    for(i=0;i<R;i++){
        for(j=0;j<C;j++){
            scanf("%d",&height[i][j]);
        }
    }
    
    memset(dp,-1,sizeof(dp));
    
    int maxlength=0;
    int length;
    for(i=0;i<R;i++){
        for(j=0;j<C;j++){
            if((length=longestpath(i,j))>maxlength){
                maxlength=length;
            }
        }
    }
    printf("%d\n",maxlength);
    return 0;
}

int longestpath(int i,int j){
    if(dp[i][j]!=-1){
        return dp[i][j];
    }
    int length=0;
    int left=1;
    int right=1;
    int up=1;
    int down=1	;
    
    //到4个方向扩展，扩展的时候注意边界
    if(j>0&&height[i][j]>height[i][j-1]){
        left=longestpath(i,j-1)+1;
    }
    if(j<C-1&&height[i][j]>height[i][j+1]){
        right=longestpath(i,j+1)+1;
    }
    if(i>0&&height[i][j]>height[i-1][j]){
        up=longestpath(i-1,j)+1;
    }
    if(i<R-1&&height[i][j]>height[i+1][j]){
        down=longestpath(i+1,j)+1;
    }
    left=left>right?left:right;
    up=up>down?up:down;
    length=left>up?left:up;
    dp[i][j]=length;
    return length;
}