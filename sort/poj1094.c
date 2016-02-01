/*
 题目的意思是给你一堆小于关系，判断能否根据给出的不等关系，找到所有元素的严格的升序序列。
 举个例子吧，以ABCD为例:
 
 1.如果给出（A<B A<C B<C C<D B<D A<B），那么根据前4组就能得出A<B<C<D，
 这时候就找到这组数据的解了，输出得到解时需要的最少的组数：4，以及得到的升序序列ABCD；
 
 2.如果给出的是（A<B A<C A<D），这时候不能确定出所有元素的升序序列，我们只知道A是最小的而已，
 无法判断BCD的大小，这时候输出不确定；
 
 3.如果是这样的（A<B B<A），这样其实就是有环了，输出矛盾。
 
 其实就是一个拓扑排序的小改动。拓扑排序是这样的：每次找一个入度为0的顶点x，然后删掉以x为起点的边，
 继续找下一个入度为0的顶点y，如此往复直到所有顶点都被访问。不过拓扑排序每次迭代时可能有多个顶点入度为0，
 而在这里如果想要得到严格的升序，必须确保每次迭代时入度为0的顶点有且只有一个。
 如果多于一个，那就无法得到升序序列，如果少于1个呢？那就是有环啦。
 */
#include <stdio.h>
#include <string.h>

int n,m;//出现前n个字母，给m组关系
int degree[26];//入度
int d[26][26];//有向图

int degree_copy[26];

char sequence[27];//保存排序的序列，给'\0'多留个位置

/**
 *能排好返回1
 *排不好返回0
 *有环返回-1
 **/
int mysort(){
    int zero_count=0;//入度为0的点的个数
    int zero_index=0;//入度为0的点
    int i,j;
    int result=1;
    
    for(i=0;i<n;i++){//最多进行n次，每次选入度为0的点
        zero_count=0;
        for(j=0;j<n;j++){
            if(degree_copy[j]==0){
                if(zero_count==0){
                    degree_copy[j]=-1;//防止干扰下次选择入度为0的点，先将它改为-1吧，代表该点已经选择过了
                    zero_index=j;
                }
                zero_count++;
                if(zero_count>1){//入度为0的点多于1个，说明排不好，但排不好不能立马返回0，还要确定是否有环，否则会WA.....
                    result = 0;
                }
            }
        }
        if(zero_count==0){//没有入度为0的点，说明有环
            return -1;
        }
        sequence[i]='A'+zero_index;//将本次选择的点记录下来
        for(j=0;j<n;j++){
            if(d[zero_index][j]){//zero_index指向的点的入度减1
                degree_copy[j]--;
            }
        }
    }
    return result;
}

int main(void){
    char c1,c2;
    int i1,i2;
    int current_relation_count;
    int result;
    while(1){
        scanf("%d %d",&n,&m);
        if(n==0&&m==0){
            return 0;
        }
        
        memset(degree,0,sizeof(degree));
        memset(d,0,sizeof(d));
        sequence[n]='\0';
        current_relation_count=0;
        result=0;
        
        getchar();//记得读换行符$....
        while(m--){
            scanf("%c<%c",&c1,&c2);
            getchar();
            if(result!=0){
                continue;
            }
            i1=(int)(c1-'A');
            i2=(int)(c2-'A');
            current_relation_count++;
            d[i1][i2]=1;
            degree[i2]++;
            
            memcpy(degree_copy,degree,sizeof(degree));
            result=mysort();
            if(result==1){
                printf("Sorted sequence determined after %d relations: %s.\n",current_relation_count,sequence);
            }
            if(result==-1){
                printf("Inconsistency found after %d relations.\n",current_relation_count);
            }
        }
        if(result==0){
            printf("Sorted sequence cannot be determined.\n");
        }
    }
    return 0;
}