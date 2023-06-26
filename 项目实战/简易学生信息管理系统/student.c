#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "student.db"
#define N 128

char *errmsg;

void do_insert(sqlite3 *db) {
    int id, score;
    char name[20], sex, sql[N];

    printf("Please input id:");
    scanf("%d", &id);

    printf("Please input name:");
    scanf("%s", name);
    getchar();

    printf("Please input sex:");
    scanf("%c", &sex);

    printf("Please input score:");
    scanf("%d", &score);

    sprintf(sql, "insert into stu values(%d, '%s', '%c', %d)", id, name, sex, score);

    if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK) {
        printf("%s\n", errmsg);
    } else {
        printf("Insert finished!\n");
    }
}

void do_delete(sqlite3 *db) {
    int id;
    char name[20], sql[N];

    printf("Please input id:");
    scanf("%d", &id);

    sprintf(sql, "delete from stu where id = %d", id);

    if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK) {
        printf("%s\n", errmsg); 
    } else {
        printf("Delete finished!\n");
    }
}

void do_update(sqlite3 *db) {
    int id, score;
    char name[20], sex, sql[N];

    printf("Please input id:");
    scanf("%d", &id);

    printf("Please input name:");
    scanf("%s", name);
    getchar();

    printf("Please input sex:");
    scanf("%c", &sex);

    printf("Please input score:");
    scanf("%d", &score);

    sprintf(sql, "update stu set name = '%s', sex = '%c', score = %d where id = %d", name, sex, score, id);

    if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK) {
        printf("%s\n", errmsg);
    } else {
        printf("Update finished!\n");
    }
}

int do_query(sqlite3 *db)
{
	char *errmsg;
	char ** resultp;
	int nrow;
	int ncolumn;

	if(sqlite3_get_table(db, "select * from stu", &resultp, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
	{
		printf("%s\n", errmsg);
		return -1;
	}
	else
	{
		printf("query done.\n");
	}

	int i = 0;
	int j = 0;
	int index = ncolumn;

	for(j = 0; j < ncolumn; j++)
	{
		printf("%-10s ", resultp[j]);
	}
	putchar(10);

	for(i = 0; i < nrow; i++)
	{
		for(j = 0; j < ncolumn; j++)
		{
			printf("%-10s ", resultp[index++]);
		}
		putchar(10);
	}

return 0;
}

 
void do_quit(sqlite3 *db) {
    printf("main exit.\n");
	sqlite3_close(db);
	exit(0);
}

int main() {
    sqlite3 *db;
    int n;

    /* 1.打开数据库 */
    if(sqlite3_open(DATABASE, &db) != SQLITE_OK) {
        printf("%s\n", sqlite3_errmsg(db));
        return -1;
    } else {
        printf("Successfully Open Database!\n");
    }

    /* 2.执行sql语句（创建表） */
    if(sqlite3_exec(db, "create table if not exists stu(id int, name char, sex char, score int);", NULL, NULL, &errmsg) != SQLITE_OK) {
        printf("%s\n", errmsg);
        return -1;
    } else {
        printf("Create table successful!\n");
    }

    /* 3.实现数据库功能 */
    while(1) {
        printf("******************************************************\n");
        printf("1: insert   2: query   3: delete   4: update   5: quit\n");
        printf("******************************************************\n");
        printf("Please input your choise:");
        scanf("%d", &n);

        switch(n) {
            case 1:
                do_insert(db);
                break;
            case 2:
                do_query1(db);
                break;
            case 3:
                do_delete(db);
                break;
            case 4:
                do_update(db);
                break;
            case 5:
                do_quit(db);
                break;
            default:
                printf("Invalid data n!\n");
        }
    }

    return 0;

}
