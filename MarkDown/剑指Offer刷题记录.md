OFFer 09.用两个栈实现队列

- 思路痛点：难点是没想到要怎么用两个栈表示队列，他们俩是怎么链接在一起的，怎么输出
- 解决：两个栈，一个负责压入，一个负责弹出，不用具象的想两个栈是怎么联系在一起的，因为他们并不是相加的关系，这里没有仔细考虑他们之间的关系，并不是一前一后或者在空间中平行相连接的结构。而应该关注于栈自身的结构特点，也就是FILO，而要实现的队列的特点是FIFO，先进就要先出，这与单个栈的顺序恰好是相反的，因此实际上2个栈刚好解决了栈弹出的顺序和队列输入的顺序相反的问题。
- 双栈：第一个栈负责输入，在栈顶将会第一个弹出的元素实际上是队列最后输入的元素，所以可以这样设计：第一个栈不负责输出元素，只需要维护元素的压入，当元素需要输出时，先将第一个栈的元素弹出到第二个栈中去，这样经过一次压入，位于第二个栈顶的元素恰好就是队列中第一个输入的元素，它也会被第二个栈第一个弹出，这样队列的顺序就没有受到影响。

代码实现：

```C++
class CQueue {
public:
    //两个栈，一个负责压入，一个负责弹出
    stack<int> in_stack, out_stack;
    CQueue() {}
    
    void appendTail(int value) {
        //压入in_stack
        in_stack.emplace(value);    //这时顺序是相反的，最先输入的将压在最底下最后输出
    }
    
    int deleteHead() {
        //若2个栈都为空则就没有东西输出了
        if (in_stack.empty() && out_stack.empty()) {
            return -1;
        }
        
        //out_stack的顺序是正确的，可以直接弹出
        if (!out_stack.empty()) {
            int ret = out_stack.top();
            out_stack.pop();
            return ret;
        }

        //当out_stack是空的，就要问in_stack要元素，in_stack顺序是反的，不能直接输出
        while (!in_stack.empty()) {
            out_stack.emplace(in_stack.top());
            in_stack.pop();
        }
        //把in_stack全部压入后
        int ret = out_stack.top();
        out_stack.pop();
        return ret;
    }
};
```



94.二叉树的中序遍历

- 迭代-----左链右栈

```C++
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> stk;
        while (root != nullptr || !stk.empty()) {
            while (root != nullptr) {
                stk.push(root);
                root = root->left;
            }
            
            root = stk.top();
            stk.pop();
            res.emplace_back(root->val);
            root = root->right;
        }
        return res;
    }
};
```



- 递归

```C++
class Solution {
public:
    void inorder(TreeNode* root, vector<int>& res) {
        if (!root) {
            return;
        }
        inorder(root->left, res);
        res.emplace_back(root->val);
        inorder(root->right, res);
    }
    
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        inorder(root, res);
        return res;
    }
};
```



### 268. 丢失的数字

1. 位运算

   1. 异或运算会遵循交换律，如2^4^5^3^2

   > 零和任何数异或都为n                 n ^ 0 = n;
   >
   > 任何数和自身异或都为0             n ^ n = 0;

   要找到数组中没有出现的数字，可以在[0, n]中和下标异或，这样最后会留下没有出现一个多余的下标，这个就是没有出现的数字

   ```C++
   //class Solution {
   public:
   	int missingNumber(vector<int>& nums) {
           int ret = n;		//下标取不到n，所以要单独加进去
           
       }
   }
   ```

2. 哈希集合

   - 使用哈希集合，可以将时间复杂度降到O(n)。
   - 首先遍历数组 \textit{nums}nums，将数组中的每个元素加入哈希集合，然后依次检查从 00 到 nn 的每个整数是否在哈希集合中，不在哈希集合中的数字即为丢失的数字。由于哈希集合的每次添加元素和查找元素的时间复杂度都是 O(1)O(1)，因此总时间复杂度是 O(n)O(n)。


   ```C++
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        unordered_set<int> set;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            set.insert(nums[i]);
        }
        int missing = -1;
        for (int i = 0; i <= n; i++) {
            if (!set.count(i)) {
                missing = i;
                break;
            }
        }
        return missing;
    }
};
   ```



