# **C++ Primer 5th**

### 1. const的引用

- 引用和引用的对象本身是相对固定的关系，C++不允许随意的变更引用的对象；

- 引用的类型必须与其所引用的对象的类型一致；

- 当一个常量引用被绑定到另一种类型上时会发生：

  - 生成一个和引用同类型的临时变量去处理另一个类型的变量，然后让引用变量去绑定这个临时变量；
  - 所以：如果引用变量不是cosnt修饰的话，就会通过修改引用变量来改变临时变量的值，这与我们设想的不同（应该改变另一类型的变量的值）

- 对const的引用可能引用一个并非cons的对象

  - 对于引用的对象本身是不是一个常量未作限定。因为对象可能是一个非常量，这样就可以通过其他途径来修改这个变量

  ```c++
  int i = 53;
  int& r1 = i;	//引用r1绑定对象i
  const int& r2 = i;	//常量引用r2绑定对象i，但不允许通过r2修改i的值
  r1 = 0；	//可以用来修改i
  r2 = 0；	//错误：r2是一个常量引用
  ```

### 2.指针和const

- 指向常量的指针不能用于改变其所指对象的值，要想存放常量对象的地址，只能使用指向常量的指针；

```C++
const double pi = 3.14;		//pi是一个常量，它的值不能改变
double *ptr = &pi;		//错误：ptr是一个普通指针，不能指向常量
const double *cptr = &pi;	//正确
*cptr = 32;		//错误
```



#### 空指针

*空指针*不指向任何对象，在试图使用一个指针之前代码可以首先检查它是否为空。

> int *pi = nullptr;		//等价于int *pi = 0;

得到空指针最直接的办法就是用字面值**nullptr**来初始化指针，过去的程序还会用到一个名为**NULL**的预处理变量，这个变量在头文件**cstdlib**中定义，它的值就是0

**#define**指令把一个名字设定为预处理变量

预处理变量不属于命名空间std,它由预处理器负责管理。预处理器是运行于编译过程之前的一段程序



#### 指向指针的引用

引用本身不是一个对象，所以不存在指向引用的指针，但是指针是一个对象，所以有指向指针的引用

```c++
int i = 42;
int *p = nullptr;
int *&r = p;	//r是一个对指针p的引用

r = &i;
*r = 0;		//i = 0
```



#### decltype类型指示符

当希望从表达式的返回值类型来定义变量的类型，但又不想用该表达式的值初始化变量



#### 处理每个字符，使用基于范围的for语句

```C++
for (declaration : expression)
    statement
    
string str("some string");
//每行输出str中的一个字符
for (auto c : str)
    cout << c << endl;
```

- 使用 rangefor语句和ispunct函数来统计string对象中标点符号的个数：

```C++
string s("Hello World!!!");
decltype(s.size()) punct_cnt = 0;
//统计s中标点符号的数量
for (auto c : s)
    if (ispunct(c))
        ++punct_cnt;
cout << punct_cnt << "punctuation characters in " << s << endl;
```



#### for indexes的iteration

use subscript execute iteration

```C++
for (decltype(s.size()) index = 0;
    index != s.size() && !isspace(s[index]); ++index)
    
    s[index] = toupper(s[index]);	//Changes the current character to uppercase
```



### Library type : vector

library type vector express the gather of objects，其中所有对象的类型都相同。集合中的每个对象都有一个与之对应的索引，索引用于访问对象。

### 对象生存期和资源管理（RALL)

- C++没有自动垃圾回收，这是一个内部进程，在程序运行时释放堆内存和其他资源。C++负责将所有获取的资源返回到操作系统。未能释放未使用的资源称为泄漏。
- C++可以通过在堆栈上声明对象来尽量避免使用堆内存。如果资源太大而无法用于堆栈，则它应该归对象所有。当对象初始化时，它将获取它拥有的资源。然后，该对象负责在其析构函数中释放资源。
- 拥有对象本身在堆栈上声明。对象拥有资源的原则也称为：RALL

下面的实例演示了一个简单的对象w。它在函数范围中的堆栈上声明，并在函数块的末尾被销毁。该对象没有资源（例如堆分配的内存）。他的唯一成员`g`本身在堆栈上声明，只需超出范围即可。不需要手动的析构函数。

```C++
class widget {
    private:
    	gadget g;	//	lifetime automatically tied to enclosing object
    public:
    	void draw();
};

void functionUsingWidget() {
    widget w;	//	lifetime automatically tied to enclosing scope
    			//	constructs w, including the w.g gadget member
    //	...
    w.draw();
    //	...
} // automatic destruction and deallocation for w and w.g
  // automatic exception safety,
  // as if "finally { w.dispose(); w.g.dispose(); }"
```

在以下示例中， `w` 拥有内存资源，因此必须在其析构函数中具有代码才能删除内存。

```cpp
class widget
{
private:
    int* data;
public:
    widget(const int size) { data = new int[size]; } // acquire
    ~widget() { delete[] data; } // release
    void do_something() {}
};

void functionUsingWidget() {
    widget w(1000000);  // lifetime automatically tied to enclosing scope
                        // constructs w, including the w.data member
    w.do_something();

} // automatic destruction and deallocation for w and w.data
```

由于 C++11，最好使用标准库中的智能指针编写上一个示例。 智能指针处理其拥有的内存的分配和删除。 使用智能指针无需在 `widget` 类中显式析构函数。

```cpp
#include <memory>
class widget
{
private:
   	
    std::unique_ptr<int[]> data;
public:
    widget(const int size) { data = std::make_unique<int[]>(size); }
    void do_something() {}
};

void functionUsingWidget() {
    widget w(1000000);  // lifetime automatically tied to enclosing scope
                        // constructs w, including the w.data gadget member
    // ...
    w.do_something();
    // ...
} // automatic destruction and deallocation for w and w.data
```

通过使用智能指针进行内存分配，可以消除内存泄漏的可能性。 此模型适用于其他资源，例如文件句柄或套接字。 C++ 的设计可确保对象超出范围时被销毁。 也就是说，它们被摧毁，因为块被退出，相反的构造顺序。 销毁对象时，将按特定顺序销毁其基项和成员。 在全局范围内在任何块之外声明的对象可能会导致问题。 如果全局对象的构造函数引发异常，则很难调试。



# 智能指针的使用

智能指针在`std std`头文件的命名空间中定义。主要目的是确保资源获取与对象初始化同时发生，从而能够创建该对象的所有资源并在某行代码中准备就绪。







