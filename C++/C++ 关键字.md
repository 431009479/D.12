[TOC]

# C++ 关键字

## auto:

​			auto用于声明变量为自动变量，具有**自动存储器**的局部变量, 自动变量意为拥有自动的生命期.

​			auto可以在声明变量的时候根据变量初始值的类型自动为此变量选择匹配的类型，类似的关键字还有decltype

```c++
    int a = 10;
    auto au_a = a;//自动类型推断，au_a为int类型
    cout << typeid(au_a).name() << endl;
```

```c++
函数或模板参数不能被声明为auto
auto不能定义数组，如果表达式为数组， auto要带上&，则推导出的类型为数组类型，如：
　　int32_t a[3] = {};
　　auto& arr = a;
　　std::cout <<typeid(arr).name() std::endl; // 这里输出int [3]
```

```
auto不是一个真正的类型，仅仅是一个占位符，不能使用一些以类型为操作数的操作符，如sizeof或typeid
cout << sizeof(auto) << endl;//错误
cout << typeid(auto).name() << endl;//错误
```

```c++
1.auto不能作为函数参数
2.auto不能直接声明数组
3. 为了避免与C++98中的auto发生混淆，C++11只保留了auto作为类型指示符的用法
4. auto在实际中最常见的优势用法就是跟以后会讲到的C++11提供的新式for循环，还有lambda表达式等进行配合使用。
5. auto不能定义类的非静态成员变量
6. 实例化模板时不能使用auto作为模板参数
```

```c++
int main(){
    auto a = 123;
    cout << sizeof(a) << endl;
    map<int, int> arr;
    arr[676556] = 1267886;
    arr[999] = 10000;
    arr[45678] = 712;
    for(auto iter = arr.begin(); iter != arr.end(); iter++){
        cout << iter->first << " " << iter->second << endl;
    }
    for(auto x : arr){
        cout << x.first << "," << x.second << endl;
    }
    return 0;
}

```



## constexpr:

> 常量表达式(const expression)：是指值不会改变并且在编译过程中就得到计算结果的表达式。(运行中得到结果的不能成为常量表达式)。

```c++
const int i=3;   //是一个常量表达式
const int j=i+1; //是一个常量表达式
int k=23;     //k的值可以改变，从而不是一个常量表达式
const int m=f(); //不是常量表达式，m的值只有在运行时才会获取。
```

> C++11允许声明constexpr类型来**由编译器检验变量的值是否是一个常量表达式**。声明为constexpr的必须是一个常量，并且只能用常量或者常量表达式来初始化。

```c++
constexpr int i=3;
constexpr int j=i+1;
constexpr int k=f(); //只有f()是一个constexpr函数时k才是一个常量表达式
一般来说，若果一旦认定变量是一个常量表达式，那就把它声明为constexpr类型
 // 尽管指针和引用都可以定义为constexpr，但是他们的初始值却受到了严格的限制。一个constexpr指针的初始值必须是nullptr或者0，或者是存储某个固定地址的对象。
  constexpr函数是指用于常量表达式的函数。
遵循以下规定：（1）函数的返回类型以及所有形参的类型都得是字面值类型；（2）函数体中必须只有一条return语句。
    
  //函数体中定义的变量并非存放在固定地址中，因此constexpr指针不可以指向这样的变量。相反的，对于所有函数体之外的对象地址是固定不变的，可以用constexpr来定义；
//必须明确一点，在constexpr声明中，如果定义了一个指针，限定符号constexpr仅仅对指针有效，与指针所指对象无关。
    
const int *p=nullptr;  //p是一个指向整型常量的指针（pointer to const）
constexpr int *q=nullptr; //p1是一个常量指针(const pointer)
p和q的类型相差甚远，p是一个指向常量的指针，q是一个常量指针，其中关键在于constexpr把它所定义的对象置为顶层const。
```

```c++
constexpr int f(int x){
    return 3 * x * x + x;
}
class A{
public :
    constexpr A(int x, int y): x(x), y(y){}
    int x, y;
};
int main(){
    const int n = 123; //const运行期
    int a;
    cin >> a;
    const int b = 2 * a;
    cout << n << endl;
    cout << b << endl;
    constexpr int c = 2 * n; //constexpr 编译期常量
//  constexpr int c = 2 * a;
    constexpr int d = f(12);
    cout << f(5) << endl;
    constexpr A k(2, 3);
    cout << k.x << "," << k.y << endl;
    return 0;
}
```

## final:

final 限制继承类

