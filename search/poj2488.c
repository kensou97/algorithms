/**
 按照马的行走规则，在棋盘上找一条路，恰好经过每个格子一次。
 比较基础的深搜，注意搜的时候8个方向是有先后顺序的（因为要求字典序输出）。
 **/
#include <stdio.h>
#include <string.h>

int p;
int q;
int visited[27][27];
char path[1400];
int path_index;

int direction[8][2]={{-2,-1},{-2,1},{-1,-2},{-1,2},{1,-2},{1,2},{2,-1},{2,1}};//方向数组

/**
 从当前点x,y开始走，（算上当前点）如果能走count个位置，则成功
 */
int dfs_visit(int x,int y,int count){//x is alpha,y is digit
    path[path_index++]=(char)('A'+x-1);//先记下路径
    path[path_index++]=(char)('0'+y);
    
    if(count==1){
        return 1;
    }
    
    visited[x][y]=1;//访问过了
    
    int i;
    int nextx,nexty;//下一个要访问的位置
    for(i=0;i<8;i++){
        nextx=x+direction[i][0];
        nexty=y+direction[i][1];
        if((nextx>=1)&&(nextx<=q)&&(nexty>=1)&&(nexty<=p)){//是否越界了
            if(!visited[nextx][nexty]){//是否访问过
                if(dfs_visit(nextx,nexty,count-1)){
                    return 1;
                }
                visited[nextx][nexty]=0;//回溯
            }
        }
    }
    path_index=path_index-2;//回溯
    return 0;
}

int main(void){
    int N;
    int i;
    scanf("%d",&N);
    for(i=1;i<=N;i++){
        scanf("%d %d",&p,&q);
        
        memset(visited,0,sizeof(visited));
        path_index=0;
        path[2*p*q]='\0';
        
        printf("Scenario #%d:\n",i);
        if(dfs_visit(1,1,p*q)){
            printf("%s\n",path);
        }else{
            printf("impossible\n");
        }
        printf("\n");		
    }
    return 0;
}