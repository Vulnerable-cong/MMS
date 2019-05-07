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
			(targetType == 1 && strcmp(target, records[i].name) == 0) ||
			(targetType == 2 && strcmp(target, records[i].singer) == 0) ||
			(targetType == 3 && strcmp(target, records[i].language) == 0))
			return i;
	}
	return -1;
}

/*
	��ѯָ����������Ϣ
	���԰�����š����������֡���������ѯ
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
		printf("û�пɹ���ѯ�ļ�¼");
		return;
	}
	while (1) {
		printf("�������ѯ�ķ�ʽ��(ֱ������س��������ѯ)\n");
		printf("1.�����\n");
		printf("2.������\n");
		printf("3.������\n");
		printf("4.������\n");
		printf("�����룺");

		gets(str);
		cn1 = atoi(str);
		if (cn1 < 1 || cn1>4) {
			printf("\n �������,�ص���ҳ\n");
			break;
		}
		if (cn1 == 0)
			break;
		switch (cn1) {
		case 1:
			printf("����������ѯ�ĸ�������ţ�");
			type = 0;
			gets(target);
			i = findRecord(target, type, 0);
			break;
		case 2:
			printf("����������ѯ�ĸ����ĸ�����");
			gets(target);
			type = 1;
			i = findRecord(target, type, 0);
			break;
		case 3:
			printf("����������ѯ�ĸ����ĸ��֣�");
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
			printf("����������ѯ�ĸ��������ֵ���ţ�");
			gets(s);
      			cn2 = atoi(s);
			if (cn2 < 1 || cn2 > 5) {
				printf("\n �������Ĭ����Ϊ��\n");
				cn2 = 0;
			}
			switch (cn2)
			{
			case 1:
				strcpy(target, "����");
				break;
			case 2:
				strcpy(target, "����");
				break;
			case 3:
				strcpy(target, "Ӣ��");
				break;
			case 4:
				strcpy(target, "����");
				break;
			case 5:
				strcpy(target, "����");
				break;
			default:        
				strcpy(target, " ");
				break;
			}
			type = 3;
			i = findRecord(target, type, 0);
			break;
		}

		//��ӡ��ѯ���ĸ�������Ϣ
		showTable();
	
		count = 0;
		while (i != -1) {
			count++;
			printf("%s\t%s\t\t%s\t\t%s\n", records[i].id, records[i].name, records[i].singer, records[i].language);
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
	int cn;

	if (numMusic == 0) {
		printf("û�пɹ�ɾ���ļ�¼");
		return;
	}

	while (1) {
		printf("����������ҵ���ɾ���ļ�¼�ķ�ʽ��");
		printf("(ֱ������س�������Ƴ�����)\n");
		printf("1.�����\n");
		printf("2.������\n");
		printf("�����룺");
		gets(str);
		cn = atoi(str);
		if (strlen(str) == 0) break;

		if (cn < 1 || cn > 2) {
			printf("\n �������,�ص���ҳ\n");
			break;
		}

		if (cn == 1) {
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
	int i, j;
	int cn1, cn2 = 0;

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
		cn1 = atoi(str);
		if (strlen(str) == 0) break;

		if (cn1 < 1 || cn1>2) {
			printf("\n �������,�ص���ҳ\n");
			break;
		}

		if (cn1 == 1) {
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
				cn2 = atoi(str);
				switch (cn2)
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

