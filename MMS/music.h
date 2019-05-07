#ifndef H_MUSIC_HH
#define H_MUSIC_HH

#pragma warning( disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define INITIAL_SIZE 100	//�����ʼ��С
#define INCR_SIZE 50		//����ÿ�����ӵĴ�С
#define MUN_LANGUAGE 5		//����������������Ӣ�������

struct music_info
{
	char id[10];		//���
	char name[20];		//����
	char singer[20];	//����
	char language[20];	//����
};
typedef struct music_info MusicInfo;

extern int numMusic;				//��¼�ĸ�����
extern MusicInfo* records;		//��¼������Ϣ������
extern char savedTag;			//��Ϣ�Ƿ��ѱ���ı�־��0Ϊ�ѱ��棬1Ϊδ����
extern int arraySize;			//�����С
extern char* language[];		//����

void handle_menu(void);										//�˵�������
int menu_select(void);										//�˵�ѡ����
void addRecord(void);										//��ǰ���ĩβ�����µ���Ϣ
void modifyRecord(void);									//�޸�ָ����������Ϣ
void display(void);											//��ʾ���еĸ�����Ϣ
void queryInfo(void);										//��ѯָ����������Ϣ
void removeRecord(void);									//ɾ��ָ���ļ�¼
int saveRecords(void);										//�ļ��洢��������
int loadRecords(void);										//�ļ���ȡ��������
void quit(void);											//�˳�
void showTable(void);										//�����ͷ
int findRecord(char* target, int targetType, int from);		//����ָ����¼
void copyRecord(MusicInfo* src, MusicInfo* dest);			//��srcָ���һ����¼���Ƹ�destָ��ļ�¼

#endif // !H_MUSIC_HH

