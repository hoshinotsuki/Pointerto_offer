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

// 面试题32（三）：之字形打印二叉树
// 题目：请实现一个函数按照之字形顺序打印二叉树，即第一行按照从左到右的顺
// 序打印，第二层按照从右到左的顺序打印，第三行再按照从左到右的顺序打印，
// 其他行以此类推。

#include <cstdio>
#include "..\Utilities\BinaryTree.h"
#include <stack>
#include <vector>
#include <stdlib.h>
#include <iostream>
using namespace std;


//
//void Print(BinaryTreeNode* pRoot)
//{
//    if(pRoot == nullptr)
//        return;
//
//    std::stack<BinaryTreeNode*> levels[2];
//    int current = 0;
//    int next = 1;
//
//    levels[current].push(pRoot);
//    while(!levels[0].empty() || !levels[1].empty())
//    {
//        BinaryTreeNode* pNode = levels[current].top();
//        levels[current].pop();
//
//        printf("%d ", pNode->m_nValue);
//
//        if(current == 0)
//        {
//            if(pNode->m_pLeft != nullptr)
//                levels[next].push(pNode->m_pLeft);
//            if(pNode->m_pRight != nullptr)
//                levels[next].push(pNode->m_pRight);
//        }
//        else
//        {
//            if(pNode->m_pRight != nullptr)
//                levels[next].push(pNode->m_pRight);
//            if(pNode->m_pLeft != nullptr)
//                levels[next].push(pNode->m_pLeft);
//        }
//
//        if(levels[current].empty())
//        {
//            printf("\n");
//            current = 1 - current;
//            next = 1 - next;
//        }
//    }
//}

vector<vector<int>> Print(BinaryTreeNode* pRoot) {
	//定义容器
	vector<int> subret;
	vector<vector<int>> ret;

	//1.入口检查
	if (!pRoot)
		return ret;

	int cur = 0;
	int next = 1;


	//level[0]奇数级节点的栈，从左至右存储,level[1]偶数级节点的栈，从右至左存储,
	stack<BinaryTreeNode*> level[2];
	//level[0]:stack1,level[1]:stack2

	//将根节点放入ret中
	subret.push_back(pRoot->m_nValue);
	ret.push_back(subret);
	subret.clear();

	//将1级的子节点放入level[0]栈中,奇数级的子节点
	level[0].push(pRoot->m_pLeft);
	level[0].push(pRoot->m_pRight);

	while (!level[0].empty() || !level[1].empty())
	{
		while (!level[cur].empty())
		{
			BinaryTreeNode* curNode = level[cur].top();
			subret.push_back(curNode->m_nValue);
			level[cur].pop();
			if (cur == 0)//
			{
				if (curNode->m_pRight)
					level[next].push(curNode->m_pRight);

				if (curNode->m_pLeft)
					level[next].push(curNode->m_pLeft);
			}
			else
			{
				if (curNode->m_pLeft) 
					level[next].push(curNode->m_pLeft);

				if (curNode->m_pRight)
					level[next].push(curNode->m_pRight);

			}
		}
		if (level[cur].empty())
		{
			cur = 1 -cur;
			next = 1 - next;
			ret.push_back(subret);
			subret.clear();
		}
	} 
	return ret;
}

// ====================测试代码====================
//            8
//        6      10
//       5 7    9  11
void Test1()
{
    BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
    BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
    BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);
    BinaryTreeNode* pNode9 = CreateBinaryTreeNode(9);
    BinaryTreeNode* pNode11 = CreateBinaryTreeNode(11);

    ConnectTreeNodes(pNode8, pNode6, pNode10);
    ConnectTreeNodes(pNode6, pNode5, pNode7);
    ConnectTreeNodes(pNode10, pNode9, pNode11);

    printf("====Test1 Begins: ====\n");
    printf("Expected Result is:\n");
    printf("8 \n");
    printf("10 6 \n");
    printf("5 7 9 11 \n\n");

    printf("Actual Result is: \n");
    //Print(pNode8);
	vector<vector<int>> ret = Print(pNode8);

	for (auto it = ret.begin(); it < ret.end(); it++)
	{
		for (int i = 0; i < (*it).size(); i++)
			cout<<(*it)[i];
	}

    printf("\n");

    DestroyTree(pNode8);
}

