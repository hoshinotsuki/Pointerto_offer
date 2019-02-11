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

// 面试题16：数值的整数次方
// 题目：实现函数double Power(double base, int exponent)，求base的exponent
// 次方。不得使用库函数，同时不需要考虑大数问题。

#include <iostream>
#include <stdio.h>
#include <cmath>
 

// bool g_InvalidInput = false;
 bool equal(double num1, double num2);
double PowerWithUnsignedExponent(double base, unsigned int exponent);

//double Power(double base, int exponent)
//{
//    g_InvalidInput = false;
//
//    if (equal(base, 0.0) && exponent < 0)
//    {
//        g_InvalidInput = true;
//        return 0.0;
//    }
//
//    unsigned int absExponent = (unsigned int) (exponent);
//    if (exponent < 0)
//        absExponent = (unsigned int) (-exponent);
//
//    double result = PowerWithUnsignedExponent(base, absExponent);
//    if (exponent < 0)
//        result = 1.0 / result;
//
//    return result;
//}
//
///*
//double PowerWithUnsignedExponent(double base, unsigned int exponent)
//{
//    double result = 1.0;
//    
//    for (int i = 1; i <= exponent; ++i)
//        result *= base;
//
//    return result;
//}
//*/
//
//double PowerWithUnsignedExponent(double base, unsigned int exponent)
//{
//    if (exponent == 0)
//        return 1;
//    if (exponent == 1)
//        return base;
//
//    double result = PowerWithUnsignedExponent(base, exponent >> 1);
//    result *= result;
//    if ((exponent & 0x1) == 1)
//        result *= base;
//
//    return result;
//}
//
bool equal(double num1, double num2)
{
    if ((num1 - num2 > -0.0000001) && (num1 - num2 < 0.0000001))
        return true;
    else
        return false;
}
////////////////////
//我的
/////////////////////

////1.全局变量标记异常值
 bool g_InvalidInput = false;
//
//double Power(double base, int exponent) {
//	//2.初始化全局变量
//	g_InvalidInput = false;
//
//	//3.如果输入底数为0，指数为负，返回0，且异常
//	if (base == 0.0 && exponent<0)
//	{
//		g_InvalidInput = true;
//		return 0;
//	}
//
//	//4.设置无符号变量存放指数的绝对值
//	unsigned int absExponent = (unsigned int)exponent;
//	if (exponent<0)
//	{
//		absExponent = -exponent;
//	}
//
//	//5.调用求指数的函数，设置double型储存指数的结果
//	double result = PowerWithUnsignedExponent(base, absExponent);
//
//	//6.如果指数是负数，就求导
//	if (exponent<0)
//		result = 1 / result;
//
//	//7.返回结果
//	return result;
//
//}
//
//
////求指数的函数double,参数：底数double,指数unsigned int，返回值：结果double。这里的指数已经取了绝对值，所以是unsigned int。
//double PowerWithUnsignedExponent(double base,unsigned int exponent)
//{
//
//	//1.如果指数为0，返回1
//	if (exponent == 0)
//		return 1;
//	//2.如果指数为1，返回底数
//	if (exponent == 1)
//		return base;
//
//	//由于数学知识可知，
//	//如果exponent为偶数，result=base^(exponent/2)*base^(exponent/2)
//	//如果exponent为偶数，result=base^((exponent-1)/2)*base^((exponent-1)/2)*base
//	//3.使用递归，可以得到base^(exponent/2),即div2的结果，用右移一位，>>1会更快
//	double result = PowerWithUnsignedExponent(base, exponent >> 1);
//
//	//4.将上面递归函数得到的div2的结果相乘
//	result = result*result;
//
//	//5.判断原来的指数的奇偶性,如果是奇数，就再乘以一个底数。这里用与位运算更快。
//	if (exponent & 1 == 1)
//		result *= base;
//
//	//6.返回结果
//	return result;
//}

double Power(double base, int exponent) {
	long long p = abs((long long)exponent);
	double r = 1.0;
	while (p) {
		if (p & 1) r *= base;
		base *= base;
		p >>= 1;
	}
	return exponent < 0 ? 1 / r : r;
}

// ====================测试代码====================
void Test(const char* testName, double base, int exponent, double expectedResult, bool expectedFlag)
{
    double result = Power(base, exponent);
    if (equal(result, expectedResult) && g_InvalidInput == expectedFlag)
        std::cout << testName << " passed" << std::endl;
    else
        std::cout << testName << " FAILED" << std::endl;
}

int main(int argc, char* argv[])
{
    // 底数、指数都为正数
    Test("Test1", 2, 3, 8, false);

    // 底数为负数、指数为正数
    Test("Test2", -2, 3, -8, false);

    // 指数为负数
    Test("Test3", 2, -3, 0.125, false);

    // 指数为0
    Test("Test4", 2, 0, 1, false);

    // 底数、指数都为0
    Test("Test5", 0, 0, 1, false);

    // 底数为0、指数为正数
    Test("Test6", 0, 4, 0, false);

    // 底数为0、指数为负数
    Test("Test7", 0, -4, 0, true);

	system("pause");

    return 0;
}

