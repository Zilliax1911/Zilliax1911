## STL

| 组件                | 描述                                                         |
| ------------------- | ------------------------------------------------------------ |
| 容器（Containers)   | 容器是用来管理某一类对象的集合。C++提供了各种不同类型的容器，比如deque、list、vector、map等。 |
| 算法（Algorithms）  | 算法作用于容器。它们提供了执行各种操作的方式，包括对容器内容执行初始化、排序、搜索和转换等操作。 |
| 迭代器（iterators） | 迭代器用于遍历对象集合的元素。这些集合可能是容器，也可能是容器的子集。 |

这三个组件都带有丰富的预定义函数，下面的程序展示了向量容器(Vector):

```c++
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> vec;
    int i;
    //显示vec的原始大小
    cout << "Vevtor size = " << vec.size() << endl;
    //插入5个值到向量中
    for (i = 0; i < 5; ++i) {
        vec.push_back(i);
    }
    //显示vec扩展后的大小
    cout << "extended vector size = " << vec.size() << endl;
    cout << "capacity vector size = " << vec.capacity() << endl;
    
    vector<int>::inerator i = vec.begin();
    while (i != vec.end()) {
        cout << "value of v = " << *v << endl;
        v++;
    }
    return 0;
}
```

- STL是C++的一部分，因此不用额外安装什么，他被内建在你的编译器之内。
- STL的一个重要特性就是将数据和操作分离。数据有容器类别加以管理，操作则由可定制的算法定义。迭代器充当两者之间的“粘合剂”。
- 程序员不需要思考STL具体的实现过程，只要能够熟练使用STL就OK了。
- STL具有高可重用性，高性能，高移植性，跨平台的优点。



## vector

- 容量：为了降低空间配置时的速度成本，vector实际配置的大小可能比客户端需求大一点，以备将来可能的扩充。
- **一个vector的容量永远大于或等于其大小，一旦容量等于大小，说明容器已经满载，再有新增的元素加入，整个vector容器就需要另觅新的空间**。
- 动态增加大小，并不是在原来的空间上增加，而是新寻找开辟一块更大的空间，然后将原数据拷贝到新空间，并释放原空间。因此，对vector的任何操作，一旦引起空间的重新配置，指向原vector的迭代器就会失效。





## stack

### ==`template <class T, class Container = deque<T>> class stack;`==

- Stacks are a type of container adaptor, specifically designed to operate in  LIFO context, where elements are inserted and extracted only from one end of the container.
- 堆栈是一种容器适配器，专门设计用于在LIFO上下文中操作，其中元素仅从容器的一端插入和提取。

### **stack容器适配器的创建**

```C++
#include <stack>
using namespace std;
```

创建stack适配器，大致分为如下几种方式。

1. 创建一个不包含任何元素的stack适配器，并采用默认的deque基础容器：

```C++
std::stack<int> values;
```

  上面这行代码，就成功的创建了一个可存储int类型元素，底层采用deque基础容器的stack适配器。

2. stack<T, Container = deque<T> >模板提供了2个参数，第二个参数用来指定stack底层要使用的序列式容器，包含vector、deque和list这3个容器。下面展示了如何定义一个使用list基础容器的stack适配器：

```C++
std::stack<std::string, std::list<int>> values;
```

3. 可以使用一个基础容器来初始化stack适配器，只要该容器的类型和stack底层使用的基础容器类型相同即可，如下：

```C++
std::list<int> {2,4,5,7};
std::stack<int, std::list<int>> my_stack (values);
```

​	注意的是：

- 初始化后的**my_stack**中，栈顶元素是7，而不是2。
- 在第2行代码中，stack<>的第二个参数必须被显式声明为**list<int>** （必须为int类型，和存储类型保持一致），否则stack底层将默认使用**deque**容器,也就无法使用list容器的内容来初始化stack适配器。

4. 可以使用一个stack适配器来初始化另一个stack适配器，只要它们存储的元素类型以及底层采用的基础容器类型是一致的即可。例如：

