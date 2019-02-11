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

// 面试题21：调整数组顺序使奇数位于偶数前面
// 题目：输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有
// 奇数位于数组的前半部分，所有偶数位于数组的后半部分。
#include <stdlib.h>
#include <cstdio>

void Reorder(int *pData, unsigned int length, bool (*func)(int));
bool isEven(int n);

// ====================方法一====================
//void ReorderOddEven_1(int *pData, unsigned int length)
//{
//    if(pData == nullptr || length == 0)
//        return;
//
//    int *pBegin = pData;
//    int *pEnd = pData + length - 1;
//
//    while(pBegin < pEnd)
//    {
//        // 向后移动pBegin，直到它指向偶数
//        while(pBegin < pEnd && (*pBegin & 0x1) != 0)
//            pBegin ++;
//
//        // 向前移动pEnd，直到它指向奇数
//        while(pBegin < pEnd && (*pEnd & 0x1) == 0)
//            pEnd --;
//
//        if(pBegin < pEnd)
//        {
//            int temp = *pBegin;
//            *pBegin = *pEnd;
//            *pEnd = temp;
//        }
//    }
//}

void ReorderOddEven_1(int *pData, unsigned int length)
{
	//1.如果数组为nullptr,长度为0，返回
	if (!pData&&length == 0)
		return;
	//2.设定两个指针，第一个指向偶数，初始值是第一个，第二个总指向奇数，初始值是最后一个
	int* even = pData;
	int* odd = pData + length - 1;
	
	//3.循环条件:当偶数指针在奇数指针前面时
	while (even < odd)
	{
		//3.1 如果第一个不指向偶数，往后移一个指针
		while (even < odd && (*even & 0x1) != 0)//0x1是零，不是欧
			even++;

		//3.2 如果第二个指针不指向奇数，往前移一个指针
		while (even < odd && (*odd & 0x1) != 1)
			odd--;

		//3.3 如果奇数在偶数前面，交换两个指针的值
		if (even < odd)
		{
			int temp = *even;
			*even = *odd;
			*odd = temp;
		}
	}
}

// ====================方法二====================
//void ReorderOddEven_2(int *pData, unsigned int length)
//{
//    Reorder(pData, length, isEven);
//}
//
//void Reorder(int *pData, unsigned int length, bool (*func)(int))
//{
//    if(pData == nullptr || length == 0)
//        return;
//
//    int *pBegin = pData;
//    int *pEnd = pData + length - 1;
//
//    while(pBegin < pEnd) 
//    {
//        // 向后移动pBegin
//        while(pBegin < pEnd && !func(*pBegin))
//            pBegin ++;
//
//        // 向前移动pEnd
//        while(pBegin < pEnd && func(*pEnd))
//            pEnd --;
//
//        if(pBegin < pEnd)
//        {
//            int temp = *pBegin;
//            *pBegin = *pEnd;
//            *pEnd = temp;
//        }
//    }
//}

//bool isEven(int n)
//{
//    return (n & 1) == 0;
//}

void ReorderOddEven_2(int *pData, unsigned int length)
{
	//Reorder(int *pData, unsigned int length, bool(*func)(int))
	//函数参数，直接传递函数名，
	return Reorder(pData,length,isEven);
}
void Reorder(int *pData, unsigned int length, bool(*func)(int))
{
	//1.如果数组为nullptr,长度为0，返回
	if (!pData&&length == 0)
		return;
	//2.设定两个指针，第一个指向偶数，初始值是第一个，第二个总指向奇数，初始值是最后一个
	int* even = pData;
	int* odd = pData + length - 1;

	//3.循环条件:当偶数指针在奇数指针前面时
	while (even < odd)
	{
		//3.1 如果第一个不指向偶数，往后移一个指针
		while (even < odd && !func(*even))//0x1是零，不是欧
			even++;

		//3.2 如果第二个指针不指向奇数，往前移一个指针
		while (even < odd && func(*odd))
			odd--;

		//3.3 如果奇数在偶数前面，交换两个指针的值
		if (even < odd)
		{
			int temp = *even;
			*even = *odd;
			*odd = temp;
		}
	}
}
//是否为偶数
bool isEven(int n)
{
	return (n & 1) == 0 ;//要加括号，不然一直是false
}

// ====================测试代码====================
void PrintArray(int numbers[], int length)
{
    if(length < 0)
        return;

    for(int i = 0; i < length; ++i)
        printf("%d\t", numbers[i]);

    printf("\n");
}

void Test(char* testName, int numbers[], int length)
{
    if(testName != nullptr)
        printf("%s begins:\n", testName);

    int* copy = new int[length];
    for(int i = 0; i < length; ++i)
    {
        copy[i] = numbers[i];
    }

    printf("Test for solution 1:\n");
    PrintArray(numbers, length);
    ReorderOddEven_1(numbers, length);
    PrintArray(numbers, length);

    printf("Test for solution 2:\n");
    PrintArray(copy, length);
    ReorderOddEven_2(copy, length);
    PrintArray(copy, length);

    delete[] copy;
}

void Test1()
{
    int numbers[] = {1, 2, 3, 4, 5, 6, 7};
    Test("Test1", numbers, sizeof(numbers)/sizeof(int));
}

void Test2()
{
    int numbers[] = {2, 4, 6, 1, 3, 5, 7};
    Test("Test2", numbers, sizeof(numbers)/sizeof(int));
}

void Test3()
{
    int numbers[] = {1, 3, 5, 7, 2, 4, 6};
    Test("Test3", numbers, sizeof(numbers)/sizeof(int));
}

void Test4()
{
    int numbers[] = {1};
    Test("Test4", numbers, sizeof(numbers)/sizeof(int));
}

void Test5()
{
    int numbers[] = {2};
    Test("Test5", numbers, sizeof(numbers)/sizeof(int));
}

void Test6()
{
    Test("Test6", nullptr, 0);
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
	system("pause");
    return 0;
}

