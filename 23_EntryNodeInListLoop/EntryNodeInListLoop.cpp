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

// 面试题23：链表中环的入口结点
// 题目：一个链表中包含环，如何找出环的入口结点？例如，在图3.8的链表中，
// 环的入口结点是结点3。

#include <cstdio>
#include <stdlib.h>
#include "../Utilities/list.h"

////鲁棒性：是否存在环
//ListNode* MeetingNode(ListNode* pHead)
//{
//	//1.鲁棒性1：如果为空链表，返回nullptr
//    if(pHead == nullptr)
//        return nullptr;
//
//	//2.slow节点走一步。
//    ListNode* pSlow = pHead->m_pNext;
//	//3.鲁棒性2：如果只有一个节点，返回nullptr
//    if(pSlow == nullptr)
//        return nullptr;
//	//4.fast节点走两步
//    ListNode* pFast = pSlow->m_pNext;
//	//5.while循环条件：fast和slow都不为nullptr时
//    while(pFast != nullptr && pSlow != nullptr)
//    {
//		//5.1 如果fast和slow相遇了，返回这个节点，这个节点一定在环中。
//        if(pFast == pSlow)
//            return pFast;
//
//		//5.2 slow 走一步
//        pSlow = pSlow->m_pNext;
//
//		//5.3 fast 走两步
//        pFast = pFast->m_pNext;
//		//5.3.1 鲁棒性3：如果fast走的第一步不为nullptr，就继续走一步
//        if(pFast != nullptr)
//            pFast = pFast->m_pNext;
//    }
//
//	//6.如果没有遇到就返回nullptr
//    return nullptr;
//}
//
//
//ListNode* EntryNodeOfLoop(ListNode* pHead)
//{
//    ListNode* meetingNode = MeetingNode(pHead);
//    if(meetingNode == nullptr)
//        return nullptr;
//
//    // 得到环中结点的数目
//    int nodesInLoop = 1;
//    ListNode* pNode1 = meetingNode;
//    while(pNode1->m_pNext != meetingNode)
//    {
//        pNode1 = pNode1->m_pNext;
//        ++nodesInLoop;
//    }
//
//    // 先移动pNode1，次数为环中结点的数目
//    pNode1 = pHead;
//    for(int i = 0; i < nodesInLoop; ++i)
//        pNode1 = pNode1->m_pNext;
//
//    // 再移动pNode1和pNode2
//    ListNode* pNode2 = pHead;
//    while(pNode1 != pNode2)
//    {
//        pNode1 = pNode1->m_pNext;
//        pNode2 = pNode2->m_pNext;
//    }
//
//    return pNode1;
//}

//鲁棒性：是否存在环
ListNode* MeetingNode(ListNode* pHead)
{
	//1.鲁棒性1：头节点为空，返回空
	if (!pHead)
		return nullptr;

	//2.slow先走一步，注意鲁棒性2： 如果slow不存在返回nullptr
	ListNode* slow = pHead->m_pNext;
	if (!slow)
		return nullptr;

	//3.fast走两步
	ListNode* fast = slow->m_pNext;

	//4.如果fast和slow都存在的情况
	while (fast&& slow)
	{
		//4.1 如果两个指针相遇了，返回相遇节点
		if (fast == slow)
			return fast;

		//4.2 slow先走到下一步
		slow = slow->m_pNext;

		//4.3 fast要走两步，先走第一步，在测试鲁棒性之后，走第二部
		fast = fast->m_pNext;
		if (fast)
		{
			fast = fast->m_pNext; 
		}
	}

	//5.如果fast和slow都没有相遇，返回nullptr
	return nullptr;
}

//找到入口
ListNode* EntryNodeOfLoop(ListNode* pHead)
{
	//1.鲁棒性检查：判断是否含有环,如果没有，返回空
	ListNode* MeetNode = MeetingNode(pHead);
	if (!MeetNode)
		return nullptr;

	//2.设置环内节点计数参数，从1开始
	int count = 1;

	//3.新建一个指针从相遇节点的下一个走
	ListNode* Node = MeetNode->m_pNext;
	
	//4.边走边计数，走到遇到自己为止，
	while (Node&& (Node != MeetNode))
	{
		Node = Node->m_pNext;
		count++;
	}
	Node = nullptr;

	//5.先让fast走n步
	ListNode* fast= pHead;
	for(int i=0;i<count;i++)
	{ 
		fast= fast->m_pNext; 
	}

	//6.slow开始走
	ListNode* slow = pHead;
	while (slow&&fast)
	{
		if (slow == fast)
			return fast;

		slow = slow->m_pNext;
		fast = fast->m_pNext;
	}



}

// ==================== Test Code ====================
void Test(char* testName, ListNode* pHead, ListNode* entryNode)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    if(EntryNodeOfLoop(pHead) == entryNode)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}

// A list has a node, without a loop
void Test1()
{
    ListNode* pNode1 = CreateListNode(1);

    Test("Test1", pNode1, nullptr);

    DestroyList(pNode1);
}

// A list has a node, with a loop
void Test2()
{
    ListNode* pNode1 = CreateListNode(1);
    ConnectListNodes(pNode1, pNode1);

    Test("Test2", pNode1, pNode1);

    delete pNode1;
    pNode1 = nullptr;
}

// A list has multiple nodes, with a loop 
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
    ConnectListNodes(pNode5, pNode3);

    Test("Test3", pNode1, pNode3);

    delete pNode1;
    pNode1 = nullptr;
    delete pNode2;
    pNode2 = nullptr;
    delete pNode3;
    pNode3 = nullptr;
    delete pNode4;
    pNode4 = nullptr;
    delete pNode5;
    pNode5 = nullptr;
}

// A list has multiple nodes, with a loop 
void Test4()
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
    ConnectListNodes(pNode5, pNode1);

    Test("Test4", pNode1, pNode1);

    delete pNode1;
    pNode1 = nullptr;
    delete pNode2;
    pNode2 = nullptr;
    delete pNode3;
    pNode3 = nullptr;
    delete pNode4;
    pNode4 = nullptr;
    delete pNode5;
    pNode5 = nullptr;
}

// A list has multiple nodes, with a loop 
void Test5()
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
    ConnectListNodes(pNode5, pNode5);

    Test("Test5", pNode1, pNode5);

    delete pNode1;
    pNode1 = nullptr;
    delete pNode2;
    pNode2 = nullptr;
    delete pNode3;
    pNode3 = nullptr;
    delete pNode4;
    pNode4 = nullptr;
    delete pNode5;
    pNode5 = nullptr;
}

// A list has multiple nodes, without a loop 
void Test6()
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

    Test("Test6", pNode1, nullptr);

    DestroyList(pNode1);
}

// Empty list
void Test7()
{
    Test("Test7", nullptr, nullptr);
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();
	system("pause");
    return 0;
}
