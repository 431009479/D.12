/*************************************************************************
	> File Name: 宏定义1.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年06月02日 星期二 09时56分08秒
 ************************************************************************/
#include<stdio.h>
#define log(frm, arg...){\
    printf("[%s : %s : %d ]", __FILE__, __func__, __LINE__);\
    printf(frm, ##arg);\
}
#define contact(a, b) a##b //##连接 , ##支持传入参数为空
int main(){
    int a = 123;
    int abcdef = 15;
    contact(abc,def) = 23;
    log("%d\n", a);
    printf("[%s : %s : %d] %d\n",__FILE__, __func__, __LINE__, a);
    log("hello world\n");
    log("%d\n", abcdef);
    return 0;
}
