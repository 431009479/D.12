# vim github相关命令

__/__  用作在vim more less等命令中进行搜索

在Vim及其他文本处理命令中，向下搜索，一般按键盘上的 __n__, 向上搜索按 __N__

用命令 __vimtutor__ 来学习vim的使用

在__行末__尾插入 __A__ 

在__行首__插入 __I__

在__下一行__插入 __o__

在当前位置插入 __i__

删除当前字符用__x__

__^__ 行首， __$__ 行末

删除当前一个单词并__保留空格__用 __de__ ，__dw__删除一个单词__不保留空格__

删除当前整行文本用__dd__

从当前位置删除到文本头部用__dgg 或 d1G__

删除到行末用__d$__

从当前位置删除10行用__d10d 或 10dd__

 将删除的文本在当前位置粘贴用__p__。

从Github或者别的远程仓库，可以使用命令**git clone 网页**将代码仓库克隆到本地，本地如果修改后，可以使用**git push**将已经提交到本地仓库的代码推送到远端

回到文本第一行首位的快捷命令是 __gg__ 

直接到文本末尾的快捷命令是__G__

回到文本第123行的命令是__123gg 或 123G__

在本地修改代码后，大致需要两个步骤将本地改动写入到本地仓库，分别是**git add .**和**git commit -m "注释"**，在git使用过程中，如果你想查看本地仓库的状态，比如有哪些文件发生改动，是否有未提交的代码等，可以使用命令**git status**。

有时候，你可能需要从其他位置拷贝代码到Vim编辑器中，但很有可能因为你对Vim的优化配置导致粘贴进去的代码格式混乱，并且因为Vim联想单词的原因，导致粘贴巨卡，在这种情况下，粘贴前，应该执行命令__:set paste__;

VIm默认配置下，是不显示行号的，我们可以通过什么命令来显示行号：__:set nu__

Vim编辑器中，我们也可以通过设置来显示一些平时看不到的字符，如TAB，断行符等，该命令是__:set list__.

## 第一个SHELL脚本

```
#注释
echo输出
```

脚本执行 

+ bash + 脚本
+ bash a.sh 执行的是bash 将a.sh文件作为标准输入到bash
+ a.sh 文件有可执行权限
+ chmod + 脚本
+ chmod a.sh 给文件一个可执行权限，通过全路径方式让操作系统去执行



## 变量与局部变量 

shell 弱类型语言

```
a=12 不用纠结12是什么类型，取决后面怎么用 因为SHELL是弱类型语言而C是强类型，必须有类型 
a=helloworld
a=`pwd` ``命令替换符
a=$a1:a2  把:a2(字符)拼接在a1后面
局部变量 local=12
{[]}整数计算
${}用来限定$符的范围
$变量引用 取变量的值
```

# SHELL语法

## 特殊变量

### 位置变量

```
$0 :获取当前执行shell脚本的文件名，包括路径(函数的第0个参数就是函数名)
$n :获取当前执行脚本的第n个参数，n=1...9,如果n大于9，则需将n使用大括号括起来
$* :获取当前shell的所有参数，将所有命令行参数视为单个字符串，相当于"$1$2$3"
$# :得到执行当前脚本的参数个数
$@ ：获取这个程序所有的参数，并保留参数之间的任何空白，相当于“$1” “$2” “$3”,这是将参数书传给其他程序的最好的办法(知道就可以，效果和$3差不多)
# 求长度
```

### 状态变量

```
$? ：判断上一指令是否成功执行，0为成功，非0为不成功
(了解)$$ :取当前进程的PID
(了解)$! :上一个指令的PID
```

## 变量，参数展开

![1](/home/unique/Desktop/海贼/picture/1.png)

## 字符串展开（了解）

![SHELL2](/home/unique/Desktop/海贼/picture/SHELL2.png)

![shell3](/home/unique/Desktop/海贼/picture/shell3.png)

## 输入输出-READ

```
read [-options] [variable...]
	  选项       变量名（...可变）  
	-a array     #把输入赋值到array中，从索引号0开始
	-p prompt	 #为输入显示提供信息，使用字符串prompt 
	-s           #Slient mode(例输入密码时卡看不见)
	-t seconds   #超时
	-d delimiter #用字符串delimiter中的第一个字符指示输入结束，而不是一个换行符
	-e           #使用Readline来处理，这使得与命令行相同的方式编辑输入
	-n num		 #读取num个输入字符，而不是整行
	-r           #Raw mode.不把反斜杠字符解释为转义字符
	-u fd        #使用文件描述fd中的输入，而不是标准输入
```

