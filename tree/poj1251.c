/*
 prim 最小生成树
 */
#include <stdio.h>
#include <string.h>

int N;
int c[28][28];
int set[28];

int prim(void){
    set[0]=1;
    int i,j,min,mi=0,mj=0;
    int count=N-1;
    int result=0;
    while(count--){
        min=10000;
        for(i=0;i<N;i++){
            for(j=i+1;j<N;j++){
                if(set[i]+set[j]==1&&c[i][j]!=-1&&c[i][j]<min){//两个点所属集合不同且权值小于min
                    min=c[i][j];
                    mi=i;
                    mj=j;
                }
            }
        }
        result+=min;
        set[mi]=1;
        set[mj]=1;
    }
    return result;
}

int main(void){
    int i,j,e,value,sn,dn;
    char s[2];
    char d[2];
    while(1){
        scanf("%d",&N);
        if(N==0){
            break;
        }
        
        memset(c,-1,sizeof(c));
        memset(set,0,sizeof(set));
        
        for(i=0;i<N-1;i++){
            scanf("%s",s);
            scanf("%d",&e);
            sn=(int)(s[0]-'A');
            for(j=0;j<e;j++){
                scanf("%s %d",d,&value);
                dn=(int)(d[0]-'A');
                c[sn][dn]=value;
                c[dn][sn]=value;
            }
        }
        printf("%d\n",prim());
    }
    return 0;
}