#### Offer53 缺失的数字

- 二分查找

  - 边界是元素值和元素下标不相等的点，二段性，左右有一个明显的不一样的特征来区分。

  ```C++
  class Solution {
  public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int l = 0;	//左端点
        int r = n - 1;	//右端点
        int m;
        
        while(l <= r) {	//临界条件
        	m = l + (l - r) / 2;	//求 
        
        }
    }  
  };
  ```




### Offer03.数组中重复的数字

- 排序后遍历，检查左手是否有相同数字

- 哈希表

```C++
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        unordered_map<int, int> mp;
        for (int i = 0; i < nums.size(); ++i) {
            if (mp.find(nums[i]) != mp.end()) return nums[i];
            else mp[nums[i]]++;
        }
        return -1;
    }
};
```

- 鸽巢原理

  - 数组的大小小于数组的长度，所以理论上每一个数字都可以在和它的下标相等的位置，即`nums[i] == i` ，遍历后如果有相等的，即为重复数字。

  ```C++
  class Solution {
  public:
      int findRepeatNumber(vector<int>& nums) {
          for (int i = 0; i < nums.size(); ++i) {
              while (nums[i] != i) {
                  if (nums[i] == nums[nums[i]]) return nums[i];
                  int tmp = nums[i];
                  nums[i] = nums[tmp];
                  nums[tmp] = tmp;
              }
          }
          return -1;
      }
  };
  ```

  

### Offer 50.第一次只出现一次的字符

```C++
class Solution {
public:
    char firstUniqChar(string s) {
        
        int map[26] = {0};
        vector<int> v;
        //设置v的容量
        v.reserve(26);
        for (auto x : s) {
            int i = x - 'a';
            if (map[i] == 0) v.push_back(i);
            map[i]++;
        }
        for (auto x : v) {
            if (map[x] == 1) return x + 'a';
        }
        return ' ';
    }
};
```

- 哈希，两次遍历

​	

```C++
class Solution {
public:
    char firstUniqChar(string s) {
        unordered_map<char, int> mp;
        for (char c : s) {
            mp[c]++;
        }
        
        for (int i = 0; i < s.size(); ++i) {
            if (mp[s[i]] == 1) {
                return s[i];
            }
        }
        return ' ';
    }
};
```



### Offer 32  从上到下打印二叉树 ll

**I. 按层打印：** 题目要求的二叉树的 **从上至下** 打印（即按层打印），又称为二叉树的 ==广度优先搜索（BFS）==。BFS 通常借助 **队列** 的先入先出特性来实现。

**II. 每层打印到一行：** 将本层全部节点打印到一行，并将下一层全部节点加入队列，以此类推，即可分为多行打印。

