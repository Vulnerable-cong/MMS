#include "music.h"
/*
	查找指定的记录
	参数：target：欲查找记录的某一项与target相同
	targetType：表明通过哪一项来查找，0为ID，1为歌名
	from：从第from个记录开始找
	返回：找到的记录的序号，若找不到则返回-1
*/
int findRecord(char* target, int targetType, int from) {
	int i;
	for (i = from; i < numMusic; i++) {
		if
			((targetType == 0 && strcmp(target, records[i].id) == 0) || 
			(targetType == 1 && strcmp(target, records[i].name) == 0) ||
			(targetType == 2 && strcmp(target, records[i].singer) == 0) ||
			(targetType == 3 && strcmp(target, records[i].language) == 0))
			return i;
	}
	return -1;
}

/*
	查询指定歌曲的信息
	可以按照序号、歌名、歌手、语种来查询
*/
void queryInfo(void) {
	char str[5] ;
	char s[5];
	char target[20];
	int type = 0;
	int count = 0;
	int i ,j = 0;
	int cn1, cn2 = 0;

	if (numMusic == 0) {
		printf("没有可供查询的记录");
		return;
	}
	while (1) {
		printf("请输入查询的方式：(直接输入回车则结束查询)\n");
		printf("1.按序号\n");
		printf("2.按歌名\n");
		printf("3.按歌手\n");
		printf("4.按语种\n");
		printf("请输入：");

		gets(str);
		cn1 = atoi(str);
		if (cn1 < 1 || cn1>4) {
			printf("\n 输入错误,回到首页\n");
			break;
		}
		if (cn1 == 0)
			break;
		switch (cn1) {
		case 1:
			printf("请输入欲查询的歌曲的序号：");
			type = 0;
			gets(target);
			i = findRecord(target, type, 0);
			break;
		case 2:
			printf("请输入欲查询的歌曲的歌名：");
			gets(target);
			type = 1;
			i = findRecord(target, type, 0);
			break;
		case 3:
			printf("请输入欲查询的歌曲的歌手：");
			gets(target);
			type = 2;
			i = findRecord(target, type, 0);
			break;
		case 4:
			for (j = 0; j < MUN_LANGUAGE; j++)
			{
				printf("%d.%s\t", j + 1, language[j]);
			}
			printf("\n");
			printf("请输入欲查询的歌曲的语种的序号：");
			gets(s);
      			cn2 = atoi(s);
			if (cn2 < 1 || cn2 > 5) {
				printf("\n 输入错误，默认设为空\n");
				cn2 = 0;
			}
			switch (cn2)
			{
			case 1:
				strcpy(target, "华语");
				break;
			case 2:
				strcpy(target, "粤语");
				break;
			case 3:
				strcpy(target, "英语");
				break;
			case 4:
				strcpy(target, "日语");
				break;
			case 5:
				strcpy(target, "韩语");
				break;
			default:        
				strcpy(target, " ");
				break;
			}
			type = 3;
			i = findRecord(target, type, 0);
			break;
		}

		//打印查询到的歌曲的信息
		showTable();
	
		count = 0;
		while (i != -1) {
			count++;
			printf("%s\t%s\t\t%s\t\t%s\n", records[i].id, records[i].name, records[i].singer, records[i].language);
			i = findRecord(target, type, i + 1);
		}

		if (count == 0)
			printf("没有符合条件的歌曲！\n");
		else
			printf("一共找到了%d首歌曲的信息\n\n", count);
	}
}

