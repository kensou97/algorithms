/**
 给一棵树，给两个节点A和B，找出最近的公共祖先。先让A走到root，把其中经过的节点标记下，在让B走到root，其中碰到的第一个标记节点就是所求节点了。
 **/
#include <stdio.h>
#include <string.h>

int parent[10000];
int visited[10000];

int main(void){
    int T;
    int N;
    int pnode;
    int cnode;
    scanf("%d",&T);
    while(T--){
        memset(parent,0,sizeof(parent));
        memset(visited,0,sizeof(visited));
        
        scanf("%d",&N);
        N--;
        while(N--){
            scanf("%d %d",&pnode,&cnode);
            parent[cnode]=pnode;
        }
        scanf("%d %d",&pnode,&cnode);
        
        while(pnode){
            visited[pnode]=1;//标记下
            pnode=parent[pnode];
        }
        
        while(cnode){
            if(visited[cnode]){//碰到了标记节点
                printf("%d\n",cnode);
                break;
            }
            cnode=parent[cnode];
        }
    }
    return 0;
}