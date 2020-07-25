[TOC]

#  python中的常见模块

## requests模块

Requests模块是第三方模块，需要预先安装，requests模块在python内置模块的基础上进行了高度的封装，从而使得python进行网络请求时.

1.安装
非常简单，打开cmd，直接pip安装,或pycharm 中搜索 requests 安装即可.

```python
pip install requests
```

2.导入模块

```python
import requests
```

Get 请求

发送无参数的get请求,尝试获取某个网页.

```python
r = requests.get('http://www.baidu.com')
```

发送无参数的get请求 设置超时时间 timeout 单位秒

```python
r = requests.get('http://www.baidu.com', timeout=1)
```

发送带参数的请求.

你也许经常想为 URL 的查询字符串(query string) 传递某种数据。如果你是手工构建 URL，那么数据会以键/值对的形式置于 URL 中，跟在一个问号的后面。例如， www.baidu.com/?key=val。 Requests 允许你使用 params 关键字参数，以一个字符串字典来提供这些参数。举例来说，如果你想传递 key1=value1 和 key2=value2 到 www.baidu.com/ ，那么你可以使用如下代码：

```python
payload = {'key1': 'value1', 'key2': 'value2'}
r = requests.get("https://www.baidu.com/", params=payload)
print(r.url)
https://www.baidu.com/?key2=value2&key1=value1
```

你还可以将一个列表作为值传入.

```python
payload = {'key1': 'value1', 'key2': ['value2', 'value3']}
r = requests.get('http://www.baidu.com/', params=payload)
print(r.url)
http://www.baidu.com/?key2=value2&key2=value3&key1=value1
```

定制请求头
如果你想为请求添加 HTTP 头部，只要简单地传递一个 dict 给 headers 参数就可以了

```python
url = 'https://www.baidu.com/s?wd=python'
headers = {
        'Content-Type': 'text/html;charset=utf-8',
        'User-Agent' : 'Mozilla/5.0 (Windows NT 10.0; Win64; x64)'
    }
r = requests.get(url,headers=headers)
```

```python
r.url                             #打印输出该 URL
r.headers                         #以字典对象存储服务器响应头，但是这个字典比较特殊，字典键不区分大小写，若键不存在则返回None
r.status_code                     #返回连接状态，200正常。
r.text                            #默认以unicode形式返回网页内容，也就是网页源码的字符串。
r.content                         #以字节形式（二进制）返回。字节方式的响应体，会自动为你解码 gzip 和 deflate 压缩。
r.json()                          #把网页中的json数据转成字典并将其返回。
r.encoding                        #获取当前的编码
r.encoding = 'ISO-8859-1'         #指定编码,r.text返回的数据类型，写在r.text之前。
```



## Json模块

JSON(JavaScript Object Notation, JS 对象标记) 是一种轻量级的数据交换格式。JSON的数据格式其实就是python里面的字典格式，里面可以包含方括号括起来的数组，也就是python里面的列表。

Json  模块提供了四个方法： dumps、dump、loads、load

序列化简单定义：变成json格式。定义：变成json格式。
反序列化简单定义： json格式变其它

### json使用(常用)：

```python
1）# 序列化，将python的值转换为json格式的字符串。序列化json.dumps() True变true了。序列化 
import json
v = [12,3,4,{'k1':'v1'},True,'asdf']
v1 = json.dumps(v)
print(v1,type(v1))
--------------结果；
[12, 3, 4, {"k1": "v1"}, true, "asdf"] <class 'str'>    
    
2）反序列化json.load（），将json格式的字符串转换成python的数据类型
import json
v2 = '["mcw",123]'
print(type(v2))
v3 = json.loads(v2)
print(v3,type(v3))
-----------------结果；
<class 'str'>
['mcw', 123] <class 'list

json序列化过程中的中文显示
val = json.dumps(v,ensure_ascii=False)
```



## math模块

```python
Python math 模块提供了许多对浮点数的数学运算函数。
Python cmath 模块包含了一些用于复数运算的函数。
cmath 模块的函数跟 math 模块函数基本一致，区别是 cmath 模块运算的是复数，math 模块运算的是数学运算。
要使用 math必须先导入：
import math
>>> import math
>>> dir(math)
['__doc__', '__file__', '__loader__', '__name__', '__package__', '__spec__', 'acos', 'acosh', 'asin', 'asinh', 'atan', 'atan2', 'atanh', 'ceil', 'copysign', 'cos', 'cosh', 'degrees', 'e', 'erf', 'erfc', 'exp', 'expm1', 'fabs', 'factorial', 'floor', 'fmod', 'frexp', 'fsum', 'gamma', 'gcd', 'hypot', 'inf', 'isclose', 'isfinite', 'isinf', 'isnan', 'ldexp', 'lgamma', 'log', 'log10', 'log1p', 'log2', 'modf', 'nan', 'pi', 'pow', 'radians', 'sin', 'sinh', 'sqrt', 'tan', 'tanh', 'tau', 'trunc']
```