## 输入输出-ECHO

```
echo string
	echo -e ""Hello HaiZei\n" #开启转义
	echo "Hello $name, This is HaiZei"
	echo "\"Hello HaiZei\""
```

## 输入输出-PRINTF

printf format-string [arguments...]

![shell4](/home/unique/Desktop/海贼/picture/shell4.png)

## 函数

```
函数定义三种形式
function _printf_ {
    echo $1
    return
}
_printf_() {
    echo $1
    return 
}
funcyion _printf() {
    echo $1
    return 
}

函数使用方法
_printf_ "Hello HaiZei"
```

## 流程控制-IF

__fi表示if的结束__

```
if [[ condition ]]; then
	#ststement
fi
```

```
if [[ condition ]]; then
 	#statement
 	else
 		#statement
 fi
```

```
if [[ condition ]]; then
	#statement
elif [[ condition ]]; then
	#statement
elif [[ condition ]]; then
	#statement
	else
	#statement
fi
```

## 流程控制for

__words表示一个列表，一个范围__

```
for i in words; do
	#statements
done
for i in $* 对每一个参数
```

```
for (( i = 0; i < 10; i++ )); do
	#statements
done
```

```
for i in `ls`; do
	echo $i
done
输出所有文件
```

```
seq 1 10
由1为步长到10
直接输出1到10
```



## 流程控制-WHILE

__condition成立时循环__

```
while [[ condition ]]; do
	#statement
done
```

```
while [[ $i -lt 100 ]]; do
	echo $i //i默认0
	i=$[ ${i} + 1]
	//let i=i+1
done
输出
0到99
```

## 流程控制-UNTIL

__循环，知道condition成立__

```
until [[ condition ]]; do
	#statement
done
```

## 流程控制-CASE

```
case word in 
	pattern )
		;;
esac
例：
case num in
	1) echo 1
		;; //相当于break
	2) echo 2
		;;
esac
```

```
read -p "input num" num//先输出input num提醒输入
case $num in 
	1) 
		echo "1"
		;;
	2)
		echo "2"
		;;
esac
```

## 数组

```
declare   -a   a
//声明一个 数组  a    
	name[subscript]=value
	//   下标
	name=(value value2 ...)
```

``` 
终端输入
file=(`ls`)一个存了当前目录下全部文件的数组
echo ${files} 相当于输出第一个元素也就是第一个文件
echo ${files[*]}输出全部文件
echo ${files[@]}输出全部文件
echo ${files[n]} 输出下标为n的元素，也就是输出下标为n的文件
echo ${#files} 输出数组数组的files的总数
echo ${!files} 	求数组全部的下标
shell数组很大可以认为没有限制
unset删除
set创建
unset files[13]删除下标为13的元素
files+=(`ls`)在files后面追加
```

![shell数组](/home/unique/Desktop/海贼/picture/shell数组.png)

![shell数组追加](/home/unique/Desktop/海贼/picture/shell数组追加.png)

### 数组操作

```
输出数组内容
	${arry[*]}
	${arry[@]}
确定数组元素个数
	${#arry[@]}
找到数组的下标
	${!arry[@]}
数组追加
	arry+=(a b c)
数组排序
	sort
删除数组与元素
	unset
```

## man test test语句

```
man test
```

# 查man 手册

man -f 

man -k 相关的

![man](/home/unique/Desktop/海贼/picture/man.png)

grep检索

# linux帮助系统

## man手册

> 用man手册来查询某个命令和功能的使用

使用方法 `man+某个命令` 例如 man + ls用来查看ls相关的命令帮助

```
man手册中有具体的描述，解释，选项及退出状态等，并且每个命令的手册分为几个部分，1 2 3 4 5，可分别查看
ls [option]...[file] []有可选的意思 option 选项 ...代表可变参数
描述中参数是按照字母顺序排列的
可以用搜索来查找某个选项的具体作用
退出状态
return 0 是成功
return 1 是小错误 
return 2 是大错误
```

在man 中，常见的几个数字的含义如下