```C++
std::list<int> values {3,5,7,9};
std::stack<int, std::list<int>> my_stack1 (values);
std::stack<int, std::list<int>> my_stack2 (my_stack1);
//或：std::stack<int, std::list<int>> my_stack2 = my_stack1;
```



### C++ memcpy()函数用法

#### 函数原型

==void memcpy(void *str1, const void *str2, size_t n)==

#### 描述

将以str2指向的地址为首地址的连续n个**字节**的数据复制到以str1指向的地址为首地址的空间内。

#### 返回值

该函数返回一个指向str1的指针

#### 说明

1. str2和str1所指的内存区域不能重叠，函数返回指向str1的指针。
2. 与`strcpy() `相比，`memcpy() `并不是遇到``'\0'``就结束，而是一定会拷贝完**n个字节**
3. **memcpy用来做内存拷贝，可以用它拷贝任何数据类型的对象，可以指定拷贝的数据长度；**例：

```C++
char a[100], b[50];
memcpy(b, a, sizeof(b[50]));	//如果用sizeof(a[100])则会造成内存地址溢出
```





### vector

vector容器还提供了data()成员函数，该函数的功能是返回指向容器中首个元素的指针。通过该指针也可以访问甚至修改元素。比如：

```c++
#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<int> values{1,2,3,4,5};
    //输出容器中第 3 个元素的值
    cout << *(values.data() + 2) << endl;
    //修改容器中第 2 个元素的值
    *(values.data() + 1) = 10;
    cout << *(values.data() + 1) << endl;
    return 0;
}
```

运行结果为：

```
3
10
```

#### 遍历vector

1. 数组方式，int len = vector.siz();

2. 可以使用基于范围的循环，此方式将会逐个遍历容器中的元素。比如：

```c++
#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<int> values{1,2,3,4,5};
    for (auto&& value : values)
        cout << value << " ";
    return 0;
}
```

运行结果为：

```
1 2 3 4 5
```



### lower_bound()函数

- lower_bound()函数用于在指定区域内查找不小于目标值的第一个元素。即有可能比目标值大

- lower_bound() 函数定义在`<algorithm>`头文件中，其语法格式有 2 种，分别为：

```c++
//在 [first, last) 区域内查找不小于 val 的元素
ForwardIterator lower_bound (ForwardIterator first, ForwardIterator last,
                             const T& val);
//在 [first, last) 区域内查找第一个不符合 comp 规则的元素
ForwardIterator lower_bound (ForwardIterator first, ForwardIterator last,
                             const T& val, Compare comp);
```

- 其中，first 和 last 都为正向迭代器，[first, last) 用于指定函数的作用范围；val 用于指定目标元素；comp 用于自定义比较规则，此参数可以接收一个包含 2 个形参（第二个形参值始终为 val）且返回值为 bool 类型的函数，可以是普通函数，也可以是函数对象。

- 此函数还会返回一个迭代器，查找成功时，指向找到的元素；反之，指向和last迭代器相同

举个例子：

```C++
#include <iostream>
#include <algorithm>    //std::lower_bound
#include <vector>
using namespace std;
//以普通函数的方式定义查找规则
bool mycomp(int i, int j) {
    return i > j;
}

//以函数对象的形式定义查找规则
class mycomp2 {
public:
    bool operator() (const int& i, const int& j) {
        return i > j;
    }
};

int main() {
    int a[5] = {1,2,7,4,5};
    //从数组中找到第一个不小于3的元素
    int *p = lower_bound(a, a+5, 3);
    cout << "*p = " << *p << endl;

    vector<int> myvector{5,3,4,1,2};
    cout << "myvector迭代：" << endl;
    for (auto it = myvector.begin(); it != myvector.end(); ++it) {
        cout << *it << " ";
    }
    cout<<endl;
    //根据mycomp2规则，从myvector容器中找到第一个违背mycomp2规则的元素
    //查找的是第一个不大于3的元素
    vector<int>::iterator it = lower_bound(myvector.begin(), myvector.end(), 3, mycomp2());
    cout << "从数组中找到第一个不小于3的元素是：" << endl;
    cout << "*it = " << *it << endl;

    return 0;
}
```



