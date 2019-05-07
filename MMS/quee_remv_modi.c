#include "music.h"
/*
	����ָ���ļ�¼
	������target�������Ҽ�¼��ĳһ����target��ͬ
	targetType������ͨ����һ�������ң�0ΪID��1Ϊ����
	from���ӵ�from����¼��ʼ��
	���أ��ҵ��ļ�¼����ţ����Ҳ����򷵻�-1
*/
int findRecord(char* target, int targetType, int from) {
	int i;
	for (i = from; i < numMusic; i++) {
		if
			((targetType == 0 && strcmp(target, records[i].id) == 0) || 
			(targetType == 1 && strcmp(target, records[i].name) == 0))
			return i;
	}
	return -1;
}

/*
	��ѯָ����������Ϣ
	���԰���ID����������ѯ
*/
void queryInfo(void) {
	char str[5];
	char target[20];
	int type;
	int count;
	int i;
	if (numMusic == 0) {
		printf("û�пɹ���ѯ�ļ�¼");
		return;
	}
	while (1) {
		printf("�������ѯ�ķ�ʽ��(ֱ������س��������ѯ)\n");
		printf("1.��ID\n");
		printf("2.������\n");
		printf("�����룺");
		gets(str);
		if (strlen(str) == 0)
			break;
		if (str[0] == '1') {
			printf("����������ѯ�ĸ�����ID��");
			gets(target);
			type = 0;
		}
		else {
			printf("����������ѯ�ĸ����ĸ�����");
			gets(target);
			type = 1;
		}

		i = findRecord(target, type, 0);

		//��ӡ��ѯ���ĸ�������Ϣ
		showTable();
	
		count = 0;
		while (i != -1) {
			count++;
			printf("%s\t%s\t%s\t%s\n", records[i].id, records[i].name, records[i].singer, records[i].language);
			i = findRecord(target, type, i + 1);
		}

		if (count == 0)
			printf("û�з��������ĸ�����\n");
		else
			printf("һ���ҵ���%d�׸�������Ϣ\n\n", count);
	}
}

/*
	ɾ��ָ���ļ�¼
*/
void removeRecord(void) {
	char str[5];
	char target[20];
	int type;
	int i, j;

	if (numMusic == 0) {
		printf("û�пɹ�ɾ���ļ�¼");
		return;
	}

	while (1) {
		printf("����������ҵ���ɾ���ļ�¼�ķ�ʽ��");
		printf("(ֱ������س�������Ƴ�����)\n");
		printf("1.��ID\n");
		printf("2.������\n");
		printf("�����룺");
		gets(str);
		if (strlen(str) == 0) break;

		if (str[0] == '1') {
			printf("������ø�����ID��");
			gets(target);
			type = 0;
		}
		else {
			printf("������ø����ĸ�����");
			gets(target);
			type = 1;
		}

		i = findRecord(target, type, 0);
		if (i == -1) printf("û�з��������ĸ�����\n");

		while (i != -1) {
			showTable();
			printf("%s\t%s\t\t%s\t\t%s\n", records[i].id, records[i].name, records[i].singer, records[i].language);
			printf("ȷ��Ҫɾ�������������Ϣ��(y/N)");
			gets(str);
			if (str[0] == 'y' || str[0] == 'Y') {
				numMusic--;

				//������ļ�¼ǰ��
				for (j = i; j < numMusic; j++) {
					copyRecord(&records[j + 1], &records[j]);
				}
			}
			//ȡ��һ�����������ļ�¼
			i = findRecord(target, type, i + 1);
		}
		printf("ɾ���ɹ���\n");
	}
	savedTag = 1;
}

/*
	��srcָ���һ����¼���Ƹ�destָ��ļ�¼
*/
void copyRecord(MusicInfo* src, MusicInfo* dest) {
	strcpy(dest->id, src->id);
	strcpy(dest->name, src->name);
	strcpy(dest->singer, src->singer);
	strcpy(dest->language, src->language);
}	

/*
	�޸�ָ��ѧ������Ϣ
*/
void modifyRecord(void) {
	char str[5];
	char target[20];
	int type;
	int i,j;
	int cn = 0;
	
	if (numMusic == 0) {
		printf("û�пɹ��޸ĵļ�¼");
		return;
	}

	while (1)
	{
		printf("����������ҵ����޸ĵļ�¼�ķ�ʽ��");
		printf("(ֱ������س�������Ƴ�����)\n");
		printf("1.�����\n");
		printf("2.������\n");
		printf("�����룺");
		gets(str);
		if (strlen(str) == 0) break;

		if (str[0] == '1') {
			printf("������ø�������ţ�");
			gets(target);
			type = 0;
		}
		else {
			printf("������ø����ĸ�����");
			gets(target);
			type = 1;
		}

		i = findRecord(target, type, 0);
		if (i == -1) printf("û�з���������ѧ����\n");
		
		while (i != -1) {
			showTable();
			printf("%s\t%s\t\t%s\t\t%s\n", records[i].id, records[i].name, records[i].singer, records[i].language);
			printf("ȷ��Ҫ�޸����ѧ������Ϣ��(y/N)");
			gets(str);
			if (str[0] == 'y' || str[0] == 'Y') {
				printf("��������������ø�������Ϣ��\n");
				printf("�����������");
				gets(records[i].name);
				printf("��������֣�");
				gets(records[i].singer);
				printf("���������֣�\n");
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
					strcpy(records[i].language, "����");
					break;
				case 2:
					strcpy(records[i].language, "����");
					break;
				case 3:
					strcpy(records[i].language, "Ӣ��");
					break;
				case 4:
					strcpy(records[i].language, "����");
					break;
				case 5:
					strcpy(records[i].language, "����");
					break;
				default:
					printf("δ������ȷ�����ֵ���ţ�Ĭ����Ϊ��\n");
					strcpy(records[i].language, " ");
					break;
				}
				printf("�޸ĳɹ���\n");
			}
			//�����������ĸ�������������
			i = findRecord(target, type, i + 1);
		}
	}
	savedTag = 1;
}