```python
# 数学相关模块
import math
r = math.floor(3.2) # 向下取整
print(r)
r = math.ceil(4.5)  # 向上取整
print(r)
r = round(3.4999)  # 四舍五入
print(r)
r = math.pow(3,4)  # =3**4
print(r)
r = math.sqrt(25)  # 开平方
print(r)
r = math.fabs(-0.23) # 绝对值(小数)
print(r)
r = abs(-2)     # 绝对值
print(r)
r = math.modf(3.14) # 拆分小数和整数
print(r)
r = math.copysign(3,-5) #-5的符号赋给3
print(r)
lt = [1,4,5,7]    # 计算lt中数字的和(结果浮点数）
r = math.fsum(lt)
print(r)
r = sum(lt)     # 同上（结果整数）
print(r)
print(math.pi)    # 圆周率
print(math.e)    # 自然对数
# 随机数模块
import random
r = random.random() # 随机获取0~1小数
print(r)
lt = [2,3,5,7,'A','C','d']
r = random.choice(lt) # 随机获取lt中一个值
print(r)
random.shuffle(lt) #打乱列表
print(lt)
r = random.randrange(5,15,2) #获取制定范围内随机的整数
print(r)
r = random.uniform(4,24)   #获取制定范围内随机数
print(r)
# 内建函数
nums = [2,3,5,7,0,23,21,-11,0.4]
print(max(nums))    # 获取最大值
print(min(nums))    # 获取最小值
# 进制相关
hex(3)
oct(3)
bin(3)
print(ord('a')) # 获取相对应的ascii码
print(chr(90))  # 获取ascii码相对应的字符
num = 99
var = 'num + 1'
nums = eval(var) # 将python字符串当做代码执行 慎用
print(nums)
```

## os模块

###  重命名 rename()方法：

rename()方法需要两个参数，当前的文件名和新文件名。

```
os.rename(current_file_name, new_file_name)
```

例子：

下例将重命名一个已经存在的文件test1.txt。

```python
#!/usr/bin/python
# -*- coding: UTF-8 -*-
import os
 
# 重命名文件test1.txt到test2.txt。
os.rename( "test1.txt", "test2.txt" )
```

### remove()方法

你可以用remove()方法删除文件，需要提供要删除的文件名作为参数。

语法：

```
os.remove(file_name)
```

例子：

下例将删除一个已经存在的文件test2.txt。

```python
#!/usr/bin/python
# -*- coding: UTF-8 -*-

import os
 
# 删除一个已经存在的文件test2.txt
os.remove("test2.txt")
```

### mkdir()方法

可以使用os模块的mkdir()方法在当前目录下创建新的目录们。你需要提供一个包含了要创建的目录名称的参数。

语法：

```
os.mkdir("newdir")
```

例子：

下例将在当前目录下创建一个新目录test。

```python
#!/usr/bin/python
# -*- coding: UTF-8 -*-

import os
 
# 创建目录test
os.mkdir("test")
```

### chdir()方法

可以用chdir()方法来改变当前的目录。chdir()方法需要的一个参数是你想设成当前目录的目录名称。

语法：

```
os.chdir("newdir")
```

例子：

下例将进入"/home/newdir"目录。

```python
#!/usr/bin/python
# -*- coding: UTF-8 -*-

import os
 
# 将当前目录改为"/home/newdir"
os.chdir("/home/newdir")
```

### getcwd()方法：

getcwd()方法显示当前的工作目录。

语法：

```
os.getcwd()
```

例子：

下例给出当前目录：

```python
#!/usr/bin/python
# -*- coding: UTF-8 -*-

import os
 
# 给出当前的目录
print os.getcwd()
```

### rmdir()方法

rmdir()方法删除目录，目录名称以参数传递。

在删除这个目录之前，它的所有内容应该先被清除。

语法：

```
os.rmdir('dirname')
```

例子：

以下是删除" /tmp/test"目录的例子。目录的完全合规的名称必须被给出，否则会在当前目录下搜索该目录。

```python
#!/usr/bin/python
# -*- coding: UTF-8 -*-

import os
 
# 删除”/tmp/test”目录
os.rmdir( "/tmp/test"  )
```

```python
#打开文件
path = '/home/xiongdongdong/'
dirs = os.listdir(path)

for file in dirs:
    print(file)

```

## datetime模块

```python
from datetime import datetime
#获取当前时间
now = datetime.now()
print(now)
#创建指定日期对象
date1 = datetime(2015, 7, 17, 11, 30, 20)
print(date1)
#当前时间转时间戳
print(now.timestamp())
#日期转字符串
print(now.strftime('%Y-%m-%d'))
#字符串转日期
date2 = datetime.strptime('2018-10-20 10:15:40', '%Y-%m-%d %H:%M:%S')
print(type(date2))
print(date2)

```

## random模块

```python
#!/usr/bin/env python
# coding=utf-8
import random
#0~1之间的随机数
print(random.random())
#10~100之间的随机数
print(random.randint(10, 100))

#随机列表的一个值
list1 = [1, 2, 3, 5, 7, 9, 17]
print(random.choice(list1))

print(random.choice([120,110,119]))

```

