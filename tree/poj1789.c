#include <stdio.h>
#include <stdlib.h>

typedef struct tEdge{
    int x;
    int y;
    int w;
}Edge;

Edge e[2000000];
char str[2000][8];
int n,ei;
int set[2000];

int cmp(const void* x,const void* y){
    return ((Edge*)x)->w-((Edge*)y)->w;
}

int find(int i){
    int j=i;
    while(i!=set[i]){
        i=set[i];
    }
    set[j]=i;
    return i;
}

int kruskal(void){
    qsort(e,ei,sizeof(Edge),cmp);
    int i=0;
    int count=n-1;
    int x,y;
    int result=0;
    while(1){
        x=find(e[i].x);
        y=find(e[i].y);
        if(x==y){
            i++;
            continue;
        }
        set[x]=y;
        result+=e[i].w;
        i++;
        count--;
        if(count==0){
            break;
        }
    }
    return result;
}

int weight(char* a,char* b){
    int i;
    int re=0;
    for(i=0;i<7;i++){
        if(a[i]!=b[i]){
            re++;
        }
    }
    return re;
}

int main(void){
    int i,j;
    while(1){
        scanf("%d",&n);
        if(n==0){
            break;
        }
        ei=0;
        for(i=0;i<n;i++){
            set[i]=i;
            scanf("%s",str[i]);
            for(j=0;j<i;j++){
                e[ei].x=i;
                e[ei].y=j;
                e[ei].w=weight(str[i],str[j]);
                ei++;
            }
        }
        printf("The highest possible quality is 1/%d.\n",kruskal());
    }
    return 0;
}