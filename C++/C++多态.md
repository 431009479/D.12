

[TOC]

# C++多态

C++的多态性用一句话概括就是：在基类的函数前加上virtual关键字，在派生类中重写该函数，运行时将会根据对象的实际类型来调用相应的函数。如果对象类型是派生类，就调用派生类的函数；如果对象类型是基类，就调用基类的函数

```c++
  //1：用virtual关键字申明的函数叫做虚函数，虚函数肯定是类的成员函数。  
  //2：存在虚函数的类都有一个一维的虚函数表叫做虚表，类的对象有一个指向虚表开始的虚指针。虚表是和类对应的，虚表指针是和对象对应的。  
  //3：多态性是一个接口多种实现，是面向对象的核心，分为类的多态性和函数的多态性。  
  //4：多态用虚函数来实现，结合动态绑定.  
  //5:纯虚函数是虚函数再加上 = 0；  
  //6：抽象类是指包括至少一个纯虚函数的类。
纯虚函数:virtual void fun()=0;即抽象类！必须在子类实现这个函数
  一旦某个函数在基类中声明为virtual，那么在所有的派生类中该函数都是virtual，而不需要再显式地声明为virtual。
```



## 虚函数

> C++允许用户使用虚函数 **(virtual function)** 来完成 **运行时决议** 这一操作，这与一般的 **编译时决定** 有着本质的区别。
>
> 虚函数的实现是由两个部分组成的，虚函数指针与虚函数表。
>
> ### 虚函数指针

```c++
/*虚函数指针 (virtual function pointer) 从本质上来说就只是一个指向函数的指针，与普通的指针并无区别。它指向用户所定义的虚函数，具体是在子类里的实现，当子类调用虚函数的时候，实际上是通过调用该虚函数指针从而找到接口。
虚函数指针是确实存在的数据类型，在一个被实例化的对象中，它总是被存放在该对象的地址首位，这种做法的目的是为了保证运行的快速性。与对象的成员不同，虚函数指针对外部是完全不可见的，除非通过直接访问地址的做法。
 只有拥有虚函数的类才会拥有虚函数指针，每一个虚函数也都会对应一个虚函数指针。所以拥有虚函数的类的所有对象都会因为虚函数产生额外的开销，并且也会在一定程度上降低程序速度。*/
在构造函数中进行虚表的创建和虚表指针的初始化，在构造子类对象时，要先调用父类的构造函数，此时编译器只“看到了”父类，并不知道后面是否还有继承者，它初始化父类对象的虚表指针，该虚表指针指向父类的虚表，当执行子类的构造函数时，子类对象的虚表指针被初始化，指向自身的虚表。虚函数表
```

### 虚函数表

每一个类的实例化对象都会拥有虚函数指针并且都排列在对象的地址首部。而它们也都是按照一定的顺序组织起来的，从而构成了一种表状结构，称为虚函数。

```
1:每一个类都有虚表
2:虚表可以继承，如果子类没有重写虚函数，那么子类虚表中仍然会有该函数的地址，只不过这个地址指向的是基类的虚函数实现。
3：派生类的虚表中虚地址的排列顺序和基类的虚表中虚函数地址排列顺序相同。
c++的多态性就是通过晚绑定技术来实现的。
```



```
class Base{
    public:
    virtual void f(){cout<<"Base::f"<<endl;}
    virtual void g(){cout<<"Base::g"<<endl;}
    virtual void h(){cout<<"Base::h"<<endl;}
};
//首先对于基类Base它的虚函数表记录的只有自己定义的虚函数
```

