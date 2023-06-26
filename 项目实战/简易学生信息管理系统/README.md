# Stu_Information_System
简易学生信息管理系统（用C语言+Sqllite实现）
> Simple student information management system (realized in C language and Sqllite)

使用的sqlite3 数据库 C语言 API 
    

```
int sqlite3_open(
    const char *filename,   /* Database filename (UTF-8) */
    sqlite3 **ppDb          /* OUT: SQLite db handle */
);
```

> ​    功能：打开数据库
> ​    参数：filename  数据库名称
> ​               ppdb      数据库句柄
> ​    返回值：成功为0 SQLITE_OK 
> ​				  出错 错误码

	int sqlite3_close(sqlite3* db);

> 功能：关闭数据库
> 参数：db    数据库句柄
> 返回值：成功为0 SQLITE_OK ,出错 错误码 

```
const char *sqlite3_errmsg(sqlite3*db);
```

> ​    功能：得到错误信息的描述

```
int sqlite3_exec(
   sqlite3* db,                                  /* An open database */
  const char *sql,                           /* SQL to be evaluated */
  int (*callback)(void* arg,int,char**,char**),  /* Callback function */
  void * arg,                                    /* 1st argument to callback */
  char **errmsg                              /* Error msg written here */
  );
```

>  功能：**执行一条sql语句**
>   参数：db  数据库句柄
>              sql sql语句
>              callback  回调函数，只有在查询时，才传参
>              arg      为回调函数传递参数
>              errmsg  错误消息
>   返回值：成功 SQLITE_OK

查询回调函数：

```
int (*callback)(void* arg,int ncolumns ,char** f_value,char** f_name),  /* Callback function */
```

> 功能：查询语句执行之后，会回调此函数
> 参数：arg   接收sqlite3_exec 传递来的参数
>       ncolumns 列数
>       f_value　列的值得地址
>       f_name   列的名称
> 返回值：0，

另一种查询方法

```
void sqlite3_free_table(char **result);
int sqlite3_get_table(
  sqlite3 *db,          /* An open database */
  const char *zSql,     /* SQL to be evaluated */
  char ***pazResult,    /* Results of the query */
  int *pnRow,           /* Number of result rows written here */
  int *pnColumn,        /* Number of result columns written here */
  char **pzErrmsg       /* Error msg written here */
);
```
