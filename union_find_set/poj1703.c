/*
 并查集
 
 敌人的敌人就是朋友.....
 */
#include <stdio.h>
#define Q 100001

int N;
int M;
int friend[Q];
int enemy[Q];
int rank[Q];

int find(int i){
    int j=i;
    while(i!=friend[i]){
        i=friend[i];
    }
    friend[j]=i;
    return i;
}

int union_set(int i,int j){
    if(i==0||j==0){
        return i|j;
    }
    i=find(i);
    j=find(j);
    if(rank[i]>rank[j]){
        friend[j]=i;
        return i;
    }
    if(rank[i]<rank[j]){
        friend[i]=j;
        return j;
    }
    friend[j]=i;
    rank[i]++;
    return i;
}

int main(void){
    int T;
    int i,j,ti,tj;
    char c;
    scanf("%d",&T);
    while(T--){
        scanf("%d %d",&N,&M);
        getchar();
        for(i=1;i<=N;i++){
            friend[i]=i;
            enemy[i]=0;
            rank[i]=0;
        }
        while(M--){
            scanf("%c %d %d",&c,&i,&j);
            getchar();
            i=find(i);
            j=find(j);
            if(c=='A'){
                if(N==2){
                    printf("In different gangs.\n");
                    continue;
                }
                if(i==j){
                    printf("In the same gang.\n");
                }else{
                    if(enemy[i]==j){
                        printf("In different gangs.\n");
                    }else{
                        printf("Not sure yet.\n");
                    }
                }
            }else{
                tj=union_set(j,enemy[i]);//敌人的敌人就是朋友
                ti=union_set(i,enemy[j]);
                enemy[ti]=tj;
                enemy[tj]=ti;
            }
        }
    }
    return 0;
}