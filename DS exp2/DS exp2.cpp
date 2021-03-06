// DS exp2.cpp: 定义控制台应用程序的入口点。
//

# include <stdio.h>
# include <malloc.h>
# include <iostream>
using namespace std;

//多项式节点
typedef struct link
{
	float coe;  //系数
	int exp;   //指数
	struct link * next;  //指针域

}LINK, *pLINK;

//创建链表
pLINK creat_link()
{
	pLINK pHead = (pLINK)malloc(sizeof(link)); //创建头结点
	pHead->next = NULL;
	pLINK temp = pHead;
	int i, e, len;
	float c;
	printf("多项式的项数(len): ");
	scanf("%d", &len);

	//如果项数不为0，进行录入系数和指数
	if (len > 0) {
		for (i = 0; i < len; i++) {
			printf("输入第%d项的系数(coe),指数(exp):\n", i + 1);
			scanf("%f%d", &c, &e);
			pLINK pNew = (pLINK)malloc(sizeof(link));
			pNew->coe = c;
			pNew->exp = e;
			pNew->next = NULL;
			temp->next = pNew;
			temp = temp->next;
		}
	}
	//如果项数为0，头节点指向NULL
	else if (len == 0) {
		temp->next = NULL;
	}

	//冒泡排序使多项式降次排列
	for (int i = 0; i < len - 1; i++) {
		pLINK temp_b = pHead->next;
		for (int j = 0; j < len - 1 - i; j++) {
			if (temp_b->exp < temp_b->next->exp) {
				float temp_coe = temp_b->next->coe;
				int temp_exp = temp_b->next->exp;
				temp_b->next->coe = temp_b->coe;
				temp_b->next->exp = temp_b->exp;
				temp_b->coe = temp_coe;
				temp_b->exp = temp_exp;
			}
			temp_b = temp_b->next;
		}
	}

	return pHead;
}

//遍历链表并写出算式
void traverse_formula(pLINK pHead)
{
	pLINK p = pHead->next;
	if (pHead->next == NULL) {
		printf("0");
	}
	else {
		for (p = pHead->next; p != NULL; p = p->next) {
			if (p != pHead->next && p->coe > 0) {
				printf("+");  // 当p非首项且指向的系数为正时才输出"+"
			}

			// 系数为1或-1时特殊处理 
			if (p->coe == 1) {
				if (p->exp == 0) {
					printf("1");
				}
			}
			else if (p->coe == -1) {
				printf("-");
			}
			else {
				cout << p->coe;  //使用C++中的 cout 内置对象，控制系数的输出
			}

			// 指数为0或1时特殊处理 
			if (p->exp == 0) {
				printf(" ");
			}
			else if (p->exp == 1) {
				printf("x");
			}
			else {
				if (p->exp < 0) {
					printf("x^(%d)", p->exp);  // 指数小于0时打括号
				}
				else {
					printf("x^%d", p->exp);
				}
			}
		}
	}
	printf("\n\n");
}

//多项式相加
pLINK add(pLINK a, pLINK b)
{
	pLINK plus = (pLINK)malloc(sizeof(link));  //和的头结点
	plus->next = NULL;
	pLINK temp = plus;

	pLINK temp_a = a->next;  //指向多项式的首节点
	pLINK temp_b = b->next;

	//循环遍历多项式A，B
	while (temp_a != NULL && temp_b != NULL) {
		//比较当前两节点的指数

		//当前 A项节点指数 < B项节点指数
		if (temp_a->exp < temp_b->exp) {
			pLINK pNew = (pLINK)malloc(sizeof(link));
			pNew->coe = temp_b->coe;
			pNew->exp = temp_b->exp;
			pNew->next = NULL;
			temp->next = pNew;
			temp = temp->next;

			temp_b = temp_b->next;  //B多项式向后遍历
		}

		//当前 A项节点指数 < B项节点指数
		else if (temp_a->exp > temp_b->exp) {
			pLINK pNew = (pLINK)malloc(sizeof(link));
			pNew->coe = temp_a->coe;
			pNew->exp = temp_a->exp;
			pNew->next = NULL;
			temp->next = pNew;
			temp = temp->next;

			temp_a = temp_a->next;  //A多项式向后遍历
		}

		//如果两节点的指数相等
		else {
			//当前指数的系数和不为0
			if ((temp_a->coe + temp_b->coe) != 0) {
				pLINK pNew = (pLINK)malloc(sizeof(link));
				pNew->coe = temp_a->coe + temp_b->coe;
				pNew->exp = temp_a->exp;
				pNew->next = NULL;
				temp->next = pNew;
				temp = temp->next;
			}

			//A,B都向后遍历
			temp_a = temp_a->next;
			temp_b = temp_b->next;
		}
	}

	//插入剩余段
	if (temp_a != NULL) {
		temp->next = temp_a;
	}
	if (temp_b != NULL) {
		temp->next = temp_b;
	}

	return plus;
}

int main()
{
	//用链表结构，创建两个多项式
	pLINK a = creat_link();
	traverse_formula(a);
	pLINK b = creat_link();
	traverse_formula(b);

	//求两个多项式的和
	pLINK plus = add(a, b);
	printf("下面是多项式和:\n\n");
	traverse_formula(plus);

	return 0;
}
