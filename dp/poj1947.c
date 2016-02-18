/**
 题意很简单，给一个N节点的树，要得到一个P节点的子树，最少要拿掉多少条边。
 
 用dp[root][i]表示剪出以root为根的i个节点的子树所需的最小代价。那么dp[root][i]=min（dp[c1][i1]+dp[c2][i2]+.....dp[cj][ij]），
 其中c1，c2.....cj代表root的子节点，而i1+i2+....ij=i-1（除去root自己还有i-1个）。
 
 也就是说，要想求dp[root][i]，需要从root的所有孩子当中共保留i-1个节点，至于i-1个节点在它所有的孩子当中要怎么分摊，才能使代价最小，
 这本身又是个分组背包问题。每个子节点代表一个分组，比如以c1为例，它是第一个分组。它可以提供0，1，2....M个节点，其中M是c1所能提供的最大值（也就是该子树所有孩子的数量），
 提供这些节点的代价又依次是dp[c1][0],dp[c1][1],.......dp[c1][M]，根据这些来做一个背包。
 **/
#include <stdio.h>
#include <string.h>
#define INF 9999999
#define M 160

int N;
int P;

int child[M][M];
int gcc[M];//grant_child_count直属孩子的个数
int acc[M];//all_child_count所有孩子的个数（包括它自己）

int d[M][M];

int root;
int nr[M];//not_root找root节点用的
int dp(int,int);

/**
 分组背包
 从以root为根的前G个子树中，背出容量恰好为V的背包的最小代价
 */
int group_pack(int root,int G,int V,int bag[M][M]){
    if(V<0||V>acc[root]-1){//不合法的V
        return INF;
    }
    if(V==0){//当前V已经为0，说明G前面所有的组中都不选，都要和它父亲剪断关系，所以代价一共是G
        return G;
    }
    if(bag[G][V]!=-1){
        return bag[G][V];
    }
    int tc;
    if(G==1){//递归到第一组了
        tc=child[root][0];
        if(V>acc[tc]){//因为必须装满V，这里不够了，所以代价视为无穷大，代表这条路不通
            return INF;
        }
        bag[1][V]=dp(tc,V);//在第一组中剪出V子树的代价
        return bag[1][V];
    }
    
    int i;
    int take;
    int min=group_pack(root,G-1,V,bag)+1;//这是不选该组的代价，加1是剪断和父亲关系的代价
    tc=child[root][G-1];
    for(i=1;i<=acc[tc];i++){//在该组中选择i
        take=group_pack(root,G-1,V-i,bag)+dp(tc,i);
        min=take<min?take:min;
    }
    bag[G][V]=min;
    return min;
}

/*
 以root为根，切出p子树的最小代价
 */
int dp(int root,int p){
    if(d[root][p]!=-1){
        return d[root][p];
    }
    if(gcc[root]==0){
        if(p==1){
            d[root][1]=0;
            return 0;
        }else{
            d[root][1]=INF;
            return INF;
        }
    }
    int bag[M][M];//每个背包单独开一个数组吧，要不会相互干扰...
    memset(bag,-1,sizeof(bag));
    d[root][p]=group_pack(root,gcc[root],p-1,bag);
    return d[root][p];
}

/*
 计算每个子树所有节点的个数
 */
int count(int root){
    int i;
    int result=1;
    int tc;
    for(i=0;i<gcc[root];i++){
        tc=child[root][i];
        acc[tc]=count(tc);
        result+=acc[tc];
    }
    return result;
}

int main(void){
    memset(gcc,0,sizeof(gcc));
    memset(nr,0,sizeof(nr));
    memset(d,-1,sizeof(d));
    memset(acc,0,sizeof(acc));
    
    scanf("%d %d",&N,&P);
    int i;
    int tp;
    int tc;
    for(i=0;i<N-1;i++){
        scanf("%d %d",&tp,&tc);
        child[tp][gcc[tp]++]=tc;
        nr[tc]=1;
    }
    for(i=1;i<=N;i++){
        if(!nr[i]){
            root=i;
            break;
        }
    }
    acc[root]=count(root);
    int result=dp(root,P);
    int take;
    for(i=1;i<N;i++){
        if(i==root){
            continue;
        }
        take=dp(i,P)+1;//非root节点能切出P的话，还要多1点代价，就是剪断和父亲的关系的代价
        result=take<result?take:result;
    }
    printf("%d\n",result);
    return 0;
}