![Picture1.png](https://pic.leetcode-cn.com/59e0600588ffdc2f34b4b563193b56c1f678743637e2754e2a9be0e7facc5d48-Picture1.png)



- 自定义函数递归

```C++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void point(TreeNode* node, vector<vector<int>>& vp, int level) {
        if (!node) {
            return;
        }

        //如果在同一层就放到一起，不在同一层就加入新的vector
        if (level >= vp.size()) {
            vector<int> v;
            vp.emplace_back(v);
        }

        vp[level].emplace_back(node->val);

        point(node->left, vp, level + 1);
        point(node->right, vp, level + 1);
    }

    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ret;
        int level = 0;
        point(root, ret, level);

        return ret;
    }
};
```



- BFS
  - 定义一个双端队列queue，存入根节点
  - 当队列为空时，跳出（叶子结点，没有东西存进队列）
  - 当队列不为空时，定义一个vector，遍历队列，队首出列
  - 若队首左右子节点存在，则入列（压入队列）
  - 将队首结点的值存入vector
  - 最后返回

```C++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ret;
        if (!root) return ret;

        queue<TreeNode*> eue;
        //压入根结点
        eue.push(root);
        while (!eue.empty()) {
            
            int n = eue.size();
            TreeNode* node = nullptr;
            vector<int> v;
            for (; n--; eue.pop()) {

                node = eue.front();

                v.emplace_back(node->val);
                if (node->left) eue.push(node->left);
                if (node->right) eue.push(node->right);
            }
            ret.emplace_back(v); 
        }
        return ret;
    }
};
```





### 2169. 得到0的操作数

#### 递归

- 当需要返回递归的次数作为结果值的时候，通常在递归语句后面+1就可以，不需要单独定义int型变量，会变得复杂。最后在跳出条件中，`return 0;`

```C++
class Solution {
public:
    int countOperations(int num1, int num2) {
        while (num1 != 0 && num2 != 0) {
            if (num1 > num2) {
                return countOperations(num1 - num2, num2) + 1;
            }else if (num1 < num2) {
                return countOperations(num1, num2 - num1) + 1;
            }else {
                return countOperations(num1 - num2, num2) + 1;
            }
        }
        return 0;
    }
};
```

#### Offer 55. 二叉树的深度

- DFS ———后序遍历
- 自下向上，利用**递归**或**栈**实现
  - 终止条件：当`root`为空，说明已越过叶结点，因此返回深度0。

```C++
class Solution {
public:
// DFS
    int maxDepth(TreeNode* root) {
        TreeNode* node = root;
        while (node != nullptr) {
            return max(maxDepth(node->left) + 1, maxDepth(node->right) + 1);
        }
        return 0;
    }
};
```

- BFS———层序遍历
- 自顶向下

```C++

```



#### Offer 32-I. 从上到下打印二叉树

- BFS（广度优先）

- 解题思路：

  - 题目要求二叉树的**从上至下**打印（即按层打印），又称为二叉树的**广度优先搜素（BFS)**。
  - BFS通常借助**队列**先入先出的特性来实现。

  ```C++
  class Solution {
  public:
  
  //BFS
  
      vector<int> levelOrder(TreeNode* root) {
          if (!root) {
              return {};
          }
          queue<TreeNode*> list;
          vector<int> v;
          list.push(root);
          while (!list.empty()) {
  
              for (int i = 0; i < list.size(); ++i) {
                  TreeNode* node = list.front();
                  v.emplace_back(node->val);
                  if (node->left) list.push(node->left);
  
                  if (node->right) list.push(node->right);
  
                  list.pop();
              }
          }
  
          return v;
      }
  };
  ```



#### 144. 二叉树的前序遍历

```C++
class Solution {
public:
//DFS
    vector<int> v;
    vector<int> preorderTraversal(TreeNode* root) {
        if (!root) {
            return {};
        }else {
            v.emplace_back(root->val);
            preorderTraversal(root->left);
            preorderTraversal(root->right);
        }
        return v;
    }
};
```



```C++
class Solution {
public:
//BFS,迭代,栈实现
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ret;
        stack<TreeNode*> s;
        s.push(root);
        while (!s.empty()) {
            TreeNode* node = s.top();
            s.pop();
            if (!node) continue;
            ret.emplace_back(node->val);
            s.push(node->right);	//压入栈中，所以顺序反着来
            s.push(node->left);
        }
        return ret;
    }
};
```



#### Offer 24. 反转链表

```C++
class Solution {
public:
    //维护一个队列，首端插入，实现倒序，再将指针指向头节点
    //遍历一遍队列，实现翻转
    ListNode* reverseList(ListNode* head) {
        if (!head) {
            return head;
        }
        list<int> list;
        ListNode* node = head;
        while (node) {
            list.emplace_front(node->val);
            node = node->next;
        }
        
        node = head;
        for (int n : list) {
            p->val = n;
            p = p->next;
        }
        return head;
    }
};
```

