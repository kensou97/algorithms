/*
 铺地板（动态规划）
 
 题意是给定高度h宽度w的矩形，用1*2的小矩形填满它，问有多少种方式。
 关键是状态的表示，可以用01对地板状态进行编码，比如11代表横着铺，上0下1代表竖着铺，
 每行所有可能的编码有2^w-1种，将这些状态记录下来，然后逐行递推就可以了。
 
 不妨用dp[i][state]记录i行，编码状态为state的铺法的总数。
 对i行的某个编码状态state，如果它能和i-1行的某个状态state_x匹配（也就是能成功无缝隙的铺好），
 那么dp[i][state]+=dp[i-1][state_x]，把i-1行所有能和它匹配的全加上，就计算出了dp[i][state]。
 不难看出，最后一行不允许有竖着铺的，那样会突出去，因此最后一排是全1，所以最终所求为dp[h-1][2^w-1] 。
 */
#include <stdio.h>
#include <string.h>

int h,w;

long long d[11][1<<12];
int end;

int digit(int x,int i){
    return x&(1<<i);
}

/*
 行（状态编码为x）是否能铺在行（状态编码为y）下面
 */
int match(int x,int y){//x是本行，y是上一行
    int i=0;
    int dx,dy;
    while(i<w){
        dx=digit(x,i);
        dy=digit(y,i);
        if(dx==0){
            if(dy==0){//如果上一行是0，那么本行必须是1，否则地板填不满
                return 0;
            }
            i++;
            continue;
        }
        //dx==1
        if(dy==0){
            i++;
            continue;
        }
        dx=digit(x,i+1);
        dy=digit(y,i+1);
        if(dx==0||dy==0){//1必须成对出现
            return 0;
        }
        i+=2;
    }
    return 1;
}

long long dp(int r,int state){
    if(d[r][state]){
        return d[r][state];
    }
    if(r==0){
        if(match(state,end)){//第一行和全1匹配就行，成功取1，不成功取0
            d[0][state]=1;
            return 1;
        }
        d[0][state]=0;
        return 0;
    }
    
    int i=0;
    long long result=0;
    while(i<=end){
        if(match(state,i)){
            result+=dp(r-1,i);
        }
        i++;
    }
    d[r][state]=result;
    return result;
}

int main(void){
    while(1){
        scanf("%d %d",&h,&w);
        if(h==0&&w==0){
            break;
        }
        if((h*w)&1){//奇数跳过
            printf("0\n");
            continue;
        }
        memset(d,0,sizeof(d));
        end=(1<<w)-1;
        printf("%lld\n",dp(h-1,end));//最后一行必须全1
    }
    return 0;
}