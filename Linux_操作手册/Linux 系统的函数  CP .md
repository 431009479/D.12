## Linux系统函数

### CP

##### open 函数   https://blog.csdn.net/weibo1230123/article/details/79036611

>  头文件：#include <sys/types.h>    #include <sys/stat.h>    #include <fcntl.h>

>  定义函数：  
>
>     int open(const char * pathname, int flags);
>
>  ​    int open(const char * pathname, int flags, mode_t mode);

```c++
函数说明：参数 pathname 指向欲打开的文件路径字符串. 下列是参数flags 所能使用的旗标:
O_RDONLY 以只读方式打开文件
O_WRONLY 以只写方式打开文件
O_RDWR 以可读写方式打开文件.
  返回值：若所有欲核查的权限都通过了检查则返回值设备描述符，表示成功，只要有一个权限被禁止则返回-1。
```

#####   create函数  https://blog.csdn.net/Wmll1234567/article/details/82992739

>   include <sys/stat.h>   #include <fcntl.h>include <sys/types.h>
>
>   creat的原型为:
>
>   int creat (const char *pathname,mode_t mode);
>
>   参数 pathname 指向欲建立的文件路径字符串
>
>   mode:创建模式，指定[用户](http://www.seotest.cn/wenzhang/yonghu/)操作权限（针对三种用户设置：所处用户，所处用户组，其他用户)

>  create函数也能打开一个文件，如果文件不存在，则创建它。和open一样，creat也在调用成功后返回一个文件描述符，如果失败，则设置errno变量并返回-1.
>
>  creat()会返回新的**文件描述词**, 若有错误发生则会返回-1, 并把错误[代码](http://www.seotest.cn/wenzhang/daima/)设给errno.

##### read 函数   https://blog.csdn.net/qq_33883085/article/details/88667003

```c++
#include<unistd.h>
ssize_t read(int fd,  void * buf ,size_t count);
```

>  ssize_t为有符号整型，size_t为无符号整型。fd为相应的文件描述符；buf为用户给定的数据缓冲区，该缓冲不是固定大小的，由count值决定其大小（用户给定，字节数）。如 read( fd , “hello” , 5 ); 此时的void *buf为char *类型。即count为请求读取的字节数（即buf的大小）。该函数的返回值为-1时，表示读取数据失败；返回值>0时，表示读出的字节数；返回值等于0时，表示已经读完了，因此没有数据可读了。

##### write函数  

```c++
头文件：#include<unistd.h>
ssize_t write(int fd,const void*buf,size_t count);
参数说明：
  fd:是文件描述符（write所对应的是写，即就是1）
  buf:通常是一个字符串，需要写入的字符串
  count：是每次写入的字节数
  成功：返回写入的字节数
 	失败：返回-1并设置errno
  ps： 写常规文件时，write的返回值通常等于请求写的字节
       数count， 而向终端设备或者网络写时则不一定
```

>  read和write函数为Linux系统函数，其缓冲区由用户来维护，即用户指定其大小，

##### cp具体代码

```c++

#include<stdio.h>
#include <unistd.h>
#include<inttypes.h>
#include<math.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <time.h>
#include<string.h>

#define B 512

int main(int argc, char **argv){
    int fd_in, fd_out, nrend;

    char buf[B + 5] = {0};
    if(argc != 3){
        printf("Usage: %s sourcefile destfile \n",argv[0]);
        exit(1);
    }
    if((fd_in = open(argv[1],O_RDONLY)) == -1){
        perror(argv[1]);
        exit(1);
    }
    if((fd_out = creat(argv[2], 0644)) == -1){
        perror(argv[2]);
        exit(1);
    }
    while((nrend = read(fd_in, buf, B)) > 0){
        int nwrite;
        if((nwrite = write(fd_out, buf, strlen(buf))) != nrend){
            perror("write");
        }
        memset(buf, 0, B);
    }
    close(fd_in);
    close(fd_out);
    return 0;
}
```