| 代号 | 代表含义                                           | 举例               |
| :--: | -------------------------------------------------- | ------------------ |
|  1   | 用户在SHELL环境下可以操作的命令或可执行文件        | `man 1 ls`         |
|  2   | 系统内核可调用的函数和工具                         | `man 2 reboot`     |
|  3   | 一些常用的函数与函数库 如scanf                     | `man 3 readdir`    |
|  4   | 设备文件的说明，通常是在`/dev`下的设备 /dev/random | `man 4 null`       |
|  5   | 配置文件或某些文件的格式                           | `man 5 interfaces` |
|  6   | 游戏                                               | `man 6 lol`        |
|  7   | 管理与协议等，例如linux文件系统，网络协议等        | `man 7 tcp`        |
|  8   | 系统管理员可用的命令                               | `man 8 reboot`     |
|  9   | 跟kernel有关的文件                                 |                    |

```
man -f + 命令 表示哪个手册里面有该命令
man -k + 命令 表示关于该命令的信息
```

## 任务管理

```
& 表后台执行
；表顺序执行
&& 前面的表达式如果错了后面就不执行了
|| 前面的表达式如果对了后面就不执行了
`` 在执行命令时，先执行``里面的，在把结果带会父命令
ctrl + z 挂起
```

fg 1 把某个状态拉回到前台来

jobs 挂起多个回来用jobs

## 管道，重定向

__管道把前一个命令的标准输出变成下一个命令的标准输入输入，传给下一个命令，将两个命令连接起来__

```
> 重新定向符，重写，箭头指向数据流向的方向
>> 追加， 将原来来的数据追加到新的文件中去
< 从文件到命令，将文件中的内容输出到命令作为标准输入
<< 
cat >> a.log   << EOF
命令到文件的重定向  用来定义一个结束的标志到EOF代表结束了
不一定用EOF 可以用任何字符表示结束但是，EOF更易懂
```

# ptython升级与tldr的安装

用which python查看位置

> <https://www.haizeix.com/course/359/task/19443/show>

# linux系统信息

# 系统信息

```
重要！！！！
uptime [phsv]    打印系统运行时长和平均负载 (在线时间 ，在线人数 ，负载)

w [husfv]        当前登录用户列表及正在执行的任务
	option  h:不打印头信息 
			s:使用短输出格式
			f:切换显示FROM 项默认
USER 登录用户名  TTY 登录后系统分配的终端号  FROM 远程主机名  LOGIN@ 登录时间 IDLE 空闲时间   PCPU 大年进城所占用时间 WHAT 当前进程正在执行的命令
JCPU 和该终端想狼的所有进程占用的时间，包含当前正在执行的后台作业
		
last [fnx] <username...> <tty...> 显示用户最近登录信息
	option 
	-f "file"：指定记录文件
	-n "num"：制定输出记录数
	-x ：显示系统关机，重新关机等信息

uname        打印当前系统信息
	uname[option]
	-a :全部信息
	-m :电脑类型
	-n ：网络上主机的名称
	-v ：os版本
	-p ：处理器类型
	-i ：硬件平台
	-o ：操作系统名称

date [dus] <参数> 显示或设置系统时间与日期 (用于随机数等)
	date +%s
	-d "string"显示字符串所指的日期
	-s "string" date -s "19:00:00" 更改时间为19:00:00
	-u :显示GMT
```

![date +](/home/unique/Desktop/海贼/picture/date +.png)

who         __显示当前登录系统的用户信息__

 + who [option]
 + -H：显示各栏的标题信息
 + -u：显示空置时间
 + -q：只显示登入系统的用户名称和总人数



whoami     __打印当前有效的用户名称__

​		查看当前有效用户到底是谁

 + who am i  显示到底是谁
 + logname 显示真实登录信息
 + id            某个用户的具体信息



cal                显示日历

 + -1， -3：显示最近一个月和三个月的日历
 + -j ：显示一年的第几天
 + -y ：显示当前年
 + 月 ：指定月份
 + 年 ：指定年份

# linux目录结构

dev 设备

/etc 全局

/home 目录是所有用户的家目录,相当于一栋楼家目录在unique

cd 回到家目录

media 识别光驱(不常用)

tmp 临时文件夹 所有文件都是777权限，重启后自动删除，

var 动态数据目录，例日志

# 文件与目录

## 目录

cd  ：切换当前工作目录

mkdir ：创建目录

pwd ：打印当前工作目录

rmdir ：删除目录

