[TOC]

# C++ 继承 

> 面向对象程序设计中最重要的一个概念是继承。继承允许我们依据另一个类来定义一个类，这使得创建和维护一个应用程序变得更容易。这样做，也达到了重用代码功能和提高执行效率的效果。这个已有的类称为**基类**，新建的类称为**派生类**。

## 三种继承方式

```c++
//继承方式影响的是外部对于子类从父类继承过来的属性和方法对外的访问权限，只能更底不能更高
我们几乎不使用 protected 或 private 继承，通常使用 public 继承。当使用不同类型的继承时，遵循以下几个规则：
公有继承（public）：当一个类派生自公有基类时，基类的公有成员也是派生类的公有成员，基类的保护成员也是派生类的保护成员，基类的私有成员不能直接被派生类访问，但是可以通过调用基类的公有和保护成员来访问。
保护继承（protected）： 当一个类派生自保护基类时，基类的公有和保护成员将成为派生类的保护成员。
私有继承（private）：当一个类派生自私有基类时，基类的公有和保护成员将成为派生类的私有员。
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190602222130347.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3N0dWR5aGFyZGk=,size_16,color_FFFFFF,t_70)

1.公有继承

![img](https://img2018.cnblogs.com/blog/1359491/201809/1359491-20180918222635267-100763317.png)

公有继承private限定符：

![img](https://img2018.cnblogs.com/blog/1359491/201809/1359491-20180918222711028-1097640678.png)

2.保护继承

![img](https://img2018.cnblogs.com/blog/1359491/201809/1359491-20180918222740121-1383406860.png)

3.私有继承

![img](https://img2018.cnblogs.com/blog/1359491/201809/1359491-20180918222756717-1972595204.png)

```c++
//无论哪种继承方式，父类中private都继承到子类中不可见位置，无法通过子类函数访问
```

```
继承中的特殊关系——隐藏与is A
1、隐藏
子类public继承父类，子类中有成员函数与父类的同名但是参数不同的情况下，无法进行重载；父类的同名函数依旧会被隐藏；
子类.函数（）;调用的是子类中的成员函数，子类.父类::函数（）;调用的是父类的成员函数，同理同名数据成员。
2、Is a

父类的指针指向子类对象的时候 只能访问子类中父类原有的数据成员和成员函数，而无法访问子类中独有的数据成员和成员函数
子类对象向父类对象赋值。或用子类对象初始化父类对象，本质是将子类当中从父类继承下来的数据成员赋值给父类对象，而其他的数据将会被截断，丢失。
父类指针指向子类对象。父类指针只能访问父类原有的成员。
```

```c++
class Alnimal {
public:
    Alnimal(string name, int age) : __name(name), age(age){}
    void say(){
        cout << "my name is : " << __name  << ",my age is : "<< age << endl;
    }

protected:
    string __name;
private:
    int age;
};

class Cat :public Alnimal{
public:
    Cat() = delete;
    Cat(string name, int age) : Alnimal(name, age){}
};

class Bat :protected Alnimal{
public:
    Bat() = delete;
    Bat(string name, int age) : Alnimal(name, age){}
    void say(){
        Alnimal::say();
        cout << "class Bat : " << __name << endl;
        //cout << "class Bat : " << age << endl;
    }
};
int main(){
    Cat a("kitty", 29);
    a.say();
    Bat b("hug", 16384);
    b.say();
    return 0;
}
```

## 构造函数

```c++
总结下来，我们必须明确的是当一个类继承与基类，并且自身还包含有其他类的成员对象的时候，构造函数的调用顺序为：调用基类的构造函数->调用成员对象的构造函数->调用自身的构造函数。构造函数的调用次序完全不受构造函数初始化列表的表达式中的次序影响，与基类的声明次数和成员对象在函数中的声明次序有关。
假设 class C : public A, public B{
		D d;
}；

//则初始化的顺序是A, B, D, C的构造函数。
//这里基类的初始化顺序是按照声明的顺序, 成员对象也是按照声明的顺序。 因此 C(int i, int j) : B(i), A(j) {} //这里成员初始化列表的顺序是不起作用的
//析构函数的顺序则刚好是调过来, 构造/析构顺序可看作是一种栈的顺序。
```



```c++
class D{
public :
    D(){ cout << "D constructor" << endl; }
    ~D(){
        cout << "D destructor" << endl;
    }
};

class A{
public :
    A() = delete;
    A(int x, int y) {cout <<"A constructor" << endl;}  
    ~A(){
        cout << "A destructor" << endl;
    }
};

class B{
public:
    B() {cout <<"B constructor" << endl;}
    ~B(){
        cout << "B destructor" << endl;
    }
};

class C : public D{
public:
   // C() {cout << "C constructor";}
    C() : a(3, 4) {cout << "C constructor" << endl;}
    ~ C(){
        cout << "C destructor" << endl;
    }
private:
    A a;
    B b;
};

int main(){
    C c;
    return 0;

    return 0;
}
```

## 菱形继承和菱形虚拟继承

### 菱形继承

（也叫钻石继承）是下面的这种情况

![这里写图片描述](https://img-blog.csdn.net/20160411232722261)

菱形继承会造成派生类的数据冗余

```c++
struct A{
    int x;
};
struct B : public A{
    void set(int x){
        this->x = x;
        cout << "set:" << &this->x << endl;
    }
};
struct C: public A{
    int get() {
        cout << "get:" << &this->x << endl; 
        return this->x;
    }
};

