# Git

https://learngitbranching.js.org/?locale=zh_CN

## 本地仓库



### git commit

- 提交快照
- 提交不是全部重新提交，而是和已经提交的父提交对比，维护有改变的一部分

### git Branch

- `git Branch $name$`

- 创建一个基于当前提交的分支，这个分支可以在当前提交和其所有的父提交的前提下开展新的代码

  分支有区别，在向新的分支提交时，要先选择分支（切换分支）

  - #### git checkout $name$（切换分支）

  ![image-20220914111244149](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220914111244149.png)

  - 切换分支还有新命令：`git switch`

  - 创建分支并切换 `git checkout -b $bugfix`

### 合并分支

- 会产生一个拥有两个父结点的新提交
- 这个提交包含了两个分支各自的新的修改

- `git merge bugFix`



- #### Git Rebase

- `git rebase main`

- 和**merge**不同，**Rebase**会产生一个线性的提交关系，并联转为串联

- 原来的提交记录依然存在，而新的提交记录是副本

- 更新main提交 `git rebase bugfix`



### 在提交树上移动

#### HEAD

- HEAD是一个对当前记录的符号引用 --- 也就是说它指向你正在其基础上进行工作的提交记录。
- HEAD总是指向当前分支上最近一次的提交记录，大多数修改提交树的Git命令都是从改变HEAD的指向开始的。
- HEAD通常情况下是指向分支名的（如 bugFix）。在你提交时，改变了bugFix的状态，这一变化通过HEAD变得可见。
- 就是改变要操作的分支或者提交记录，如果没有任何指令，HEAD是指向分支的，可以用两种命令将HEAD从分支指向提交记录
  - git checkout c1
  - git checkout main^

### 强制修改分支位置

- `git branch -f main HEAD~3`

### 撤销变更

#### git Reset

- ==git reset HEAD~1==

- `git reset` 通过把分支记录回退几个提交记录来实现撤销改动。你可以将这想象成“改写历史”。`git reset` 向上移动分支，原来指向的提交记录就跟从来没有提交过一样。

- 这种方法对远程分支无效

#### git Revert

- ==git revert HEAD==

![image-20220914134754403](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220914134754403.png)

- 奇怪！在我们要撤销的提交记录后面居然多了一个新提交！这是因为新提交记录 `C2'` 引入了**更改** —— 这些更改刚好是用来撤销 `C2` 这个提交的。也就是说 `C2'` 的状态与 `C1` 是相同的。

  revert 之后就可以把你的更改推送到远程仓库与别人分享啦。

### 整理提交记录

#### `git cherry-pick <提交号>...`

如果你想将一些提交复制到当前所在的位置（`HEAD`）下面的话，Cherry-pick是最直接的方式了。

- ==`git cherry-pick c2 c4`==



#### 交互式的 rebase

- 交互式 rebase 指的是使用带参数 `--interactive` 的 rebase 命令, 简写为 `-i`

  如果你在命令后增加了这个选项, Git 会打开一个 UI 界面并列出将要被复制到目标分支的备选提交记录，它还会显示每个提交记录的哈希值和提交说明，提交说明有助于你理解这个提交进行了哪些更改。

  在实际使用时，所谓的 UI 窗口一般会在文本编辑器 —— 如 Vim —— 中打开一个文件。 

- `git rebase -i HEAD~4`



#### 本地栈式提交

- 情景：代码经过了多次的修改，每次修改都在分支中生成了一次提交记录，最终只需要最后一版，就不能直接将所有提交记录合并回`main`分支



## 远程仓库



### 创建

- `git clone` 
  - 远程分支`o/main`
  - 远程分支反映了远程仓库(在你上次和它通信时)的**状态**。这会有助于你理解本地的工作与公共工作的差别 —— 这是你与别人分享工作成果前至关重要的一步.
  - 远程分支有一个特别的属性，==在你检出时自动进入分离 HEAD 状态。==Git 这么做是出于不能直接在这些分支上进行操作的原因, 你必须在别的地方完成你的工作, （更新了远程分支之后）再用远程分享你的工作成果。

- 远程分支有一个命名规范 —— 它们的格式是:

  - `<remote name>/<branch name>`

  因此，如果你看到一个名为 `o/main` 的分支，那么这个分支就叫 `main`，远程仓库的名称就是 `o`。

  大多数的开发人员会将它们主要的远程仓库命名为 `origin`，并不是 `o`。这是因为当你用 `git clone` 某个仓库时，Git 已经帮你把远程仓库的名称设置为 `origin` 了

### 提交

- `git commit`并不会在远程产生新的提交，当HEAD指向``o/main`会进入分离状态

### 从远程仓库获取数据

- `git fetch`
  - 从远程仓库下载本地仓库中缺失的提交记录
  - 更新远程分支指针（如`o/main`)
- `git fetch` 实际上将本地仓库中的远程分支更新成了远程仓库相应分支最新的状态。
- `git fetch` 通常通过互联网（使用 `http://` 或 `git://` 协议) 与远程仓库通信。
- `git fetch` 并不会改变你本地仓库的状态。它不会更新你的 `main` 分支，也不会修改你磁盘上的文件。所以, 你可以将 `git fetch` 的理解为单纯的下载操作。

### 将获取到的数据更新到本地

当远程分支中有新的提交时，你可以像合并本地分支那样来合并远程分支。也就是说就是你可以执行以下命令:

- `git cherry-pick o/main`
- `git rebase o/main`
- `git merge o/main`
- 等等

实际上，由于先抓取更新再合并到本地分支这个流程很常用，因此 Git 提供了一个专门的命令来完成这两个操作。它就是我们要讲的 `git pull`。

- `git pull` 就是`git fetch` 和 `git merge ` 的缩写
  - 实现了下载和合并



### 上传变更到指定的远程仓库

- `git push` 



### 远程仓库历史偏离

![image-20220914155951316](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220914155951316.png)

什么都没有变，因为命令失败了！`git push` 失败是因为你最新提交的 `C3` 基于远程分支中的 `C1`。而远程仓库中该分支已经更新到 `C2` 了，所以 Git 拒绝了你的推送请求。