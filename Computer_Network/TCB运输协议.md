# TCB运输协议

### TCB的运输连接的协议

> TCP是面向连接的协议。运输连接有三个阶段：建立连接、数据传输以及释放连接。TCP连接的建立采用客户服务器的方式。主动发起连接建立的应用进程叫做客户，而被动等待连接建立的应用进程叫做服务器

##### TCP连接

![image.png](http://ww1.sinaimg.cn/large/00882iMugy1gehd6rytwhj30w70i5tha.jpg)

> 为什么A还要发送最后一次确认呢？这是防止已失效的连接请求报文段突然又传送到了B而引发错误。失效的连接请求：A第一次先发送了一个请求，但是丢失了，于是A再发送一个连接请求，重新建立连接，发送数据并释放连接。

> 但是有可能出现异常情况，即A发送的连接请求并没有丢失，而是滞留了在网络中。如果在传输数据完成之后，这个请求又发到B，B误以为A还要发送数据，因此发送确认报文，但是A没有运输需求，因此不予理睬。如果没有最后一次确认，B一直等待A的确认，这样会造成的浪费。采用三报文握手，如果B没有收到A的确认，则可以知道A没有建立连接的需求，就可以避免上述这种情况。

##### TCP的连接释放

![image.png](http://ww1.sinaimg.cn/large/00882iMugy1gehdd52yopj30rp0ghwml.jpg)

> 那么，为什么要等待2MSL的时间呢？

> 保证A最后发送的ACK报文段能够到达B。因为这个报文可能丢失，因此B会重传最后一个确认报文段，A再重新发送确认报文，并且重启计时器，直到A，B都能正常进入到CLOSED状态；

> 防止上面提到的“已失效的连接请求报文”。这段时间内，这些连接请求报文就可能在网络中消失。此外，B要比A先进入CLOSED状态。

![image.png](http://ww1.sinaimg.cn/large/00882iMugy1gehdev5brwj30sd0gqalf.jpg)

### TCB的流量控制

![image.png](http://ww1.sinaimg.cn/large/00882iMugy1gehdlclez8j30wh0gwwqd.jpg)

![image.png](http://ww1.sinaimg.cn/large/00882iMugy1gehdolw8rij30x20gygw1.jpg)

![image.png](http://ww1.sinaimg.cn/large/00882iMugy1gehdr521gxj30uv0dngsv.jpg)

### TCB的可靠传输的实现

![image.png](http://ww1.sinaimg.cn/large/00882iMugy1gehdvbrewpj30wc0icn4s.jpg)

![image.png](http://ww1.sinaimg.cn/large/00882iMugy1gehdwqizagj30xg0j5n6e.jpg)

![image.png](http://ww1.sinaimg.cn/large/00882iMugy1gehdxjxvc0j30xb0ifwt4.jpg)

### TCP超时重传时间的选择

```
由于TCP下层是互联网环境，发送的报文会经过一个高速率的局域网，也可能经过多个低速率的网络，并且每个IP报文所选择的路由器还可能不同，那么问题就来了。如果把超时重传的时间设置得太短，就会引起很多报文产生不必要的重传，但如果把超时重传的时间设的太长就会影响传输速率。 
TCP采用的超时重传RTO 
RTO=RTTs+4xRTTD 
RTT为报文段的往返时间，RTTs是加权往返时间 
RTTs=(1-a)x(旧的RTTs)+ax(RTT样本) 
0<=a<1 
RTTD是RTTs的偏差的加权平均值 
RTTD=(1-b)x(旧的RTTD)+bx|RTTs-新的RTT样本| 
```

![image.png](http://ww1.sinaimg.cn/large/00882iMugy1gehhv9lj5vj30wu0imguf.jpg)

![image.png](http://ww1.sinaimg.cn/large/00882iMuly1gehi0kc5drj30st0gftg7.jpg)

![image.png](http://ww1.sinaimg.cn/large/00882iMuly1gehi5j6kzkj30t90g87b1.jpg)

### TCP的拥塞控制

> 在某段时间，若**对网络中某一资源的需求超过了该资源所能提供的可用部分，网络性能就要变坏**，这种情况就叫做**网络拥塞**。

> 在计算机网络中数位链路容量（即带宽）、交换结点中的缓存和处理机等，都是网络的资源。

> 若**出现拥塞而不进行控制**，整个网络的**吞吐量将随输入负荷的增大而下降**。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190731190238241.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQxNDMxNDA2,size_16,color_FFFFFF,t_70)

TCP的四种拥塞控制算法
1.慢开始
2.拥塞控制
3.快重传
4.快恢复

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190731155254165.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQxNDMxNDA2,size_16,color_FFFFFF,t_70)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190731184314574.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQxNDMxNDA2,size_16,color_FFFFFF,t_70)

![img](https://img-blog.csdnimg.cn/20190731184640178.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQxNDMxNDA2,size_16,color_FFFFFF,t_70)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190731184935595.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQxNDMxNDA2,size_16,color_FFFFFF,t_70)

### TCP报文段的首部格式

![image.png](http://ww1.sinaimg.cn/large/00882iMugy1gehhq6n0x1j30r80ht76y.jpg)

1. ```
   1. 源端口和目的端口：各占2个字节。
   2. 序号：4字节。0~2^31-1，指的是本报文段所发送的数据的第一个字节的序号。比如本次发送的报文从301开始，报文长度是100字节，那么下次发送的报文段序号应该就是401。
   3. 确认号：4字节。确认到该字节为止之前的报文都正确接收了。确认号=N，那么表明到N-1为止的所有数据都已正确接收。
   4. 数据偏移：4位，因为有长度不定的选项字节段，因此用数据偏移来表示TCP报文段的数据从哪里开始。前面从源端口到紧急指针是固定的20个字节，数据偏移共有4位，能表达最大的数是15，数据偏移的单位是32位，也就是4字节，因此，tcp首部长度不能超过15*4=60字节，也是意味着选项的长度不能超过40字节。
   5. 保留：占6位，为今后使用，目前置为0.
   6. 紧急URG：URG=1时，说明这个报文段是紧急数据，你应该立即上传给应用层，比如中断命令等。
   7. 确认ACK：ACK=1时，是TCP建立阶段用，以及在连接简历后所有报文段都置1.
   8. 推送PSH：PSH=1时，需要快速响应的报文，接收方不等缓存填满，直接把目前的缓存都推送上去
   9. 复位RST：RST=1时，表明TCP连接出现严重差错，必须释放连接，然后重新建立连接。
   10. 同步SYN：建立连接时用，SYN=1，ACK=0时，代表建立连接报文段，对方的响应是SYN=1，ACK=1。因此SYN=1时就代表这是一个请求连接或连接接受报文。
   11. 终止FIN：用来释放连接，FIN置1时，就代表要求释放运输连接
   12. 窗口：2字节，指的是发送该报文段的接收窗口还能接受多少，告诉对方，你还能发送多少。这个是根据缓存大小和缓存内已存储的数据大小决定的
   13. 校验和：2字节。
   14. 紧急指针：2字节，配合URG使用，URG置1时，它指出本报文段中的紧急数据的字节数（紧急数据结束以后就是普通数据），窗口为0时也是可以发送紧急数据的
   15. 选项：长度可变，最大40字节。最大报文段长度（MSS）、窗口扩大、时间戳、选择确认
   ```

   