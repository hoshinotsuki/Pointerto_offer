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

// 面试题24：	
// 题目：定义一个函数，输入一个链表的头结点，反转该链表并输出反转后链表的
// 头结点。
#include <stdlib.h>
#include <cstdio>
#include "..\Utilities\List.h"

//ListNode* ReverseList(ListNode* pHead)
//{
//    ListNode* pReversedHead = nullptr;
//    ListNode* pNode = pHead;
//    ListNode* pPrev = nullptr;
//    while(pNode != nullptr)
//    {
//        ListNode* pNext = pNode->m_pNext;
//
//        if(pNext == nullptr)
//            pReversedHead = pNode;
//
//        pNode->m_pNext = pPrev;
//
//        pPrev = pNode;
//        pNode = pNext;
//    }
//
//    return pReversedHead;
//}

//ListNode* ReverseList(ListNode* pHead)
//{
//	//1.鲁棒1：空链表返回nullptr
//	if (!pHead)
//		return nullptr;
//
//	//2.定义三个指针pPre,pNode,pNext和ReverseHead
//	ListNode* pNode = pHead;
//	ListNode* pPre = nullptr;
//	ListNode* pNext = nullptr;
//	ListNode* ReverseHead = nullptr;
//
//	//3.while(pNode)
//	while (pNode)
//	{
//		//3.1 记录下个节点
//		pNext = pNode->m_pNext;
//
//		//3.2 如果是尾节点，更新ReverseHead = pNode;
//		if (!pNext)
//			ReverseHead = pNode;
//
//		//3.3 反转节点
//		pNode->m_pNext = pPre;
//
//		//3.4 更新pPre,pNode
//		pPre = pNode;
//		pNode = pNext;
//
//	}
//
//	//4.返回ReverseHead
//	return ReverseHead;
//}

// //递归
//ListNode* ReverseList(ListNode* pHead) {
//	//如果链表为空或者链表中只有一个元素
//	if (pHead == NULL || pHead->m_pNext == NULL) return pHead;
//
//	//先反转后面的链表，走到链表的末端结点
//	ListNode* pReverseNode = ReverseList(pHead->m_pNext);
//
//	//再将当前节点设置为后面节点的后续节点
//	pHead->m_pNext->m_pNext = pHead;
//
//	//断开当前节点和原链表的后续节点
//	pHead->m_pNext = NULL;
//
//	return pReverseNode;
//}

//递归
ListNode* ReverseList(ListNode* pHead)
{
	//1.结束条件 ： 如果空链表，或者 只有一个节点，返回pHead
	if (!pHead || !(pHead->m_pNext))
		return pHead;

	//2.新链表的头节点 ：递归下一个节点，递归到最后一个节点时，返回最后一个节点
	ListNode* ReverseHead = ReverseList(pHead->m_pNext);

	//3.反转，pNode->next->next=pNode
	pHead->m_pNext->m_pNext = pHead;

	//4.并将原链表的pNode->next设为空，断开
	pHead->m_pNext = nullptr;
	
	//5.返回新链表的头节点
	return ReverseHead;
}

// ====================测试代码====================
ListNode* Test(ListNode* pHead)
 {
    printf("The original list is: \n");
    PrintList(pHead);

    ListNode* pReversedHead = ReverseList(pHead);

    printf("The reversed list is: \n");
    PrintList(pReversedHead);

    return pReversedHead;
}

// 输入的链表有多个结点
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

    ListNode* pReversedHead = Test(pNode1);

    DestroyList(pReversedHead);
}

// 输入的链表只有一个结点
void Test2()
{
    ListNode* pNode1 = CreateListNode(1);

    ListNode* pReversedHead = Test(pNode1);

    DestroyList(pReversedHead);
}

// 输入空链表
void Test3()
{
    Test(nullptr);
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();
	system("pause");
    return 0;
}

