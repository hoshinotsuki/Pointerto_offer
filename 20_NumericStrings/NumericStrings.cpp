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

// 面试题20：表示数值的字符串
// 题目：请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。例如，
// 字符串“+100”、“5e2”、“-123”、“3.1416”及“-1E-16”都表示数值，但“12e”、
// “1a3.14”、“1.2.3”、“+-5”及“12e+5.4”都不是

#include <stdio.h>
#include <stdlib.h>

bool scanUnsignedInteger(const char** str);
bool scanInteger(const char** str);
//
//// 数字的格式可以用A[.[B]][e|EC]或者.B[e|EC]表示，其中A和C都是
//// 整数（可以有正负号，也可以没有），而B是一个无符号整数
//bool isNumeric(const char* str)
//{
//    if(str == nullptr)
//        return false;
//
//    bool numeric = scanInteger(&str);
//
//    // 如果出现'.'，接下来是数字的小数部分
//    if(*str == '.')
//    {
//        ++str;
//
//        // 下面一行代码用||的原因：
//        // 1. 小数可以没有整数部分，例如.123等于0.123；
//        // 2. 小数点后面可以没有数字，例如233.等于233.0；
//        // 3. 当然小数点前面和后面可以有数字，例如233.666
//        numeric = scanUnsignedInteger(&str) || numeric;
//    }
//
//    // 如果出现'e'或者'E'，接下来跟着的是数字的指数部分
//    if(*str == 'e' || *str == 'E')
//    {
//        ++str;
//
//        // 下面一行代码用&&的原因：
//        // 1. 当e或E前面没有数字时，整个字符串不能表示数字，例如.e1、e1；
//        // 2. 当e或E后面没有整数时，整个字符串不能表示数字，例如12e、12e+5.4
//        numeric = numeric && scanInteger(&str);
//    }
//
//    return numeric && *str == '\0';
//}
//
//bool scanUnsignedInteger(const char** str)
//{
//    const char* before = *str;
//    while(**str != '\0' && **str >= '0' && **str <= '9')
//        ++(*str);
//
//    // 当str中存在若干0-9的数字时，返回true
//    return *str > before;
//}
//
//// 整数的格式可以用[+|-]B表示, 其中B为无符号整数
//bool scanInteger(const char** str)
//{
//    if(**str == '+' || **str == '-')
//        ++(*str);
//    return scanUnsignedInteger(str);
//}
//



                       
// 整数的格式可以用[+|-]B表示, 其中B为无符号整数
bool scanInteger(const char** str) 
{
	//1.如果前面有[+|-]号，往后移一位
	if (**str == '+' || **str == '-')
		(*str)++;//注意这里(*str) 要打括号 ++比*优先级高。

	//2.返回无整形扫描
	return scanUnsignedInteger(str);
}

bool scanUnsignedInteger(const char** str)
{
	//1.定义before指针，指向str第一个字符
	const char* before = *str;
	//2.如果*str不为空，且是数字的话，进行下一个字符
	while (*str&&**str >= '0'&&**str <= '9')
		(*str)++;
	//3.如果有数字字符的话，就返回真,否则返回假
	return before < *str ? true : false;
}

// 数字的格式可以用A[.[B]][e|EC]或者.B[e|EC]表示，其中A和C都是
// 整数（可以有正负号，也可以没有），而B是一个无符号整数
bool isNumeric(const char* str)
{
	//1.如果为空
	if (!str)
		return false;

	//2.判断第一个字符是否是数值，A  
	bool numeric = scanInteger(&str);

	//3.如果遇到小数点 . 用||,因为小数点有三种情况，1.1/0.1/1.0
	if (*str == '.')
	{
		//3.1 str++成为左值，因为要取地址
		str++;
		//3.2 不用return 更新numeric的值
		numeric= scanUnsignedInteger(&str) || numeric  ;//细节：先扫描小数位B，是否为unsigned，因为如果numeric==ture就不会扫描小数位了
	}

	//4.如果遇到指数e|E ,用&&，因为指数前后必须都要是数字， e2,1e是错的
	if (*str == 'e' || *str == 'E')
	{
		str++;
		numeric= numeric&&scanInteger(&str);
	}

	//5.返回是否为数值numeric,且已经扫描到了'\0'
	return numeric&&*str=='\0';
}


// ====================测试代码====================
void Test(const char* testName, const char* str, bool expected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    if(isNumeric(str) == expected)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}


int main(int argc, char* argv[])
{
    Test("Test1", "100", true);
    Test("Test2", "123.45e+6", true);
    Test("Test3", "+500", true);
    Test("Test4", "5e2", true);
    Test("Test5", "3.1416", true);
    Test("Test6", "600.", true);
    Test("Test7", "-.123", true);
    Test("Test8", "-1E-16", true);
    Test("Test9", "1.79769313486232E+308", true);

    printf("\n\n");

    Test("Test10", "12e", false);
    Test("Test11", "1a3.14", false);
    Test("Test12", "1+23", false);
    Test("Test13", "1.2.3", false);
    Test("Test14", "+-5", false);
    Test("Test15", "12e+5.4", false);
    Test("Test16", ".", false);
    Test("Test17", ".e1", false);
    Test("Test18", "e1", false);
    Test("Test19", "+.", false);
    Test("Test20", "", false);
    Test("Test21", nullptr, false);
	system("pause");

    return 0;
}
