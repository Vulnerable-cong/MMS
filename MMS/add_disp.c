#include "music.h"

/*
	�����ͷ
*/
void showTable(void) {
	printf("���\t����\t\t����\t\t����\n");
}

/*
	��ʾ���и���
*/
void display(void) {
	int i;
	if (numMusic == 0) {
		printf("û�пɹ���ʾ�ļ�¼��");
		return;
	}
	showTable();
	for (i = 0; i < numMusic; i++) {
		//��ӡ������Ϣ
		printf("%s\t%s\t\t%s\t\t%s\n", records[i].id, records[i].name, records[i].singer, records[i].language);

		//��ӡ��20����¼��ͣ����
		if (i % 19 == 0 && i!=0) {
			printf("������һ�ַ������...");
			_getch();		//�ӿ���̨��ȡһ���ַ���������ʾ����Ļ�ϣ����û�����ĳ���ַ�ʱ�������Զ���ȡ�����谴�س�
			printf("\n\n");
			showTable();
		}
	}
}

/*
	�����¼�¼���ڵ�ǰ��ĩβ�����µ���Ϣ
	�����records�н���¼�µ���Ϣ����������С��������������������ռ�
*/
void addRecord(void) {
	char str[10];
	int j;
	int cn = 0;
	char id[10];
	if (numMusic == 0)
		printf("ԭ��û�м�¼�����ڽ����¸赥\n");
	else
		printf("�����ڵ�ǰ���ĩβ�����µ���Ϣ\n");
	while(1)
	{
		printf("����Ҫ���һ�׸�����Ϣ��ȷ���𣿣�Y/n��");
		gets(str);
		if (str[0] == 'n' || str[0] == 'N')		//��������µ���Ϣ
			break;
		else if (numMusic >= arraySize)		//���ڵ�����ռ䲻�㣬��Ҫ��������ռ�
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
			printf("���������:");
			gets(records[numMusic].name);
			printf("���������:");
			gets(records[numMusic].singer);
			printf("��ѡ������\n");
			for (j = 0; j < MUN_LANGUAGE; j++)
			{
				printf("%d.%s\t", j + 1, language[j]);
			}
			printf("\n");
			printf("���������ֵ���ţ�");
			gets(str);
			cn = atoi(str);
			switch (cn)
			{
			case 1:
				strcpy(records[numMusic].language, "����");
				break;
			case 2:
				strcpy(records[numMusic].language, "����");
				break;
			case 3:
				strcpy(records[numMusic].language, "Ӣ��");
				break;
			case 4:
				strcpy(records[numMusic].language, "����");
				break;
			case 5:
				strcpy(records[numMusic].language, "����");
				break;
			default:
				printf("δ������ȷ�����ֵ���ţ�Ĭ����Ϊ��\n");
				strcpy(records[numMusic].language, " ");
				break;
			}
			numMusic++;
			printf("������ӳɹ���\n");
			printf("\n");
		}
	}
	printf("����һ����%d����Ϣ\n", numMusic);
	printf("\n");
	savedTag = 1;
}