/*************************************************************************
	> File Name: 宏定义.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年06月02日 星期二 09时35分05秒
 ************************************************************************/

#include<stdio.h>
/*#define MAX(a, b)({\
    __typeof(a) __a = (a);\
    __typeof(b) __b = (b);\
    __a > __b ? __a : __b;\
})*/


#define MAX(a, b)((a) > (b) ? (a) : (b))
#define P(func){\
    printf("%s = %d\n", #func, func);\
}

int main(){
    int a = 7;
    P(MAX(2, 3));
    P(5 + MAX(2, 3));
    P(MAX(2, MAX(2, 3)));
    P(MAX(2, 3 > 4 ? 3 : 4));
    P(MAX(a++, 3)); // 9 ~ 13行是为了a不会累加两次
    P(a);
    return 0;
}

