# 操作系统原理

https://space.bilibili.com/40333442/channel/collectiondetail?sid=444904&ctype=0

### I/O通信技术

#### 可编程I/O

- 轮询：CPU一直占用着总线，不断的检查I/O模块的状态，别的啥事也不做，也叫做程序控制的I/O；

#### 中断驱动I/O

- CPU向I/O发送一条指令，并且告诉中断请求线，I/O执行完毕后会向中断请求线发送信号，CPU每执行完一条指令就会去检查是否有信号；
- 这样当前进程A就会阻塞，另外一个就绪的进程B开始执行；
- 但是数据中的每个字不论是从存储器到I/O，还是从I/O到存储器都必须通过处理器处理，这就导致中断驱动仍然会很花费处理器时间；

#### 直接存储器访问（DMA）

- CPU的代理人，由DMA模块来处理硬盘和内存的数据传输；
- 会占用总线，同样会影响处理器性能；



### Epoll

epoll全称eventpoll，是linux内核实现IO多路复用的一个实现。

**IO多路复用**意思是：在一个操作里同时监听多个输入输出源，在其中一个或多个输入输出源可用的时候返回，然后对其进行读写操作。和epoll类似的有select和poll。

**epoll和select的主要区别**

epoll监听的fd（文件描述符）集合是在内核中的

### 015.什么是进程

#### 地址空间

- 进程是一个正在执行的程序，进程是一个容器，它保存运行程序所需的所有信息；程序本身是静态的可执行文件，存放在硬盘的某个位置；
- 与每个进程相关联的是它在内存中的地址空间
- 与进程相关联的还有一组资源，包括正在使用的寄存器、打开的文件列表等

#### 017.进程的状态

- 进程轨迹和调度器Dispatcher
  - 轨迹：通过列出为该进程而执行的指令序列来描述单个进程的行为；
  - 调度器：操作系统来决定停止当前程序转而加载哪一个程序；使处理器从一个程序切换到另一个程序的小程序；
- 进程的创建：
- 进程的派生：
- 进程的终止：
- 进程的挂起：Suspend
  - 进程无法在内存中放下时，就会把进程搬到硬盘；
  - 涉及将整个进程的一部分从主内存移动到磁盘
  - 当主内存中没有一个进程处于就绪状态时，操作系统会将其中一个**被阻塞的进程**交换到磁盘上的挂起队列中；
- 挂起进程的特征：
  - 无法立即被执行
  - 进程可能在或者不在等待事件
  - 为阻止进程执行，可以通过代理把这个进程置于挂起态，代理可以是进程自己，也可以是父进程或者操作系统；

![image-20230417001222822](C:\Users\LeeON\AppData\Roaming\Typora\typora-user-images\image-20230417001222822.png)

- CPU状态寄存器中user mode 用来做内核态和用户态的切换（0 = 内核；1 = 用户）

##### 一旦操作系统决定创建新进程：

- 给新进程分配一个唯一的进程标识号
- 给进程分配空间
- 初始化进程控制块（pc寄存器的值加载到CPU中，就完成了转换）
- 设置正确的连接
- 创建或扩充其他数据结构

![image-20230417002034266](C:\Users\LeeON\AppData\Roaming\Typora\typora-user-images\image-20230417002034266.png)



## Linux 系统编程

伪文件（内核缓冲区）：管道、块设备、字符设备，套接字；不占内存空间；

普通文件，目录，软连接；这些是真文件，占内存空间

`pid_t waitpid(pid_t pid, int *wststus, int options);`

### 进程控制

1. `pid_t fork();`

- 创建子进程；父子进程各自返回，父进程返回子进程pid，子进程返回0；
  - getpid(); getppid();
- 循环创建N个子进程模型，每个子进程标识自己的身份
- 父子进程相同点：
  - 刚fork后：data段、text段、堆、栈、环境变量、全局变量、宿主目录位置、信号处理方式；
- 父子进程不同点：
  - 进程id、返回值、各自的父进程、进程创建时间、闹钟（定时器）、未决信号集；
- 父子进程共享：
  - ==全局变量：读时共享，写时复制；==
  - 文件描述符（打开文件的结构体）、mmap建立的映射区；

2. gdb父子进程调试

- 由于fork后会有父子两个分支，所以调试时需要指定分支方向；

- `set follow-fork-mode child` 跟踪子进程执行逻辑

#### exec函数族

