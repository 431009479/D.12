[TOC]

# C++ 重载运算符

> C++ 允许在同一作用域中的某个**函数**和**运算符**指定多个定义，分别称为函数重载和运算符重载。
>
> 重载声明是指一个与之前已经在该作用域内声明过的函数或方法具有相同名称的声明，但是它们的参数列表和定义（实现）不相同。

> 重载的运算符是带有特殊名称的函数，函数名是由关键字 operator 和其后要重载的运算符符号构成的。与其他函数一样，重载运算符有一个返回类型和一个参数列表。
>
> ```c++
> 声明加法运算符用于把两个 Box 对象相加，返回最终的 Box 对象。大多数的重载运算符可被定义为普通的非成员函数或者被定义为类成员函数。如果我们定义上面的函数为类的非成员函数，那么我们需要为每次操作传递两个参数，如下所示：
> Box operator+(const Box&, const Box&);
> ```

运算符重载有两种方式：一种是类内重载（运算符重载函数作为类的成员函数），另一种是类外重载（运算符重载函数作为类的友元函数）

## 类内重载

```c++
类内重载
class Point{
public:
    Point(){};
    Point (int x, int y): x(x),y(y) {};
    Point operator+(const Point &a){ //类内重载，运算符重载函数作为类的成员函数
        Point ret;
        ret.x = this->x + a.x;
        ret.y = this->y + a.y;
        return ret;
    }
    int x,y;
};

int main() {
    Point a(2,4),b(5,3);
    Point c = a + b;
	cout<< "x :" << c.x << endl;
    cout<<"y :" << c.y << endl;
}
//运算符重载是类内重载时，运算符重载函数作为类的成员函数，以上述代码为例 a + b 相当于 a 对象调用+方法并且传入参数时 b 对象
```

## 类外重载

```c++

class Point{
public:
    Point(){};
    Point (int x, int y): x(x),y(y) {};
    friend Point operator+(const Point &, const Point &);
    int x,y;
};
Point operator+(const Point &a,const Point &b){//类外重载,运算符重载函数作为类的友元函数
    Point ret;
    ret.x = a.x + b.x;
    ret.y = a.y + b.y;
    return ret;
}
int main() {
     Point a(2,4),b(5,3);
    Point c = a + b;
	cout<< "x :" << c.x << endl;
    cout<<"y :" << c.y << endl;
}
```



```c++
各种运算符重载实例
下面将进行各种运算符重载实例的代码演示，演示几种基本的运算符重载。
插入运算符重载>> and 提取运算符重载<<
以提取运算符重载<<为例，cout 是 ostream类的对象。ostream 类和 cout 都是在头文件 <iostream>中声明的。ostream 类将<<重载为成员函数。
```

具体规则如下：

| 运算符                                                   | 建议使用       |
| -------------------------------------------------------- | -------------- |
| 所有一元运算符                                           | 成员函数       |
| ＝ ( ) [ ] ->                                            | 必须是成员函数 |
| += -= /= *= ^= &= != %= >>= <<= , 似乎带等号的都在这里了 | 成员函数       |
| 所有其它二元运算符, 例如: –,+,*,/                        | 友元函数       |
| << >>                                                    | 必须是友元函数 |

```c++
//下面是不可重载的运算符列表：
//.：成员访问运算符
//.*, ->*：成员指针访问运算符
//::：域运算符
//sizeof：长度运算符
//?:：条件运算符
//#： 预处理符号
```

下面是可重载的运算符列表：

