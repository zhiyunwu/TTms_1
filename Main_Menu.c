#include <stdio.h>
#include "Main_Menu.h"
#include "Studio_UI.h"
#include "../Service/Account.h"	
#include "Queries_Menu.h"
#include "Query_Play_UI.h"
#include "Sale_UI.h"
#include "Play_UI.h"
#include "SalesAnalysis_UI.h"
#include "Play_UI.h"	
#include "conio.h"

void Main_Menu(account_t usr)
{

	char choice;
	switch (usr.type)
	{
	case 1:
		do {
            system("cls");
			printf("\n\n\n\n\n\n\n\t\t\t\t\t��ƱԱ����,��ѡ��\n\n"); 
			printf("\t\t\t\t\t  1.��Ŀ��Ϣ\n");
			printf("\t\t\t\t\t  2.��Ʊ����Ʊ\n");
			printf("\t\t\t\t\t  3.��ѯ\n");
			printf("\t\t\t\t\t  4.����ͳ�������\n");
			printf("\t\t\t\t\t  5.�޸�����\n");
			printf("\t\t\t\t\t  6.�˳�\n");
			printf("\n\t\t\t\t\t:");
			choice = getche();
			switch (choice) {
			case '5':
				Account_UI_MgtEntry();
				break;
			case '1':
				Play_UI_MgtEntry(1);
				break;
			case '3':
				Queries_Menu();
				break;
			case '2':
				Sale_UI_MgtEntry();
				break;
			case '4':
				SalesAanalysis_UI_MgtEntry();
				break;
			}
		} while ('6' != choice);
	
		break;
	case 2:
		do {
            system("cls");
			printf("\n\n\n\n\n\n\n\t\t\t\t\t��������,��ѡ��\n\n"); 
			printf("\t\t\t\t\t  1.��Ŀ����\n");
			printf("\t\t\t\t\t  2.��ѯ\n");
			printf("\t\t\t\t\t  3.����ͳ�������\n");
			printf("\t\t\t\t\t  4.�޸�����\n");
			printf("\t\t\t\t\t  5.�˳�\n");
			printf("\n\t\t\t\t\t:");
			choice = getche();
			switch (choice) {
			case '4':
				Account_UI_MgtEntry();
				break;
			case '1':
				Play_UI_MgtEntry(0);
				break;
			case '2':
				Queries_Menu();
				break;
			case '3':
				SalesAanalysis_UI_MgtEntry();
				break;
			}
		} while ('5' != choice);
		break;
	case 9:
		do {
            system("cls");
			printf("\n\n\n\n\n\n\n\t\t\t\t\t����Ա����,��ѡ��\n\n"); 
			printf("\t\t\t\t\t  1.�ݳ�������\n");
			printf("\t\t\t\t\t  2.�˻�����\n");
			printf("\t\t\t\t\t  3.�˳�\n");
			printf("\n\t\t\t\t\t:");
			choice = getche();
			switch (choice) {
			case '1':
				Studio_UI_MgtEntry(usr.type);
				break;
			case '2':
				Account_UI_MgtEntry();
				break;
			}
		} while ('3' != choice);
		break;
	case 0:
	default:
		do {
            system("cls");
			printf("\n\n\n\n\n\n\n\t\t\t\t\t����,��ѡ��\n\n"); 
			printf("\t\t\t\t\t  1.��Ŀ��ѯ\n");
			printf("\t\t\t\t\t  2.��ѯ\n");
			printf("\t\t\t\t\t  3.�˳�\n");
			printf("\n\t\t\t\t\t:");
			choice = getche();
			switch (choice) {
			case '2':
				Queries_Menu();
				break;
			case '1':
				Play_UI_MgtEntry(1);
				break;
			}
		} while ('3' != choice);
		break;
	}
	printf("\n\t\t\t");
	getchar();
}
