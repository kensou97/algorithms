/**
 棋盘问题（简单搜索）
 **/
#include <stdio.h>

int n;
int k;
int count;

int row[8];
int col[8];
int myindex;
char ch[8][9];

int find(int v,int* t){
    int i;
    for(i=0;i<myindex;i++){
        if(t[i]==v){
            return 1;
        }
    }
    return 0;
}

void try(int left_count,int bi){
    int i,j;
    if(left_count>n-bi){//剪枝，剩下的棋子数量大于可用行数，那么肯定至少有两个棋子在同一行（鸽巢）。
        return;
    }
    for(i=bi;i<n;i++){
        if(find(i,row)){//同行
            continue;
        }
        for(j=0;j<n;j++){
            if(find(j,col)){//同列
                continue;
            }
            if(ch[i][j]=='.'){
                continue;
            }
            row[myindex]=i;
            col[myindex++]=j;
            if(left_count==1){//找到一个可行解
                count++;
            }else{
                try(left_count-1,i+1);
            }
            myindex--;//回溯
        }
    }
}

int main(void){
    int i;
    while(1){
        scanf("%d %d",&n,&k);
        if(n==-1&&k==-1){
            break;
        }
        
        for(i=0;i<n;i++){
            scanf("%s",ch[i]);
        }
        
        count=0;
        myindex=0;
        try(k,0);
        printf("%d\n",count);
    }
    return 0;
}