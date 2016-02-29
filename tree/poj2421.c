/**
 对于已经修好的路（必选边）可以将其权设为0，这样这几条边就会被优先选到了。
 判断回路可以用并查集做，用简单的数组实现就可以了。
 边最好按照权值排个序吧，或者弄个最小堆，我直接遍历找的最小。
 **/
#include <stdio.h>

int road[100][100];
int N;

int set[100];

int get_min_road(int* min_i,int* min_j){
    int i;
    int j;
    int min_road=1001;
    for(i=0;i<N-1;i++){
        for(j=i+1;j<N;j++){
            if(road[i][j]!=-1&&road[i][j]<min_road){
                min_road=road[i][j];
                *min_i=i;
                *min_j=j;
            }
        }
    }
    
    return min_road;
}

int find(int i){//找i所属的集合
    while(i!=set[i]){
        i=set[i];
    }
    return i;
}

int main(void){
    scanf("%d",&N);
    int i;
    int j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            scanf("%d",&road[i][j]);
        }
        set[i]=i;
    }
    
    int Q;
    scanf("%d",&Q);
    while(Q--){
        scanf("%d %d",&i,&j);
        road[i-1][j-1]=0;
        road[j-1][i-1]=0;
    }
    
    int sum=0;
    int min_road;
    int times=N-1;
    while(times){
        min_road=get_min_road(&i,&j);
        road[i][j]=-1;//已经选择过的边不妨将权值设为-1
        road[j][i]=-1;
        
        i=find(i);
        j=find(j);
        
        if(i!=j){//选择该边当且仅当该边的两端点不属于同一个集合
            set[j]=i;//合并集合
            sum+=min_road;
            times--;
        }
    }
    printf("%d\n",sum);
    return 0;
}