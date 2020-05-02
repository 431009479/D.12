## Linux 系统的函数

### exec中的函数

##### strchr 函数

>  char *strchr(const char *s, int c);

>  它表示在字符串 s 中查找字符 c，返回字符 c 第一次在字符串 s 中出现的位置，如果未找到字符 c，则返回 NULL。也就是说，strchr 函数在字符串 s 中从前到后（或者称为从左到右）查找字符 c，找到字符 c 第一次出现的位置就返回，返回值指向这个位置，如果找不到字符 c 就返回 NULL。

##### strrchr 函数

>  char *strrchr(const char *s, int c);

>  ##### 与 strchr 函数一样，它同样表示在字符串 s 中查找字符 c，返回字符 c 第一次在字符串 s 中出现的位置，如果未找到字符 c，则返回 NULL。但两者唯一不同的是，strrchr 函数在字符串 s 中是从后到前（或者称为从右向左）查找字符 c，找到字符 c 第一次出现的位置就返回，返回值指向这个位置。下面的示例代码演示了两者之间的区别：

1. ```c++
    int main() {
   	   char str[] = "I welcome any ideas from readers， of course.";
   	    char *lc = strchr(str, 'o');
   	    printf("strchr： %s\n", lc);
   	    char *rc = strrchr(str, 'o');
   	    printf("strrchr： %s\n", rc);
   	    return 0;
   }
   示例代码运行结果为：
   strchr： ome any ideas from readers， of course.
   strrchr： ourse.
   ```

   ##### wait函数   https://blog.csdn.net/paraionnnnn/article/details/77479346

>  #####include <sys/types.h>  提供类型pid_t的定义 

>  \#include <sys/wait.h>

>  int wait(int * status)

>  父进程一旦调用wait函数就立即阻塞自己，由wait分析是否当前进程的某个子进程已经退出，如果让它找到了这样一个已经变成zombie的子进程，wait就会收集这个子进程的信息，并把它彻底销毁后返回，如果没有找到，就一直阻塞，直至找到一个结束的子进程或接收到了一个指定的信号为止。

```c++
Wait()与fork()配套出现，如果在fork()之前调用wait(), wait返回-1，正常情况下，应返回子进程pid。 
参数status用来保存被收集进程退出时的状态，它是一个指向int类型的指针，如果我们对这个子进程如何死掉的不在意，只想这把这个被僵尸进程消灭掉，就把这个参数置为NULL， 
Pid=wait（NULL）； 
如果成功返回子进程pid，如果没有子进程，失败，则返回-1，同时，error被置为Echild。
如果status的值不是NULL，wait把子进程的退出状态取出并存入其中，这是一个整数值（int） 
它指出了子进程是正常退出还是非正常结束，以及正常结束的返回值，或被那个信号结束等信息。
```

```c++
下面说说子进程和父进程 
1) 父进程先于子进程结束 
子进程成了孤儿进程，当父进程退出时，系统会让pid为1的进程接管子进程。 
Ps：pid为1的进程是init或者systemd 
2) 子进程先于父进程结束 
子进程成了僵尸（zombie）进程，并且子进程会一直保持这样的状态直至重启，此时内核只会保留进程的一些必要信息以备父进程所需，此时子进程始终占有资源，同时也减少了系统可以创建的最大进程数。 
3) 子进程先于父进程结束，但是父进程调用了wait函数 
此时，父进程会等待子进程结束
```

##### execlp函数   https://www.cnblogs.com/mickole/p/3187409.html

https://blog.csdn.net/y396397735/article/details/53762196?depth_1-utm_source=distribute.pc_relevant.none-task&utm_source=distribute.pc_relevant.none-task

```c++
execlp()函数：从PATH环境变量中查找文件并执行
头文件： #include<unistd.h>
定义函数：
intexeclp(const char * file, const char * arg, ...);
```

>  函数说明：execlp()会从PATH 环境变量所指的目录中查找符合参数file 的文件名, 找到后便执行该文件, 然后将第二个以后的参数当做该文件的argv[0],argv[1], ..., 最后一个参数必须用空指针(NULL)作结束.

>  返回值：如果执行成功则函数不会返回,执行失败则直接返回-1, 失败原因存于errno 中.

```
/* 执行ls -al /etc/passwd execlp()会依PATH 变量中的/bin 找到/bin/ls */ 
#include <unistd.h>
main(){
	execlp("ls", "ls","-al", "/etc/passwd", (char *)0);
}
执行：  -rw-r--r-- 1 root root 705 Sep 3 13 :52/etc/passwd
```

实现exec函数代码

```c++
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
int main(int argc, char ** argv){
    pid_t pid;
    char fname[512] = {0};
    char *sub; 
    char name[512] = {0};
    char typ[256] = {0};
    if(argc < 2){
       // fprintf(s)
        return 1;
    }
    strcpy(fname, argv[1]);
    sub = strrchr(fname, '.');
    strncpy(name, fname, sub - fname);
    strcpy(typ, sub);
    char cmd[512] = {0};
    if(!strcmp(typ, ".c")){
        strcpy(cmd, "gcc");
    }else if(!strcmp(typ, ".cpp")){
        strcpy(cmd, "g++");
    }else{
        return 2;
    }
    if((pid = fork()) < 0){
        perror("fork");
        return 3;
    }
    if(pid == 0){
        execlp("vim", "vim", fname, NULL);
    }
    wait(NULL);
    if((pid = fork()) < 0){
        perror("fork");
        return 3;
    }
    if(pid == 0){
      //  execlp(cmd, cmd, fname,"-o", name, NULL);
        execlp(cmd, cmd, fname, NULL);
    }
    int status;
    wait(&status);
    if(status == 0){
        printf("OK\n");
       // char Name[25] = {0};
       // sprintf(Name,"./%s", name);
        //   execlp(Name, name, NULL);
        execlp("./a.out", "./a.out", NULL);
    }else return 4;
    return 0;
}

```

