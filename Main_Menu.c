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
			printf("\n\n\n\n\n\n\n\t\t\t\t\t售票员您好,请选择\n\n"); 
			printf("\t\t\t\t\t  1.剧目信息\n");
			printf("\t\t\t\t\t  2.售票与退票\n");
			printf("\t\t\t\t\t  3.查询\n");
			printf("\t\t\t\t\t  4.销售统计与分析\n");
			printf("\t\t\t\t\t  5.修改密码\n");
			printf("\t\t\t\t\t  6.退出\n");
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
			printf("\n\n\n\n\n\n\n\t\t\t\t\t经理您好,请选择\n\n"); 
			printf("\t\t\t\t\t  1.剧目管理\n");
			printf("\t\t\t\t\t  2.查询\n");
			printf("\t\t\t\t\t  3.销售统计与分析\n");
			printf("\t\t\t\t\t  4.修改密码\n");
			printf("\t\t\t\t\t  5.退出\n");
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
			printf("\n\n\n\n\n\n\n\t\t\t\t\t管理员您好,请选择\n\n"); 
			printf("\t\t\t\t\t  1.演出厅管理\n");
			printf("\t\t\t\t\t  2.账户管理\n");
			printf("\t\t\t\t\t  3.退出\n");
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
			printf("\n\n\n\n\n\n\n\t\t\t\t\t您好,请选择\n\n"); 
			printf("\t\t\t\t\t  1.剧目查询\n");
			printf("\t\t\t\t\t  2.查询\n");
			printf("\t\t\t\t\t  3.退出\n");
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
