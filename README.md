# MiniSQL
Homework for Database System
# Standardization
1. Try to use C++.
1. Make a floder for a new module.
1. Using Camel-Case for infterface and variables
# Requirement
- 总功能：
MiniSQL是一个精简型单用户DBMS，能够使用户通过字符界面输入SQL语言实现表的建立/删除、索引的建立/删除、记录的插入/删除/查找。
- 语法说明：
支持标准的SQL语句：每一条SQL语句以分号结尾，一条SQL语句可以一行或多行，关键字均为小写。除了常规语句，还支持exec <FILENAME>批量执行语句。
- 数据类型：
MiniSQL支持三种数据类型：int, char(n), float。其中1<n<255。
- 表定义：
支持最多32个属性，支持unique，可以定义单属性主键。
- 索引：
对主键自动建立B+树索引，对unique属性可以建立或者删除B+树索引B+树索引均为单属性、单值。
- 记录：
支持等值查找，范围查找和and连接的多条件查找。支持单条记录的插入，单条或多条记录的删除。
