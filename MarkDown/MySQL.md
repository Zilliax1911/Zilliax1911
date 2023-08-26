# MySQL

### MySQL-服务启动与关闭

1. Win+s打开命令行端口，以管理员身份运行
2. 输入`net stop mysql57` --- 服务启动
3. 输入`net start mysql57` --- 服务关闭

二、MySQL的逻辑结构

1. 逻辑结构
   1. 1 DBMS（数据库管理系统）->数据库 -> 数据表（声明字段） -> 字段（列）
   2. 数据存储在字段中
   3. 一行数据称为记录（元组）
2. 在DBMS管理工具中通过SQL指令来完成对数据库的操作

三、SQL

1. SQL概述

> SQL (S) 结构化查询语言，用于存取、查询、更新数据以及管理关系型数据库系统

2. SQL发展

- IBM(1981) 

在DBMS管理工具中，通过SQL命令来管理数据库

> sql(structured query language) 结构化查询语言，用于存取、查询、更新数据以及管理关系型数据库系统

1. ### SQL分类

> 根据SQL指令完成的数据库操作的不同，可以将SQL指令分为四类：

- **DDL** 数据定义语言
  - 用于完成对数据库对象（数据库、数据表、视图、索引）的创建、删除、修改
- **DML** 数据操作语言
  - 用于完成对数据表中的数据的（数据从数据表）添加、删除、修改操作
- **DQL** 数据查询语言
  - 用于将数据表中的数据查询出来
- **DCL **数据控制语言
  - 用于完成事务管理等控制性操作



2. ### SQL基本语法

- SQL指令不区分大小写
- 每条SQL指令都以`;`做结尾
- 输入指令后还有小箭头：表示语句没有结束，要加上分号
- SQL指令之间以`空格`进行分隔
- SQL之间不限制换行（可以用空格的地方，就可以有换行）；



3. ### DDL

- 创建数据库 `create database db_name;`
- 创建时加上判断 `create database db_name if not exists;`

```mysql
# 创建数据库
create database db_name;
# 创建时加上判断 
create database db_name if not exists;
# 创建数据库时指定字符集(存储的编码格式) 
create database db_name character set utf8/gbk


# 显示指定名称的数据库的信息	
show create database db_name;
```



### 修改数据库的字符集

```mysql
## 修改：
alter database db_name character set utf8;	#utf8 gbk
```

### 删除数据库 

删除数据库时会删除当前数据库中所有的数据表以及数据表中的数据

```mysql
# 删库跑路
drop database db_name;
# 如果数据库存在则删除数据库
drop database if exists db_name;
```

### 创建数据表

```sql
# 切换数据库/使用数据库
use db_name;

# 创建表
	# 创建列
create table tableName (stu_num char(8) not null unique, # 定长字符串, 
                        stu_name varchar(20) not null,# 可变字符串, 
                        stu_gender char(2) not null, 
                        stu_age int not null auto_increament, 
                        stu_tel char(11) not null unique, 
                        stu_qq varchar(11) unique# qq长度有变化，不固定
);
```

**查询数据表**

```sql
show tables;
# 显示表结构
desc tableName;
# 删除表
drop table tableName;
# 判断
drop table if exists tableName;
```

##### 插入数据

```sql
insert into 数据库名.表格名 (列名1，列名2，列名3)
values (数值1，数值2，数值3) #varchar和date里的字符要用''括起来
INSERT INTO eggs(id, name, date)
VALUES (1, '鸡蛋', '2022-02-03');

INSERT INTO egg
VALUES (DEFAULT, '乌龟', '2033-02-04');	# id类型设置为auto_increament
```

**修改数据表**

```SQL
# 修改表的名字
alter table tablename rename to newtablename;

# 数据表也是有字符集的，默认和数据库一致,但可以修改
alter stable students character set utf8;

# 添加字段
alter table students add stu_remark varchar(200);

# 修改字段名（列名）和类型
alter table tablename change <原列名> <新字段名> <新类型名>;

# 修改字段（列）类型
alter table tablename modify <字段名 ColumnName> <类型名>

# 删除列(字段)
alter table tablename drop <字段名>;

#添加新列
alter table databasename.tablename
add stock INT NULL;

# 更新数据
update table databasename.tablename
set sold = '2022-08-08'
where id = 3;
```

##### 删除

```sql
# 删除某条数据
delete from 数据库名.表格名
where id = 1; # 位置

# 删除表格
drop table 数据库名.表格名;

# 删除整个数据库
drop database 数据库名;
```

##### 查询