//            5
//          4
//        3
//      2
void Test2()
{
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
    BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);

    ConnectTreeNodes(pNode5, pNode4, nullptr);
    ConnectTreeNodes(pNode4, pNode3, nullptr);
    ConnectTreeNodes(pNode3, pNode2, nullptr);

    printf("====Test2 Begins: ====\n");
    printf("Expected Result is:\n");
    printf("5 \n");
    printf("4 \n");
    printf("3 \n");
    printf("2 \n\n");

    printf("Actual Result is: \n");
    Print(pNode5);
    printf("\n");

    DestroyTree(pNode5);
}

//        5
//         4
//          3
//           2
void Test3()
{
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
    BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);

    ConnectTreeNodes(pNode5, nullptr, pNode4);
    ConnectTreeNodes(pNode4, nullptr, pNode3);
    ConnectTreeNodes(pNode3, nullptr, pNode2);

    printf("====Test3 Begins: ====\n");
    printf("Expected Result is:\n");
    printf("5 \n");
    printf("4 \n");
    printf("3 \n");
    printf("2 \n\n");

    printf("Actual Result is: \n");
    Print(pNode5);
    printf("\n");

    DestroyTree(pNode5);
}

void Test4()
{
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);

    printf("====Test4 Begins: ====\n");
    printf("Expected Result is:\n");
    printf("5 \n\n");

    printf("Actual Result is: \n");
    Print(pNode5);
    printf("\n");

    DestroyTree(pNode5);
}

void Test5()
{
    printf("====Test5 Begins: ====\n");
    printf("Expected Result is:\n");

    printf("Actual Result is: \n");
    Print(nullptr);
    printf("\n");
}

//        100
//        /
//       50   
//         \
//         150
void Test6()
{
    BinaryTreeNode* pNode100 = CreateBinaryTreeNode(100);
    BinaryTreeNode* pNode50 = CreateBinaryTreeNode(50);
    BinaryTreeNode* pNode150 = CreateBinaryTreeNode(150);

    ConnectTreeNodes(pNode100, pNode50, nullptr);
    ConnectTreeNodes(pNode50, nullptr, pNode150);

    printf("====Test6 Begins: ====\n");
    printf("Expected Result is:\n");
    printf("100 \n");
    printf("50 \n");
    printf("150 \n\n");

    printf("Actual Result is: \n");
    Print(pNode100);
    printf("\n");
}

//                8
//        4              12
//     2     6       10      14
//   1  3  5  7     9 11   13  15
void Test7()
{
    BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
    BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNode12 = CreateBinaryTreeNode(12);
    BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
    BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
    BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
    BinaryTreeNode* pNode14 = CreateBinaryTreeNode(14);
    BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
    BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);
    BinaryTreeNode* pNode9 = CreateBinaryTreeNode(9);
    BinaryTreeNode* pNode11 = CreateBinaryTreeNode(11);
    BinaryTreeNode* pNode13 = CreateBinaryTreeNode(13);
    BinaryTreeNode* pNode15 = CreateBinaryTreeNode(15);

    ConnectTreeNodes(pNode8, pNode4, pNode12);
    ConnectTreeNodes(pNode4, pNode2, pNode6);
    ConnectTreeNodes(pNode12, pNode10, pNode14);
    ConnectTreeNodes(pNode2, pNode1, pNode3);
    ConnectTreeNodes(pNode6, pNode5, pNode7);
    ConnectTreeNodes(pNode10, pNode9, pNode11);
    ConnectTreeNodes(pNode14, pNode13, pNode15);

    printf("====Test7 Begins: ====\n");
    printf("Expected Result is:\n");
    printf("8 \n");
    printf("12 4 \n");
    printf("2 6 10 14 \n");
    printf("15 13 11 9 7 5 3 1 \n\n");

    printf("Actual Result is: \n");
    Print(pNode8);
    printf("\n");

    DestroyTree(pNode8);
}

int main(int argc, char* argv[])
{
    Test1();
 /*   Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();*/

    return 0;
}