- 双指针

```C++
class Solution {
public:
//双指针
    ListNode* reverseList(ListNode* head) {
        ListNode* pre = nullptr;//初始指向末尾空
        ListNode* cur = head;//初始指向头节点

        while (cur) {
            ListNode* tmp = cur->next;//暂存
            cur->next = pre;//改变方向，向回指
            pre = cur;//向前移动
            cur = tmp;//向前移动
        }

        return pre;//重点：返回的是后面的指针，一开始为空的指针
    }
};
```



#### 3. 无重复字符的最长字串

```C++
class Solution {
public:
    //滑动窗口，unordered_set
    int lengthOfLongestSubstring(string s) {
        if (s.size() == 0) {
            return 0;
        }

        unordered_set<char> set;
        int left = 0;
        int ret = 0;
        for (int i = 0; i < s.size(); ++i) {
            while (set.find(s[i]) != set.end()) {
                set.erase(s[left]);
                left++;
            }
            ret = max(ret, i - left + 1);
            set.insert(s[i]);
        }
        return ret;
    }
};
```



#### 94. 二叉树的中序遍历

```C++
class Solution {
public:
    //迭代，栈实现
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ret;
        stack<TreeNode*> sk;
        while (root != nullptr || !sk.empty()) {
            while (root != nullptr) {
                sk.emplace(root);
                root = root->left;
            }
            //此时root == nullptr
            root = sk.top();    //指向左子节点为空的结点
            sk.pop();
            ret.emplace_back(root->val);
            root = root->right;
        }
        return ret;
    }
};
```



查找最后一个单词的长度

- 要输入一段字符串而不是遇见空格就停止应该：getline(cin, str);

- reverse()翻转字符串，要加上头文件`#include <algorithm>`

- string::find()提供一个查找字符的函数，返回size_t类型的值，如果没有找到，返回string::npos

- size_t：

