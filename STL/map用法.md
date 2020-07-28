[TOC]

# map用法



```c++
map是STL的一个关联容器，它提供一对一的hash。
第一个可以称为关键字(key)，每个关键字只能在map中出现一次；
第二个称为该关键字的值(value)；
map內部的实现自建一颗红黑树，这颗树具有对数据自动排序的功能。在map内部所有的数据都是有序的。

map的功能
自动建立key － value的对应。key 和 value可以是任意你需要的类型。

使用map得包含map类所在的头文件
#include <map> //注意，STL头文件没有扩展名.h

map对象是模板类，需要关键字和存储对象两个模板参数：
std:map<int, string> personnel;
这样就定义了一个用int作为索引,并拥有相关联的指向string的指针.
```



```c++
C++ maps是一种关联式容器，包含“关键字/值”对
begin()         返回指向map头部的迭代器
clear(）        删除所有元素
count()         返回指定元素出现的次数
empty()         如果map为空则返回true
end()           返回指向map末尾的迭代器
equal_range()   返回特殊条目的迭代器对
erase()         删除一个元素
find()          查找一个元素
get_allocator() 返回map的配置器
insert()        插入元素
key_comp()      返回比较元素key的函数
lower_bound()   返回键值>=给定元素的第一个位置
max_size()      返回可以容纳的最大元素个数
rbegin()        返回一个指向map尾部的逆向迭代器
rend()          返回一个指向map头部的逆向迭代器
size()          返回map中元素的个数
swap()           交换两个map
upper_bound()    返回键值>给定元素的第一个位置
value_comp()     返回比较元素value的函数
```



```c++
#include<iostream>
#include<string>
#include<map>
#include <unordered_map>
using namespace std;


int main(){
    map<double, string> arr;
    arr[1.2] = "hello";
    arr[4.3] = "world";
    arr[-4.5] = "haizei";
    arr[89.7] = "world";

    double n;
    while(cin >> n){
        if(arr.find(n) != arr.end()){
            cout <<"find: " << arr[n] << endl;
        }else{
            cout << "not found : " << n << endl;
        }
    }
//    cout << arr[1.2] << endl;
//    cout << arr[4.3] << endl;
    for(auto iter = arr.begin(); iter != arr.end(); iter++){
        cout << iter->first << " " << iter->second << endl;
    }
    return 0;
}
```



```c++
#include<stdio.h>
#include<map>

using namespace std;

int main(){
    map<char,int> mp;
    mp['a']=5;
    mp['b']=10;
    mp['d']=40;
    mp['c']=20;
    mp['c']=30;//20被覆盖
    printf("%d\n",mp['c']);//30
    
    mp.erase('b');//删除键为b的映射，也就是b 10
    for(map<char,int>::iterator it=mp.begin();it!=mp.end();it++){
        printf("%c %d\n",it->first,it->second);
    }
    //a 5
    //c 30
    //d 40
    map<char,int>::iterator it=mp.find("a");
    mp.erase(it);//删除a 5
    for(map<char,int>::iterator it=mp.begin();it!=mp.end();it++){
        printf("%c %d\n",it->first,it->second);
    }
    //c 30
    //d 40
    mp['e']=50;
    mp['f']=60;
    map<char,int>::iterator it=mp.find("d");
    mp.erase(it,mp.end());//删除区间， d 40  e 50
    return 0;
}
```

```c++
int main() {
    string name;
    int n, age;
    set<int> s;
    s.insert(3);
    s.insert(5);
    s.insert(2);
    s.insert(3);
    cout << *s.begin() << endl;
    s.erase(s.begin());
    for (auto iter = s.begin(); iter != s.end(); iter++) {
        cout << *iter << " ";
    }
    cout << endl;
    map<int, string> arr;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> age >> name;
        arr[age] = name;
    }
    for (auto iter = arr.begin(); iter != arr.end(); iter++) {
        cout << iter->second << endl; 
    }
    return 0;
}
```

