#include "music.h"

/*
	��ʼ��
*/
int numMusic = 0;												//��¼�ĸ�����
MusicInfo* records = NULL;										//��¼������Ϣ������
char savedTag = 0;												//��Ϣ�Ƿ��ѱ���ı�־��1Ϊδ���棬0Ϊ�ѱ���
int arraySize;													//�����С
char* language[] = { "����","����","Ӣ��","����","����" };		//����
int id = 1;														//ID

/*
	������
*/
int main() {
	//��ʼ������
	records = (MusicInfo*)malloc(sizeof(MusicInfo) * INITIAL_SIZE);
	if (records == NULL) {
		printf("memory fail!");
		exit(-1);
	}
	arraySize = INITIAL_SIZE;

	printf("\n");
	printf("\t************************\n");
	printf("\t        ����һ��        \n");
	printf("\t      �赥�������      \n");
	printf("\t ���Զ�������Ϣ���й��� \n");
	printf("\t    ��ӭʹ�ù������    \n");
	printf("\t************************\n");
	printf("\n");
	
	handle_menu();
}

/*
	�˵�������
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
	�˵�ѡ����
*/
int menu_select() {
	char s[2];
	int cn = 0;
	printf("\n");
	printf("\t1.���Ӹ������赥\n");
	printf("\t2.�޸ĸ赥����\n");
	printf("\t3.��ʾ�赥����\n");
	printf("\t4.��ѯ�赥����\n");
	printf("\t5.ɾ���赥����\n");
	printf("\t6.����赥����¼�ļ�\n");
	printf("\t7.�Ӽ�¼�ļ���ȡ�赥\n");
	printf("\t8.��������\n");
	printf("\n\t������ֶ�Ӧ����ѡ����ѡ1-8��");

	for ( ; ; ) {
		gets(s);		//��������Ϊ�ַ�������(�����û������ּ�������ĸ��)
		cn = atoi(s);	//�������յ��ַ���ת����ֵ
		if (cn < 1 || cn>8) printf("\n\t �����������ѡ1-8��");
		else break;
	}
	return cn;
}

/*
	�������У��˳�
*/
void quit(void) {
	char str[5];
	if (savedTag == 1)
	{
		printf("�Ƿ񱣴�ԭ���ļ�¼��(Y/n)");
		gets(str);
		if (str[0] != 'n' && str[0] != 'N')
			saveRecords();
	}
	free(records);		//�ͷ�������ڴ�ռ�
	exit(0);
}