```sql
SELECT *	# *表示查看表格的全部数据
FROM 表格名；

# 查看某些列
SELECT 列名1，列名2，列名3
FROM 表格名；

# 只显示指定列的不重复数据
SELECT DISTINCT 列名 
FROM 表格名;

# 排序显示
SELECT *
FROM 表格名
ORDER BY 列名 DESC # DESC为从高到低，默认为ASC

# 增加筛选条件
SELECT *
FROM biaogeming
WHERE id >= 100 AND name != 'xiaomei'
-- WHERE NOT 取反
-- WHERE id BETWEEN 100 AND 200
-- WHERE name IN ('xiaomie', 'xiaoming')
-- WHERE name LIKE '%x'	# 模糊搜索
-- WHERE name = 'wei' or name = 'shuai'
ORDER BY date ASC;
```

##### 合并

```sql
# 交集
SELECT *
FROM datatable1
INNER JOIN datatable2
ON datatable1.name = datatable2.name;

# 并集
SELECT name
FROM datatable1
UNION	# UNION ALL  全部，有重复
SELECT name
FROM datatable2
```

```SQL
# 大小写转换
select lower(name) as ename form emp;

# 字符串截取
select substr(name, 1, 1) from emp; -- substr(字符串，开始位置，截取长度)

# 拼接
select concat(name, sal) from emp;

# 随机数
select rand() * 100 from emp;

# round 四舍五入

# 查询最大值
select max(sal) from emp;
select min(sal) from emp;
select sum(sal) from emp;
select count(sal) from emp;

# 表分组 group by
select sum(sal), job from emp group by job order by sum(sal) asc;
```



### 数据类型

> 数据类型：数据表中的字段中支持存放的类型

- 数值类型

  在mysql中有多种数据类型可以存放数值，但不同的类型存放的数值的范围或者形式是不同的。

  | 类型            | 内存空间大小 | 范围                                      | 说明                                                         |
  | --------------- | ------------ | ----------------------------------------- | ------------------------------------------------------------ |
  | tinyint         | 1byte        | 有符号：-127~127<br>无符号：0~255         | 特小型整数（年龄）                                           |
  | smallint        | 2byte        | 有符号：-32768~32767<br/>无符号：0~65535  | 小型整数                                                     |
  | mediumint       | 3byte        | 有符号：-2^31~2^31-1<br/>无符号：0~2^32-1 | 中型整数                                                     |
  | ==int/integer== | 4byte        |                                           | 整数（默认）                                                 |
  | bigint          | 8byte        |                                           | 大型整数                                                     |
  | float           | 4byte        |                                           | 单精度                                                       |
  | double          | 8byte        |                                           | 双精度                                                       |
  | decimal         | 第一个参数+2 |                                           | 使用时要指定长度 <br>decimal(10, 2)<br>表示数值一共有10位，小数位有两位 |

  

- 字符类型

| 类型    | 字符序列的长度范围 | 说明           |
| ------- | ------------------ | -------------- |
| char    | 0~255（字节）      |                |
| varchar | 0~65535（字节）    | 可变长度字符串 |
|         |                    |                |
|         |                    |                |
|         |                    |                |
|         |                    |                |
|         |                    |                |



- 日期类型



### 1、关系型和非关系型数据库的区别你了解多少？

- 关系型数据库的优点
  - 容易理解。因为它采用了关系模型来组织数据。
  - 可以保持数据的一致性。
  - 数据更新的开销小。
  - 支持复杂查询（带where子句的查询）
- 非关系型数据库的优点
  - 不需要经过SQL层的解析，读写效率高。
  - 基于键值对，数据的扩展性很好。
  - 可以支持多种类型数据的存储，如图片，文档等等。

### 2、索引的基本原理

- 索引用来快速地寻找具有特定值的记录，如果没有索引，一般就会在查询时遍历整张表。
- 索引的原理：把无序的数据变为有序的查询
  - 将创建了索引的列的内容进行排序
  - 对排序结果生成倒排表
  - 在倒排表内容上去拼上数据地址链
  - 在查询的时候，先拿到倒排表内容，再取出数据地址链，从而拿到具体数据

## 数据库：保存有组织的数据的容器

- 数据库软件应该称为DBMS（数据库管理系统）。数据库是通过DBMS创建和操纵的容器。
- 我们不能直接访问数据库；我们是通过使用DBMS来替我们访问数据库。

#### 表

某种特定类型数据的结构化清单。

数据库的每一个表都有一个唯一的名字，在相同的库中不能出现相同的表名。

存储在表中的数据应该是一种类型的数据