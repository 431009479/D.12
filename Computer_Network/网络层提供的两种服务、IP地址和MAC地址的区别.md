# 网络层提供的两种服务、IP地址和MAC地址的区别

### 网络层提供的两种服务

![image.png](http://ww1.sinaimg.cn/large/00882iMugy1gej2lv2ljoj30ss0ertid.jpg)

![image.png](http://ww1.sinaimg.cn/large/00882iMugy1gej2ncfeuwj30sj0en7dy.jpg)

### IP地址和MAC地址的区别

> IP地址分为IPV4和IPV6。IPV4由32位整数组成，分成4个部分，每块8位二进制。IPV6由128位整数组成，分成8个部分，每个部分16位二进制，即4位6进制。一个完整的IP地址由两个部分组成：网络地址+主机地址。
> 网络地址用于路由选择；主机地址用于在网络或子网内部寻找一个单独的主机。

![image.png](http://ww1.sinaimg.cn/large/00882iMugy1gej2pbh6q8j30qd0670vn.jpg)

![image.png](http://ww1.sinaimg.cn/large/00882iMugy1gej2tldqgjj30sv0ezgq8.jpg)

![image-20200506220851613](/home/xiongdongdong/.config/Typora/typora-user-images/image-20200506220851613.png)

IP地址是每台计算机在网络中的唯一标识。采用“点分十进制”的方式来记忆IP地址。 举：192.168.32.80

![image-20200506222106462](/home/xiongdongdong/.config/Typora/typora-user-images/image-20200506222106462.png)

![image-20200506222239548](/home/xiongdongdong/.config/Typora/typora-user-images/image-20200506222239548.png)

IP地址和MAC地址的关系：首先，IP 间的通信依赖 MAC 地址。使用 ARP 协议凭借 MAC 地址进行通信：

> MAC地址用于在网络中唯一标示一个网卡，一台设备若有一或多个网卡，则每个网卡都需要并会有一个唯一的MAC地址。MAC地址工作于局域网，局域网之间的互连一般通过现有的公用网或专用线路，需要进行网间协议转换。MAC地址共48位（6个字节），以十六进制表示。前24位由IEEE决定如何分配，后24位由实际生产该网上设备的厂商自行指定。

![image.png](http://ww1.sinaimg.cn/large/00882iMugy1gej3u8hziaj30se0e9tji.jpg)

在网络上，通信的双方在同一局域网（LAN）内的情况是很少的，通常是经过多台计算机和网络设备中转才能连接到对方。而在进行中转时，会利用下一站中转设备的 MAC 地址来搜索下一个中转目标。这时，会采用 ARP 协议（Address Resolution Protocol）。

ARP 是一种用以解析地址的协议，根据通信方的 IP 地址就可以反查出对应的 MAC 地址。
![image.png](http://ww1.sinaimg.cn/large/00882iMugy1gej40yibgkj30sh0eegqz.jpg)

![image.png](http://ww1.sinaimg.cn/large/00882iMugy1gej43kwl30j30rx0d0wle.jpg)

![image.png](http://ww1.sinaimg.cn/large/00882iMugy1gej44vfeh8j30h30evqd1.jpg)