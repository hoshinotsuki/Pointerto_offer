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

// 面试题18（二）：删除链表中重复的结点
// 题目：在一个排序的链表中，如何删除重复的结点？例如，在图3.4（a）中重复
// 结点被删除之后，链表如图3.4（b）所示。

#include <cstdio>
#include <stdlib.h>
#include "../Utilities/list.h" 

//void DeleteDuplication(ListNode** pHead)
//{
//    if(pHead == nullptr || *pHead == nullptr)
//        return;
//
//    ListNode* pPreNode = nullptr;
//    ListNode* pNode = *pHead;
//    while(pNode != nullptr)
//    {
//        ListNode *pNext = pNode->m_pNext;
//        bool needDelete = false;
//        if(pNext != nullptr && pNext->m_nValue == pNode->m_nValue)
//            needDelete = true;
//
//        if(!needDelete)
//        {
//            pPreNode = pNode;
//            pNode = pNode->m_pNext;
//        }
//        else
//        {
//            int value = pNode->m_nValue;
//            ListNode* pToBeDel = pNode;
//            while(pToBeDel != nullptr && pToBeDel->m_nValue == value)
//            {
//                pNext = pToBeDel->m_pNext;
//
//                delete pToBeDel;
//                pToBeDel = nullptr;
//
//                pToBeDel = pNext;
//            }
//
//            if(pPreNode == nullptr)
//                *pHead = pNext;
//            else
//                pPreNode->m_pNext = pNext;
//            pNode = pNext;
//        }
//    }
//}

//函数的参数:ListNode** pHead。
//因为头节点可能重复，会被删除，所以不用ListNode* pHead
void DeleteDuplication(ListNode** pHead) 
{
	//1.如果是空链表或头节点为空，返回 
	if (!pHead || !*pHead) 
		return;
	 
	//2.ListNode* pNode:初始化指向当前头节点*pHead
	ListNode* pNode = *pHead;
	 
	//3.ListNode* pPreNode:指向上个节点,初始化为空
	ListNode* pPreNode = nullptr;

	//4.循环遍历
	while (pNode)
	{
		//4.1.新建一个节点pNext，指向下个节点
		ListNode* pNext = pNode->m_pNext;

		//4.2 设置标记：pNode节点是否需要删除
		bool needDetele = false;

		//4.3 如果下个节点pNext不为空，且pNode节点值和下个节点pNext的值相同，pNode节点就需要删除
		if (pNext!=nullptr && pNext->m_nValue == pNode->m_nValue)
			needDetele = true;
		   
		//4.4 如果不需要删除，就遍历下一个
		if (!needDetele)
		{
			//4.4.1 上个节点pPreNode设为当前节点pNode 
			pPreNode = pNode;

			//4.4.2 当前节点pNode设为下个节点pNext
			pNode = pNext;
		/*	pNode->m_nValue = pNext->m_nValue;
			pNode->m_pNext = pNext->m_pNext;*/
		}
 
		//4.5 否则，开始删除
		else
		{
			//4.5.1 记录pNode值
			int value = pNode->m_nValue;

			//4.5.2 定义要删除的节点变量toBeDeleted，初始化为该节点
			ListNode* toBeDeleted = pNode; 
	 
			//4.5.3 循环遍历：如果toBeDeleted节点不为空，且等于下一个节点，就将toBeDeleted删除，
			while (toBeDeleted&&value == toBeDeleted->m_nValue)
			{
				//4.5.3.1 pNext指向toBeDeleted下个节点
				pNext = toBeDeleted->m_pNext;

				//4.5.3.2 删除toBeDeleted节点
				delete toBeDeleted;
				toBeDeleted = nullptr;

				//4.5.3.3 toBeDeleted节点赋值为下个节点pNext
				toBeDeleted = pNext; 
			} 

			//4.5.4 如果删除的是头节点,即pPreNode为空，将头节点改为下个节点
			if (!pPreNode)
				*pHead = pNext;

			//4.5.5 否则，将pPreNode的下个节点设置为下个节点pNext
			else
				pPreNode->m_pNext = pNext;

			//4.5.6 当前节点pNode设为下个节点pNext
			pNode = pNext;
		}	
	}
}

// ====================测试代码====================
void Test(char* testName, ListNode** pHead, int* expectedValues, int expectedLength)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    DeleteDuplication(pHead);

    int index = 0;
    ListNode* pNode = *pHead;
    while(pNode != nullptr && index < expectedLength)
    {
        if(pNode->m_nValue != expectedValues[index])
            break;

        pNode = pNode->m_pNext;
        index++;
    }

    if(pNode == nullptr && index == expectedLength)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}

