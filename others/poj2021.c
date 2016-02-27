/**
  可以用宽搜从Ted开始逐步往外扩展，但好像用递归的方法更简洁些。
 **/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tDescendant{
    int age;
    char name[100];
    int parent;
    int cost;
}Descendant;

Descendant d[100];
int X;

int search(char* str,int size){
    int i;
    for(i=0;i<size;i++){
        if(strcmp(d[i].name,str)==0){
            return i;
        }
    }
    return -1;
}

int cmp(const void* x1,const void* y1){
    Descendant* x=(Descendant*)x1;
    Descendant* y=(Descendant*)y1;
    if(x->age!=y->age){
        return y->age-x->age;//年龄降序
    }
    return strcmp(x->name,y->name);//字典序
}

/*
 *计算i的年龄，有点dp的意思，如果i年龄是-1，那么先递归计算其父亲的年龄。
 */
int calculate_age(int i){
    if(d[i].age!=-1){
        return d[i].age;
    }
    d[i].age=calculate_age(d[i].parent)-d[i].cost;
    return d[i].age;
}

int main(void){
    int N;
    scanf("%d",&N);
    
    d[0].age=100;
    strcpy(d[0].name,"Ted");
    d[0].parent=-1;
    
    int i,j;
    int name_count;
    char fname[100];
    char cname[100];
    int cost;
    int fi,ci;
    for(i=1;i<=N;i++){
        printf("DATASET %d\n",i);
        scanf("%d",&X);
        
        name_count=1;
        for(j=1;j<=X;j++){
            d[j].age=-1;
        }
        
        for(j=0;j<X;j++){
            scanf("%s %s %d",fname,cname,&cost);
            fi=search(fname,name_count);//index of father
            if(fi==-1){
                strcpy(d[name_count].name,fname);
                fi=name_count;
                name_count++;
            }
            ci=search(cname,name_count);//index of child
            if(ci==-1){
                strcpy(d[name_count].name,cname);
                ci=name_count;
                name_count++;
            }
            d[ci].parent=fi;//父子关系
            d[ci].cost=cost;//父子年龄差
        }
        
        for(j=1;j<=X;j++){
            calculate_age(j);
        }
        
        qsort(d+1,X,sizeof(Descendant),cmp);
        for(j=1;j<=X;j++){
            printf("%s %d\n",d[j].name,d[j].age);
        }
    }
    return 0;
}