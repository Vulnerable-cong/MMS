#include "music.h"

/*
	�ļ��洢��������
	���������records��������ָ���ļ�
*/
int saveRecords() {
	FILE* fp;
	char fname[30];

	if (numMusic == 0) {
		printf("û�м�¼�ɴ棡");
		return -1;
	}
	
	printf("������Ҫ������ļ���(ֱ�ӻس�ѡ���ļ� music_info );");
	gets(fname);
	if (strlen(fname) == 0)
		strcpy(fname, "music_info");

	if ((fp = fopen(fname, "wb")) == NULL) {
		printf("���ܴ����ļ���\n");
		return -1;
	}

	printf("\n���ļ�...\n");
	fwrite(records, sizeof(MusicInfo) * numMusic, 1, fp);
	fclose(fp);
	printf("%d����¼�Ѿ������ļ��������������\n", numMusic);
	savedTag = 0;		//�����Ƿ��ѱ���ı��
	return 0;
}

/*
	�ļ���ȡ��������
	�����records��Ϊ��ָ���ļ��ж�ȡ���ļ�¼
*/
int loadRecords(void) {
	FILE* fp;
	char fname[30];
	char str[5];

	if (numMusic != 0 && savedTag == 0) {
		printf("��ѡ������Ҫ�������м�¼(Y),����Ҫ����ȡ�ļ�¼��ӵ����м�¼֮��(n)? \n");
		printf("ֱ�ӻس��򸲸����м�¼ \n");
		gets(str);

		if (str[0] == 'n' || str[0] == 'N') {
			//����ȡ�ļ�¼��ӵ����м�¼֮��
			savedTag = 1;
		}
		else {
			if (savedTag == 1) {
				//�������м�¼
				printf("��ȡ�ļ��������ԭ���ļ�¼���Ƿ񱣴�ԭ���ļ�¼��(Y/n)");
				gets(str);
				if (str[0] != 'n' && str[0] != 'N')
					saveRecords();
			}
			numMusic = 0;
		}
	}

	printf("������Ҫ��ȡ���ļ���(ֱ�ӻس�ѡ���ļ� music_info ): ");
	gets(fname);
	if (strlen(fname) == 0)
		strcpy(fname, "music_info");

	if ((fp = fopen(fname, "rb")) == NULL) {
		printf("�򲻿��ļ���������ѡ��\n");
		return -1;
	}

	printf("\nȡ�ļ�...\n");
	while (!feof(fp)) {
		//���ڵ�����ռ䲻�㣬��Ҫ��������ռ�
		if (numMusic >= arraySize)
		{
			records = realloc(records, (arraySize + INCR_SIZE) * sizeof(MusicInfo));
			if (records == NULL) {
				printf("memory failed!");
				exit(-1);
			}
			arraySize = arraySize + INCR_SIZE;
		}

		if (fread(&records[numMusic], sizeof(MusicInfo), 1, fp) != 1) break;
		numMusic++;
	}

	fclose(fp);
	printf("���ڹ���%d����¼��", numMusic);
	return 0;
}