// 某些结点是重复的
void Test1()
{
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(3);
    ListNode* pNode5 = CreateListNode(4);
    ListNode* pNode6 = CreateListNode(4);
    ListNode* pNode7 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);
    ConnectListNodes(pNode5, pNode6);
    ConnectListNodes(pNode6, pNode7);

    ListNode* pHead = pNode1;

    int expectedValues[] = { 1, 2, 5 };
    Test("Test1", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

    DestroyList(pHead);
}

// 没有重复的结点
void Test2()
{
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);
    ListNode* pNode6 = CreateListNode(6);
    ListNode* pNode7 = CreateListNode(7);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);
    ConnectListNodes(pNode5, pNode6);
    ConnectListNodes(pNode6, pNode7);

    ListNode* pHead = pNode1;

    int expectedValues[] = { 1, 2, 3, 4, 5, 6, 7 };
    Test("Test2", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

    DestroyList(pHead);
}

// 除了一个结点之外其他所有结点的值都相同
void Test3()
{
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(1);
    ListNode* pNode3 = CreateListNode(1);
    ListNode* pNode4 = CreateListNode(1);
    ListNode* pNode5 = CreateListNode(1);
    ListNode* pNode6 = CreateListNode(1);
    ListNode* pNode7 = CreateListNode(2);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);
    ConnectListNodes(pNode5, pNode6);
    ConnectListNodes(pNode6, pNode7);

    ListNode* pHead = pNode1;

    int expectedValues[] = { 2 };
    Test("Test3", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

    DestroyList(pHead);
}

// 所有结点的值都相同
void Test4()
{
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(1);
    ListNode* pNode3 = CreateListNode(1);
    ListNode* pNode4 = CreateListNode(1);
    ListNode* pNode5 = CreateListNode(1);
    ListNode* pNode6 = CreateListNode(1);
    ListNode* pNode7 = CreateListNode(1);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);
    ConnectListNodes(pNode5, pNode6);
    ConnectListNodes(pNode6, pNode7);

    ListNode* pHead = pNode1;

    Test("Test4", &pHead, nullptr, 0);

    DestroyList(pHead);
}

// 所有结点都成对出现
void Test5()
{
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(1);
    ListNode* pNode3 = CreateListNode(2);
    ListNode* pNode4 = CreateListNode(2);
    ListNode* pNode5 = CreateListNode(3);
    ListNode* pNode6 = CreateListNode(3);
    ListNode* pNode7 = CreateListNode(4);
    ListNode* pNode8 = CreateListNode(4);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);
    ConnectListNodes(pNode5, pNode6);
    ConnectListNodes(pNode6, pNode7);
    ConnectListNodes(pNode7, pNode8);

    ListNode* pHead = pNode1;

    Test("Test5", &pHead, nullptr, 0);

    DestroyList(pHead);
}

// 除了两个结点之外其他结点都成对出现
void Test6()
{
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(1);
    ListNode* pNode3 = CreateListNode(2);
    ListNode* pNode4 = CreateListNode(3);
    ListNode* pNode5 = CreateListNode(3);
    ListNode* pNode6 = CreateListNode(4);
    ListNode* pNode7 = CreateListNode(5);
    ListNode* pNode8 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);
    ConnectListNodes(pNode5, pNode6);
    ConnectListNodes(pNode6, pNode7);
    ConnectListNodes(pNode7, pNode8);

    ListNode* pHead = pNode1;

    int expectedValues[] = { 2, 4 };
    Test("Test6", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

    DestroyList(pHead);
}

// 链表中只有两个不重复的结点
void Test7()
{
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);

    ConnectListNodes(pNode1, pNode2);

    ListNode* pHead = pNode1;

    int expectedValues[] = { 1, 2 };
    Test("Test7", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

    DestroyList(pHead);
}

// 结点中只有一个结点
void Test8()
{
    ListNode* pNode1 = CreateListNode(1);

    ConnectListNodes(pNode1, nullptr);

    ListNode* pHead = pNode1;

    int expectedValues[] = { 1 };
    Test("Test8", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

    DestroyList(pHead);
}

// 结点中只有两个重复的结点
void Test9()
{
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(1);

    ConnectListNodes(pNode1, pNode2);

    ListNode* pHead = pNode1;

    Test("Test9", &pHead, nullptr, 0);

    DestroyList(pHead);
}

// 空链表
void Test10()
{
    ListNode* pHead = nullptr;

    Test("Test10", &pHead, nullptr, 0);
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
    Test8();
    Test9();
    Test10();

	system("pause");
    return 0;
}
