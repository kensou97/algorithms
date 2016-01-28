//如果用dp[i]表示str串从i位置开始匹配需要删掉的字母数量，那么对i位置，可以做两种选择，用i处的字符进行匹配，或者不用i处的字符匹配。
//1.如果不用i处匹配，状态转化比较好写：dp[i]=dp[i+1]+1，也就是将i处的字符删掉（代价为1），然后继续从i+1位置开始匹配。
//2.如果用i处匹配，那么首先找到首字母与i处字符相同的单词，计算出把该单词全部匹配完需要删掉的字母数（也就是代价），然后从str的下一个位置继续匹配。比如str是“broxwtndcodw”，某单词是brown，那么从0处匹配brown，需要删掉两个字母（字母x和t），然后继续从下一个位置7（d的位置）开始匹配，所以对这种匹配的方程就是dp[0]=2+dp[7]，然后其他的就依次类推。如果有多个单词首字母都和i处字符相等，那就要把各种匹配遍历一遍，然后选代价最小的。
//然后dp[i]最后的决策就是从上述1和2中选一个最小的。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int w;
int sl;

char dic[600][26];
char str[301];

int dt[301];

int cmp(const void* x,const void* y){
    return strcmp((char*)x,(char*)y);
}

int match(int l,int di,int* nl){
    int i=l;
    int j=0;
    int count=0;//匹配完该单词需要删除的字母数
    int len=strlen(dic[di]);
    while(i<sl&&j<len){
        if(str[i]==dic[di][j]){
            j++;
        }else{
            count++;
        }
        i++;
    }
    if(j!=len){//必须全部匹配完才有效，否则无效
        return -1;
    }
    *nl=i;//匹配完后的下一个位置
    return count;
}

int dp(int l){
    if(dt[l]!=-1){
        return dt[l];
    }
    if(l==sl){//匹配到末尾了
        return 0;
    }
    char c=str[l];
    int i,tx,nl;
    int x=300;
    for(i=0;i<w;i++){//匹配该位置
        if(dic[i][0]<c){//首字母太小
            continue;
        }
        if(dic[i][0]>c){//首字母太大
            break;
        }
        tx=match(l,i,&nl);
        if(tx==-1){//无效的匹配
            continue;
        }
        tx+=dp(nl);//这中匹配的方式的代价==匹配该单词的代价+匹配完该单词后匹配下一个位置的代价
        x=tx<x?tx:x;
    }
    int y=dp(l+1)+1;//不匹配该位置
    x=x<y?x:y;
    dt[l]=x;
    return x;
}

int main(void){
    memset(dt,-1,sizeof(dt));
    scanf("%d %d",&w,&sl);
    scanf("%s",str);
    int i;
    for(i=0;i<w;i++){
        scanf("%s",dic[i]);
    }
    qsort(dic,w,sizeof(dic[0]),cmp);//先按字典序排个序，便于匹配
    printf("%d\n",dp(0));
    return 0;
}