struct D : public B, public C{};

int main(){
    D d;
    d.set(9973);
    cout << sizeof(d) << endl;
    cout << d.get() << endl;
    return 0;
}
```



### 虚拟继承

> virtual 虚拟的关键字

可以解决菱形继承的二义性和数据冗余的问题。虚继承的提出就是为了解决多重继承时，可能会保存两份副本的问题，也就是说用了虚继承就只保留了一份副本，但是这个副本是被多重继承的基类所共享的

![img](https://img-blog.csdn.net/20160411234152764)

```c++
struct A{
    int x;
};
struct B : virtual public A{
    void set(int x){
        this->x = x;
        cout << "set:" << &this->x << endl;
    }
};
struct C: virtual public A{
    int get() {
        cout << "get:" << &this->x << endl; 
        return this->x;
    }
};

struct D : public B, public C{};

int main(){
    D d;
    d.set(9973);
    cout << sizeof(d) << endl;
    cout << d.get() << endl;
    return 0;
}
```

## C++虚函数

> C++允许用户使用虚函数 **(virtual function)** 来完成 **运行时决议** 这一操作，这与一般的 **编译时决定** 有着本质的区别。
>
> 虚函数的实现是由两个部分组成的，虚函数指针与虚函数表。
>
> ### 虚函数指针
>
> ```c++
> 虚函数指针 (virtual function pointer) 从本质上来说就只是一个指向函数的指针，与普通的指针并无区别。它指向用户所定义的虚函数，具体是在子类里的实现，当子类调用虚函数的时候，实际上是通过调用该虚函数指针从而找到接口。
>    虚函数指针是确实存在的数据类型，在一个被实例化的对象中，它总是被存放在该对象的地址首位，这种做法的目的是为了保证运行的快速性。与对象的成员不同，虚函数指针对外部是完全不可见的，除非通过直接访问地址的做法或者在DEBUG模式中，否则它是不可见的也不能被外界调用。
>     只有拥有虚函数的类才会拥有虚函数指针，每一个虚函数也都会对应一个虚函数指针。所以拥有虚函数的类的所有对象都会因为虚函数产生额外的开销，并且也会在一定程度上降低程序速度。
> ```
>
> **虚函数表**
>
> ```
> > 每个类的实例化对象都会拥有虚函数指针并且都排列在对象的地址首部。而它们也都是按照一定的顺序组织起来的，从而构成了一种表状结构，称为虚函数。this指针
> ```

```c++
class Base{
    public:
    virtual void f(){cout<<"Base::f"<<endl;}
    virtual void g(){cout<<"Base::g"<<endl;}
    virtual void h(){cout<<"Base::h"<<endl;}
};
//首先对于基类Base它的虚函数表记录的只有自己定义的虚函数
```

![img](https://images0.cnblogs.com/blog/514794/201307/11192917-932f16a9db654164b4f8a9d2b3602f09.jpg)

```c++
//子类一般覆盖继承,首先是最常见的继承，子类Derived对基类的虚函数进行覆盖继承
class Derived:public Base{
	public:
    virtual void f(){cout<<"Derived::f"<<endl;}
    virtual void g1(){cout<<"Derived::g1"<<endl;}
    virtual void h1(){cout<<"Derived::h1"<<endl;}
}
```

![img](https://images0.cnblogs.com/blog/514794/201307/11195425-795497a4edd54824815aecb5688ad0c3.jpg)

> 当多重继承的时候，表项将会增多，顺序会体现为继承的顺序，并且子函数自己的虚函数将跟在第一个表项后

![img](https://images0.cnblogs.com/blog/514794/201307/11202442-57573dac02f14024b79840ca7b0cc815.jpg)

![img](https://images0.cnblogs.com/blog/514794/201307/11202508-9575b5f392f04f71a64194264dcbdd4d.jpg)

> C++中一个类是公用一张虚函数表的，基类有基类的虚函数表，子类是子类的虚函数表，这极大的节省了内存

```c++
class Animal{
public:
    virtual void runI(){ //虚函数
        cout << "I don't konw how to run" << endl;
    }
};

class Cat :public Animal{
public :
    void runI() override{ //override保留字表示当前函数重写了基类的虚函数,强制编译器检查某个函数是否重写基类虚函数,如果没有则报错.
        cout << "I can run whit four legs" << endl;
    }
};

class Dog :public Animal{
public:
    void runI()override{
        cout << "I can run with four legs, tail yao a yao" << endl;
    }
};
class Bat :public Animal{
public:
    void runI()override{
        cout << "I can fly!" << endl;
    }
};

class A{	
public :
    int x;
    virtual void say(){} //虚函数，在虚函数表是虚函数指针，虚函数表占8个字节。
    virtual void run(){} //和say()同在一个虚函数表中。
};

int main(){
    cout << sizeof(A) << endl; //16；
    srand(time(0));
    Cat a;
    cout << sizeof(Cat) << endl;
    Animal k;
    Animal &b = a;
    Animal *c[10];
    a.runI();
    b.runI();
    k.runI();

    for(int i = 0; i < 10; i++){
        int n = rand() % 3;
        switch(n){
            case 0: c[i] = new Cat(); break;
            case 1: c[i] = new Dog(); break;
            case 2: c[i] = new Bat(); break;
        }
    }
    for(int i = 0; i < 10; i++){
        c[i]->runI();
    }
    return 0;
}
```