```c++
class Base final{
};
// 错误，Derive不能从Base派生。
class Derive: public Base{
};
```

一个虚函数不希望被重写

```c++
class Base{
public:
        virtual void Fun() final{}
};
 
class Derive: public Base{
public:
        // 错误，不能覆盖基类的函数。
        virtual void Fun() override{ }
};
```

## nullprt:

> 引入nullptr的原因，这个要从NULL说起。对于C和C++程序员来说，一定不会对NULL感到陌生。但是C和C++中的NULL却不等价。NULL表示指针不指向任何对象，但是问题在于，NULL不是关键字，而只是一个宏定义(macro)。

```c++
//NULL在C中的定义
//在C中，习惯将NULL定义为void*指针值0：
#define NULL (void*)0  
//在C++中，NULL却被明确定义为整常数0：
#ifndef NULL  
#ifdef __cplusplus  
#define NULL    0  
#else  
#define NULL    ((void *)0)  
#endif  
#endif  
```



# C++——左右值及函数重载

```c++
1. c++变量名：
     由字母，数字或下划线组成，且第一个字符必须是字母或者下划线，不能是数字。
2. 左值：
     左值可以出现在赋值语句的左边或者右边， 例如：变量是左值；
3. 右值：
     右值只能出现在赋值的右边不能出现在赋值语句的左边，例如：数字字面值是右值。
    sizeof：
  sizeof是c++中的关键字不是函数。
     int a = 1;
     sizeof(int) // right
     sizeof(a) // right
     sizeof a // right
     sizeof int // error
```

左值是指存在于单个表达式之外的对象。你可以把左值当成有名字的对象。

所有的变量，包括常变量，都是左值。

右值是一个暂时存在的值存在于单个表达式之内的对象。

有点拗口（难理解），通俗来说就是，左值的生存期不只是这句话，后面还能用到它。

而右值呢，出了这句话就挂了，所以也叫（将亡值）。

> 左值相当于地址值，右值相当于数据值。右值指的是引用了一个存储在某个内存地址里的数据。

```c++
1. int main()  {  
3.    	int i, j, *p;  
5.    	*// 正确的使用: 变量是左值* 
6.    	i = 7;  
8.    *// 错误的使用: 左边的操作 必须是 左值 (C2106)*
9.    7 = i; *// C2106*  
10.    j * 4 = 7; *// C2106*  
11.   
12.    *// 正确的使用: 被间接引用的指针是左值*
13.    *p = i;   
15.    const int ci = 7;  
16.    *// 错误的使用: 左边的操作 是 常量左值 (C3892)*
17.    ci = 9; *// C3892* 
19.    *// 正确的使用: 条件操作 返回了左值*
20.    ((i < 3) ? i : j) = 7;  
21. }  
```


左值引用:

使用语法：类型 + &（引用符） + 表达式

```cpp
type-id & cast-expression 
```

```c++
可以把左值引用当成对象的另一个名字，引用必须初始化，而且不能改变。
一个对象的地址可以 转化成 一种指定类型的指针 或者 转化成 一个 相似类型的引用。意义是相同的。
不要混淆 取地址 和 引用，当&说明符前面带有类型声明，则是引用，否则就是取地址。
通俗来说 &在 ”=” 号左边的是引用，右边的是取地址。 
```

右值引用:

使用语法：类型 + && + 表达式

```cpp
type-id && cast-expression  
```





```c++
#define TEST(a, f){\
    cout << #a << " : " << #f << " "; \
    f(a);\
}
//左值引用
void f2(int &x){
    cout << "left value" << endl;
}
//右值引用
void f2(int &&x){
    cout << "right value" << endl;
}
//左值引用
void f(int &x){
    cout << "left value" << endl;
    TEST(x, f2);
}
//右值引用
void f(int &&x){
    cout << "right value" << endl;
    TEST(move(x), f2); 				//move 强制转换右值
    TEST(forward<int &&>(x), f2); //forward 转换右值   forward<int &&>(x) 转换左值
}

int main(){
    int a, b = 1, c = 3;
    (++a) = b + c; //++a 左值
    cout << a << endl;
    (a++); //右值
    (a = b) = c; //a是左值
    cout << a << "," << b << endl;
    int arr[10];
    arr[3] = 12; //a是左值
    (a += 3) = 67; //a是左值
    cout << a << endl;
    TEST(a += 3, f); //a是左值
    TEST(1 + 4, f);
    TEST(b + c, f);
    TEST(a++, f);
    TEST(++a, f); //a是左值
    return 0;
}
```

