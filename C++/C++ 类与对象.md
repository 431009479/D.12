[TOC]

# C++ 类与对象

C++ 在 C 语言的基础上增加了面向对象编程，C++ 支持面向对象程序设计。类是 C++ 的核心特性，通常被称为用户定义的类型。类用于指定对象的形式，它包含了数据表示法和用于处理数据的方法。类中的数据和方法称为类的成员。函数在一个类中被称为类的成员。

## C++ 类定义

定义一个类，本质上是定义一个数据类型的蓝图。这实际上并没有定义任何数据，但它定义了类的名称意味着什么，也就是说，它定义了类的对象包括了什么，以及可以在这个对象上执行哪些操作。

类定义是以关键字 **class** 开头，后跟类的名称。类的主体是包含在一对花括号中。类定义后必须跟着一个分号或一个声明列表。

```c++
class Box{
   public:
      double length;   // 盒子的长度
      double breadth;  // 盒子的宽度
      double height;   // 盒子的高度
};
```

##  C++ 对象

类提供了对象的蓝图，所以基本上，对象是根据类来创建的。声明类的对象，就像声明基本类型的变量一样。下面的语句声明了类 Box 的两个对象：

```c++
Box Box1;          // 声明 Box1，类型为 Box 
Box Box2;          // 声明 Box2，类型为 Box

访问数据成员
类的对象的公共数据成员可以使用直接成员访问运算符 (.) 来访问。
需要注意的是，私有的成员和受保护的成员不能使用直接成员访问运算符 (.) 来直接访问。
```

## C++ 类成员函数

​		类的成员函数是指那些把定义和原型写在类定义内部的函数，就像类定义中的其他变量一样。类成员函数是类的一个成员，它可以操作类的任意对象，可以访问对象中的所有成员。

```c++
class Box{
   public:
      double length;         // 长度
      double breadth;        // 宽度
      double height;         // 高度
      double getVolume(void);// 返回体积
};
```

成员函数可以定义在类定义内部，或者单独使用**范围解析运算符 ::** 来定义。在类定义中定义的成员函数把函数声明为**内联**的，即便没有使用 inline 标识符。所以您可以按照如下方式定义 **Volume()** 函数：I

```c++
class Box
{
   public:
      double length;      // 长度
      double breadth;     // 宽度
      double height;      // 高度
   
      double getVolume(void)
      {
         return length * breadth * height;
      }
};
您也可以在类的外部使用范围解析运算符 :: 定义该函数，如下所示：
double Box::getVolume(void)
{
    return length * breadth * height;
}
```

## C++ 类访问修饰符

```c++
数据封装是面向对象编程的一个重要特点，它防止函数直接访问类类型的内部成员。类成员的访问限制是通过在类主体内部对各个区域标记 public、private、protected 的关键字 称为访问修饰符。
一个类可以有多个 public、protected 或 private 标记区域。每个标记区域在下一个标记区域开始之前或者在遇到类主体结束右括号之前都是有效的。成员和类的默认访问修饰符是 private。
```

> 公有（public）成员
> 公有成员在程序中类的外部是可访问的。您可以不使用任何成员函数来设置和获取公有变量的值，

> 私有（private）成员
>
> 私有成员变量或函数在类的外部是不可访问的，甚至是不可查看的。只有类和友元函数可以访问私有成员。默认情况下，类的所有成员都是私有的。如果您没有使用任何访问修饰符，类的成员将被假定为私有成员：

> 保护（protected）成员
>
> 保护成员变量或函数与私有成员十分相似，但有一点不同，保护成员在派生类（即子类）中是可访问的。

```c++
1.private 成员只能被本类成员（类内）和友元访问，不能被派生类访问；
2.protected 成员可以被派生类访问。
```

## 构造函数

类的**构造函数**是类的一种特殊的成员函数，它会在每次创建类的新对象时执行。编译系统对象分配内存空间，并自动调用该构造函数->由构造函数完成成员的初始化工作

构造函数的名称与类的名称是完全相同的，并且不会返回任何类型，也不会返回 void。构造函数可用于为某些成员变量设置初始值。

### 无参数构造函数

> 如果创建一个类你没有写任何构造函数,则系统会自动生成默认的无参构造函数，函数为空，什么都不做

```c++
class People{
public:
    People(){
        arr = new int[10];
        cout << "default constructor" << endl;
    }
    int *arr;
};
int main(){
    People a;
    a.arr[9] = 18;
    cout << "hello world" << endl;
    return 0;
}
```

### 带参数的构造函数

```c++
class People{
public:
  	People(){};
    People(string name){
        this->name = name;
    }
    People(int x){
        cout << "int parm constructor";
        this->x = x;
    }
};
int main(){
  	People a = string("xiong");
    People d("dong");
    People b = 678;
    People c(123);
    return 0;
}
```

### 复制构造函数

> 复制构造函数参数为类对象本身的引用，用于根据一个已存在的对象复制出一个新的该类的对象，一般在函数中会将已存在对象的数据成员的值复制一份到新创建的对象中 ,若没有显示的写复制构造函数，则系统会默认创建一个复制构造函数，

```c++
class People{
public:
  	People(){};
    People(string name){
        this->name = name;
    }
    People(int x){
        cout << "int parm constructor";
        this->x = x;
    }
	People(const People &a){ //复制构造函数.
        this->name = a.name;
        this->x = x;
    }
};
int main(){
  	People a = string("xiong");
    a = 111;
    People e = a;
    cout << e.name << " " << e.x << endl;
    return 0;
}
```

### 赋值构造函数

> 注意，这个类似复制构造函数，将=右边的本类对象的值复制给等号左边的对象，它不属于构造函数，等号左右两边的对象必须已经被创建。 若没有显示的写=运算符重载，则系统也会创建一个默认的=运算符重载

