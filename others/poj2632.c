/**
 简单模拟
 **/
#include <stdio.h>
#include <string.h>

typedef struct tRobot{
    int x;
    int y;
    int d;
}Robot;

int A,B,N,M;
Robot r[101];
int occ[101][101];

int directions[4][2]={{0,1},{1,0},{0,-1},{-1,0}};

int get_direction(char* str){
    if(str[0]=='N'){
        return 0;
    }
    if(str[0]=='E'){
        return 1;
    }
    if(str[0]=='S'){
        return 2;
    }
    return 3;
}

int main(void){
    int K,i,j,x,y,rn,re,d,fail;
    char str[2];
    scanf("%d",&K);
    while(K--){
        scanf("%d %d",&A,&B);
        scanf("%d %d",&N,&M);
        memset(occ,0,sizeof(occ));
        fail=0;
        for(i=1;i<=N;i++){
            scanf("%d %d %s",&x,&y,str);
            r[i].x=x;
            r[i].y=y;
            occ[x][y]=i;
            r[i].d=get_direction(str);
        }
        for(i=0;i<M;i++){
            scanf("%d %s %d",&rn,str,&re);
            if(fail){
                continue;
            }
            if(str[0]=='L'){
                r[rn].d=(r[rn].d+3*re)%4;
                continue;
            }
            if(str[0]=='R'){
                r[rn].d=(r[rn].d+re)%4;
                continue;
            }
            x=r[rn].x;
            y=r[rn].y;
            d=r[rn].d;
            for(j=0;j<re;j++){
                occ[x][y]=0;
                x+=directions[d][0];
                y+=directions[d][1];
                if(x<=0||x>A||y<=0||y>B){
                    fail=1;
                    printf("Robot %d crashes into the wall\n",rn);
                    break;
                }
                if(occ[x][y]){
                    fail=1;
                    printf("Robot %d crashes into robot %d\n",rn,occ[x][y]);
                    break;
                }
            }
            r[rn].x=x;
            r[rn].y=y;
            occ[x][y]=rn;
        }
        if(!fail){
            printf("OK\n");
        }
    }
    return 0;
}