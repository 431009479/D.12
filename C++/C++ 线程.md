[TOC]

# C++ 线程

> 并发：在同一个时间里CPU同时执行两条或多条命令，这就是所谓的并发。
>
> 并发的物理基础，发展出了多核CPU，这样就为实现真并发提供了物理基础。但这仅仅是硬件层面提供了并发的机会，还需要得到语言的支持。
>
> 线程间的同步：线程的同步是指在一些确定点上需要线程之间相互合作，协同工作。就是在访问同一个临界资源（互斥资源）时，两个线程间必须有一个先后顺序，因为临界资源一次只能供一个线程使用，

>**临界资源：**对于同一进程的多个线程，进程资源中有些对线程是共享的，但有些资源一次只能供一个线程使用，这样的资源被称为临界资源，也可以叫做**互斥资源**，即只能被各个线程互斥访问。

> 临界区：线程中对临界资源实施操作的那段程序，称之为临界区。
>
> 多线程中实现同步互斥的两种方法
>
>   C++11中实现多线程间同步与互斥有两种方法：信号量机制和锁机制，其中锁机制最为常用.
>
> 多进程中实现同步互斥仍然可以采用信号量机制和锁机制

## 多线程

> 多线程是多任务处理的一种特殊形式，多任务处理允许让电脑同时运行两个或两个以上的程序。一般情况下，两种类型的多任务处理：**基于进程和基于线程**。
>
> - 基于进程的多任务处理是程序的并发执行。
> - 基于线程的多任务处理是同一程序的片段的并发执行。

> 创建线程比较简单，使用std的thread实例化一个线程对象就创建完成了
>
> **< mutex >** :包含了与互斥量相关的类以及其他类型和函数
>
> -lpthread连接选项
>
> thread::join()，join的作用是让主线程等待直到该子线程执行结束
>
> include<mutex>，mutex是用来保证线程同步的，防止不同的线程同时操作同一个共享数据

```c++
void func(){
    cout << "hello world" << endl;
}
void func2(int x){
    cout << x << " hello world" << endl;
}
void func3(int &x){
    x += 1;
    cout << x << " hello world" << endl;
}
int main(){   
    thread t1(func); //构造thread对象时传入一个可调用对象作为参数（如果可调用对象有参数，把参数同时传入），这样构造完成后，新的线程马上被创建，同时执行该可调用对象；
    t1.join();  //主线程等待直到该子线程执行结束

    thread t4(func2, 4);
    t4.join();

    int n = 0;  
    thread t7(func3, ref(n));//ref能用包装类型reference_wrapper来代替原本会被识别的值类型，而reference_wrapper能隐式转换为被引用的值的引用类型。 
    t7.join();
    cout << n << endl;
    return 0;
}
```

## 线程池

> 1、管理线程的数量--->一般用vector存线程vector<thread *>
>
> 2、能够执行传入的任何函数 --->一般封装成类Teat；
>
> 3、执行过程，按优先级顺序--->一般使用队列，优先队列。

### 一、管理线程的数量

```c++
void start(){
        if(is_running) return ;
        is_running = true; //is_running创建线程时被fuzhi
        for(int i = 0; i < max_thread_num ; i++){
            threads.push_back(new thread(&ThreadPool::worker, this));//threads是线程队列，worker是成员函数。this是隐藏参数。
        }
    }
```

### 二、传入函数

> 一般要传任何类型的函数，会封装成类。

```c++
class Task{
public:
    template<typename T, typename ...ARGS>//变参模板
    Task(T func, ARGS... args){//构造函数
        this->func = bind(func, forward<ARGS>(args)...);//用bind封装函数名和参数。
    }
    void operator()(){
        this->func();
        return ;
    }
private:
    function<void()>func; //用function定义函数模板。
};
```

> 在线程池会有一个成员函数来处理任务， 任务就是函数。

```c++
  void worker(){
        thread::id id = this_thread::get_id(); //获取线程的id
        is_running[id] = true; //正常的任务设置为true；
        while(is_running[id]){ //true表示为正常任务，执行；
            Task *t = getOneTask(); //getOneTask()函数表示为从任务队列取任务。
            (*t)();//执行
            delete t;、、销毁
        }
        return ;
    }
```

> getOneTask()取任务函数，为私有函数。

```c++
Task *getOneTask(){
        unique_lock<mutex> lock(m_mutex);//抢碗-->资源,加锁
        while(task_queue.empty()) {//等待,队列中任务
            //使用while循环是：可能存在等待任务的进程接收信号但没有任务队列是空,可能刚添加的任务，被其他线程拿走了。
            m_cond.wait(lock);     //wait(lock)是等待资源。
        }
        Task *t = task_queue.front(); //从队列中取任务
        task_queue.pop();//弹出已经被取出的任务。
        return t;//返回任务。
    }
```

> 添加任务到队列中
>
> ```c++
> template<typename T, typename ...ARGS>
>     void addOneTask(T func, ARGS...args){ //变参函数
>         unique_lock<mutex> lock(m_mutex);//加锁
>         task_queue.push(new Task(func, forward<ARGS>(args)...)); //push到队列中
>         m_cond.notify_one();//通知一个等待线程，队列中有任务了。
>         return ;
>     }
> ```



![lALPDiQ3MDES-TvNAY_NAnU_629_399.png](http://ww1.sinaimg.cn/large/00882iMugy1ghrozcr6w2j30hh0b3gmu.jpg)

![lALPDh0cMucbC6rNAQnNA3c_887_265.png](http://ww1.sinaimg.cn/large/00882iMugy1ghrozpmilhj30on07dgm7.jpg)

> 线程池中的线程停止和销毁。

```c++
 void stop(){
         this_thread::sleep_for(chrono::seconds(2)); //sleep(2)
        for(int i = 0; i < max_thread_num; i++){ 
            addOneTask(&ThreadPool::stop_task, this); //往队列中添加max_thread_num个特殊任务--->终止任务。is_running[id] = false;
        }
        for(int i = 0; i < this->max_thread_num; i++){ 
            threads[i]->join(); //等待线程结束，
            delete threads[i];//销毁线程
        }
        threads.clear(); //销毁队列。
        return;
    }
```

### 三、主函数添加任务到队列中

```c++
ThreadPool tp(6);
    tp.start();
    for(int i = 0, j = 1; i< 5; i++, j += 200000){
        tp.addOneTask(task_func, j, j + 200000 - 1);
    }
    tp.stop();
```

