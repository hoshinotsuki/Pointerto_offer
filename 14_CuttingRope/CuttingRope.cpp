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

// 面试题14：剪绳子
// 题目：给你一根长度为n绳子，请把绳子剪成m段（m、n都是整数，n>1并且m≥1）。
// 每段的绳子的长度记为k[0]、k[1]、……、k[m]。k[0]*k[1]*…*k[m]可能的最大乘
// 积是多少？例如当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此
// 时得到最大的乘积18。

#include <iostream>
#include <cmath>
#include <stdlib.h>

// ====================动态规划====================
//int maxProductAfterCutting_solution1(int length)
//{
//    if(length < 2)
//        return 0;
//    if(length == 2)
//        return 1;
//    if(length == 3)
//        return 2;
//
//    int* products = new int[length + 1];
//    products[0] = 0;
//    products[1] = 1;
//    products[2] = 2;
//    products[3] = 3;
//
//    int max = 0;
//    for(int i = 4; i <= length; ++i)
//    {
//        max = 0;
//        for(int j = 1; j <= i / 2; ++j)
//        {
//            int product = products[j] * products[i - j];
//            if(max < product)
//                max = product;
//
//            products[i] = max;
//        }
//    }
//
//    max = products[length];
//    delete[] products;
//
//    return max;
//}

int maxProductAfterCutting_solution1(int length)
{
	//1. 根据题意，如果长度小于2，返回0
	if (length < 2)
		return 0;

	//2. 长度为2：1*1，返回1
	if (length == 2)
		return 1;

	//3. 长度为3：1*2，返回2
	if (length == 3)
		return 2;
	
	//4. 新建一个数组，保存最优解
	int* products = new int[length + 1];
	products[0] = 0;
	products[1] = 1;
	products[2] = 2;
	products[3] = 3;

	//5. 定义max变量
	int max = 0;

	//6. 由下至上开始循环，从4开始，到length结束
	for (int i = 4; i <= length; i++)
	{	
		//6.1 从头到尾遍历,寻找products[i]的最大值
		for (int j = 1; j<= i / 2; j++)
		{
			//6.1.1 依次求出长度为i的最优解
			products[i] = products[j] * products[i - j];
			//6.1.2 找到最大值
			if (products[i] > max)
				max = products[i];
		}

		//6.2 更新products[i]
		products[i] = max;
	}

	//7.将max变量更新为所求长度的最优解
	max = products[length];

	//8.释放最优解数组的内存
	delete[] products;
	
	//9.返回该长度的最优解
	return max;

}

// ====================贪婪算法====================
//int maxProductAfterCutting_solution2(int length)
//{
//    if(length < 2)
//        return 0;
//    if(length == 2)
//        return 1;
//    if(length == 3)
//        return 2;
//
//    // 尽可能多地减去长度为3的绳子段
//    int timesOf3 = length / 3;
//
//    // 当绳子最后剩下的长度为4的时候，不能再剪去长度为3的绳子段。
//    // 此时更好的方法是把绳子剪成长度为2的两段，因为2*2 > 3*1。
//    if(length - timesOf3 * 3 == 1)
//        timesOf3 -= 1;
//
//    int timesOf2 = (length - timesOf3 * 3) / 2;
//
//    return (int) (pow(3, timesOf3)) * (int) (pow(2, timesOf2));
//}

int maxProductAfterCutting_solution2(int length){

	//1.由题意，长度小于2时，返回0
	if (length < 2)
		return 0;

	//2. 长度等于2时，返回1*1
	if (length == 2)
		return 1;

	//3.长度等于3时，返回2*1
	if (length == 3)
		return 2;

	// 下面讨论长度大于等于4的情况，由于因为2*2>3*1，题目说至少剪一刀，所以等于4时，剪2*2 
	
	// 由数学证明可知，n>=5时，2(n-2)>n,3(n-3)>n，且3(n-3)>2(n-2)，所以当长度大于等于5时，尽可能地剪长度为3的
	//4. 计算最多剪长度为3的个数
	int timesof3 = length / 3;

	//5. 如果剩下长度为4，则剪2*2，
	if (length - timesof3 * 3 == 1)
		timesof3-=1;

	//6. 计算剪长度为2的个数
	int timesof2 = (length - timesof3 * 3) / 2;

	//7. 返回总和=3的指数次*2的指数次
	return (int)pow(3, timesof3) * (int)pow(2, timesof2); 
}

// ====================测试代码====================
void test(const char* testName, int length, int expected)
{
    int result1 = maxProductAfterCutting_solution1(length);
    if(result1 == expected)
        std::cout << "Solution1 for " << testName << " passed." << std::endl;
    else
        std::cout << "Solution1 for " << testName << " FAILED." << std::endl;

    int result2 = maxProductAfterCutting_solution2(length);
    if(result2 == expected)
        std::cout << "Solution2 for " << testName << " passed." << std::endl;
    else
        std::cout << "Solution2 for " << testName << " FAILED." << std::endl;
}

void test1()
{
    int length = 1;
    int expected = 0;
    test("test1", length, expected);
}

void test2()
{
    int length = 2;
    int expected = 1;
    test("test2", length, expected);
}

void test3()
{
    int length = 3;
    int expected = 2;
    test("test3", length, expected);
}

void test4()
{
    int length = 4;
    int expected = 4;
    test("test4", length, expected);
}

void test5()
{
    int length = 5;
    int expected = 6;
    test("test5", length, expected);
}

void test6()
{
    int length = 6;
    int expected = 9;
    test("test6", length, expected);
}

void test7()
{
    int length = 7;
    int expected = 12;
    test("test7", length, expected);
}

void test8()
{
    int length = 8;
    int expected = 18;
    test("test8", length, expected);
}

void test9()
{
    int length = 9;
    int expected = 27;
    test("test9", length, expected);
}

void test10()
{
    int length = 10;
    int expected = 36;
    test("test10", length, expected);
}

void test11()
{
    int length = 50;
    int expected = 86093442;
    test("test11", length, expected);
}

int main(int agrc, char* argv[])
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    test11();
	system("pause");


    return 0;
}