​		**fork**创建子进程后执行的是和父进程相同的程序，子进程往往需要调用一种exec函数来执行另一个程序。调用exec函数并不创建新线程，所以线程id不会改变。

​		当调用新程序时，该进程用户空间的代码和数据将被完全由新程序替换。

- `int execl(const char *path, const char *arg,...);`            //多参数变参函数，所以在参数结尾处加上NULL，表示参数输入结束，“哨兵”
- `int execlp(const char *file, const char *arg, ...);`
- `int execvp(const char *file, char *argv[]);`
- execlp 函数
  - 加载一个进程，借助PATH变量
  - 成功：无返回；失败：-1
- execl 函数
  - 加载一个进程，指定路径来执行用户程序;
  - `execl("用户路径，绝对路径", "./a.out", NULL);`

#### 回收子进程

1. **孤儿进程**

- 父进程先于子进程终止，子进程会被init进程领养。

2. **僵尸进程**

- 子进程终止，父进程尚未对子进程回收，在此期间，子进程为僵尸进程。

3. **wait(int *status)函数**

- 作用：
  - 阻塞等待子进程退出；
  - 清理子进程残留在内核中的pcb资源；
  - 通过传出参数status，得到子进程结束状态；

- 父进程阻塞等待子进程结束，成功返回子进程pid，失败-1；

- pid_t wait(&status);
  - status有关的几种宏函数
    - WIFEXITED(status);  bool
    - WEXITSTATUS(status);
    - WIFSIGNALED(status);  bool
    - WTERMSIG(status);

4. **waitpid()函数**

- 作用等同于wait，但可以指定pid进程清理，可以不阻塞。
- `pid_t waitpid(pid_t pid, int *status, int options);`成功：返回清理掉的子进程id，失败-1（无子进程）
- int options : WNOHANG ：不阻塞，如果子进程没结束直接返回0；需要阻塞则0；
- 参数pid：
  - 大于0，代表指定的子进程的id
  - -1：回收任意子进程（相当于wait）
  - 0 ：回收和当前调用waitpid一个组的所有子进程
- 返回值：
  - 大于0：表示成功回收的子进程id
  -  = 0：函数调用时，指定了WNOHANG，并且没有子进程结束
  - -1 ：失败



#### 进程间通信

父子进程之间具有相同的内核空间，3G~4G为内核空间；0-3G为各自独立的用户空间；

Linux环境下，进程地址空间相互独立，每个进程各自有不同的用户地址空间。任何一个进程的全局变量在另一个进程中都看不到，所以进程之间不能相互访问，要交换数据必须通过内核在内核中开辟一片缓冲区。进程1把数据拷到内核缓冲区，进程2再从内核缓冲区将数据读走，内核提供的这种机制称为进程间通信（IPC）

1. 常见的通信方式

- 管道（最简单）
  - 匿名管道：有血缘关系才可以用（文件描述符相同）
  - 命名管道
- 共享内存（共享映射区，无血缘关系）
- 信号量（开销最小）
- 套接字（最稳定，实现复杂度最高）

2. 管道的概念：
   1. 调用pipe 系统函数即可创建一个管道，特质如下：
      1. 本质是一个内核缓冲区
      2. 由2个文件描述符引用；
      3. 只能单向，只能从读端进，写端出；
      4. 原理：内核使用环形队列机制，借助内核缓冲区（4K）实现。
   2. 管道的局限性：
      1. 数据不能进程自己写，自己读；一头进肯定是另一头出；
      1. 管道中的数据不可以反复读取（队列的特性），一旦读走 不再存在；
      1. 半双工方式；（对讲机）不能在一次通信中即读又写；

   3. **管道的基本用法**

      1. `int pipe(int pipefd[2]);`
      2. pipe函数创建并打开管道；参数：fd[0] ：读端，fd[1] : 写端；
      3. 成功：0；失败：-1；

   4. 管道的读写行为

      - 读管道：

        - 管道中有数据，read返回实际读到的字节数；

           - 管道中无数据：1）写端被关闭，read直接返回0；

             ​                           2）读端存在，read挂起（阻塞等待）；

      - 写管道

        - 管道读端被关闭，异常终止（SIGPIPE）

        - 有读端           1）管道已满，阻塞等待；（缓冲区4096满了内核会扩容）

          ​                       2）管道未满，write返回写入的字节数；

      - ulimit - a命令查看管道缓冲区大小

