#ifndef H_MUSIC_HH
#define H_MUSIC_HH

#pragma warning( disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define INITIAL_SIZE 100	//数组初始大小
#define INCR_SIZE 50		//数组每次增加的大小
#define MUN_LANGUAGE 5		//语种数，（华语、粤语、英语、日语、韩语）

struct music_info
{
	char id[10];		//序号
	char name[20];		//歌名
	char singer[20];	//歌手
	char language[20];	//语种
};
typedef struct music_info MusicInfo;

extern int numMusic;				//记录的歌曲数
extern MusicInfo* records;		//记录歌曲信息的数组
extern char savedTag;			//信息是否已保存的标志，0为已保存，1为未保存
extern int arraySize;			//数组大小
extern char* language[];		//语种

void handle_menu(void);										//菜单处理函数
int menu_select(void);										//菜单选择函数
void addRecord(void);										//当前表的末尾增加新的信息
void modifyRecord(void);									//修改指定歌曲的信息
void display(void);											//显示所有的歌曲信息
void queryInfo(void);										//查询指定歌曲的信息
void removeRecord(void);									//删除指定的记录
int saveRecords(void);										//文件存储操作函数
int loadRecords(void);										//文件读取操作函数
void quit(void);											//退出
void showTable(void);										//输出表头
int findRecord(char* target, int targetType, int from);		//查找指定记录
void copyRecord(MusicInfo* src, MusicInfo* dest);			//将src指向的一条记录复制给dest指向的记录

#endif // !H_MUSIC_HH

