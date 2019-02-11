/*******************************************************************
Copyright(c) 2016, Harry He
All rights reserved.

Distributed under the BSD license.
(See accompanying file LICENSE.txt at
https://github.com/zhedahht/CodingInterviewChinese2/blob/master/LICENSE.txt)
*******************************************************************/

//==================================================================
// 《剑指Offer——名企面试官精讲典型编程题》代码
// 作者：何海涛
//==================================================================

// 面试题18（一）：在O(1)时间删除链表结点
// 题目：给定单向链表的头指针和一个结点指针，定义一个函数在O(1)时间删除该
// 结点。

#include <cstdio>
#include <stdlib.h>
#include "..\Utilities\List.h"

//void DeleteNode(ListNode** pListHead, ListNode* pToBeDeleted)
//{
//    if(!pListHead || !pToBeDeleted)
//        return;
//
//    // 要删除的结点不是尾结点
//    if(pToBeDeleted->m_pNext != nullptr)
//    {
//        ListNode* pNext = pToBeDeleted->m_pNext;
//        pToBeDeleted->m_nValue = pNext->m_nValue;
//        pToBeDeleted->m_pNext = pNext->m_pNext;
// 
//        delete pNext;
//        pNext = nullptr;
//    }
//    // 链表只有一个结点，删除头结点（也是尾结点）
//    else if(*pListHead == pToBeDeleted)
//    {
//        delete pToBeDeleted;
//        pToBeDeleted = nullptr;
//        *pListHead = nullptr;
//    }
//    // 链表中有多个结点，删除尾结点
//    else
//    {
//        ListNode* pNode = *pListHead;
//        while(pNode->m_pNext != pToBeDeleted)
//        {
//            pNode = pNode->m_pNext;            
//        }
// 
//        pNode->m_pNext = nullptr;
//        delete pToBeDeleted;
//        pToBeDeleted = nullptr;
//    }
//}

//已知该节点存在链表中
void DeleteNode(ListNode** pListHead, ListNode* pToBeDeleted)
{
	//1.如果链表头节点或待删除节点为空，返回
	if (!pListHead || !pToBeDeleted)
		return;
	//2.多个节点的链表，前n-1个非尾节点
	if (pToBeDeleted->m_pNext)
	{
		//2.1 pNext：待删除节点J的下个节点K
		ListNode* pNext = pToBeDeleted->m_pNext;
		//2.2 复制值J=K
		pToBeDeleted->m_nValue = pNext->m_nValue;
		//2.3 复制指针J->NEXT=K->NEXT
		pToBeDeleted->m_pNext = pNext->m_pNext;

		//2.4 删去下个节点K(pNext)
		delete pNext;

		//2.5 pNext设为空指针
		pNext = nullptr;

	}

	//3.只有一个节点的链表，删完要将头节点指针设为空
	else if(*pListHead==pToBeDeleted)
	{
		//3.1删除节点
		delete pToBeDeleted; 

		//3.2 释放删除节点的指针
		pToBeDeleted = nullptr;

		//3.3 删除后将头节点设为空指针
		*pListHead = nullptr;

	}
	//4.如果是最后一个尾节点，就用遍历
	else
	{
		//4.1 pNode：遍历指针,从头开始
		ListNode* pNode = *pListHead;
		//4.2 while遍历找到pNode的下一个节点是要删除的节点
		while(pNode->m_pNext == pToBeDeleted)
		{ 
			//4.2.1 指针向后指
			pNode = pNode->m_pNext; 
		}
		//4.3 将pNode的下一个节点设为空
		pNode->m_pNext = nullptr;

		//4.4 删除最后的节点
		delete pToBeDeleted;
		//4.5 释放指针 
		pToBeDeleted = nullptr; 

	}


}

// ====================测试代码====================
void Test(ListNode* pListHead, ListNode* pNode)
{
    printf("The original list is: \n");
    PrintList(pListHead);

    printf("The node to be deleted is: \n");
    PrintListNode(pNode);

    DeleteNode(&pListHead, pNode);
    
    printf("The result list is: \n");
    PrintList(pListHead);
}

// 链表中有多个结点，删除中间的结点
void Test1()
{
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);

    Test(pNode1, pNode3);

    DestroyList(pNode1);
}

// 链表中有多个结点，删除尾结点
void Test2()
{
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);

    Test(pNode1, pNode5);

    DestroyList(pNode1);
}

// 链表中有多个结点，删除头结点
void Test3()
{
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);

    Test(pNode1, pNode1);

    DestroyList(pNode1);
}

// 链表中只有一个结点，删除头结点
void Test4()
{
    ListNode* pNode1 = CreateListNode(1);

    Test(pNode1, pNode1);
}

// 链表为空
void Test5()
{
    Test(nullptr, nullptr);
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
	system("pause");
    return 0;
}