3. **==FIFO==**

   1. 命名管道，用在没有血缘关系之间
   2. 创建：mkfifo(name, mode);
   3. 返回值：成功：0；失败：-1；

   ```c
   #include <stdio.h>
   #include <unistd.h>
   #include <sys/stat.h>
   #include <sys/types.h>
   #include <fcntl.h>
   #include <string.h>
   
   int main(int argc, char *argv[]) {
       int fd, len;
       char buf[4096];
       if (argc < 2) {
           printf("./a.out fifoname\n");
           return -1;
       }
       //int fd = mkfifo("testfifo", 644);
       //open(fd, ...);
       fd = open(argv[1], 0_RDONLY);	//打开管道文件
       if (fd < 0)
           sys_err("open");
       while (1) {
           len = read(fd, buf, sizeof(buf));	//从管道读端获取数据
           write(STDOUT_FILENO, buf, len);
           sleep(3);		//多个读端时应增加睡眠秒数，放大效果
       }
       close(fd);
       return 0;
   }
   ```

4. 文件实现进程间通信：

   1. 打开的文件是内核中的一块缓冲区，多个无血缘关系的进程，可以同时访问该文件。
   2. mmap函数的保险调用方式：
      1. fd = open("文件名", 0_RDWR);
      2. mmap(NULL, 有效文件大小， PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

   3. 父子进程使用mmap通信：
      1. 父进程创建映射区：open---》mmap
      2. 指定MAP_SHARED 权限；
      3. fork()创建子进程；




P125 02-信号的概念和机制

#### 信号的概念

- 信号的特质：强制性，信号时软件层面上实现的中断；
- 每个进程收到的所有信号，都是由==内核==发送，处理的；

#### 与信号相关的事件和状态：

##### 信号的产生：

- 按键产生：ctrl + c；ctrl + z（暂停）
- 系统调用产生，如：kill、raise、abort
- 软件条件产生：如：定时器alarm（sleep()）
- 硬件异常产生：如：非法访问内存（段错误）、除0、内存对齐出错（总线错误）
- 命令产生，如：kill命令

##### 递达：递送并且到达进程。（信号由内核产生）

##### 未决：产生和递达之间的状态。主要由于阻塞（屏蔽）导致该状态。

##### 信号的处理方式：

- 执行默认动作
- 忽略（不是未决状态）
- 捕捉（调用户处理函数）

Linux内核的进程控制块**PCB**是一个结构体，里边有阻塞信号集，未决信号集；

##### 阻塞信号集（信号屏蔽字）：

​	将某些信号加入集合，对他们设置为屏蔽，信号一旦被屏蔽就会一直处于未决态；

##### 信号4要素

1~33号信号，有默认处理动作；

1. 编号 2. 名称  3. 信号事件 4. 默认处理动作



#### 创建会话

- 进程组组长不能创建新的会话（父进程）
- 创建后的组id，会话id就是进程自己的id
- 创建后要舍弃原来的终端，新会话没有自己的终端
- pid_ t setsid(0);

##### 创建守护进程模型

1. 创建子进程，父进程退出
2. 在子进程中创建新会话
   1. setsid()函数
3. 根据需要，改变当前目录位置
   1. int chidr (const char *path);
4. 根据需要，重设文件权限掩码
   1. umask()函数
   2. 防止继承的文件创建屏蔽字拒绝某些权限
   3. 增加守护进程灵活性
5. 根据需要，关闭/重定向文件描述符
   1. 继承的打开文件用不到，浪费系统资源，无法卸载
6. 开始执行守护进程核心工作守护进程退出处理程序模型

#### 线程概念

- 线程非共享资源

1. 线程ID
2. 处理器现场和栈指针
3. 独立的栈空间（用户空间栈）
4. errno变量
5. 信号屏蔽字
6. 调度优先级

- 线程优、缺点

1. 优点：提高程序并发性， 开销小，数据通信、共享数据方便
2. 缺点：库函数，不稳定，调试困难，不支持gdb

#### 线程控制原语

- `pthread_t pthread_self(void);`函数

  - 获取线程id，用于在进程中区分不同线程
  - 成功：返回线程id；失败：无
- `int pthread_create(pthread_t *thread, const pthread_attr_t *attr, ...)`

  - 创建一个新线程，对应进程中的fork()函数；
  - 成功：返回0；失败：返回错误号；
  - 参数1：传出参数，保存系统为我们分配好的线程ID；
  - 参数2：通常传NULL，表示使用线程的默认属性；
  - 参数3：函数指针，指向线程主函数（回调函数）（线程体），该函数运行结束，则线程结束；
  - 参数4：回调函数的参数；

  - 子线程创建出来后，会自动去执行回调函数；
- 线程与共享
  - **独享栈空间（用户栈，内核栈）**
  - **线程之间共享全局变量	**
  - 线程默认共享数据段、代码段等地址空间，常用的是全局变量。而进程不共享全局变量，只能借助mmap；
- `void pthread_exit(void *retval);`
  - 退出当前线程，retval函数用来回收线程的返回值，无退出值时，NULL；

- `int pthread_join(pthread_t thread, void** retval);`
  - pthread_join()用来等待一个线程的结束，当一个线程调用_join时，它会被挂起（阻塞），直到指定线程结束为止；
  - 参数1：指定线程的线程ID；
  - 参数2：用户定义的指针，用来存储被等待线程的返回值（线程退出值是void*，所以用void**来回收）；
- `int pthread_detach(pthread_t thread);`
  - 使用来分离线程，分离后的线程会自动回收；
  - 参数：thread：待分离的线程id
  - 返回值：成功：0；失败：errno；



#### 线程属性设置分离线程

- 设置分离属性	==pthread_attr_函数==
- 创建一个线程属性结构体变量
  - `pthread_attr_t attr;`
- 初始化线程属性
  - `pthread_attr_t attr;`

- 设置线程属性为分离态
  - `pthread_attr_setdetachstate(&attr, PTHREAD_REATE_DETACHED);`
- 借助修改后的设置线程属性，创建分离态线程
  - `pthread_create(&tid, &attr, func, NULL);`
- 销毁线程属性
  - `pthread_attr_destroy(&attr);`

## 线程同步概念部分

### 互斥锁

- 数据混乱
  - 资源共享
  - 调度随机
  - 缺乏必要的同步机制
- 多个控制流访问同共一个共享资源，必须同步

#### mutex

- 建议锁
- 锁不会限制访问资源
- 线程不按规则访问也会成功，但会出现数据混乱

#### 函数

- pthread_mutex_t类型
  - 本质：结构体
  - 简化：取值只能为1，n
- 返回值
  - 成功：0
  - 失败：错误号
- pthread_mutex_init
  - 初始化一把互斥锁	1
  - 参数
    - mutex（传出）
    - attr（出入）
    - 两个参数都是指针，默认NULL
  - 静态初始化
    - 宏定义：pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
- pthread_mutex_destroy
  - 销毁一个互斥锁
- pthread_mutex_lock
  - 加锁
  - 参数：互斥锁&mutex
  - mutex--；（原来初值为1的互斥量，变为0，再加锁就阻塞状态）
- pthread_mutex_unlock
  - 解锁
  - 参数：互斥锁&mutex
  - 同时将阻塞在该锁上的所有线程全部唤醒
  - mutex++；
- pthread_mutex_trylock
  - 非阻塞加锁
  - mutex++；
  - 返回EBUSY（表示锁正忙）
- 锁的粒度越小越好，访问前加锁，访问后立即解锁

#### 死锁

- 产生原因：对同一个互斥量重复加锁
- 避免方法：
  - 当一个线程得不到所需资源时，放弃当前以及获得的资源，等待。
  - 保证资源的获取顺序一致。

#### ==读写锁==

- 使用要领：
  - 读共享，写独占
  - 写锁优先级高
- 使用场景：对数据的读操作次数远大于写操作



## 网络通信

### 套接字

在通信过程中，套接字总是成对出现的。

#### linux套接字通信原理

文件描述符：sfd；指向一个套接字；一个套接字只有一个文件描述符

一个套接字内部有两个缓冲区；

#### 网络字节序

- （pc）小端法：高位存高地址，低位存低地址
- （tcp/ip）大端法：高位存低地址，低位存高地址  网络数据流采用大端法

- htonl---> 本地 ---》网络 （IP）

- ntohl

- 相关函数
  - **uint32_t  htonl()**	[本地字节序转网络字节序]主要针对IP协议
  - **uint16_t htons()**        [本地字节序转网络字节序]针对对口号
- 192.168.1.11(string) ---> (int) ---> htonl ---> 网络字节序
  - **ip地址转换函数** ---> **int inet_pton(int af, const char  *src, void *dst)**         本地字节序（string IP）---> 网络字节序
    - af：AF_INET、AF_INET6
    - src：传入，IP地址（点分十进制）
    - dst：传出，转换后的网络字节序的IP地址（二进制）
    - 返回值：
      - 成功：1
      - 异常：0   传入的ip地址无效
      - 失败：-1
  - const char* inet_ntop(int af, const void *src, char *dst, socklen_t dst_size);



### sockaddr 地址结构

sell : man 7 ip

struct sockaddr addr;

addr.sin_family = AF_INET/AF_INET6;

addr.sin_port = htons(9527);

【*】addr.sin_addr.s_addr = htonl(ADDRIN_ANY);	//取出系统中有效的任意IP地址，二进制类型

bind(fd, (struct sockaddr*)&addr, size);



#### server端

- socket();
- bind()绑定IP+port
- listen()设置监听上限
- accpet()阻塞监听客户端连接
- 建立连接的socket和通信的socket不同
- 通信的新socket是由accpet()函数返回的

#### client端

- socket();
- connect(); 绑定IP，port
- write();

#### 各个相关参数

- #include <sys/socket.h>

- int socket(int  domain, int type, int protocol);	//创建一个套接字

  - domain: AF_INET、AF_INET6、AF_UNIX
  - type ：SOCK_STREAM、SOCK_DGRAM
  - protocol：0（stream：tcp，dgram：udp）

  - 返回值：成功：返回新套接字所对应的文件描述符；失败：-1

- int bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen);   //给socket绑定一个地址结构（IP+port）

  - sockfd：socket 函数返回值
  - struct sockaddr_in addr;
  - addr.sin_family = AF_INET;
  - addr.sin_port = htons(8888);
  - addr.sin_addr.s_addr = htonl(INADDR_ANY);
  - addrlen：sizeof(addr)    地址结构的大小
  - 返回值：成功：0；失败：-1

