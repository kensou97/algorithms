/**
   频繁的统计某区间范围内的数一共有多少个，只不过这里可以认为区间左端点始终是0，区间查询问题
 **/
#include <stdio.h>
#include <stdlib.h>

typedef struct tNode{
    int left;//区间左端点
    int right;//右端点
    int count;
}Node;

Node node[32005*8];
int N;
int level[15000];
int result;

/*
 递归创建线段树
 */
void create_node(int i,int left,int right){
    node[i].left=left;
    node[i].right=right;
    node[i].count=0;
    if(left!=right){
        int mid=(left+right)>>1;
        create_node(2*i+1,left,mid);
        create_node(2*i+2,mid+1,right);
    }
}

/*
 根据x坐标更新线段树的count值
 */
void insert(int i,int value){
    node[i].count++;
    if(node[i].left==node[i].right){
        return;
    }
    int mid=(node[i].left+node[i].right)>>1;
    if(value<=mid){//走左子还是右子
        insert(2*i+1,value);
    }else{
        insert(2*i+2,value);
    }
}

/*
 统计[tleft,tright]的count值
 */
void search(int i,int tleft,int tright){
    int left=node[i].left;
    int right=node[i].right;
    if(tright<left||tleft>right){//与node区间无交集
        return;
    }
    if(tleft<=left&&tright>=right){//完全囊括node区间，无须再走孩子
        result+=(node[i].count);
        return;
    }
    //部分交集，继续去孩子探索
    search(2*i+1,tleft,tright);
    search(2*i+2,tleft,tright);
}

int main(void){
    create_node(0,0,32000);
    int x,y;
    int i;
    scanf("%d",&N);
    for(i=0;i<N;i++){
        scanf("%d %d",&x,&y);
        result=0;
        search(0,0,x);
        level[result]++;
        insert(0,x);
    }
    for(i=0;i<N;i++){
        printf("%d\n",level[i]);
    }
    return 0;
}