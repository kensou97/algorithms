/**
 一开始写的三维的，dp[l][t][st]代表从l湖开始，总共有t时间能钓到的鱼的最大数量，st代表的是已经在这个湖待的时间（因为鱼是随着时间不断减少的），
 这样算来应该是25*192*192，提交超时了。
 以为是因为某种情况没考虑到导致死循环了（以前超时经常是这个原因），就找了不少数据，把官方数据拿过来跑了个遍，结果都对，还是超时，那确实应该就是三维太大了。。。
 
 然后重新开始想状态该怎么设计，然后发现其实可以事先把每个湖待t时间所钓的鱼的总量先求出来，
 保存到fish[l][t]，l代表湖，t代表时间。然后那个三维的就变成二维的了。这就过了。
 **/
#include <stdio.h>
#include <string.h>

int n,h;
int fi[25];
int di[25];
int ti[24];

int fish[25][193];

int dt[25][193];
int waitTime[25][193];

int dp(int l,int t){
    if(t<=0){//不合法的时间
        return 0;
    }
    if(dt[l][t]!=-1){
        return dt[l][t];
    }
    if(l==n-1){//到最后一个湖了
        dt[l][t]=fish[l][t];
        waitTime[l][t]=t;
        return dt[l][t];
    }
    int max=-1;
    int i,x,maxi=0;
    for(i=0;i<=t;i++){//遍历在当前湖可以待的时间，0就相当于立刻去下一个湖了
        x=fish[l][i]+dp(l+1,t-i-ti[l]);
        if(x>=max){//一定是大于等于，说明鱼数量相同的情况下，在前一个池塘待尽量长的时间
            max=x;
            maxi=i;
        }
    }
    waitTime[l][t]=maxi;
    dt[l][t]=max;
    return max;
    
}

int main(void){
    int i,j,result,in;
    while(1){
        scanf("%d",&n);
        if(n==0){
            break;
        }
        scanf("%d",&h);
        h*=12;
        for(i=0;i<n;i++){
            scanf("%d",fi+i);
        }
        for(i=0;i<n;i++){
            scanf("%d",di+i);
            in=fi[i];
            fish[i][0]=0;
            for(j=1;j<=h;j++){
                fish[i][j]=in+fish[i][j-1];
                in-=di[i];
                in=in>=0?in:0;
            }
        }
        for(i=0;i<n-1;i++){
            scanf("%d",ti+i);
        }
        
        memset(dt,-1,sizeof(dt));
        
        result=dp(0,h);
        
        j=waitTime[0][h]+ti[0];
        printf("%d",5*waitTime[0][h]);
        for(i=1;i<=n-1;i++){
            h-=j;
            if(h>0){
                printf(", %d",5*waitTime[i][h]);
                j=(waitTime[i][h]+ti[i]);
            }else{
                printf(", 0");
            }
        }
        printf("\nNumber of fish expected: %d\n\n",result);
    }
    return 0;
}