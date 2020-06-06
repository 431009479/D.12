/*************************************************************************
	> File Name: ex_gcd.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年06月06日 星期六 11时03分02秒
 ************************************************************************/

#include<iostream>
using namespace std;



int ex_gcd(int a, int b, int &x, int &y) {
    if(b==0){
        x=1;
        y=0;
        return a;  //到达递归边界开始向上一层返回
    }
    int r=ex_gcd(b,a%b,x,y);
    int temp=y;    //把x y变成上一层的
    y=x-(a/b)*y;
    x=temp;
    return r;   
}

int main() {
    int a, b, x, y;
    while (~scanf("%d%d", &a, &b)) {
        printf("gcd(%d, %d) = %d\n", a, b, ex_gcd(a, b, x, y));
        printf("%d * %d + %d * %d = %d\n", a, x, b, y, a * x + b * y);
    }
    return 0;
}