- int listen(int sockfd, int backlog);        //设置同时与服务器建立连接的上限数。（同时进行3次握手的客户端数量）

  - sockfd：socket函数返回值
  - backlog：上限数值。最大值128
  - 返回值：成功：0；失败：-1

- int accept(int sockfd, struct sockaddr* addr, socklen_t* addrlen);     //阻塞等待客户端连接，成功的话，返回一个与客户端成功连接的socket文件描述符

  - sockfd：socket 函数返回值
  - addr：传出参数，成功与服务器建立连接的那个客户端的地址结构（IP + port）
  - 返回值：成功：返回一个能与客户端通信的socket对应的文件描述符；失败：-1

- int connect(int sockfd, const struct sockaddr* addr, socklen_t addrlen);  使用现有的socket与服务器建立连接
  - sockfd

  - addr ：传入参数，**服务器的地址结构**
    - struct sockaddr_in srv_addr;			//服务器地址结构

    - srv_addr.sin_family = AF_INET;

    - srv_addr.sin_port = 和服务器端设定的端口号一致

    - inet_pton(AF_INET, "服务器IP地址", （传出到）&srv_addr.sin_addr.s_addr);

  - addrlen：服务器的地址结构大小

- 如果不使用bind绑定客户端地址结构，采用隐式绑定