- [size_t是一个无符号整数类型，用于表示对象或数组的大小。](https://en.cppreference.com/w/c/types/size_t)[1](https://en.cppreference.com/w/c/types/size_t)[2](https://en.cppreference.com/w/cpp/types/size_t)

  [size_t的取值范围是目标平台下最大可能的数组尺寸，它可能和unsigned int不同。](https://www.zhihu.com/question/24773728)[3](https://www.zhihu.com/question/24773728)

  [size_t常用于数组索引和循环计数，它可以安全地存储任何非成员指针的值。](https://en.cppreference.com/w/cpp/types/size_t)[2](https://en.cppreference.com/w/cpp/types/size_t)



计算某字符出现的次数

isupper();	tolower();



[unordered_map 和 map 的主要区别有以下几点](https://www.geeksforgeeks.org/map-vs-unordered_map-c/)[1](https://www.geeksforgeeks.org/map-vs-unordered_map-c/)：

- [unordered_map 是用哈希表实现的，而 map 是用红黑树实现的](https://blog.csdn.net/jpc20144055069/article/details/108170073)[2](https://blog.csdn.net/jpc20144055069/article/details/108170073)[1](https://www.geeksforgeeks.org/map-vs-unordered_map-c/)。
- [unordered_map 中的元素是无序存储的，而 map 中的元素是按照键值升序存储的](https://blog.csdn.net/jpc20144055069/article/details/108170073)[2](https://blog.csdn.net/jpc20144055069/article/details/108170073)[1](https://www.geeksforgeeks.org/map-vs-unordered_map-c/)[3](https://zhuanlan.zhihu.com/p/210458185)。
- [unordered_map 的搜索、插入和删除操作的平均时间复杂度是 O(1)，而 map 的这些操作的时间复杂度是 O(log N)](https://stackoverflow.com/questions/13799593/how-to-choose-between-map-and-unordered-map)[4](https://stackoverflow.com/questions/13799593/how-to-choose-between-map-and-unordered-map)[1](https://www.geeksforgeeks.org/map-vs-unordered_map-c/)。
- [unordered_map 通常占用更多的内存空间，因为每个桶都需要额外的信息来链接其元素，而 map 只需要一些指针来维护红黑树](https://stackoverflow.com/questions/2196995/is-there-any-advantage-of-using-map-over-unordered-map-in-case-of-trivial-keys)[5](https://stackoverflow.com/questions/2196995/is-there-any-advantage-of-using-map-over-unordered-map-in-case-of-trivial-keys)[2](https://blog.csdn.net/jpc20144055069/article/details/108170073)。



**随机数**

- vector容器存储长数组
- unordered_set容器去重   if(set.insert(num).second) {}
- sort(vector::begin(), vector::end())   升序排序



**十六进制转十进制**

```C++
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main()
{
    string str;
    while (cin >> str)
    {
        int len = str.size();
        int sum = 0;
        //十六进制转换为十进制
        for (int i = len - 1; i >= 0;)
    }
}
```



**取近似值**

```C++
int main() {
    float number;
    float i = 0.5;
    int count;
    cin >> number;
    while (number >= i) {
        count++;
        i++;
    }
    
    cout << count << endl;
    return 0;
}
```



输入一个 int 型的正整数，计算出该 int 型数据在内存中存储时 1 的个数。

数据范围：保证在 32 位整型数字范围内

\#include <iostream>

\#include <bitset>

using namespace std;



int main() {

  int n;

  cin >> n;

  bitset<32> b(n);

  cout << b.count();

}



**HJ38 小球落下**

- 题目要求输出的两个值不在同一个状态下

- 第五次落地时，一共有5次落下，4次弹起

- 以弹起次数为循环边界

- ```c++
  #include 
  
  void bounceBall(int num) {
      int bounce_time = 5;
      double path_length = double(num);
      double bounce_high = double(num);
      for (int i = 1; i < bounce_time; i++) {	//以第一次弹起为起始
      	bounce_high /= 2;
      	path_length += bounce_high * 2;	
      }
      cout << path_length << endl;
      cout << bounce_high / 2 << endl;	//第5次弹起
  }
  ```



#### Offer 17.打印从1到最大的n位数

- 一直打印到跳出条件为止

- 怎样判断一个整数的位数

  - 使用算数运算符，进行一个循环判断

  ```C++
  /*
  如果n是一个正整数，则‘n’除以10直到商为0，所用的次数就是‘n'的位数
  */
  int main() {
      int n = 12345;
      int digits = 0;
      while (n != 0) {	
          n /= 10;
          digits++;
      }
      return digits;
  }
  ```

  - 使用数学函数

  ```cpp
  #include <iostream>
  #include <cmath>
  using namespace std;
  int main() {
      int n = 12345;
      int digits = int(log10(n)) + 1;
      cout << "The number of digits in " << n << " is " << digits << endl;
      return 0;
  }
  ```



#### Offer 18. 删除链表节点

- 一开始想到了栈存储目标节点之前的指针
- 栈空间复杂度高，可以定义两个链表指针；前一个记录，后一个遍历链表。因为删除时只需要前一个节点



#### Offer 22.链表中倒数第k个节点

- 放入栈中
- 放入数组中
- 双指针



#### Offer 21.调整数组顺序使奇数位于偶数前面

- 双指针交换
- 从数组头部开始遍历，如果是偶数，则和尾部交换，尾部指针前进，**首部指针不动**，再次判断首部指针所指数（交换前尾部的数）这样的好处是不需要既判断队首又判断队尾；



#### Offer 24. 反转链表

- 递归

```C++
ListNode* reverseList(ListNode* head) {
    if (!head || !head->next)
        return head;
    ListNode* node = reverseList(head->next);
    head->next->next = head;
    head->next = nullptr;
    return node;
}
```



#### Offer 25. 合并链表

- 递归

```C++
ListNode* mergeLists(ListNode* l1, ListNode* l2) {
    if (!l1) return l2;
    if (!l2) return l1;
    if (l1->val <= l2->val) {
        l1->next = mergeLists(l1->next, l2);
        return l1;
    }else {
        l2->next = mergeLists(l1, l2->next);
        return l2;
    }
}
```



#### Offer 26. 判断B二叉树是否是A二叉树的子树

- 初见思考

  - 如果迭代，判断是否相等，再迭代下一个节点

  - 终止条件：b子树节点为空指针，或a为空指针

  - 问题是，树会有向左和向右两个指针，无法在一次遍历中同时判断左右两子树是否有一子树和B树节点值相等

- 成熟逻辑

  - B树必不能为空
  - B树是A树的子结构，则满足以下三点任一点：或的关系
    - b根和a根重合
    - b根在a树左子树中
    - b根在a树右子树中
  - 先序遍历A中的每个节点（对应函数：isSubStructure()）
  - 判断B树的根是不是包含在A树中（recur（A, B))

```C++
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        return ((A && B) && (recur(A, B) || isSubStructure(A->left, B) || isSubStructure(A->right, B)));	//根节点对不上，b不动，a向下走
    }
    bool recur(TreeNode* A, TreeNode* B) {
        if (!B) return true;//走完直接为真
        if (!A || A->val != B->val) return false;//判断值很巧妙
        return recur(A->left, B->left) && recur(A->right, B->right);//b为空也没问题，如果两边子节点都为空，又因为前置判断过父节点值相等，所以返回true;
    }
```



#### Offer 27. 二叉树的镜像

- dfs递归

```C++
TreeNode* mirrorTree(TreeNode* root) {
    if (!root) return nullptr;
    TreeNode* tmp = root->left;
    root->left = mirrorTree(root->right);
    root->right = mirrorTree(tmp);
    return root;
}
```



#### 判断两个二叉树是否相等

```C++
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (p == nullptr && q == nullptr) return true;
    if (p == nullptr || q == nullptr) return false;
    if (p->val != q->val) return false;
    return (isSameTree(p->left, q->left) && isSameTree(p->right, q->right));
}
```



#### Offer 12.矩阵中的路径（字母矩阵中找单词）

- dfs + 剪枝

```c++
private:
	int rows, cols;
	bool dfs(vector<vector<int>>& board, string word, int i, int j, int k) {
        if (i >= rows || i < 0 || j >= cols || j < 0 || board[i][j] != word[k]) return false;
        if (k == word.size() - 1) return true;
        board[i][j] = '\0';
        bool res = dfs(board, word, i+1, j, k+1) || dfs(board, word, i-1, j, k+1) || dfs(board, word, i, j+1, k+1) || dfs(board, word, i, j-1, k+1);
        board[i][j] = work[k];
        return res;
    }
```



- 每日一题 0730 / 142.环形链表II

双指针，快慢指针，快指针每一步是慢指针的2倍，所以快指针总会追上慢指针（如果是闭环）

- 第一次相遇：

1. f = 2s
2. fast比slow多走了n个环的长度，即f = s +nb
3. 得：s = nb 即 fast和slow分别走了2n,n个环的周长

- 第二次相遇：

1. f = 0
2. s = nb
3. 当f = a，s = a + nb时，两指针重合

#### HJ16 购物单

- 01背包问题
  - 问题描述：有一个背包可以装物品的总重量为W，现有N个物品，每个物品中w[i]，价值v[i]，用背包装物品，能装的最大价值是多少？
  - 状态转移方程：dp[i] [j] = max(dp[i-1] [j], dp[i-1] [j-w[i]] + v[i])
  - dp[i-1] [j]表示当前物品不放入背包，dp[i-1][j-w[i]]+v[i]表示当前物品放入背包，**即当前第i个物品要么放入背包，要么不放入背包**。





- 235.二叉搜索树的最近公共祖先
  - 祖先的定义：一个节点p在节点root的左子树或者右子树中，或者p == root，则称root是p的祖先。
