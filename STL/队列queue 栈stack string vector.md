[TOC]

# 队列queue 栈stack string vector

## 队列queue

> C++队列queue模板类的定义在头文件中,queue 模板类需要两个模板参数，一个是元素类型，一个容器类型，元素类型是必要的，容 器类型是可选的，默认为deque 类型。
> C++队列Queue是一种容器适配器，它给予程序员一种先进先出(FIFO)的数据结构

```c++
C++队列Queue类成员函数如下:
queue入队，如例：q.push(x); 将x 接到队列的末端。
queue出队，如例：q.pop(); 弹出队列的第一个元素，注意，并不会返回被弹出元素的值。
访问queue队首元素，如例：q.front()，即最早被压入队列的元素。
访问queue队尾元素，如例：q.back()，即最后被压入队列的元素。
判断queue队列空，如例：q.empty()，当队列空时，返回true。
访问队列中的元素个数，如例：q.size()
```

```c++
#include <cstdlib>
#include <iostream>
#include <queue>
using namespace std;
int main(){
    int e,n,m;
    queue< int > q1;
    for (int i = 0; i<10; i++)
       q1.push(i);
    if(!q1.empty())
    cout << "队列不为空\n" ;
    n = q1.size();
    cout << n << endl;
    m = q1.back();
    cout << m << endl;
    for(int j = 0; j < n; j++){
       e = q1.front();
       cout << e <<" ";
       q1.pop();
    }
    cout << endl;
    if(q1.empty())
    cout << "队列不为空\n";
    system("PAUSE");
    return 0;
}
```

## 栈stack

> stack翻译为栈，时STL中实现的一个后进先出的容器
>
> 定义方法与其他容器相同，typename可以任意基本类型数据类型或容器

```c++
stack<typename> name;
stack<int> s1;
stack<string> s2;
```

```c++
stack容器内元素的访问
由于栈（stack）本身就是一种后进先出的数据结构
在STL的stack中只能通过top()来访问栈顶元素
```

```c++
stack 的基本操作有：
s.push(x);   //入栈
s.pop();     //出栈，注意，出栈操作只是删除栈顶元素，并不返回该元素。
s.top();     //访问栈顶,但不删除该元素
s.empty();   //判断栈空，当栈空时，返回true。
s.size();    //访问栈中的元素个数
```

```c++
#include<iostream>
#include<stack>
using namespace std;
int main(){
	int a;
	stack<int> st;
	for (int i = 1; i < 4; i++){
		cin >> a;
		st.push(a);
	}
	for (int i = 1; i < 3; i++){
		cout << st.top();
		st.pop();
	}

	return 0;
}
```

## STRING

string 类：字符串

			头文件：string
			命名空间：std
			声明：string  s1, s2;

|                       |            |
| --------------------: | :--------- |
|            `s1 == s2` | 字符串判等 |
|             `s1 < s2` | 字典序小于 |
|             `s1 > s2` | 字典序大于 |
|            `s1 += s2` | 字符串连接 |
| `s1.length()`时间o(1) | 字符串长度 |

代码演示

```c++
#include <iostream>
#include <string>
using namespace std;

int main() {
	string input;
    cin >> input;
	cout << input << endl;
    cout << input.length() << endl;
    cout << input[0] << endl;
    string str = "yangzhou301";
    auto result = input + str; //自动类型推导
    cout << result << endl;
    cout << (result < str) << endl;
    return 0;
}
```

## vector用法

> vector 是向量类型，它可以容纳许多类型的数据，如若干个整数，所以称其为容器。vector 是C++ STL的一个重要成员，使用它时需要包含头文件：

```c++
#include<vector>;
```

```c++
一、vector 的初始化：可以有五种方式,举例说明如下：
    (1) vector<int> a(10); //定义了10个整型元素的向量（尖括号中为元素类型名，它可以是任何合法的数据类型），但没有给出初值，其值是不确定的。
   （2）vector<int> a(10,1); //定义了10个整型元素的向量,且给出每个元素的初值为1
   （3）vector<int> a(b); //用b向量来创建a向量，整体复制性赋值
   （4）vector<int> a(b.begin(),b.begin+3); //定义了a值为b中第0个到第2个（共3个）元素
   （5）int b[7]={1,2,3,4,5,9,8};
 	vector<int> a(b,b+7); //从数组中获得初值
```

