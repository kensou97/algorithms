/**
 题意是每次消去最大的可以消去的小球的集合，然后将小球做相应的下沉或者左移的操作，
 继续重复上述步骤，直到游戏结束。
 找最大的集合用宽搜或深搜都行吧，消去后的操作也是要注意好下标。
 **/
#include <stdio.h>
#include <string.h>

int N;
char a[10][16];

int left;
int score;
int visited[10][15];

int direction[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

/*
 深搜，返回从该点（算上该点）可以到达的点的总数
 进行多次深搜的话，每次搜索到的点的集合（即cluster），可以用flag来区别
 */
int dfs(int r,int c,int flag){
    int i;
    int nr;
    int nc;
    int count=1;
    visited[r][c]=flag;//设为已访问
    for(i=0;i<4;i++){
        nr=r+direction[i][0];
        nc=c+direction[i][1];
        if(nr>=0&&nr<10&&nc>=0&&nc<15){//是否越界
            if((!visited[nr][nc])&&(a[r][c]==a[nr][nc])){//没访问过且颜色相同
                count+=dfs(nr,nc,flag);
            }
        }
    }
    return count;
}

void solve(){
    int i,j;
    int move_index=1;
    int dfsflag=1;
    int max_cluster_size=1;
    int respective_r;
    int respective_c;
    int cluster_size;
    int max_cluster_flag;
    int move_score;
    while(1){
        if(left==0||left==1){//game over
            break;
        }
        dfsflag=1;
        max_cluster_size=1;
        for(i=0;i<15;i++){
            for(j=0;j<10;j++){//注意遍历顺序，先从下到上（row），再从左到右（col）
                if(!visited[j][i]){
                    cluster_size=dfs(j,i,dfsflag);
                    if(cluster_size>max_cluster_size){//记下最大的cluster的相关信息
                        max_cluster_size=cluster_size;
                        respective_r=j;
                        respective_c=i;
                        max_cluster_flag=dfsflag;
                    }
                    dfsflag++;//flag最大只能到151
                }
            }
        }
        if(max_cluster_size==1){//game over
            break;
        }
        
        //输出move信息
        left-=max_cluster_size;
        move_score=(max_cluster_size-2)*(max_cluster_size-2);
        score+=move_score;
        printf("Move %d at (%d,%d): ",move_index++,respective_r+1,respective_c+1);
        printf("removed %d balls of color %c, ",max_cluster_size,a[respective_r][respective_c]);
        printf("got %d points.\n",move_score);
        
        //消去之后的操作
        int index;
        int emptycol[15];
        memset(emptycol,0,sizeof(emptycol));
        //元素的下沉操作....
        for(i=0;i<15;i++){
            index=0;
            for(j=0;j<10;j++){
                if(visited[j][i]==max_cluster_flag||visited[j][i]==1000){
                    continue;
                }
                a[index][i]=a[j][i];
                visited[index][i]=0;
                index++;
            }
            if(index==0){//该列为空
                emptycol[i]=1;
            }
            for(j=index;j<10;j++){
                visited[j][i]=1000;//1000是已经消去元素的flag
            }
        }
        
        //如有空列，列左移操作
        index=0;
        for(i=0;i<15;i++){
            if(emptycol[i]){
                continue;
            }
            for(j=0;j<10;j++){
                a[j][index]=a[j][i];
                visited[j][index]=visited[j][i];
            }
            index++;
        }
        for(i=index;i<15;i++){
            for(j=0;j<10;j++){
                visited[j][i]=1000;
            }
        }
    }
    if(!left){
        score+=1000;
    }
    printf("Final score: %d, with %d balls remaining.\n",score,left);
}

void initialize(){
    left=150;
    score=0;
    memset(visited,0,sizeof(visited));
}

int main(void){
    scanf("%d",&N);
    int i,j;
    for(i=1;i<=N;i++){
        initialize();
        for(j=9;j>=0;j--){
            scanf("%s",a[j]);
        }
        printf("Game %d:\n\n",i);
        solve();
        printf("\n");
    }
    return 0;
}