#### TCP通信流程分析：

- server：
  - 1.socket()--------创建socket
  - 2.bind()------------绑定服务器地址结构
  - 3.listen()----------设置监听上限
  - 4.accept()---------阻塞监听客户端连接
  - 5.read()------------读 socket获取客户端数据
  - 6.小——大写------toupper()
  - 7.write(fd);
  - 8.close()
- client:
  - 1.socket()-----------创建socket
  - 2.connect()---------与服务器建立连接
  - 3.write()--------------写数据到 socket
  - 4.read()---------------读转换后的数据
  - 5.显示读取结果
  - 6.close()



### TCP三次握手

- 客户端：标志位SYN ：代表要和服务器建立连接 包号（从0开始）（包数据大小），<数据上限1460> （以太网帧46~1500字节，IP首部和TCP首部各占20字节）
- 服务器应答：标志位ACK 1001（代表1001号之前的数据我都收到了（服务器最大上限）
- ACK = SYN（服务器）+ 1
- 三次握手实现在内核态，在用户态的表现就是accept()和connect()函数成功实现

### 断开连接四次挥手（半关闭）

- 通常是客户端开始发送标志位表示要断开连接 标志位FIN（**标志位用一个字节存储**）
- 服务器端：ACK：FIN+1（完成一次半关闭，客户端不能再发数据了，但还能接收数据）
  - 一个套接字里有2个缓冲区，半关闭完成后，写缓冲关闭，读缓冲还存在
  - 造成tcp连接关闭需要四次步骤的原因是：半关闭