```c++
二、vector对象的几个重要操作，举例说明如下：
（1）a.assign(b.begin(), b.begin()+3); //b为向量，将b的0~2个元素构成的向量赋给a
    （2）a.assign(4,2); //是a只含4个元素，且每个元素为2
    （3）a.back(); //返回a的最后一个元素
    （4）a.front(); //返回a的第一个元素
    （5）a[i]; //返回a的第i个元素，当且仅当a[i]存在2013-12-07
    （6）a.clear(); //清空a中的元素
    （7）a.empty(); //判断a是否为空，空则返回ture,不空则返回false
    （8）a.pop_back(); //删除a向量的最后一个元素
    （9）a.erase(a.begin()+1,a.begin()+3); //删除a中第1个（从第0个算起）到第2个元素，也就是说删除的元素从a.begin()+1算起（包括它）一直到a.begin()+         3（不包括它）
    （10）a.push_back(5); //在a的最后一个向量后插入一个元素，其值为5
    （11）a.insert(a.begin()+1,5); //在a的第1个元素（从第0个算起）的位置插入数值5，如a为1,2,3,4，插入元素后为1,5,2,3,4
    （12）a.insert(a.begin()+1,3,5); //在a的第1个元素（从第0个算起）的位置插入3个数，其值都为5
    （13）a.insert(a.begin()+1,b+3,b+6); //b为数组，在a的第1个元素（从第0个算起）的位置插入b的第3个元素到第5个元素（不包括b+6），如b为1,2,3,4,5,9,8         ，插入元素后为1,4,5,9,2,3,4,5,9,8
    （14）a.size(); //返回a中元素的个数；
    （15）a.capacity(); //返回a在内存中总共可以容纳的元素个数
    （16）a.resize(10); //将a的现有元素个数调至10个，多则删，少则补，其值随机
    （17）a.resize(10,2); //将a的现有元素个数调至10个，多则删，少则补，其值为2
    （18）a.reserve(100); //将a的容量（capacity）扩充至100，也就是说现在测试a.capacity();的时候返回值是100.这种操作只有在需要给a添加大量数据的时候才         显得有意义，因为这将避免内存多次容量扩充操作（当a的容量不足时电脑会自动扩容，当然这必然降低性能） 
    （19）a.swap(b); //b为向量，将a中的元素和b中的元素进行整体性交换
    （20）a==b; //b为向量，向量的比较操作还有!=,>=,<=,>,<

```

```c++
从现有向量中选择元素向向量中添加
int a[6]={1,2,3,4,5,6};
vector<int> b;
vector<int> c(a,a+4);
for(vector<int>::iterator it=c.begin();it<c.end();it++)
b.push_back(*it);
```

```c++
通过遍历器方式读取
int a[6]={1,2,3,4,5,6};
vector<int> b(a,a+4);
for(vector<int>::iterator it=b.begin();it!=b.end();it++)
    cout<<*it<<" ";
```

```c++
几种重要的算法，使用时需要包含头文件：
#include<algorithm>
（1）sort(a.begin(),a.end()); //对a中的从a.begin()（包括它）到a.end()（不包括它）的元素进行从小到大排列
（2）reverse(a.begin(),a.end()); //对a中的从a.begin()（包括它）到a.end()（不包括它）的元素倒置，但不排列，如a中元素为1,3,2,4,倒置后为4,2,3,1
（3）copy(a.begin(),a.end(),b.begin()+1); //把a中的从a.begin()（包括它）到a.end()（不包括它）的元素复制到b中，从b.begin()+1的位置（包括它）开        始复制，覆盖掉原有元素
（4）find(a.begin(),a.end(),10); //在a中的从a.begin()（包括它）到a.end()（不包括它）的元素中查找10，若存在返回其在向量中的位置
```

