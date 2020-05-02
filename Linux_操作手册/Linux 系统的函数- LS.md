## Linux 系统的函数

### ls中的函数

##### getopt函数 ： https://www.cnblogs.com/water-moon/p/5983139.html

>  头文件      include<unistd.h>
>
>  定义函数   int getopt(int argc,  char * const argv[ ],  const char * optstring);
>
>  选项字符串："ab:cd::e"，由getopt(argc, argv, "ab:cde::")

>        getopt()用来分析命令行参数。参数argc和argv是由main()传递的参数个数和内容。
>
>        参数optstring 则代表欲处理的选项字符串。此函数会返回在argv 中下一个的选项字母，此字母会对应参数optstring 中的字母。

```c++
如果执行命令：./main zheng -b "qing er" han -c123 qing	
命名包含了选项-b,其参数"qing er"；-c,其参数123，程序参数(操作数)zheng,han,qing 和程序名./main
则：
./main	zheng	 -b 	    "qing er"	        han 	       -c123	       qing
argv[0]	argv[1]	argv[2]	    argv[3]		      argv[4]	      argv[5]	    argv[6]
argc = 7
```

![图片](https://static.dingtalk.com/media/lALPDgtYsHwWv4zNAbbNA98_991_438.png_620x10000q90g.jpg?auth_bizType=IM&auth_bizEntity=%7B%22cid%22%3A%22745883422%3A745883422%22%2C%22msgId%22%3A%223183648376387%22%7D&bizType=im&open_id=745883422)

##### opendir函数 ：https://www.iteye.com/blog/lobert-1706165

>  头文件：#include <sys/types.h>  #include <dirent.h>
>
>  函数：DIR *opendir（const char *name）;*
>
>  *含义： opendir()用来打开参数name 指定的目录, 并返回DIR*形态的目录流, 和open()类似, 接下来对目录的读取和搜索都要使用此返回值.  在失败的时候返回一个空的指针。

```c++
先说说DIR这一结构体，以下为DIR结构体的定义：
struct __dirstream {   
    void *__fd;    
    char *__data;    
    int __entry_data;    
    char *__ptr;    
    int __entry_ptr;    
    size_t __allocation;    
    size_t __size;     
    __libc_lock_define (, __lock)    
   };   
typedef struct __dirstream DIR;  
```

>  DIR结构体类似于FILE，是一个内部结构，以下几个函数用这个内部结构保存当前正在被读取的目录的有关信息函数 .而该指针由以下几个函数使用:

```c++
struct dirent *readdir(DIR *dp);   
void rewinddir(DIR *dp);   
int closedir(DIR *dp);   
long telldir(DIR *dp);   
void seekdir(DIR *dp,long loc);  
```

##### readdir函数   https://www.iteye.com/blog/lobert-1706165

>  头文件：#include<sys/types.h> #include <dirent.h>
>
>  函数：struct dirent *readdir(DIR *dir);
>
>  含义:readdir()返回结构体指针目录流的下个目录进入点。

```c++
struct dirent{
    ino_t d_ino; //d_ino 此目录进入点的inode
    ff_t d_off; //d_off 目录文件开头至此目录进入点的位移
    signed short int d_reclen; //d_reclen _name 的长度, 不包含NULL 字符
    unsigned char d_type; //d_type d_name 所指的文件类型 d_name 文件名
    har d_name[256];
};
```

![图片](https://static.dingtalk.com/media/lALPDgtYsHzTqlVpzQKi_674_105.png_620x10000q90g.jpg?auth_bizType=IM&auth_bizEntity=%7B%22cid%22%3A%22745883422%3A745883422%22%2C%22msgId%22%3A%223178609820373%22%7D&bizType=im&open_id=745883422)

##### **closedir函数（关闭目录）**

|      |                                         |
| ---- | --------------------------------------- |
| 相关函数 | opendir                                 |
| 表头文件 | #include<sys/types.h>#include<dirent.h> |
| 定义函数 | int closedir(DIR *dir);                 |
| 函数说明 | closedir()关闭参数dir所指的目录流。                |
| 返回值  | 关闭成功则返回0，失败返回-1，错误原因存于errno 中。          |
| 错误代码 | EBADF 参数dir为无效的目录流                      |
| 范例   | 参考readir()。                             |

##### 获得终端窗口大小的方法   https://blog.csdn.net/weixin_42205987/article/details/82080615

```c++
include<stdio.h>
# include<sys/types.h>
# include<sys/ioctl.h>
# include<unistd.h>
include<termios.h>
int main(){
//定义winsize 结构体变量
struct winsize size;
//TIOCSWINSZ命令可以将此结构的新值存放到内核中
ioctl(STDIN_FILENO,TIOCGWINSZ,&size);
printf("%d\n",size.ws_col);
printf("%d\n",size.ws_row);
return 0;
}
```

##### getpwuid()函数   

>  通过用户uid查找用户的相关信息,并以passwd的结构体返回其数据. 头文件:#include <sys/types.h>    #include <pwd.h> 

>  函数原型:struct  passwd *getpwuid(uid_t  uid); 参数 文件所有者的uid; 返回值:成功passwd 结构体,uid所对应的用户信息,错误返回空指针,

```c++
和系统数据相关的一个结构passwd定义如下 
/* The passwd structure.      */ 
struct passwd { 
      char *pw_name;       /* 用户名*/ 
      char *pw_passwd;     /* 密码.*/ 
      __uid_t pw_uid;      /* 用户ID.*/ 
     __gid_t pw_gid;      /*组ID.*/ 
     char *pw_gecos;      /*真实名*/ 
      char *pw_dir;        /* 主目录.*/ 
      char *pw_shell;      /*使用的shell*/ 
}; 
```



##### getgrgid()函数    https://www.zhangshengrong.com/p/On1vo4Wpay/

>  通过gid,找到该组的相关信息,并以group结构体返回其信息, 头文件:#include <grp.h>,#include <sys/types.h> 参数     文件所属组的组id; 返回值:成功返回group结构体,错误返回NULL; 

```c++
struct group {
  char   *gr_name;        /* group name */
  char   *gr_passwd;      /* group password */
  gid_t   gr_gid;         /* group ID */
  char  **gr_mem;         /* NULL-terminated array of pointer                         };
```

##### stat函数和stat命令   https://www.cnblogs.com/xiaoshiwang/archive/2019/04/24/10764243.html

>  stat函数：取得指定文件的文件属性，文件属性存储在结构体stat里。

```c++
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
int stat(const char *pathname, struct stat *statbuf);
int fstat(int fd, struct stat *statbuf);
int lstat(const char *pathname, struct stat *statbuf);
```

```c++
struct stat 结构体详解：  https://blog.csdn.net/qq_40839779/article/details/82789217
struct stat{
    dev_t     st_dev;     /* ID of device containing file */文件使用的设备号
    ino_t     st_ino;     /* inode number */    索引节点号 
    mode_t    st_mode;    /* protection */  文件对应的模式，文件，目录等
    nlink_t   st_nlink;   /* number of hard links */    文件的硬连接数  
    uid_t     st_uid;     /* user ID of owner */    所有者用户识别号
    gid_t     st_gid;     /* group ID of owner */   组识别号  
    dev_t     st_rdev;    /* device ID (if special file) */ 设备文件的设备号
    off_t     st_size;    /* total size, in bytes */ 以字节为单位的文件容量   
    blksize_t st_blksize; /* blocksize for file system I/O */ 包含该文件的磁盘块的大小   
    blkcnt_t  st_blocks;  /* number of 512B blocks allocated */ 该文件所占的磁盘块  
    time_t    st_atime;   /* time of last access */ 最后一次访问该文件的时间   
    time_t    st_mtime;   /* time of last modification */ /最后一次修改该文件的时间   
    time_t    st_ctime;   /* time of last status change */ 最后一次改变该文件状态的时间 };
```