/*
	删除指定的记录
*/
void removeRecord(void) {
	char str[5];
	char target[20];
	int type;
	int i, j;
	int cn;

	if (numMusic == 0) {
		printf("没有可供删除的记录");
		return;
	}

	while (1) {
		printf("请输入如何找到欲删除的记录的方式：");
		printf("(直接输入回车则结束移除操作)\n");
		printf("1.按序号\n");
		printf("2.按歌名\n");
		printf("请输入：");
		gets(str);
		cn = atoi(str);
		if (strlen(str) == 0) break;

		if (cn < 1 || cn > 2) {
			printf("\n 输入错误,回到首页\n");
			break;
		}

		if (cn == 1) {
			printf("请输入该歌曲的序号：");
			gets(target);
			type = 0;
		}
		else {
			printf("请输入该歌曲的歌名：");
			gets(target);
			type = 1;
		}

		i = findRecord(target, type, 0);
		if (i == -1) printf("没有符合条件的歌曲！\n");

		while (i != -1) {
			showTable();
			printf("%s\t%s\t\t%s\t\t%s\n", records[i].id, records[i].name, records[i].singer, records[i].language);
			printf("确定要删除这个歌曲的信息吗？(y/N)");
			gets(str);
			if (str[0] == 'y' || str[0] == 'Y') {
				numMusic--;

				//将后面的记录前移
				for (j = i; j < numMusic; j++) {
					copyRecord(&records[j + 1], &records[j]);
				}
			}
			//取下一个符合条件的记录
			i = findRecord(target, type, i + 1);
		}
		printf("删除成功！\n");
	}
	savedTag = 1;
}

/*
	将src指向的一条记录复制给dest指向的记录
*/
void copyRecord(MusicInfo* src, MusicInfo* dest) {
	strcpy(dest->id, src->id);
	strcpy(dest->name, src->name);
	strcpy(dest->singer, src->singer);
	strcpy(dest->language, src->language);
}	

/*
	修改指定学生的信息
*/
void modifyRecord(void) {
	char str[5];
	char target[20];
	int type;
	int i, j;
	int cn1, cn2 = 0;

	if (numMusic == 0) {
		printf("没有可供修改的记录");
		return;
	}

	while (1)
	{
		printf("请输入如何找到欲修改的记录的方式：");
		printf("(直接输入回车则结束移除操作)\n");
		printf("1.按序号\n");
		printf("2.按歌名\n");
		printf("请输入：");
		gets(str);
		cn1 = atoi(str);
		if (strlen(str) == 0) break;

		if (cn1 < 1 || cn1>2) {
			printf("\n 输入错误,回到首页\n");
			break;
		}

		if (cn1 == 1) {
			printf("请输入该歌曲的序号：");
			gets(target);
			type = 0;
		}
		else {
			printf("请输入该歌曲的歌名：");
			gets(target);
			type = 1;
		}

		i = findRecord(target, type, 0);
		if (i == -1) printf("没有符合条件的学生！\n");

		while (i != -1) {
			showTable();
			printf("%s\t%s\t\t%s\t\t%s\n", records[i].id, records[i].name, records[i].singer, records[i].language);
			printf("确定要修改这个学生的信息吗？(y/N)");
			gets(str);
			if (str[0] == 'y' || str[0] == 'Y') {
				printf("下面请重新输入该歌曲的信息：\n");
				printf("请输入歌名：");
				gets(records[i].name);
				printf("请输入歌手：");
				gets(records[i].singer);
				printf("请输入语种：\n");
				for (j = 0; j < MUN_LANGUAGE; j++)
				{
					printf("%d.%s\t", j + 1, language[j]);
				}
				printf("\n");
				printf("请输入语种的序号：");
				gets(str);
				cn2 = atoi(str);
				switch (cn2)
				{
				case 1:
					strcpy(records[i].language, "华语");
					break;
				case 2:
					strcpy(records[i].language, "粤语");
					break;
				case 3:
					strcpy(records[i].language, "英语");
					break;
				case 4:
					strcpy(records[i].language, "日语");
					break;
				case 5:
					strcpy(records[i].language, "韩语");
					break;
				default:
					printf("未输入正确的语种的序号，默认设为空\n");
					strcpy(records[i].language, " ");
					break;
				}
				printf("修改成功！\n");
			}
			//可能有重名的歌曲，继续查找
			i = findRecord(target, type, i + 1);
		}
	}
	savedTag = 1;
}

