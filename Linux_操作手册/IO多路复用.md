## IO多路复用

#### select    https://www.cnblogs.com/alantu2018/p/8612722.html

select系统调用的的用途是：在一段指定的时间内，监听用户感兴趣的文件描述符上可读、可写和异常等事件。	

```c++
#include <sys/select.h>   
int select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset,struct timeval *timeout);
```

![图片](https://static.dingtalk.com/media/lALPDgtYsrrinYPNAc3NAjA_560_461.png_620x10000q90g.jpg?auth_bizType=IM&auth_bizEntity=%7B%22cid%22%3A%22745883422%3A745883422%22%2C%22msgId%22%3A%223500144571759%22%7D&bizType=im&open_id=745883422)

```shell
fd_set集合可以通过一些宏由人为来操作，比如： 
`FD_ZERO(fd_set *);`清空集合 
`FD_SET(int, fd_set *);`将一个给定的文件描述符加入集合之中 
`FD_CLR(int, fd_set*);` 将一个给定的文件描述符从集合中删除 
检查集合中指定的文件描述符是否可以读写`FD_ISSET(int ,fd_set* )`。
```

![图片](https://static.dingtalk.com/media/lALPDh0cK_PaWeLNASLM_g_254_290.png_620x10000q90g.jpg?auth_bizType=IM&auth_bizEntity=%7B%22cid%22%3A%22745883422%3A745883422%22%2C%22msgId%22%3A%223509249418701%22%7D&bizType=im&open_id=745883422)

#### poll

```c++
int poll(struct pollfd *fds, nfds_t nfds, int timeout)
fds 可以传递多个结构体，也就是说可以监测多个驱动设备所产生的事件，只要有一个产生了请求事件，就能立即返回
　　struct pollfd {
　　　　int fd; /* 文件描述符 */
　　　　short events; /* 请求的事件类型，监视驱动文件的事件掩码 */
　　　　short revents; /* 驱动文件实际返回的事件 */
　　} ;
nfds 监测驱动文件的个数
timeout 超时时间，单位为ms
```

#### epoll

>  Epoll 是一种高效的管理socket的模型，相对于select和poll来说具有更高的效率和易用性。传统的select以及poll的效率会因为 socket数量的线形递增而导致呈二次乃至三次方的下降，而epoll的性能不会随socket数量增加而下降。

>  ##### epoll_create函数

```c++
函数声明：int epoll_create(int size)
该函数生成一个epoll专用的文件描述符，其中的参数是指定生成描述符的最大范围。
```

>  ##### epoll_ctl函数

```c++
函数声明：int epoll_ctl(int epfd, int op, int fd, struct epoll_event event)
该函数用于控制某个文件描述符上的事件，可以注册事件，修改事件，删除事件。 如果调用成功返回0,不成功返回-1
参数：epfd：由 epoll_create 生成的epoll专用的文件描述符；
op：要进行的操作例如注册事件，可能的取值
EPOLL_CTL_ADD 注册、
EPOLL_CTL_MOD 修改、
EPOLL_CTL_DEL 删除
fd：关联的文件描述符；
event：指向epoll_event的指针；
```

>  ##### epoll_wait函数

```c++
函数声明:int epoll_wait(int epfd,struct epoll_event   events,int maxevents,int timeout)
该函数用于轮询I/O事件的发生；     返回发生事件数。-1有错误。
参数：epfd:由epoll_create 生成的epoll专用的文件描述符；
epoll_event:用于回传代处理事件的数组；
maxevents:每次能处理的事件数；
timeout:等待I/O事件发生的超时值（ms）；-1永不超时，直到有事件产生才触发，0立即返回。
```

```c++
typedef union epoll_data {
	void ptr;
	int fd;
	__uint32_t u32;
	__uint64_t u64;
} epoll_data_t;
struct epoll_event {
	__uint32_t events;    / Epoll events /
	epoll_data_t data;    / User data variable /
}
```

![![![img](https://static.dingtalk.com/media/lALPDgfLNBa2NfjNAXPNA5Y_918_371.png_620x10000q90g.jpg?auth_bizType=IM&auth_bizEntity=%7B%22cid%22%253A%22745883422%253A745883422%22%252C%22msgId%22%253A%223508544424021%22%7D&bizType=im&open_id=745883422)![img](https://static.dingtalk.com/media/lALPDgfLNBa2NfjNAXPNA5Y_918_371.png_620x10000q90g.jpg?auth_bizType=IM&auth_bizEntity=%7B%22cid%22%253A%22745883422%253A745883422%22%252C%22msgId%22%253A%223508544424021%22%7D&bizType=im&open_id=745883422)图片](https://static.dingtalk.com/media/lALPDgfLNBa2NfjNAXPNA5Y_918_371.png_620x10000q90g.jpg?auth_bizType=IM&auth_bizEntity=%7B%22cid%22%3A%22745883422%3A745883422%22%2C%22msgId%22%3A%223508544424021%22%7D&bizType=im&open_id=745883422)

```c++
select，poll实现需要自己不断轮询所有fd集合，直到设备就绪，期间可能要睡眠和唤醒多次交替。而epoll其实也需要调用epoll_wait不断轮询就绪链表，期间也可能多次睡眠和唤醒交替，但是它是设备就绪时，调用回调函数，把就绪fd放入就绪链表中，并唤醒在epoll_wait中进入睡眠的进程。虽然都要睡眠和交替，但是select和poll在“醒着”的时候要遍历整个fd集合，而epoll在“醒着”的时候只要判断一下就绪链表是否为空就行了，这节省了大量的CPU时间。这就是回调机制带来的性能提升。
select，poll每次调用都要把fd集合从用户态往内核态拷贝一次，并且要把current往设备等待队列中挂一次，而epoll只要一次拷贝，而且把current往等待队列上挂也只挂一次（在epoll_wait的开始，注意这里的等待队列并不是设备等待队列，只是一个epoll内部定义的等待队列）。这也能节省不少的开销.
```

|       | select                        | poll                        | epoll                                    |
| ----- | ----------------------------- | --------------------------- | ---------------------------------------- |
| 操作方式  | 遍历                            | 遍历                          | 回调                                       |
| 底层实现  | 数组                            | 链表                          | 哈希表                                      |
| IO效率  | 每次调用都进行线性遍历，时间复杂度为O(n)        | 每次调用都进行线性遍历，时间复杂度为O(n)      | 事件通知方式，每当fd就绪，系统注册的回调函数就会被调用，将就绪fd放到readyList里面，时间复杂度O(1) |
| 最大连接数 | 1024（x86）或2048（x64）           | 无上限                         | 无上限                                      |
| fd拷贝  | 每次调用select，都需要把fd集合从用户态拷贝到内核态 | 每次调用poll，都需要把fd集合从用户态拷贝到内核态 | 调用epoll_ctl时拷贝进内核并保存，之后每次epoll_wait不拷贝   |