### equel_range()函数

定义在`<algorithm>`头文件中，用于在指定范围内查找等于目标值的所有元素。

当指定范围内的数据支持用 < 小于运算符直接做比较时，可以使用如下格式的 equel_range() 函数：

```c++
//找到 [first, last) 范围中所有等于 val 的元素
pair<ForwardIterator,ForwardIterator> equal_range (ForwardIterator first, ForwardIterator last, const T& val);
```

如果指定范围内的数据为自定义的类型（用结构体或类），就需要自定义比较规则，这种情况下可以使用如下格式的 equel_range() 函数：

```c++
//找到 [first, last) 范围内所有等于 val 的元素
pair<ForwardIterator,ForwardIterator> equal_range (ForwardIterator first, ForwardIterator last, const T& val, Compare comp);
```

以上 2 种格式中，first 和 last 都为正向迭代器，[first, last) 用于指定该函数的作用范围；val 用于指定目标值；comp 用于指定比较规则，此参数可接收一个包含 2 个形参（第二个形参值始终为 val）且返回值为 bool 类型的函数，可以是普通函数，也可以是函数对象。

同时，该函数会返回一个 pair 类型值，其包含 2 个正向迭代器。当查找成功时：

1. 第 1 个迭代器指向的是 [first, last) 区域中第一个等于 val 的元素；
2. 第 2 个迭代器指向的是 [first, last) 区域中第一个大于 val 的元素。

反之如果查找失败，则这 2 个迭代器要么都指向大于 val 的第一个元素（如果有），要么都和 last 迭代器指向相同。

举个例子：

```c++
#include <iostream>     // std::cout
#include <algorithm>    // std::equal_range
#include <vector>       // std::vector
using namespace std;
//以普通函数的方式定义查找规则
bool mycomp(int i, int j) { return i > j; }
//以函数对象的形式定义查找规则
class mycomp2 {
public:
    bool operator()(const int& i, const int& j) {
        return i > j;
    }
};
int main() {
    int a[9] = { 1,2,3,4,4,4,5,6,7};
    //从 a 数组中找到所有的元素 4
    pair<int*, int*> range = equal_range(a, a + 9, 4);
    cout << "a[9]：";
    for (int *p = range.first; p < range.second; ++p) {
        cout << *p << " ";
    }

    vector<int>myvector{ 7,8,5,4,3,3,3,3,2,1 };
    pair<vector<int>::iterator, vector<int>::iterator> range2;
    //在 myvector 容器中找到所有的元素 3
    range2 = equal_range(myvector.begin(), myvector.end(), 3,mycomp2());
    cout << "\nmyvector：";
    for (auto it = range2.first; it != range2.second; ++it) {
        cout << *it << " ";
    }
    return 0;
}
//a[9]：4 4 4
//myvector：3 3 3 3
```



此程序中演示了 equal_range() 函数的 2 种适用场景，其中 a[9] 数组中存储的为升序序列；而 myvector 容器中存储的序列虽然整体是乱序的，但对于目标元素 3 来说，所有符合 mycomp2(element, 3) 规则的元素都位于其左侧，不符合的元素都位于其右侧，因此 equal_range() 函数仍可正常执行。



### emplace_back()和push_back()的区别

emplace和push的区别，就在于底层实现的机制不同。



### 移动构造函数

==移动构造函数是C++11中新增加的一种构造函数，其作用是提高程序性能。==

- push_back()函数就会调用移动构造函数，复制返回对象的指针。因为push_back()会在其他地方创建元素，然后再插入vector
- 因此使用emplace_back()会比push_back()效率高，因为emplace_back()是在对应位置直接生成元素
