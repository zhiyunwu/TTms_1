
#include "SalesAnalysis_UI.h"
#include "../Common/list.h"
#include "../Common/common.h"
#include "../Service/SalesAnalysis.h"
#include "conio.h"
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

//�ⲿ����gl_CurUser ���ڴ洢��¼�û���Ϣ
extern account_t gl_CurUser;

//�����ҳ������ҳ���СΪ5
static const int SALESANALYSIS_PAGE_SIZE = 5;

//��Ժ�������а���,������ʾ��ֹĿǰ��Ժ��ӰƱ�����а�
void SalesAnalysis_UI_BoxOffice() {
	salesanalysis_list_t  head;
	salesanalysis_node_t  *pos;
	int i;
	char choice;
	//��������
	 //paging.totalRecords = Studio_Srv_FetchAll(head);
	
	Pagination_t paging;
	paging.offset = 0;
	
	List_Init(head, salesanalysis_node_t);
	
	Paging_Locate_FirstPage(head, paging);
	//���÷�ҳ��С
	paging.totalRecords = Salesanalysis_Srv_StaticSale(head);
	//printf("%d\n",paging.totalRecords);
	SalesAnalysis_Srv_SortBySale(head);
	/*���÷�ҳ��ʾҳ���С*/
	paging.pageSize = SALESANALYSIS_PAGE_SIZE;
	do {
		system("cls");
		printf("\n\n\t\t\t                        ��Ʊ������\n");
		printf("\t\t\t=========================================================\n");
		printf("\t\t\t     %10s  %16s  %10s\n", "����", "Ӱ�� ", "Ʊ��");
		//��ʾ����
		int icount = 1;
		for (i = 0, pos = head->next;
			pos != head && i < paging.pageSize; i++)
		{
			printf("\t\t\t     %8d  %18s  %10ld\n",icount, pos->data.name,pos->data.sales);
			pos = pos->next;
			icount++;
		}
		printf("\t\t\t=========================================================\n");
		printf("\n\t\t\t1.��ʾ��һҳ��ĿƱ��������Ϣ\n");
		printf("\t\t\t2.��ʾ��һҳ��ĿƱ��������Ϣ\n");
		printf("\t\t\t3.�˳�\n");
		printf("\n\t\t\t��");
		fflush(stdin);
 		choice = getche();
		switch (choice)
		{
		case '1':
			if (1 < Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, salesanalysis_node_t);
			}
			break;
		case '2':
			if (Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, salesanalysis_node_t);
			}
			break;
		}
	} while (choice != '3');
}

//��ʾ��ƱԱ�ڸ��������������Ʊ���
void SalesAnalysis_UI_StatSale(int usrID, user_date_t stDate, user_date_t endDate){
	int rtn;
	account_t buf;
	Account_Srv_FetchByID(usrID, &buf);
	rtn = Salesanalysis_Srv_CompSaleVal(usrID, stDate,endDate);
	system("cls");
	printf("\n\n\t\t\t                        ��ƱԱ��Ϣ\n");
	printf("\t\t\t=========================================================\n");
	printf("\t\t\t\t%-10s %-20s %-15s\n", "ID", "�û���", "����");
	printf("\t\t\t\t%-10d %-20s %-15d\n", buf.id, buf.username, rtn);
	printf("\n\n\t\t\t�����������");
	getch(); 
	return ;
}

//���۷�����ں�������ʾ�˵����˵�����"������ʾ��ֹĿǰ��Ժ��ӰƱ�����а�"������ʾ���ѯ������ƱԱ��Ʊ�������
//����ѯ������������ĳ��ƱԱ��Ʊ�����
void SalesAanalysis_UI_MgtEntry() {
	char choice;
	int id;
	user_date_t stDate;
	user_date_t endDate;
	if (gl_CurUser.type == 2) {
		do
		{
			printf("\n\t\t\t==================================================================\n");
			printf("\t\t\t                        �������ݹ���                           \n");
			printf("\t\t\t------------------------------------------------------------------\n");
			printf("\t\t\t[T]�ܼ� |[U]�������� | [S]�������� |[R]����");
			printf("\n\t\t\t==================================================================\n");
			printf("\t\t\t����������ѡ��:");
			choice = getche();
			switch (choice)
			{
			case 't':
			case 'T':
				printf("\n");
				SalesAnalysis_UI_BoxOffice();
				break;
			case 'u':
			case 'U':
				printf("\n\t\t\t������cherk��id:");
				scanf("%d", &id);
				printf("\t\t\t�����뿪ʼ��ѯ����:");
				scanf("%d%d%d", &stDate.year, &stDate.month, &stDate.day);
				printf("\t\t\t�����������ѯ����:");
				scanf("%d%d%d", &endDate.year, &endDate.month, &endDate.day);
				getchar();
				SalesAnalysis_UI_StatSale(id, stDate, endDate);
				break;
			case 's':
			case 'S':
				printf("\n\t\t\t������cherk��id:");
				scanf("%d", &id);
				getchar();
				stDate = DateNow();
				endDate = DateNow();
				SalesAnalysis_UI_StatSale(id, stDate, endDate);
				break;
			}
		} while (choice != 'r' && choice != 'R');
	}
	else {
		do
		{
			system("cls");
			printf("\n\n\t\t\t                      �������ݹ���\n");
			printf("\t\t\t=========================================================\n");

			printf("\t\t\t    1.�ܼ�  2.��ѯ�Լ�  3.��ѯ��������Ա 4.����");
			printf("\n\t\t\t=========================================================\n");
			printf("\n\t\t\t:");
			choice = getche();
			switch (choice)
			{
			case '1':
				printf("\n");
				SalesAnalysis_UI_BoxOffice();
				break;
			case '2':
				id = gl_CurUser.id;
				stDate = DateNow();
				endDate = DateNow();
                //printf("%d-%d-%d\n",stDate.year,stDate.month,stDate.day);
				SalesAnalysis_UI_StatSale(id, stDate, endDate);
				break;
			case '3':
				printf("\n\n\t\t\tҪ��ѯ����ƱԱ��ID:");
				scanf("%d",&id);
				getchar();
				stDate = DateNow();
				endDate = DateNow();
				SalesAnalysis_UI_StatSale(id, stDate, endDate);
				break;
			}
		} while (choice != '4');

	}
}



