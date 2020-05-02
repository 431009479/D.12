## Linux 系统的函数

### more中的函数    

##### https://blog.csdn.net/u014507230/article/details/45312567

##### fopen函数的用法   

>  在C语言中，操作文件之前必须先打开文件；所谓“打开文件”，就是让程序和文件建立连接的过程。
>
>  打开文件之后，程序可以得到文件的相关信息，例如大小、类型、权限、创建者、更新时间等。在后续读写文件的过程中，程序还可以记录当前读写到了哪个位置，下次可以在此基础上继续操作。

```c++
使用 <stdio.h> 头文件中的 fopen() 函数即可打开文件，它的用法为：
FILE *fopen(char *filename, char *mode);
filename  为文件名（包括文件路径） mode   为打开方式，它们都是字符串。
```

```c++
fopen() 函数的返回值   fopen() 会获取文件信息，包括文件名、文件状态、当前读写位置等，并将这些信息保存到一个 FILE 类型的结构体变量中，然后将该变量的地址返回。
FILE 是 <stdio.h> 头文件中的一个结构体，它专门用来保存文件信息。我们不用关心 FILE 的具体结构，只需要知道它的用法就行。
如果希望接收 fopen() 的返回值，就需要定义一个 FILE 类型的指针。例如：
FILE *fp = fopen("demo.txt", "r");
表示以“只读”方式打开当前目录下的 demo.txt 文件，并使 fp 指向该文件，这样就可以通过 fp 来操作 demo.txt 了。fp 通常被称为文件指针。
```

##### 关闭文件

文件一旦使用完毕，应该用 fclose() 函数把文件关闭，以释放相关资源，避免数据丢失。fclose() 的用法为：

```c++
int fclose(FILE *fp);
fp 为文件指针。例如：fclose(fp);
```

##### fgets() 函数：http://c.biancheng.net/view/235.html

>  \# include <stdio.h>
>
>  char *fgets(char *s, int size, FILE *stream);
>
>  s 代表要保存到的内存空间的首地址，可以是字符数组名，也可以是指向字符数组的字符指针变量名。size 代表的是读取字符串的长度。stream 表示从何种流中读取，可以是标准输入流 stdin，也可以是文件流，即从某个文件中读取，

>  fgets() 虽然比 gets() 安全，但安全是要付出代价的，代价就是它的使用比 gets() 要麻烦一点，有三个参数。它的功能是从 stream 流中读取 size 个字符存储到字符指针变量 s 所指向的内存空间。它的返回值是一个指针，指向字符串中第一个字符的地址。

##### fputs() 函数  http://c.biancheng.net/view/238.html

```c++
该函数用来显示字符串的，它的原型是：
# include <stdio.h>
int fputs(const char *s, FILE *stream);
```

>  s 代表要输出的字符串的首地址，可以是字符数组名或字符指针变量名。

>  stream 表示向何种流中输出，可以是标准输出流 stdout，也可以是文件流。标准输出流即屏幕输出，printf 其实也是向标准输出流中输出的。
>
>  fputs() 和 puts() 有两个小区别：
>
>  puts() 只能向标准输出流输出，而 fputs() 可以向任何流输出。
>
>  使用 puts() 时，系统会在自动在其后添加换行符；而使用 fputs() 时，系统不会自动添加换行符。

##### 实现more具体代码

```c++
#include<stdio.h>
#include<stdlib.h>
#include<sys/ioctl.h>
#include<termios.h>
#include<signal.h>
#include<unistd.h>
#define L 512


void do_more(FILE *fp);

int main(int argc, char **argv){
    FILE *fp;
    printf("%d\n", argc);
    if(argc == 1) {
        do_more(stdin);
    }else{
        while(--argc){
            if((fp = fopen(*++argv, "r")) != NULL){
                do_more(fp);
            }
        }
    }
    return 0;
}

void do_more(FILE *fp){
    struct winsize info;
    ioctl(STDIN_FILENO,TIOCGWINSZ,&info);
    int P = info.ws_row;
    char line[L] = {0};
    FILE *cmd = fopen("/dev/tty", "r");
    int num_line = 0, reply;
    int get_cmd(FILE *, int x);
    while(fgets(line, L, fp)){
        if(num_line == P){
            reply = get_cmd(cmd, P);
            if(reply == 0)break;
          //  if(reply == 1)
           // do_more(fp);
            num_line -= reply;
        }
    
        if(fputs(line, stdout) == EOF){
            perror("fputc");
            exit(1);
        }
        num_line++;
    }

}
int get_cmd(FILE *fp, int P){
    printf("more:");
    int c;
    while((c = fgetc(fp)) != EOF){
        if(c == 'q') return 0;
        else if(c == ' ') return P;
        else if(c == '\n') return 1;
    }
    return -1;
}
```

