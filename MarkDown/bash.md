26/8/2023

# Bash 终端颜色设置（Bash Color Setting)

- 文章源地址：https://blog.csdn.net/mu936k/article/details/105183088

1. 配置bash_profile文件；路径：~/.bash_profile

2. 在配置文件中环境变量PS1，如下：（除了待显示文本，不能有任何多余空格）

   1. `export PS1="\u@ \t\e[32;1m\]\W $\[\e[0m\]\[\033[32m\]\$(parse_git_branch)\[\033[00m\] "`

   2. PS1的内容由若干个如下片段组成（除了最后一个片段）：

      

      **/[** 颜色描述字符串 **/]** 待显示文本

   3. 颜色描述字符串的格式为：

      

      **/033[**特殊格式 **;**字体颜色 **;**背景颜色 m

   4. 最后一个片段没有待显式文本，待显示文本就是用户输入的命令。这里用的颜色 `/[/033[0m/] `，是指默认值。/[和/]是转义符，其内部是非打印字符，有时候可以不要这两个转义符。

   5. 其中/033是键盘上Esc键对应的ASCII码（27=/033=0x1B），指示：后面的内容是特殊含义的，等效写法有 ^[ 以及 /e 。特殊格式、字体颜色、背景颜色可以省略，其顺序也无所谓，只要中间用;隔开即可。下面的表格列举了各个成员的可能取值及其含义，可以看到各成员的取值两类不同。

      | 特殊格式 | 含义     | 字体颜色值 | 背景颜色值 | 颜色 |
      | -------- | -------- | ---------- | ---------- | ---- |
      | 0        | 默认值   | 30         | 40         | 黑色 |
      | 1        | 粗体     | 31         | 41         | 红色 |
      | 22       | 非粗体   | 32         | 42         | 绿色 |
      | 4        | 下划线   | 33         | 43         | 黄色 |
      | 24       | 非下划线 | 34         | 44         | 蓝色 |
      | 5        | 闪烁     | 35         | 45         | 洋红 |
      | 25       | 非闪烁   | 36         | 46         | 青色 |
      | 7        | 反显     | 37         | 47         | 白色 |
      | 27       | 非反显   |            |            |      |

   6. **转义符：**

       /a        an ASCII bell character (07)
       /d         the date in "Weekday Month Date" format (e.g., "Tue May 26")
       /D{format}  the format is passed to strftime(3) and the result is inserted into the prompt string an empty format
                  results in a locale-specific time representation. The braces are required
       /e         an ASCII escape character (033)
       /h         the hostname up to the first `.'
       /H         the hostname
       /j         the number of jobs currently managed by the shell
       /l         the basename of the shell's terminal device name
       /n         newline
       /r         carriage return
       /s         the name of the shell, the basename of $0 (the portion following the final slash)
       /t         the current time in 24-hour HH:MM:SS format
       /T         the current time in 12-hour HH:MM:SS format
       /@         the current time in 12-hour am/pm format
       /A         the current time in 24-hour HH:MM format
       /u         the username of the current user
       /v         the version of bash (e.g., 2.00)
       /V         the release of bash, version + patch level (e.g., 2.00.0)
       /w         the current working directory, with $HOME abbreviated with a tilde
       /W        the basename of the current working directory, with $HOME abbreviated with a tilde
       /!         the history number of this command
       /#         the command number of this command
       /$         if the effective UID is 0, a #, otherwise a $
       /nnn       the character corresponding to the octal number nnn
       //         a backslash
       /[         begin a sequence of non-printing characters, which could be used to embed a terminal control sequence into the prompt
       /]         end a sequence of non-printing characters

      - `\u `：当前用户的账号名称
      - `\w `：完整的工作目录名称。家目录会以 ~代替
      - `\W` ：利用 basename 取得工作目录名称，所以只会列出最后一个目录
      - `\H`：完整的主机名称。例如：我的机器名称为：fc4.linux，则这个名称就是 fc4.linux
      - `\h` ：仅取主机的第一个名字，如上例，则为 fc4，.linux 则被省略
      - `\d` ：代表日期，格式为 weekday month date，例如："Mon Aug1"
      - `\t `：显示时间为 24 小时格式，如：HH：MM：SS
      - `\T` ：显示时间为 12 小时格式
      - `\A` ：显示时间为 24 小时格式：HH：MM
      - `\v` ：BASH 的版本信息
      - `# `：下达的第几个命令
      - `$` ：提示字符，如果是 root 时，提示符为：# ，普通用户则为：$

      > 参考：

      - [linux 系统终端命令提示符设置（PS1）记录 - 散尽浮华 - 博客园 (cnblogs.com)](https://link.zhihu.com/?target=https%3A//www.cnblogs.com/kevingrace/p/5985970.html)



# 设置Bash为默认终端

> 参考：

https://zhuanlan.zhihu.com/p/418321777

## 1 设置为默认终端

1. Windows Terminal 配置 Git bash 为默认终端
2. VSCode 配置 Git bash 为默认终端

### 1.1 Windows Terminal 配置 Git bash 为默认终端

现在 Windows Terminal 有了图形界面，直接选择就好



![img](https://pic4.zhimg.com/80/v2-f5ab73bb87783dd158e5bac6936ca1db_720w.webp)



具体 json 文件配置

```text
"defaultProfile": "{c891c3d2-b798-4857-83c0-89bf2ea34021}",
    "profiles": 
    {
        "defaults": 
        {
            ...
        },
        "list": 
        [
            {
                "commandline": "D:\\Environment\\Git\\bin\\bash.exe --login -i",
                "guid": "{c891c3d2-b798-4857-83c0-89bf2ea34021}",
                "name": "Git Bash",
                "icon": "D:\\Program_Files\\Git\\mingw64\\share\\git\\git-for-windows.ico"
            },
```

其中 `"commandline": "D:\\Environment\\Git\\bin\\bash.exe --login -i",`

之所以加了--login -i 后面见 「2 可能出现的问题」

### 1.2 VSCode 配置 Git bash 为默认终端

前排提示：我最初在网上搜索，发现之前许多教程里的 json 变量 `“terminal.integrated.shell.windows”` 已经过时了，现在是需要配置 profiles。



![img](https://pic1.zhimg.com/80/v2-043c7dad363d49018076c8346b578238_720w.webp)



参考官网的文档：[Integrated Terminal in Visual Studio Code](https://link.zhihu.com/?target=https%3A//code.visualstudio.com/docs/editor/integrated-terminal)

Ctrl+,打开设置，搜索 `shell:windows`，在 `settings.json` 的最后添加下面的配置

自行修改 Git Bash 和 Powershell exe 的路径

```text
"terminal.integrated.automationShell.windows": "D:\\Environment\\Git\\bin\\bash.exe",
  "terminal.integrated.profiles.windows": {
    "PowerShell": {
      "path": "C:\\Program Files\\PowerShell\\7-preview\\pwsh.exe",
      "icon": "terminal-powershell",
      "args": [
        "-NoLogo" //不显示 powershell 开头的输出
//不加载Powershell的配置和美化
//,"-NoProfile" 
      ]
    },
    "Command Prompt": {
      "path": [
        "${env:windir}\\Sysnative\\cmd.exe",
        "${env:windir}\\System32\\cmd.exe"
      ],
      "args": [],
      "icon": "terminal-cmd"
    },
    "Bash": {
      "path": [
        "D:\\Environment\\Git\\bin\\bash.exe" //Git bash路径
      ],
      "icon": "terminal-bash",
      "args": ["-i","-l"] // 激活Git在外部的配置
        }
  },
```

## 2 可能出现的配置问题

1. Windows Terminal 和 VSCode 打开 Git Bash，发现不会加载配置
2. Git Bash 不会加载 `~/.bashrc` 的配置
3. Git-Bash 修改前缀 (隐藏用户 @ 主机)
4. 修复 Git Bash 中文乱码

### 2.1 Windows Terminal 和 VSCode 打开 Git Bash，发现不会加载配置

解决方法，其实上面已经给出了，就是在 bash.exe 后面加-l, - i 配置，这样激活 Git Bash 就会加载 `~/.bash_profile` 的配置

### 2.2 Git Bash 不会加载 `~/.bashrc` 的配置

确实是这样，Git Bash 在 Win 端只会 `source ~/.bash_profile` 而不会激活 `~/.bashrc` 的配置。所以如果你和我一样，喜欢在 `~/.bashrc` 配置别名，在 `~/.bash_profile` 配置环境的话，

解决方法是那就在 `~/.bash_profile` 加一行，`source ~/.bashrc` 就好啦！

### 2.3 Git-Bash 修改前缀 (隐藏用户 @ 主机)

如果直接打开 Git Bash 终端，你会发现显示的东西很冗余

有用户 @ 主机名，MINGW64，绝对路径。其中前面两个都是固定的，所以就想要把这个隐藏



在 Git-Bash 中我们输入以下代码: `vi ~/.bash_profile` , 然后把以下内容添加到配置文件里面。我这里是隐藏了用户 @ 主机，同时把绝对路径改成了只显示当前文件夹， 需要看全路径的话用 `pwd` 就显示了。这样不至于截图、被人看到时，太暴露隐私哈哈哈。

根据需要自行选择配置。

```text
# Shows Git branch name in prompt.
parse_git_branch() {
  git branch 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/ (\1)/'
}
# 显示 用户 @ 主机
# export PS1="\u@\h \W\[\033[32m\]\$(parse_git_branch)\[\033[00m\] $ "
# 隐藏用户 @ 主机，显示当前文件夹 
#export PS1="\W\[\033[32m\]\$(parse_git_branch)\[\033[00m\]"

# 只显示当前文件夹
export PS1="\[\e[32;1m\]\W $\[\e[0m\]\[\033[32m\]\$(parse_git_branch)\[\033[00m\] "

# 显示全路径
#export PS1="\[\e[32;1m\]\w $\[\e[0m\]\[\033[32m\]\$(parse_git_branch)\[\033[00m\] "
```

粘贴完后，`source .bash_profile` 可以看到结果。



### 3.4 添加一些常用别名增加效率（很好用！）

我的 `~/.bashrc` 文件

```text
# 为了更好的push到github，配置代理
export http_proxy=http://127.0.0.1:10809
export https_proxy=http://127.0.0.1:10809

# 方便cd 进 hexo
alias blog='cd /e/blog'
# hexo 博客发布，num run是package.json中script list配置的别名
alias dev='npm run v'
alias publish='npm run p'

# 配置tree别名
alias tree='tree -FCN'
```