- TCP通信过程与函数实现的对应

![image-20230414232221659](C:\Users\LeeON\AppData\Roaming\Typora\typora-user-images\image-20230414232221659.png)

- read()函数返回0，客户端半关闭：FIN_WAIT_2

#### warp()错误处理函数的封装



### 多进程并发服务器

父进程：lfd，监听套接字

子进程：创建cfd

1.Socket()；	创建监听套接字 lfd

2.Bind()：  	 绑定地址结构sockaddr

3.Listen()：

4.while(1) {

​				cfd = Accept();				接收客户端连接请求

​				pfd = fork();

​				if (pid == 0) {					子进程

​								close(lfd)			关闭用于监听的套接字lfd（子进程用不上）：为什么用不上就要关闭

​								read()

​				}else if (pid > 0) {				父进程

​								close(cfd)			关闭用于通信的套接字cfd

​								continue；

​				}

}

5.子进程：

- close(lfd);
- 执行逻辑

6.父进程：

- close(cfd);
- 注册信号捕捉函数：  SIGCHLD
- 执行回调函数回收子进程
  - while (waitpid())		：为什么？为什么是waitpid？



### 多线程并发服务器

1. 前三步相同

4. ```C++
   while (1) {
       cfd = Accept(lfd, );
       pthread_create(&tid, NULL, tfn, NULL);
   }
   ```

5. 子线程：

```C++
void *tfn(void *arg) {
    close(lfd);
    rad(cfd);
    小---》大
        wirte(cfd);
}
```

6. 子线程回收
   1. pthread_join();	阻塞，不适用      //pthread_join(tid, void **); 回收子线程状态  兄弟线程之间可以回收，兄弟进程之间不可以。--->进程信号捕捉
   2. pthread_detach(tid);       父子线程分离





以下是一个简单的==C epoll==示例代码：¹

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#define MAX_EVENTS 10
#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    int server_fd, client_fd, epoll_fd, nfds, n, i;
    struct sockaddr_in server_addr = {0}, client_addr = {0};
    socklen_t client_addr_len = sizeof(client_addr);
    struct epoll_event ev, events[MAX_EVENTS];
    char buf[BUF_SIZE] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 5) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((epoll_fd = epoll_create(MAX_EVENTS)) == -1) {
        perror("epoll_create");
        exit(EXIT_FAILURE);
    }

    ev.events = EPOLLIN;
    ev.data.fd = server_fd;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &ev) == -1) {
        perror("epoll_ctl: server_fd");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1)) == -1) {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }

        for (n = 0; n < nfds; ++n) {
            if (events[n].data.fd == server_fd) {
                if ((client_fd = accept(server_fd,
                                        (struct sockaddr *)&client_addr,
                                        &client_addr_len)) == -1) {
                    perror("accept");
                    exit(EXIT_FAILURE);
                }

                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = client_fd;

                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd,
                              &ev) == -1) {
                    perror("epoll_ctl: client_fd");
                    exit(EXIT_FAILURE);
                }
            } else {
                i = 0;
                memset(buf, 0x00, BUF_SIZE);

                while ((n = read(events[n].data.fd,
                                 buf + i,
                                 BUF_SIZE - i)) > 0) {
                    i += n;

                    if (i >= BUF_SIZE) {
                        break;
                    }
                }

                if (n == -1) {
                    perror("read");
                    exit(EXIT_FAILURE);
                }

                printf("%s\n", buf);

                ev.events = EPOLLOUT | EPOLLET;
                ev.data.fd = events[n].data.fd;

                if (epoll_ctl(epoll_fd, EPOLL_CTL_MOD,
                              events[n].data.fd,
                              &ev) == -1) {
                    perror("epoll_ctl: mod");
                }
            }
        }
    }

    return 0;
}
```

你可以参考这篇文章了解更多关于epoll的底层实现：²

Source: Conversation with Bing, 8/6/2023
(1) epoll经典代码示例_epoll代码示例_叨陪鲤的博客-CSDN博客. https://blog.csdn.net/s2603898260/article/details/106821040.
(2) 深入了解epoll模型（特别详细） - 知乎 - 知乎专栏. https://zhuanlan.zhihu.com/p/427512269.
(3) Nginx源码分析——Epoll事件模块详解 - 知乎 - 知乎专栏. https://zhuanlan.zhihu.com/p/344758424.