| 双目算术运算符 | + (加)，-(减)，*(乘)，/(除)，% (取模)                        |
| -------------- | ------------------------------------------------------------ |
| 关系运算符     | ==(等于)，!= (不等于)，< (小于)，> (大于>，<=(小于等于)，>=(大于等于) |
| 逻辑运算符     | \|\|(逻辑或)，&&(逻辑与)，!(逻辑非)                          |
| 单目运算符     | + (正)，-(负)，*(指针)，&(取地址)                            |
| 自增自减运算符 | ++(自增)，--(自减)                                           |
| 位运算符       | \| (按位或)，& (按位与)，~(按位取反)，^(按位异或),，<< (左移)，>>(右移) |
| 赋值运算符     | =, +=, -=, *=, /= , % = , &=, \|=, ^=, <<=, >>=              |
| 空间申请与释放 | new, delete, new[ ] , delete[]                               |
| 其他运算符     | **()**(函数调用)，**->**(成员访问)，**,**(逗号)，**[]**(下标) |

## 实例：

```c++
#include<iostream>
using namespace std;

namespace haizei {

class istream{  //像std一样的空间
public:
    istream &operator>>(int &n){ //重载>>
        std::cin >> n;
        return *this;
    }
private:

};

class ostream{
public:

    ostream &operator<<(int &n){ //重载<<
        std::cout << n;
        return *this;
    }
    ostream &operator=() //重载=
    ostream &operator<<(const char *mag){
        std::cout << mag;
        return *this;
    }
private:
    

};
    istream cin;
    ostream cout;
};

haizei::ostream &operator<<(haizei::ostream &out, double &z){ //类外重载
    std::cout << z;
    return out;
}

ostream &operator+(ostream &out, const int &x){ 
    cout << x;
    return out;
}
int main(){
    int n, m;
    haizei::cin >> n >> m;
    haizei::cout << n << " " << m << "\n";
    double k = 5.6;
    haizei::cout << k << "\n";
    cout + 8 + 9 + 10;
    return 0;
}
```



```c++
class Point {
public :
    Point() :__x(0), __y(0){}
    Point(int x, int y) :__x(x), __y(y){}
    int x() const {return __x;}
    int y() const {return __y;}
    Point operator+(const Point &a){
        return Point(x() + a.x(), y() + a.y());
    }
    Point &operator+=(const Point &a){
        this->__x += a.x();
        this->__y += a.y();
        return *this;
    }
    Point &operator++(){ 
        __x += 1;
        __y += 1;
        return *this;
    }
    Point operator++(int){ //区分前++ 和后++（int）
        Point temp(*this);
        __x += 1;
        __y += 1;
        return temp;
    }

private:
    int __x, __y;
};

ostream &operator<<(ostream &out, const Point &a){
    out <<"Point (" << a.x() << "," << a.y() << ")";
    return out;
}

int main(){
    Point a(4, 5), b(3, 4),c(1, 1);
    cout << a << " "  << b<<" " << c << endl;
    cout << a + b << endl;
    cout << "pre incr : " << ++(c += b) << endl;
    cout << c << endl;
    cout << "after incr : " << c++ << endl;
    cout << c << endl;
    return 0;
}
```

```c++
class A{
public :
    A() {
        arr = new int[10];
    }
    A(const A &a) : A(){
        for(int i = 0; i < 10; i++){
            this->arr[i] = a.arr[i];
        }
       // this->x = a.x;
       // this->y = a.y;
        return ;
    }
    int x, y;
    int *arr;
};

class B{
public :
    B() : obj(nullptr){
        arr = new int[10];
        arr[3] = 9973;
    }
    B(A *obj) : B(){
        this->obj = obj;
    }
    int operator()(int a, int b){
        return a + b;
    }
    int &operator[](int ind){
        return arr[ind];
    }
    void operator[](const char *msg){
        cout << msg << endl;
        return ;
    }
    A *operator->(){
        return obj;
    }
    A &operator*(){
        return *obj;
    }
    ~B(){
        delete arr;
    }
private:
    int *arr;
    A *obj;
};

ostream &operator <<(ostream &out, const A &a){
    out << "A(" << a.x << "," << a.y << ")";
    return out;
}
int main(){
    B add;
    cout << add(3, 4) << endl;
    cout << add[3] << endl;
    add[3] = 8876;
    cout << add[3] << endl;
    add["hello world"];

    A a, b(a);
    a.x = 67, a.y = 98;
    b.x = 68, b.y = 99;
    B p = &a;
    cout << p->x << " " << p->y << endl;
    cout << *p << endl;
    a.arr[3] = 9973;
    b.arr[3] = 6687;
    cout << a.x << " " << a.y << endl;
    cout << b.x << " " << b.y << endl;
    cout << a.arr[3] << " " << b.arr[3] << endl;
    return 0;
}
```

