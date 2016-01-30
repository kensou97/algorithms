/*
 数独dfs
 
 做法肯定就是dfs了，只是dfs之前最好做些处理。
 将所有未知的点可以填的数字算出来，每个数字称为一个候选，每一个未知点的候选的个数称为候选数。
 那么最好对所有未知的点根据候选数做个排序，然后dfs的时候从小到大进行。
 做不做排序还是差很多的，不做的话可能会超时。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tPoint{//未知点
    int row;
    int col;
    int cand_count;//候选个数
    int cand[10];//各个候选的值
}Point;

Point unknown_points[81];
int unknown_count;
int occur[10];

int o[9][9];

int cmp(const void* x,const void* y){
    return ((Point*)x)->cand_count-((Point*)y)->cand_count;
}

/*
 计算（row，col）位置的候选数字
 */
void candidate(int ci,int row,int col){
    memset(occur,0,sizeof(occur));
    unknown_points[ci].cand_count=0;
    int i,j;
    for(i=0;i<9;i++){
        occur[o[row][i]]=1;//行
        occur[o[i][col]]=1;//列
    }
    row/=3;
    col/=3;
    for(i=3*row;i<3*row+3;i++){//3*3方格
        for(j=3*col;j<3*col+3;j++){
            occur[o[i][j]]=1;
        }
    }
    
    for(i=1;i<=9;i++){
        if(!occur[i]){//i在行、列、3*3方格中均未出现，添加为候选
            unknown_points[ci].cand[unknown_points[ci].cand_count++]=i;
        }
    }
}

/*
 判断（row，col）位置能否放value
 */
int can_put(int row,int col,int value){
    int i,j;
    for(i=0;i<9;i++){
        if(o[row][i]==value){//行
            return 0;
        }
        if(o[i][col]==value){//列
            return 0;
        }
    }
    row/=3;
    col/=3;
    for(i=3*row;i<3*row+3;i++){//3*3方格
        for(j=3*col;j<3*col+3;j++){
            if(o[i][j]==value){
                return 0;
            }
        }
    }
    return 1;
}

int dfs(int current){
    if(current==unknown_count){
        return 1;
    }
    int i;
    int cand_count=unknown_points[current].cand_count;
    int row=unknown_points[current].row;
    int col=unknown_points[current].col;
    for(i=0;i<cand_count;i++){//遍历候选
        if(can_put(row,col,unknown_points[current].cand[i])){//该候选能否放到该位置
            o[row][col]=unknown_points[current].cand[i];
            if(dfs(current+1)){
                return 1;
            }
            o[row][col]=0;//回溯
        }
    }
    return 0;
    
}

int main(void){
    char str[10];
    int i,j;
    int N;
    scanf("%d",&N);
    while(N--){
        unknown_count=0;
        for(i=0;i<9;i++){
            scanf("%s",str);
            for(j=0;j<9;j++){
                o[i][j]=(int)(str[j]-'0');
            }
        }
        
        for(i=0;i<9;i++){
            for(j=0;j<9;j++){
                if(!o[i][j]){
                    unknown_points[unknown_count].row=i;
                    unknown_points[unknown_count].col=j;
                    candidate(unknown_count,i,j);
                    unknown_count++;
                }
            }
        }
        qsort(unknown_points,unknown_count,sizeof(Point),cmp);//按照候选的个数从小到大排个序，从小到大深搜
        dfs(0);
        for(i=0;i<9;i++){
            for(j=0;j<9;j++){
                printf("%d",o[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}