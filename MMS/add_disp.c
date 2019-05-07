#include "music.h"

/*
	输出表头
*/
void showTable(void) {
	printf("序号\t歌名\t\t歌手\t\t语种\n");
}

/*
	显示所有歌曲
*/
void display(void) {
	int i;
	if (numMusic == 0) {
		printf("没有可供显示的记录！");
		return;
	}
	showTable();
	for (i = 0; i < numMusic; i++) {
		//打印歌曲信息
		printf("%s\t%s\t\t%s\t\t%s\n", records[i].id, records[i].name, records[i].singer, records[i].language);

		//打印满20个记录后停下来
		if (i % 19 == 0 && i!=0) {
			printf("输入任一字符后继续...");
			_getch();		//从控制台读取一个字符，但不显示在屏幕上，当用户按下某个字符时，函数自动读取，无需按回车
			printf("\n\n");
			showTable();
		}
	}
}

/*
	增加新记录，在当前表末尾增加新的信息
	结果：records中将记录新的信息，如果数组大小不够，会重新申请数组空间
*/
void addRecord(void) {
	char str[10];
	int j;
	int cn = 0;
	char id[10];
	if (numMusic == 0)
		printf("原来没有记录，现在建立新歌单\n");
	else
		printf("下面在当前表的末尾增加新的信息\n");
	while(1)
	{
		printf("您将要添加一首歌曲信息，确定吗？（Y/n）");
		gets(str);
		if (str[0] == 'n' || str[0] == 'N')		//不再添加新的信息
			break;
		else if (numMusic >= arraySize)		//现在的数组空间不足，需要重新申请空间
		{
			records = realloc(records, (arraySize + INCR_SIZE) * sizeof(MusicInfo));
			if (records == NULL) {
				printf("memory failed!");
				exit(-1);
			}
			arraySize = arraySize + INCR_SIZE;
		}
		else {
			itoa(numMusic+1, id, 10);
			strcpy(records[numMusic].id, id);
			printf("请输入歌名:");
			gets(records[numMusic].name);
			printf("请输入歌手:");
			gets(records[numMusic].singer);
			printf("请选择语种\n");
			for (j = 0; j < MUN_LANGUAGE; j++)
			{
				printf("%d.%s\t", j + 1, language[j]);
			}
			printf("\n");
			printf("请输入语种的序号：");
			gets(str);
			cn = atoi(str);
			switch (cn)
			{
			case 1:
				strcpy(records[numMusic].language, "华语");
				break;
			case 2:
				strcpy(records[numMusic].language, "粤语");
				break;
			case 3:
				strcpy(records[numMusic].language, "英语");
				break;
			case 4:
				strcpy(records[numMusic].language, "日语");
				break;
			case 5:
				strcpy(records[numMusic].language, "韩语");
				break;
			default:
				printf("未输入正确的语种的序号，默认设为空\n");
				strcpy(records[numMusic].language, " ");
				break;
			}
			numMusic++;
			printf("歌曲添加成功！\n");
			printf("\n");
		}
	}
	printf("现在一共有%d条信息\n", numMusic);
	printf("\n");
	savedTag = 1;
}