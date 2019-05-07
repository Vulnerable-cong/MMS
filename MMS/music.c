#include "music.h"

/*
	初始化
*/
int numMusic = 0;												//记录的歌曲数
MusicInfo* records = NULL;										//记录歌曲信息的数组
char savedTag = 0;												//信息是否已保存的标志，1为未保存，0为已保存
int arraySize;													//数组大小
char* language[] = { "华语","粤语","英语","日语","韩语" };		//语种
int id = 1;														//ID

/*
	主函数
*/
int main() {
	//初始化数组
	records = (MusicInfo*)malloc(sizeof(MusicInfo) * INITIAL_SIZE);
	if (records == NULL) {
		printf("memory fail!");
		exit(-1);
	}
	arraySize = INITIAL_SIZE;

	printf("\n");
	printf("\t************************\n");
	printf("\t        这是一个        \n");
	printf("\t      歌单管理程序      \n");
	printf("\t 可以对音乐信息进行管理 \n");
	printf("\t    欢迎使用管理程序    \n");
	printf("\t************************\n");
	printf("\n");
	
	handle_menu();
}

/*
	菜单处理函数
*/
void handle_menu(void) {
	for ( ; ; ) {
		switch (menu_select())
		{
			case 1:
				addRecord();
				break;
			case 2:
				modifyRecord();
				break;
			case 3:
				display();
				break;
			case 4:
				queryInfo();
				break;
			case 5:
				removeRecord();
				break;
			case 6:
				saveRecords();
				break;
			case 7:
				loadRecords();
				break;
			case 8:
				quit();
				break;
		}
	}
}

/*
	菜单选择函数
*/
int menu_select() {
	char s[2];
	int cn = 0;
	printf("\n");
	printf("\t1.增加歌曲至歌单\n");
	printf("\t2.修改歌单歌曲\n");
	printf("\t3.显示歌单歌曲\n");
	printf("\t4.查询歌单歌曲\n");
	printf("\t5.删除歌单歌曲\n");
	printf("\t6.保存歌单至记录文件\n");
	printf("\t7.从记录文件读取歌单\n");
	printf("\t8.结束运行\n");
	printf("\n\t左边数字对应功能选择，请选1-8：");

	for ( ; ; ) {
		gets(s);		//将输入作为字符串接收(无论用户按数字键还是字母键)
		cn = atoi(s);	//将所接收的字符串转成数值
		if (cn < 1 || cn>8) printf("\n\t 输入错误，请重选1-8：");
		else break;
	}
	return cn;
}

/*
	结束运行，退出
*/
void quit(void) {
	char str[5];
	if (savedTag == 1)
	{
		printf("是否保存原来的记录？(Y/n)");
		gets(str);
		if (str[0] != 'n' && str[0] != 'N')
			saveRecords();
	}
	free(records);		//释放数组的内存空间
	exit(0);
}