相对路径：相对与某个基准目录的路径。

绝对路径：[绝对路径](https://www.baidu.com/s?wd=%E7%BB%9D%E5%AF%B9%E8%B7%AF%E5%BE%84&tn=44039180_cpr&fenlei=mv6quAkxTZn0IZRqIHckPjm4nH00T1Y3rjN-mvNWuW6dmWDdnv7b0ZwV5Hcvrjm3rH6sPfKWUMw85HfYnjn4nH6sgvPsT6KdThsqpZwYTjCEQLGCpyw9Uz4Bmy-bIi4WUvYETgN-TLwGUv3EPjTLnjfkPjfL)就是你的主页上的文件或目录在硬盘上真正的路径，(URL和物理路径)例如： C:\xyz\test.txt 代表了test.txt文件的绝对路径。CD切换工作目录

### CD切换工作目录

```
cd /ect 直接切换到/ect目录，常用
cd ..   切换到上一层目录，常用
cd -	回到上一次工作目录，常用
cd      回到自己的家目录，常用
cd .	切换当前目录
cd ~	回到自己的家目录	

```

### pwd打印当前工作目录

pwd [-LP]

 + L 显示逻辑工作地址
 + P  显示物理工作地址

比如当前在/var/run 

 + pwd -L 就会显示/var/run
 + pwd -P 就会显示/run

### mkdir 创建目录

mkdir [pm]  <dir>

 + -p  自动创建父目录
 + -m 设置权限

### rmdir 删除目录（不常用,常用rm）

rmdir [p] <dir>

​	p 删除祖先

## 文件与目录的管理

### ls  __显示文件及目录信息__

​	option

+ ls ： -a 等于ls --all	
+ -l  ：用长的列表模式
+ -h ：人可读,显示字节兆
+ -d ：只显示这个目录，而不是目录下的全部文件,例假如说想看/ect目录，如果用ls -al /ect会显示出ect目录下的所有文件，所以用 ls -ald /ect只显示该目录

### rm  __删除__

 + option
	+ -f :force	
 + -i :互动模式
 + -r :递归删除

### cp [irapdslu] <sour>  <des>__拷贝__

 + option
 + -i ：若文件存在，询问用户
 + -r ：递归复制
 + -p ：联通文件属性一起拷贝
 + -d ：若源文件为连接文件的属性，则复制连接文件的属性
 + -s ：拷贝为软连接
 + -l  ：拷贝为硬连接
 + -u ：源文件比目的文件新才拷贝

### mv [ifu] <source...> <dest> __移动__

+ mv source 1 source 2 source 3 dir
+ 把source 1 source 2 source 3 移动到dir 
+ option
+ -i ：互动模式
+ -f ：force
+ -u ：原文件更新才会移动

### basename __取文件名__ 

+ basename a.out --> a.out
+ basename /a.out -->a.out
+ 根据目录分隔符，求出最后一个目录分隔符后面的字符串，不在乎文件是否存在

### dirname __取目录名__

+ dirname ~/a.out -->/home/pi
+ dirname /a.out -->/
+ dirname /a.out/cd/ -->/a,out
+ 用来提取路径的目录

## 文件内容的查阅

### cat  [-AbEnTv] <fie>__正向连续读__

 + -A：相当于-vET
 + -v：列出看不出的字符
 + -E：显示断行符为$
 + -T :  显示TAB为^I
 + -n：列出行号，两桶空行也编号
 + -b：列出行号

### tac __反向连续读__

### nl  __输出行号显示文件__

+ -b ：行号指定的方式
  + -b  a ：相当于cat -a
  + -b  t ：相当于cat -b
+ -n ：列出行号的表示方法
  + -n  ln ：行号在屏幕最左边
  + -n  rn ：行号在自己字段的最右边显示
  + -n  rz ：行号在自己字段的最右边显示，前面自动补全0
+ -w <num> ：行号所占位数

### more

###  __一页一页的显示文件内容__

+ /string 向下查找string关键字
+ :f 显示文件名称和当前显示的行数
+ q 离开

### less 

### __与more相似，但是可以上下翻看__

+ /string 向下查找    n ：继续向下查找
+ /?string  反向查找 N ：继续反向查找

### head [-n num] <file>__只看头几行__

+ -n  num ：显示前num行
+ -n  -num：除了后num行外，其他都显示

### tail [-n num] <file>__只看尾几行__

+ -n  num ：显示文件后num行
+ -n  +num：除了前num行， 其他都显示

### od [-t TYPE] <file> __以二进制方式查看文件内容__

+ -t ：
  + a：默认字符输出
  + c：ASCII字符输出
  + d[size] ：十进制输出，每个数占用size bytes
  + f[size] ：浮点数输出，每个数占用size bytes
  + o[size]：八进制数出， 每个数占用size bytes
  + x[size]：十六进制数出，每个数占用size bytes

查看文件的101到120行

mas ls | nl -b a -n rz -w 3 |head -120 | tail -n 20

## tr

## 修改文件时间与新建文件

### 文件的三个时间

mtime  内容数据改动时才更新这个时间  modify

ctime 文件的权限，属性改动时更新这个时间 change

atime 文件的内容被取用access时更改这个时间(读时) access

```
 ls -l --time=ctime /etc/hostname  ls显示时间默认为mtime
--后接选项的原型，全程
 -rw-rw-r-- 第一个rw代表用户的所属者权限 第二个rw代表群组所在的人的权限 最后一组代表其他人的权限尽是可读
 第一个符号代表类型
 -代表普通文件
```

### touch 

touch [-acdmt] <file>  __创建文件__

+ -a 仅修改访问时间
+ -c  仅修改文件呢的时间，若文件不存在，不新建
+ -d  修改文件日期
+ -m 仅修改mtime
+ -t 修改文件时间

## 文件隐藏属性

## chattr

chattr [+-=]_[ASacdistu]

+ A ：不修改atime （在浏览摸个文件后时间不会改动）
+ S ：同步写入 
+ a ：只能增加数据
+ c ： 自动压缩，解压
+ d ：不会被dump程序备份
+ i ：不能删除，修改，建立连接
+ s ：文件删除时，直接从磁盘删除
+ u ：文件删除时，数据内容存在磁盘中
+ 做完以上操作后如果不想要了可以用chattr - 加上不想要的操作

```
cd ~+目录名 可快速回到家目录或进入目录ss
-rwx       -rwx          -rwx
usr          group         other
set_uid   set_gid        sticky bit黏着位
重要
软连接 新文件是指向的
硬连接 两个名字一样的是一个文件
```

777 

__三个三个一组   2 软硬链接口   root     group    文件大小 mtime__

![权限](/home/unique/Desktop/海贼/picture/权限.png)

### lsattr

lsattr [-adR] <file_or_dir>

+ -a ：打印隐藏的的隐藏属性
+ -d ：如果是目录，仅打印目录的信息
+ -R ：递归

## 文件的特殊权限

+ set_uid 占位符是s 在权限位三个中的user的x位置上，如果x和s都有那就显示s，如果只有s没有x那就显示S 例如修改密码，因为passwd文件夹有s权限就可以以所有者身份修改密码
+ set_gid 占位符是s 放在权限位的group里面的x
+ sticky Bit (黏着位) 占位符t 放在权限位的other 里t代表有x权限T代表没有

![特殊权限](/home/unique/Desktop/海贼/picture/特殊权限.png)

## 命令以文件的查询

+ which 查找执行文件
+ whereis 查找特定文件
+ locate 搜索文件
+ find 多样化高级查找

#### which

+ which 寻找可执行文件
+ 查找PATH路径下所有的可执行文件

![whilch](/home/unique/Desktop/海贼/picture/whilch.png)

#### whereis

where [-bmsu] <ile_or_dir>

+ -b ：只查找二进制文件
+ -m ：只查找manual路径下的文件
+ -s ：只查找sourse源文件
+ -u ：查找其他文件

#### locate 模糊定位（索引技术）

locate [-ir] keyword

+ -i ：忽略大小写
+ -r ：后面可接正则表达式
+ 相关文件：/ect/updatedb.conf
+ /var/bin/mlocate
+ 缺点 不能找最近的 可以用updatedb 让其重新扫描一遍

#### find 高级查找

find [PATH].  [option].  [action]

+ 与时间相关的参数：atime, ctime, mtime
+ -mitime n ：n天前的 “一天之内”修改的文件
+ -mtime +n ：n天之前，不包括n,修改过的文件
+ -mtime -n ：n天之内，包含n，修改过的文件
+ -newer file ：比file还要新的文件



+ 与用户或用户组相关的参数
+ -uid n ：用户Uid为n
+ -gid n ：群组Gid为n
+ -user name ：用户名为name
+ -group name ：群组名为name
+ nouser ：文件所有者不存在
+ nogroup ：文件所在组不存在



+ 与文件权限及名称有关的参数
+ -name filename ：文件名为filename
+ -size [+-] SIZE  ：查找比size大或小的
+ -type TYPE  ：f b c d l s p
+ -perm mode ：mode 刚好等于的文件
+ -perm -mode ：全部包含mode 的文件

__find  命令 -exec ls -l {} \;__ 将命令找到的文件展示出来

# 数据提取操作

+ cut ：切分 
+ grep ：检索
+ sort ：排序
+ wc ：统计字符，字数，行数
+ uniq ：去重
+ tee ：双向重导向
+ split ：文件切分
+ xargs ：参数代换
+ tr ：替换，压缩和删除

## tr 

tr对标准输入的字符串替换压缩删除

tr [cdst] <字符集>　<字符集>

+ c　取代所有不属于第一字符集的字符
+ d　删除所有不属于第一字符集的字符
+ s　将连续重复的字符 以单独一个字符表示
+ t 　先删除第一字符集较第二字符集多出的字符

```
cat a.log | tr [0-9][a-z] 将文件的0到9替换为a到z
ls | tr[a-z] [A-Z]将ls下全部文件替换为为大写后显示出来
```

将当前目录下文件名全部改为大写

![途欢](/home/unique/Desktop/海贼/picture/途欢.png)

```
面试真题
对一个文件做词频统计 
cat a.log | tr -s -c [a-z] ' ' | tr ' ' '\n' | sort | uniq -c | sort -n -r
对文件将[a-z]之外的字符替换成空格再将连续的空格变成一个在排序，排序好去重并标出每个单词出现的频路，最后在排序让其成倒序，即让出现次数最高的单词在前面
输出频率最高的前20个
cat a.log | tr -s -c [a-z] ' ' | tr ' ' '\n' | sort | uniq -c | sort -n -r | head -n 20
```



## cut 切分

cut [-dfc]. [file]

+ -d c　：以c字符分割 c是一个值，只能是单个字符
+ -f num 　：显示num字段的内容 【n- ; n-m ; -m】
+ -b num　：字符
+ -c num　：字符

## grep 检索

grep [-acinv] <string> <file>

+  -a　：将二进制文件以普通形式搜寻数据
+  -c　：统计搜寻到的次数
+  -i　：忽略大小写
+  -n　：顺序输出行号
+  -v 　：反向输出（输出没找到的）
+  -w  ：找一个词word

## sort 排序

sort [-fnMnrtuk] <file_or_stdio>

+ -f ：忽略大小写
+ -b ：忽略最前面的空格
+ -M ：以月份名称排序
+ -n ：以纯数字方式排序
+ -r ：反向排序
+ -u ：uniq
+ -t ：分割符，默认TAB
+ -k ：以那个区间排序

## wc

wc 统计字符，字数，行数

wc [-lwm] <file_or_stdin>

+ -l :仅列出行号
+ -w :仅列出多少字
+ -m :仅列出多少字符

## uniq 去重

uniq [-ic] (配合sort 使用，因为uniq 只能将两个相邻的重复的去掉)

+ -i ：忽略大小写字符的不同
+ -c ：进行计数

## tee 双向重导向

tee [-a] file 

+ -a : append

![trr](/home/unique/Desktop/海贼/picture/trr.png)

执行ls 命令并将他同时给后面的文件

## split 文件切分

split [-bl] <file> PREFIX（前缀）代表切分后的文件名前缀是什么

split -l 10 a.log a.log 切分文件a.log 十个一个，每个文件名前缀为a.log

![split](/home/unique/Desktop/海贼/picture/split.png)

+ -b SIZE  ：切分为SIZE大小的文件
+ -l num ：以num行为大小切割

## xarg参数代换

__用来把管道前面的标准输出转化为后面一有个命令的一个参数而非标准输入__

xarg [-0pne] <conmmand> 

+ -0 ：将特殊字符还原为普通字符
+ -eEOF ：当xargs读到EOF时停止,EOF为你想要的最后一个字符的下一个，是自己输入的 
+ -p ：执行指令前询问
+ -n num ：每次执行command时需要的参数个数

 ```
kill -l 看信号
errnu error number
errnu 13 错误号13 
操作系统里不是用1234而是用宏定义 标记不同的错误
以_t结束的是自定义类型
 ```
# 实现ls

## 函数

ls    -a   /ect -a是选项   /etc是参数

```
opendir 打开目录 
头文件 #include <sys/types.h>
	  #include <dirent.h>
	 
函数原型 DIR *opendir(const char *name) 返回DIR 通过传入一个目录名打开目录
打开失败或者错了返回NULL
```

```
perror 加字符串返回上次错误信息
```

```
readdir opendir返回的给他 
读文件返回指针指向下一个目录里的一个成员
```

```
getpot 函数
函数原型 
int getopt (int argc, char * const argv[])如果已经没有选项了就返回-1
```

+ 用getopt来处理选项及参数，用opendir判断是目录还是文件，定义两个计数器分别记录当前选项是a还是l
+ 



# 用户管理

## 重要配置文件

### /ect/passwd 

__用户名 密码位 用户编号 归属组编号 姓名___

x 为密码占位符

![passwd](/home/unique/Desktop/海贼/picture/passwd.png)

### /ect/shadow 

__用户名 已加密密码 密码改动信息 密码策略__

通过该文件可以实现永和的个性化管理

![shodow](/home/unique/Desktop/海贼/picture/shodow.png)

### /ect/group 

群组名 密码位 群组编号 密码改动信息 密码策略

![GROUP](/home/unique/Desktop/海贼/picture/GROUP.png)

### /ect/gshadow 群组密码相关文件

![GSHADOW](/home/unique/Desktop/海贼/picture/GSHADOW.png)

### /ect/sudoers 用户名 权限定义 权限 

用户名 权限定义 权限

用来维护那些用户能使用sudo命令

## 用户管理相关的命令

| 命令    | 说明          | 命令    | 说明               |
| ------- | ------------- | ------- | ------------------ |
| su      | 切换用户      | sudo    | 临时切换为root用户 |
| passwd  | 设定用户密码  | gpasswd | 设定群组密码       |
| chsh    | 更改用户shell | usermod | 修改用户账号       |
| useradd | 新建用户      | userdel | 删除用户           |
| id      | 显示用户信息  | ...     | ...                |

## SU切换用户

 `su [-lmpfc] <username>`

```
- | -l : 重新登录
-m | -p : 不更改环境变量
-c command : 切换后执行命令，并退出
```

## sudo 

__临时切换到root__

`sudo [-siul] <command>`

+ -s : 切换为 root shell
+ -i : 切换到root shell ，并初始化
+ -u username | uid : 执行命令的身份
+ -l : 显示自己的权限

```
给一个用户sudo 权限
：
改sudo这个组的成员
修改sudoers文件
```

```
sudo -i 切换root权限
su -root 切换用户
```

### passwd 

`passwd [-dleSxnsf] <username> `

+ -d : 清楚密码
+ -l : 锁定账户
+ -e : 使密码过期
+ -S : 显示密码认证信息
+ -x days : 密码过期后最大使用天数
+ -n days : 密码冻结后最小使用天数
+ -s  : 更改登录shell
+ -f : 更改用户信息

### gpasswd（用得少）

`gpasswd [-adrAM] <群组名>`

+ -a username  : 将用户加入群组
+ -d username : 将用户从数组中删除
+ -r : 删除密码
+ -A username : 将用户设置为群组管理员
+ -M username1, username2... : 设置群成员

### chsh

`chsh -s Shell <username>`

用来修改用户shell 

+ ![chsh](/home/unique/Desktop/海贼/picture/chsh.png)

### useradd 

`useradd [-dmMsugGnefcD] <username>`

+ -d dir : 指定$HOME
+ -m :  自动建立$HOME（用的多）
+ -M : 不自动建立$HOME
+ -s shell : 设置用户登录shell（用的多）
+ -u uid : 设置用户编号
+ -g groupname : 设置用户归属群组（用的多）
+ -G groupname : 设置用户归属附加群组（用的多）
+ -n : 不建立以用户名称为群组名称的群组
+ -e days : 设置账号过期时间
+ -f days :缓冲时间，days天后关闭账号
+ -c string : 设置用户备注
+ -D [表达式]: 更改预设置

/etc/login.defs 新建用户规则

/etc/skel/ 新建用户默认文件

### userdel 用户名

`userdel -r <username>`

- -r : 删除用户相关文件和目录

### usermod 

`usermod [-cdefgGlLsuU] <username>`

- -c string : 修改备注信息
- -d dir : 修改$HOME
- -e days : 密码期限
- -f days : 密码过期后宽限的日期
- -g groupname : 修改用户所属群组
- -G groupname : 修改用户所附加群组
- -l username : 修改用户账号名称
- -L : 锁定用户密码，使密码无效
- -s shell : 修改用户登录后所使用的shell
- -u uid : 修改用户ID
- -U :  解除密码锁定

### ID

`id [-gGnru] <username>`

- -g : 下属所属组ID
- -G : 显示附加组ID
- -n :  显示用户，所属组 ， 或附加群组的名称
- -u : 显示用户ID
- -r : 显示实际ID

# 进程管理

| 命令   | 说明                      | 命令  | 说明                                  |
| ------ | ------------------------- | ----- | ------------------------------------- |
| free   | 打印系统情况和内存情况    | top   | 显示当前系统进程情况，内存，CPU等信息 |
| dstat  | 实时监控磁盘，CPU，网络等 | ps    | 报告当前进程状态                      |
| pstree | 以树状下那是进程派生关系  | pgrep | 查找进程ID                            |
| kill   | 删除执行中的程序和工作    | pkill | 批量按照进程名杀死进程                |

## free

`free [-bkmgotsh]`

- -b | k | m | g : 以字节，KB，M， G显示
- -o : 忽略缓冲区调节剂
- -t seconds : 每隔seconds执行一次
- -h : 以可读形式显示

## top

`top [-bcdsSupnq]`

- -b : 以批处理模式操作
- -c : 下那是完整的命令
- -d seconds : 屏幕刷新间隔时间
- -s : 以安全模式运行
- -S :  累积模式
- -u uname : 指定username
- -p pid : 指定PID
- -n nums  : 循环显示次数
- -q : root 时，给尽可能高的优先级

## dstat

- dstat
- dstat2
- dstat 2 10
- dstat -list
- dstat 2 10 -output /tmp/data.csv

## ps

- ps -aux  显示进程信息，包括无终端的（x）和针对用户（u）的进程：如USER, PID, %CPU, %MEM等
- ps -ef

## pstree

`pstree [-acGhHlnpuU]`

- -a : 显示每个程序的完整指令
- -n : 使用PID排序
- -p : 显示PID
- -u : 显示用户名
- -l : 使用长列格式显示树状

## pgrep

`pgrep --onlpgtu <进程名>`

- -o : 起始进程号
- -n : 结束进程号
- -l : 显示进程名称
- -p pid : 指定父进程
- -g gid : 指定进程组
- -t try : 指定开启的进程终端
- -u uid : 指定 uid

## kill

`kill [-alpsu] <PID>`

- -a :处理当前进程时，不限制命令名和进程号的对应关系
- -l 信号ID : 不加信号ID ，则列出去全部信号
- -p pid : 给pid的进程值打印相关进程号，而不发送任何信号
- -s 信号ID  | 信号name:  指定要发出的信号
- -u : 指定用户
- kill -9 pid
- kill pid

## pkill 

`pkill [-onpgt] <进程名称>`

- -o : 起始Pid
- -n : 结束pid
- -p pid : 指定父进程号发送信号
- -g : 指定进程组
- -t try : 制定终端

PS 报告当前进程

ps -aux

ps -ef



ps -ef | grep helper 查询进程是否进行

pkill 杀死进程

kill 5572 

kill -9 5572 杀死顽固性进程

## pstree 以树状

以树状显示进程派生关系

## pgrep查找进程ID

## kill

删除执行中的程序和工作

## pkill 

批量按照进程名杀死进程

## 任务管理

### cron （用的多）

crontab -e 编辑

crontab -l 显示列表

crond为守护进程

## at

__在指定时间执行一个指定任务__

`at [ldc] <args>`

- -l : 列出前用户的at 任务列表也可以使用atq
- -d  任务编号 : 删除一个at任务等同于atrm
- -c : 显示该任务的实际内存

![at](/home/unique/Desktop/海贼/picture/at.png)

atd为at提供守护进程，需要保证atd启动

Ctrl+d EOF 结束

free(一次) top(操作麻烦) dstat htop nmon(多用于服务器) 查看系统当前的
