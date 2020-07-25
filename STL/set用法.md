[TOC]

# set用法

set具备的两个特点：

set中的元素都是排序好的
set中的元素都是唯一的，没有重复的.

其实set的大部分操作是与vector类似的，不过set不支持随机访问，必须要使用迭代器去访问。由于set放入一个元素就会调整这个元素的位置，把它放到合适的位置，所以set中只有一个insert插入操作。

```c++
include<set>       //set 的头文件 
set<int> s;        //声明一个int型set变量,名为s　
s.empty()       //判定 s 是否为空 
s.insert(1);       //把数字1插入到s中 
s.clear();        //清空s 
s.erase(1);        //假若s存在1，则删除1 
erase(iterator)  ,删除定位器iterator指向的值
erase(first,second),删除定位器first和second之间的值
erase(key_value),删除键值key_value的值

 
s.begin();        //返回s中第一个元素地址  所以 *s.begin() 
s.end();        //返回s中最后一个元素地址  
                    //这个特殊一点，返回的是s中最后一个元素的下一个元素 
                    //所以  *(--s.end())是s最后一个元素 
s.rbegin();        //rbegin可以看做逆向的第一个地址   相当于(--s.end())  此处取的已经是s最后一个元素 
s.rend();        //rend可以看做逆向的最后一个地址  相当于 s.begin() 
s.count(1);        //计算s中1出现的次数，而次数只存在0与1，所以可以借来查找是否存在1 
s.size();        //返回s中元素的个数 
s.max_size();    //s最大能存元素的数目 
s.find(2);        //查找2 
set<int>::iterator iter;    //迭代器 
```

```c++
//lower_bound(key_value) ，返回第一个大于等于key_value的定位器
//upper_bound(key_value)， 返回最后一个大于等于key_value的定位器
#include <iostream>
#include <set>
using namespace std;
int main(){
    set<int> s;
    s.insert(1);
    s.insert(3);
    s.insert(4);
    cout<<*s.lower_bound(2)<<endl;
    cout<<*s.lower_bound(3)<<endl;
    cout<<*s.upper_bound(3)<<endl;
    return 0;
}
```

```
216.OJ
```

![image.png](http://ww1.sinaimg.cn/large/00882iMuly1gh18rxfujej30mw0mhta2.jpg)

```c++
#include<iostream>
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
#include<vector>
#include <map>
#include <set>
#include<cstdlib>
using namespace std;
typedef pair<string, int> PIR; //定义新的类型
int main(){
    set<PIR> s; //定义set的集合
    string name;
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> name;
        name = name.substr(name.find(".") + 1, name.size());
        //返回一个string，包含name中从name.find() + 1开始到name.size()个字符的拷贝（name.size()的默认值是s.size() - pos）
        s.insert(PIR(name, i));
    }
    for(auto iter = s.begin(); iter != s.end(); iter++){ //迭代器；
        cout << iter->first << endl; //取PIR类型的第一个 参数。
    }
    return 0;
}
```

```
287.OJ
```

![image.png](http://ww1.sinaimg.cn/large/00882iMuly1gh18u18pejj30nz0lpmzq.jpg)



```c++
#include<iostream>
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
#include<vector>
#include<set>
#include<cstdlib>
using namespace std;

typedef pair<int, int> PII;
int main(){
    int n, a, t = 0, sum = 0;
    cin >> n;
    set<PII> s;
    for(int i = 0; i < n ; i++){
        cin >> a;
        s.insert(PII(a, t++));
    }
    for(int i = 0; i < n - 1; i++){
        int a = s.begin()->first;
        s.erase(s.begin());
        int b = s.begin()->first;
        s.erase(s.begin());
        sum += a + b;
        s.insert(PII(a + b, t++));
    }
    return 0;
}
```

