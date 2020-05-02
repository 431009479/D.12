## Linux系统函数

### 服务端  

##### https://blog.csdn.net/wy1550365215/article/details/76376875

![图片](https://static.dingtalk.com/media/lALPDhmOq7S_RrXNAx7NA84_974_798.png_620x10000q90g.jpg?auth_bizType=IM&auth_bizEntity=%7B%22cid%22%3A%2230800141428%22%2C%22msgId%22%3A%223274001314593%22%7D&bizType=im&open_id=745883422)

#### socket函数：

>  ```c++
>  include<sys/socket.h>
>  int**socket**(int domain,int type, int protocol)
>  返回值：非负文件描述符 – 成功，-1 - 出错
>  其中：
>  domain 指明了协议族/域，通常AF_INET、AF_INET6、AF_LOCAL等；
>  type 是套接口类型，主要SOCK_STREAM、SOCK_DGRAM、SOCK_RAW；
>  protocol一般取为0。成功时，返回一个小的非负整数值，与文件描述符类似。
>  ```

#### sockaddr结构体和sockaddr_in结构体  

>  https://blog.csdn.net/will130/article/details/53326740/

sockaddr在头文件`#include <sys/socket.h>`中定义，sockaddr的缺陷是：sa_data把目标地址和端口信息混在一起了，如下：

```c++
struct sockaddr {  
     sa_family_t sin_family;//地址族
　　  char sa_data[14]; //14字节，包含套接字中的目标地址和端口信息               
　　 }; 
```

sockaddr_in在头文件`#include<netinet/in.h>或#include <arpa/inet.h>`中定义，该结构体解决了sockaddr的缺陷，把port和addr 分开储存在两个变量中，如下： 
![这里写图片描述](https://img-blog.csdn.net/20161125160930613)

```
 sin_port和sin_addr都必须是网络字节序（NBO），一般可视化的数字都是主机字节序（HBO）。
二者长度一样，都是16个字节，即占用的内存大小是一致的，因此可以互相转化。二者是并列结构，指向sockaddr_in结构的指针也可以指向sockaddr。
sockaddr常用于bind、connect、recvfrom、sendto等函数的参数，指明地址信息，是一种通用的套接字地址。 
sockaddr_in 是internet环境下套接字的地址形式。所以在网络编程中我们会对sockaddr_in结构体进行操作，使用sockaddr_in来建立所需的信息，最后使用类型转化就可以了。一般先把sockaddr_in变量赋值后，强制类型转换后传入用sockaddr做参数的函数：sockaddr_in用于socket定义和赋值；sockaddr用于函数参数。
```

#### bind函数  

https://blog.csdn.net/Z_Stand/article/details/102533220

```c++
#include <sys/types.h>

#include <sys/socket.h>

int  bind(int sockfd，const struct sockaddr *addr，socklen_t addrlen);
```

```c++
bind API能够将套接字文件描述符、端口号和ip绑定到一起
注意：
绑定的一定是自己的 ip和和端口，不是对方的；比如对于TCP服务器来说绑定的就是服务器自己的ip和端口
sockfd 表示socket函数创建的通信文件描述符
addrlen 表示所指定的结构体变量的大小
addr 表示struct sockaddr的地址，用于设定要绑定的ip和端口
```

#### listen函数

https://blog.csdn.net/z_stand/article/details/102535421

```c++
# include <sys/socket.h>
int listen(int sockfd, int backlog);
函数功能：将套接字文件描述符从主动转为被动文件描述符，然后用于被动监听客户端的连接
函数返回值：成功返回0，失败返回-1， errno被设置
参数：
a. sockfd 表示socket创建的套接字文件描述符
b. backlog 指定队列的容量
这个队列用于记录正在连接但是还没有连接完成的客户端，一般设置队列的容量为2，3即可。队列的最大容量需要小于30
服务器监听客户端链接时，使用的是socket返回的“套接字文件描述符”来实现的，但是这个文件描述符默认是主动文件描述符（主动向对方发送数据），所以需要使用listen函数将其转换为被动描述符（只能被动得等待别人主动发送数据，再回应），否则无法用于被动监听客户端。
```

#### accept函数

https://www.cnblogs.com/java20130726/archive/2011/12/20/3218630.html

```c++
#include <sys/types.h>
#include <sys/socket.h>
int accept(int sockfd,struct sockaddr addr,socklen_t addrlen);
accept()系统调用主要用在基于连接的套接字类型，比如SOCK_STREAM和SOCK_SEQPACKET。它提取出所监听套接字的等待连接队列中第一个连接请求，创建一个新的套接字，并返回指向该套接字的文件描述符。新建立的套接字不在监听状态，原来所监听的套接字也不受该系统调用的影响。
备注：新建立的套接字准备发送send()和接收数据recv()。

参数：
sockfd,    利用系统调用socket()建立的套接字描述符，通过bind()绑定到一个本地地址(一般为服务器的套接字)，并且通过listen()一直在监听连接；
addr,    指向struct sockaddr的指针，该结构用通讯层服务器对等套接字的地址(一般为客户端地址)填写，返回地址addr的确切格式由套接字的地址类别(比如TCP或UDP)决定；若addr为NULL，没有有效地址填写，这种情况下，addrlen也不使用，应该置为NULL；
addrlen,    一个值结果参数，调用函数必须初始化为包含addr所指向结构大小的数值，函数返回时包含对等地址(一般为服务器地址)的实际数值；
备注：一般来说，实现时accept()为阻塞函数，当监听socket调用accept()时，它先到自己的receive_buf中查看是否有连接数据包；
若有，把数据拷贝出来，删掉接收到的数据包，创建新的socket与客户发来的地址建立连接；
若没有，就阻塞等待；
返回值
成功时，返回非负整数，该整数是接收到套接字的描述符；出错时，返回－1，相应地设定全局变量errno。
```

##### recv函数

```c++
头文件 #include <sys/socket.h>
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
函数功能：接收对方发送当数据

返回值：成功返回发送的字节数；失败返回-1，同时errno被设置
函数参数:
a. sockfd 通信文件描述符
b. buf 应用缓存，用于存放要发送到数据
可以是任何类型：结构体，int , char,float，字符串
c. len buf的大小
d. flags 一般设置为0，此时send为阻塞式发送
```

##### server全部代码

```c++
# include<stdio.h>
# include<stdlib.h>
# include<unistd.h>
# include<sys/types.h>
# include<sys/socket.h>
# include<sys/wait.h>
# include<arpa/inet.h>

int main(int argc, char **argv){

	if(argc != 2){
    	fprintf(stderr, "Usage: %s port\n", argv[0]);
    	exit(1);
	}
	int port, server_listen;
	int *status;
	port = atoi(argv[1]);

	if((server_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    	perror("socket");
    	exit(1);
	}
	printf("Socket create.\n");
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = INADDR_ANY;

	if(bind(server_listen, (struct sockaddr*)&server, sizeof(server)) <0){
    	perror("bind");
    	exit(1);
	}
	printf("sockfd bind.\n");
	if(listen(server_listen, 20) < 0){
    	perror("listen");
    	exit(1);
	}
	while(1){
    	int sockfd;
		printf("sockfd before accept.\n");
    	if((sockfd = accept(server_listen, NULL, NULL)) <0){
        	perror("accept");
        	close(sockfd);
        	continue;
    	}
    	pid_t pid;
    	if((pid = fork()) < 0){
        	perror("fork");
       	 continue;
    	}else if(pid == 0){
        	close(server_listen);
        	char nume[20] = {0};
        	if(recv(sockfd, nume, sizeof(nume), 0) <=0){
            	perror("recv");
            	close(sockfd);
       		 }
        	printf("nume: %s\n", nume);
        	exit(0);
    	}else {
                wait(status);
        }
    }
	return 0;
}
```

