/*
 根据题目中给的dfs序列构造出一个左孩子右兄弟表示的树，
 然后求树高就可以了。
 */
#include <stdio.h>
#include <string.h>

typedef struct tNode{
    int p;
    int l;//left child
    int r;//right child
    int lc;//last child
}Node;

char str[20000];
Node n[10000];

int height(int i){
    int l=n[i].l;
    int r=n[i].r;
    int lh=0;
    int rh=0;
    if(l!=-1){
        lh=height(l);
    }
    if(r!=-1){
        rh=height(r);
    }
    return lh>rh?lh+1:rh+1;
}

int main(void){
    int i,ci,cur;
    int ti=1;
    char c;
    int bh,bhmax;
    while(1){
        scanf("%s",str);
        if(str[0]=='#'){
            break;
        }
        
        memset(n,-1,sizeof(n));
        ci=i=bh=bhmax=cur=0;
        
        while((c=str[i++])!='\0'){
            if(c=='d'){
                bh++;
                bhmax=bh>bhmax?bh:bhmax;
                
                ci++;
                n[ci].p=cur;
                if(n[cur].l==-1){//ci is the first child of cur
                    n[cur].l=ci;
                    n[cur].lc=ci;
                }else{//not first,let it be the right child of cur's last child
                    n[n[cur].lc].r=ci;
                    n[cur].lc=ci;
                }
                cur=ci;
            }else{
                bh--;
                cur=n[cur].p;
            }
        }
        printf("Tree %d: %d => %d\n",ti++,bhmax,height(0)-1);
    }
    return 0;
}