![img](https://images0.cnblogs.com/blog/514794/201307/11192917-932f16a9db654164b4f8a9d2b3602f09.jpg)

```
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
//实例：
string rand_name(int n) {
    string name = "";
    for (int i = 0; i < n; i++) {
        name = name + (char)(rand() % 26 + 'A');
    }
    return name;
}

class Animal {
public :
    Animal(string name) : name(name) {}
    string tell_me_your_name() { return this->name; }
    virtual void run() {
        cout << "I don't know how to run" << endl;
    }
    virtual void say() = 0;
    virtual void func0() {}
    virtual ~Animal() {
        cout << "Animal destructor" << endl;
    }
private :
    string name;
};

class Cat : public Animal {
public :
    Cat() : Animal(rand_name(5) + " Cat") {}
    void run() override {
        cout << "I can run with four legs" << endl;
    }
    void func0() override {
        cout << "this is funco" << endl;
    }
    void say() override {
        cout << "miao~ miao~ miao~" << endl;
    }
    ~Cat() {
        cout << "Cat destructor" << endl;
    }
};

class Bat : public Animal {
public :
    Bat() : Animal(rand_name(5) + " Bat") {}
    void run() override {
        cout << "I can fly" << endl;
    }
    void say() override {
        cout << "zzz~ zzz~ zzz~" << endl;
    }
    ~Bat() {
        cout << "Bat destructor" << endl;
    }
};

int main() {
    Cat a;
    Bat b;
    cout << a.tell_me_your_name() << endl;
    a.run();
    cout << b.tell_me_your_name() << endl;
    b.run();
    Animal ** arr = new Animal*[10];
    for (int i = 0; i < 10; i++) {
        if (rand() % 2) {
            arr[i] = new Cat();
        } else {
            arr[i] = new Bat();
        }
    }
    for (int i = 0; i < 10; i++) {
        cout << arr[i]->tell_me_your_name() << endl;
        arr[i]->run();
        arr[i]->say();
    }
    for (int i = 0; i < 10; i++) {
        delete arr[i];
    }
    delete[] arr;
    return 0;
}
```



## 抽象类

在虚函数的后面写上 = 0，则这个函数为纯虚函数。**包含纯虚函数的类叫做抽象类（也叫接口类），抽象类不能实例化出对象。派生类继承后也不能实例化出对象**。只有重写纯虚函数，派生类才能实例化出对象。纯虚函数规范了派生类必须重写，另外纯虚函数更体现了接口继承。

```c++
class Car{
public:
	//纯虚函数
	virtual void Drive() = 0;
};

class Benz :public Car{
public:
	virtual void Drive(){
		cout << "Benz-舒适" << endl;
	}
};

class BMW :public Car{
public:
	virtual void Drive(){
		cout << "BMW-操控" << endl;
	}
};

void Test(){
	Car* pBenz = new Benz;
	pBenz->Drive();

	Car* pBMW = new BMW;
	pBMW->Drive();
}

int main(){
	Test();
	system("pause");
	return 0;
}
```



# 多态里的析构函数

> 在实现多态的时候，**定义抽象父类的时候记得定义虚析构函数**

```c++
void test1()
{
    Son *pson = new Son("tom", 20);
    pson->getInfo();
    delete pson;
}
************************************************
void test2()
{
    Base *p = new Son("jack", 22);
    p->getInfo();
    delete p;
}
```

```
在test1中创建的是Son类型的指针，所以在delete的时候删除的是Son类型指针，那么肯定会执行Son的析构函数，可是test2中创建的是Base类型指针，所以在delete是删除的是Base类型的指针，而Son虽然继承了Base，但是却没有重写Base的析构函数，所以执行不到Son里面去，也就无法执行Son的析构函数，因为压根儿delete的就不是Son指针。如果是这样的话，那么就会带来一个很严重的问题，那就是如果Son类中含有堆取开辟的空间需要在析构函数中释放，就会导无法释放，造成内存泄漏。
```

```
为了实现动态绑定，所以需要将父类的析构函数定义成虚函数，从而使调用父类西沟函数时动态绑定到子类的析构函数上。当然这里编译器还帮我们干了一件事，就是编译器把父类的析构函数数和子类的析构函数进行了一个绑定，因为正常情况下，只有子类重写了父类函数才会被动态绑定，但是这里虽然两个析构函数名都不一样，但是仍然能动态绑定，这就是编译器进行的一种绑定。
```



## this指针

> 在 C++ 中，每一个对象都能通过 **this** 指针来访问自己的地址。**this** 指针是所有成员函数的隐含参数。因此，在成员函数内部，它可以用来指向调用对象。

> 友元函数没有 **this** 指针，因为友元不是类的成员。只有成员函数才有 **this** 指针。

> 当我们调用成员函数时，实际上是替某个对象调用它。成员函数通过一个名为 this 的额外隐式参数来访问调用它的那个对象，当我们调用一个成员函数时，用请求该函数的对象地址初始化 this。

```c++
//类中用const修饰的函数通常用来防止修改对象的数据成员，函数末尾的const是用来修饰this指针，防止在函数内对数据成员进行修改，而静态函数中是没有this指针的，无法访问到对象的数据成员，与C++ static语义冲突，所以不能。
1.C++中this关键字是一个指向对象自己的一个常量指针，不能给this赋值；
2.只有成员函数才有this指针，友元函数不是类的成员函数，没有this指针；
3.同样静态函数也是没有this指针的，静态函数如同静态变量一样，不属于具体的哪一个对象；
4.this指针作用域在类成员函数内部，在类外也无法获取；
5.this指针并不是对象的一部分，this指针所占的内存大小是不会反应在sizeof操作符上的。
```

> this指针是什么时候创建的？对象new的过程中创建的

```c++
class Animal {
public :
    Animal() {
        x = 8827, y = 65123;
    }
    virtual void say(int x) {
        cout << "I don't know how to say" << endl;
    }
    virtual void run() {
        cout << "I don't know how to run" << endl;
    }
protected :
    int x, y;
};

class Cat : public Animal {
public :
    void say(int x) override {
        cout << this << endl;
        cout << this->x  << " " << this->y << endl;
        cout << x << endl;
        cout << "miao~ miao~ miao~" << endl;
    }
    void run() override {
        cout << "I can run with four legs" << endl;
    }
};

void output_raw_data(void *q, int n) {
    printf("%p : ", q);
    unsigned char *p = (unsigned char *)q;
    for (int i = 0; i < n; i++) {
        printf("%02X ", p[i]);
    }
    printf("\n");
    return ;
}

typedef void (*func)(void *, int x);

int main() {
    Cat a, b;
    output_raw_data(&a, sizeof(a));
    output_raw_data(&b, sizeof(b));
    ((func **)(&a))[0][0](&a, 123);
    return 0;
}
```

