
#include "SalesAnalysis_UI.h"
#include "../Common/list.h"
#include "../Common/common.h"
#include "../Service/SalesAnalysis.h"
#include "conio.h"
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

//外部变量gl_CurUser 用于存储登录用户信息
extern account_t gl_CurUser;

//定义分页机制中页面大小为5
static const int SALESANALYSIS_PAGE_SIZE = 5;

//剧院销售排行榜函数,降序显示截止目前剧院电影票房排行榜
void SalesAnalysis_UI_BoxOffice() {
	salesanalysis_list_t  head;
	salesanalysis_node_t  *pos;
	int i;
	char choice;
	//载入数据
	 //paging.totalRecords = Studio_Srv_FetchAll(head);
	
	Pagination_t paging;
	paging.offset = 0;
	
	List_Init(head, salesanalysis_node_t);
	
	Paging_Locate_FirstPage(head, paging);
	//设置分页大小
	paging.totalRecords = Salesanalysis_Srv_StaticSale(head);
	//printf("%d\n",paging.totalRecords);
	SalesAnalysis_Srv_SortBySale(head);
	/*设置分页显示页面大小*/
	paging.pageSize = SALESANALYSIS_PAGE_SIZE;
	do {
		system("cls");
		printf("\n\n\t\t\t                        总票房排名\n");
		printf("\t\t\t=========================================================\n");
		printf("\t\t\t     %10s  %16s  %10s\n", "排名", "影名 ", "票房");
		//显示数据
		int icount = 1;
		for (i = 0, pos = head->next;
			pos != head && i < paging.pageSize; i++)
		{
			printf("\t\t\t     %8d  %18s  %10ld\n",icount, pos->data.name,pos->data.sales);
			pos = pos->next;
			icount++;
		}
		printf("\t\t\t=========================================================\n");
		printf("\n\t\t\t1.显示上一页剧目票房排行信息\n");
		printf("\t\t\t2.显示下一页剧目票房排行信息\n");
		printf("\t\t\t3.退出\n");
		printf("\n\t\t\t：");
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

//显示售票员在给定日期区间的售票情况
void SalesAnalysis_UI_StatSale(int usrID, user_date_t stDate, user_date_t endDate){
	int rtn;
	account_t buf;
	Account_Srv_FetchByID(usrID, &buf);
	rtn = Salesanalysis_Srv_CompSaleVal(usrID, stDate,endDate);
	system("cls");
	printf("\n\n\t\t\t                        售票员信息\n");
	printf("\t\t\t=========================================================\n");
	printf("\t\t\t\t%-10s %-20s %-15s\n", "ID", "用户名", "总数");
	printf("\t\t\t\t%-10d %-20s %-15d\n", buf.id, buf.username, rtn);
	printf("\n\n\t\t\t按任意键返回");
	getch(); 
	return ;
}

//销售分析入口函数，显示菜单，菜单包含"降序显示截止目前剧院电影票房排行榜"，“显示或查询当日售票员售票情况”，
//“查询给定日期区间某售票员售票情况”
void SalesAanalysis_UI_MgtEntry() {
	char choice;
	int id;
	user_date_t stDate;
	user_date_t endDate;
	if (gl_CurUser.type == 2) {
		do
		{
			printf("\n\t\t\t==================================================================\n");
			printf("\t\t\t                        销售数据管理                           \n");
			printf("\t\t\t------------------------------------------------------------------\n");
			printf("\t\t\t[T]总计 |[U]销售区间 | [S]今日销售 |[R]返回");
			printf("\n\t\t\t==================================================================\n");
			printf("\t\t\t请输入您的选择:");
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
				printf("\n\t\t\t请输入cherk的id:");
				scanf("%d", &id);
				printf("\t\t\t请输入开始查询日期:");
				scanf("%d%d%d", &stDate.year, &stDate.month, &stDate.day);
				printf("\t\t\t请输入结束查询日期:");
				scanf("%d%d%d", &endDate.year, &endDate.month, &endDate.day);
				getchar();
				SalesAnalysis_UI_StatSale(id, stDate, endDate);
				break;
			case 's':
			case 'S':
				printf("\n\t\t\t请输入cherk的id:");
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
			printf("\n\n\t\t\t                      销售数据管理\n");
			printf("\t\t\t=========================================================\n");

			printf("\t\t\t    1.总计  2.查询自己  3.查询其他销售员 4.返回");
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
				printf("\n\n\t\t\t要查询的售票员的ID:");
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



