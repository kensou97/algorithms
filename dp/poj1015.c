/**
 dp（n，m，r）代表前n个里边选m个，使D(J)-P(J)==r，dp（n，m，r）记录此时的D(J)+P(J) 。
 这地方因为r有可能是负数，所以要先做一下处理了。
 具体的写法有点像背包。然后可以从r==0开始往数轴两边算，直到有一种方案可行，就找到当前最优的了。
 **/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int n,m;
int p[201];
int d[201];
int t[201];
int dt[201][21][801];
int path[201][21][801];
int parray[20];

int cmp(const void* x,const void* y){
    return *((int*)x)-*((int*)y);
}

int dp(int nn,int mm,int re){//前nn个里选mm个，使D(J) - P(J)==re
    if(dt[nn][mm][re]!=-1){
        return dt[nn][mm][re];
    }
    if(nn<mm||nn<0||mm<0){
        return -1;
    }
    if(mm==0){
        path[nn][mm][re]=-1;
        if(re==0){
            return 0;
        }
        return -2;
    }
    if(nn==mm){//恰好够
        int i;
        int s=0;
        int sp=0;
        for(i=0;i<nn;i++){//全选上试试行不行
            s+=t[i];
            sp+=(p[i]+d[i]);
        }
        if(s==re){//全选上恰好符合要求
            for(i=nn;i>0;i--){
                path[i][i][s]=i-1;//全选上
                s-=t[i-1];
            }
            dt[nn][mm][re]=sp;
            return sp;
        }
        dt[nn][mm][re]=-2;
        return -2;
    }
    //nn>mm
    int x=dp(nn-1,mm,re);//不选
    int y=dp(nn-1,mm-1,re-t[nn-1]);//选
    if(x==-2&&y==-2){//选或不选都走不通
        dt[nn][mm][re]=-2;
        return -2;
    }
    //至少有一个能走通
    if(x==-2){//“选” 走通
        y+=(p[nn-1]+d[nn-1]);
        dt[nn][mm][re]=y;
        path[nn][mm][re]=nn-1;
        return y;
    }
    if(y==-2){//“不选” 走通
        dt[nn][mm][re]=x;
        path[nn][mm][re]=-1;//-1代表不选
        return x;
    }
    //x!=-2&&y!=-2
    //走到这，说明选不选该点都能走通
    //那就继续根据和判断，挑选和较大的一个
    y+=(p[nn-1]+d[nn-1]);
    if(x<y){
        path[nn][mm][re]=nn-1;
        x=y;
    }else{
        path[nn][mm][re]=-1;
    }
    dt[nn][mm][re]=x;
    return x;
}

int main(void){
    int i,e=0,f=0,x,nn,mm;
    int j=1;
    while(1){
        scanf("%d %d",&n,&m);
        if(n==0&&m==0){
            break;
        }
        
        memset(dt,-1,sizeof(dt));//初始化
        memset(parray,-1,sizeof(parray));
        
        for(i=0;i<n;i++){
            scanf("%d %d",p+i,d+i);
            t[i]=p[i]+20-d[i];
        }
        
        x=20*m;
        for(i=0;i<=x;i++){
            e=dp(n,m,x+i);//以x为起始往两边找
            f=dp(n,m,x-i);
            if(e!=-2||f!=-2){
                break;
            }
        }
        
        i=e>f?i:-i;
        e=e>f?e:f;
        x+=i;
        printf("Jury #%d\n",j++);
        printf("Best jury has value %d for prosecution and value %d for defence:\n",(e+i)/2,(e-i)/2);
        
        f=0;
        nn=n;
        mm=m;
        for(i=0;i<n;i++){//顺着找路径
            e=path[nn][mm][x];
            if(e!=-1){//选择了某个点
                mm--;
                x-=t[nn-1];//扣除掉该点的信息
                parray[f++]=e;
            }
            nn--;//nn始终减1
        }
        qsort(parray,m,sizeof(int),cmp);
        for(i=0;i<m;i++){
            printf(" %d",parray[i]+1);
        }
        printf("\n\n");
    }
    return 0;
}