```c++
class People{
public:
  	People(){};
    People(string name){
        this->name = name;
    }
    People(int x){
        cout << "int parm constructor";
        this->x = x;
    }
	void operator=(const People &a){
        cout << "operator=" << endl;
        this->name = a.name;
        this->x = a.x;
    }
};
int main(){
  	People a = string("xiong");
    a = 111;
    People c(123);
    c = a;
    cout << e.name << " " << e.x << endl;
    return 0;
}
```

### 析构函数

> 类的析构函数是类的一种特殊的成员函数，它会在每次删除所创建的对象时执行。析构函数的名称与类的名称是完全相同的，只是在前面加了个波浪号（~）作为前缀，它不会返回任何值，也不能带有任何参数。析构函数有助于在跳出程序（比如关闭文件、释放内存等）前释放资源。

```c++
class People{
public:
    People(){};
    ~People(){
        cout << "delete" << endl;
    }
    int x;
};
int main(){
    People a;
    return 0;
}
```

```c++
default 和 delete 关键字
People() = default;//限制默认函数的生成
People() = delete; //函数被delete过了，那么重载该函数也是非法的，该函数我
```

## static

> 在类中声明static变量或者函数时，初始化时使用作用域运算符来标明它所属类，因此，静态数据成员是类的成员，而不是对象的成员

```c++
(1)类的静态成员函数是属于整个类而非类的对象，所以它没有this指针，这就导致 了它仅能访问类的静态数据和静态成员函数。
(2)不能将静态成员函数定义为虚函数。
(3)static并没有增加程序的时空开销，相反她还缩短了子类对父类静态成员的访问 时间，节省了子类的内存空间。 
(4)静态数据成员在<定义或说明>时前面加关键字static。
(5)静态成员初始化与一般数据成员初始化不同:
	初始化在类体外进行，而前面不加static，以免与一般静态变量或对象相混淆；
	初始化时不加该成员的访问权限控制符private，public等；       
	初始化时使用作用域运算符来标明它所属类；
           所以我们得出静态数据成员初始化的格式：
	<数据类型><类名>::<静态数据成员名>=<值>
(6)为了防止父类的影响，可以在子类定义一个与父类相同的静态变量，以屏蔽父类的影响。这里有一点需要注意：我们说静态成员为父类和子类共享，但我们有重复定义了静态成员，这会不会引起错误呢？不会，我们的编译器采用了一种绝妙的手法：name-mangling 用以生成唯一的标志。
```

```c++

class Box{
   public:
      static int objectCount;
      // 构造函数定义
      Box(double l=2.0, double b=2.0, double h=2.0){
         cout <<"Constructor called." << endl;
         length = l;   breadth = b;  height = h;
         // 每次创建对象时增加 1
         BOX::objectCount++;
      }
      double Volume(){
         return length * breadth * height;
      }
    ~People(){
        //每次销毁对象
        cout << "delete" << endl;
        BOX::objectCount--;
    }
   private:
      double length;     // 长度
      double breadth;    // 宽度
      double height;     // 高度
};
// 初始化类 Box 的静态成员
int Box::objectCount = 0;
int main(void){
   Box Box1(3.3, 1.2, 1.5);    // 声明 box1 
   // 输出对象的总数
   cout << "Total objects: " << Box::objectCount << endl;
 
   return 0;
}
```

## const修饰类

> const修饰变量一般有两种方式：const T *a，或者 T const *a，这两者都是一样的.

> 类的成员函数后面加 const，表明这个函数不会对这个类对象的数据成员（准确地说是非静态数据成员）作任何改变。

> 在设计类的时候，一个原则就是对于不改变数据成员的成员函数都要在后面加 const，而对于改变数据成员的成员函数不能加 const。所以 const 关键字对成员函数的行为作了更加明确的限定：

> （1）有 const 修饰的成员函数（指 const 放在函数参数表的后面，而不是在函数前面或者参数表内），只能读取数据成员，不能改变数据成员；没有 const 修饰的成员函数，对数据成员则是可读可写的。
> （2）除此之外，在类的成员函数后面加 const 还有什么好处呢？那就是常量（即 const）对象可以调用 const 成员函数，而不能调用非const修饰的函数。

```c++
在C++中只有被声明为const的成员函数才能被一个const类对象调用。

若将成员函数声明为const，则不允许通过其修改类的数据成员。 值得注意的是，如果类中存在指针类型的数据成员即便是const函数只能保证不修改该指针的值，并不能保证不修改指针指向的对象
 const成员函数的写法有两种
　　1、void fun(int a，int b) const{}
　　2、void const fun(int a,int b){}
这两种写法的本质是：void fun (const 类 *this, int a,int b);
1）const成员函数可以访问非const对象的非const数据成员、const数据成员，也可以访问const对象内的所有数据成员；
2）非const成员函数可以访问非const对象的非const数据成员、const数据成员，但不可以访问const对象的任意数据成员；
```

```c++
class Point {
public :
    Point() {}
	Point(int x, int y) : Point() {
        cout << "param constructor : " << this << endl;
        this->x = x;
        this->y = y;
    }

    void set(int x, int y){
        this->x = x;
        this->y = y;
    }
    void get() const{
        get_cnt += 1;
        cout << this->x << " " << this->y << endl;
    }

    int S() const{return get_cnt;}
    
private:
    int x, y;
    mutable int get_cnt = 0;
};

int main() {
    Point a();
 	a(3, 4);
    const Point e(6, 7);
    e.get();
    e.get();
    e.get();
    e.get();
    cout << e.S() << endl;
    return 0;
}
```

