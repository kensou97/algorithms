/**
  最基本的题了，一直合并合并，最后数数集合的数量就好了
 **/
#include <stdio.h>

int n,m;
int set[50001];
int occ[50001];

int find(int i){
    int j=i;
    while(i!=set[i]){
        i=set[i];
    }
    set[j]=i;
    return i;
}

void union_set(int i,int j){
    i=find(i);
    j=find(j);
    set[i]=j;
}

int main(void){
    int i,x,y,result;
    int in=1;
    while(1){
        result=0;
        scanf("%d %d",&n,&m);
        if(n==0&&m==0){
            break;
        }
        for(i=1;i<=n;i++){
            set[i]=i;
            occ[i]=0;
        }
        for(i=0;i<m;i++){
            scanf("%d %d",&x,&y);
            union_set(x,y);
        }
        for(i=1;i<=n;i++){
            x=find(i);
            if(!occ[x]){
                occ[x]=1;
                result++;
            }
        }
        printf("Case %d: %d\n",in++,result);
    }
    return 0;
}