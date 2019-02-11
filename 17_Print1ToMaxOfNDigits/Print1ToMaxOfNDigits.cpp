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

// 面试题17：打印1到最大的n位数
// 题目：输入数字n，按顺序打印出从1最大的n位十进制数。比如输入3，则
// 打印出1、2、3一直到最大的3位数即999。

#include <cstdio>
#include <stdio.h>
#include <memory>

void PrintNumber(char* number);
bool Increment(char* number);
void Print1ToMaxOfNDigitsRecursively(char* number, int length, int index);

// ====================方法一====================
void Print1ToMaxOfNDigits_1(int n)
{
	//1.如果小于等于0，直接返回
    if (n <= 0)
        return;
	//2.大数用字符串数组表示，新分配一个n+1长度的字符串数组，最后一位存放结束符'\0'
    char *number = new char[n + 1];
	//3.memset初始化前n位数为0
    memset(number, '0', n);
	//4.将数组最后一位赋值'\0'
    number[n] = '\0';


	//5.重复执行递增字符串函数并打印，直到字符串超过N位数时，停止打印
    while (!Increment(number))
    {
		//5.1 打印字符串函数，前面为0的数不打印。
        PrintNumber(number);
    }
	//6.释放字符串数组内存。
    delete[]number;
}

// 字符串number表示一个数字，在 number上增加1
// 如果做加法溢出，则返回true；否则为false
bool Increment(char* number)
{
	//1.bool标志是否溢出，初始化false
    bool isOverflow = false;
	//2.int 进位
	int nTakeOver = 0;
	//3.记录number的个数，除去结束符
    int nLength = strlen(number);

	//4.加法溢出循环函数，字符串从后往前循环，结束条件:最高位达到10就break
    for (int i = nLength - 1; i >= 0; i--)
    {
		//4.1 nSum=字符串i位的数值+是否进位
        int nSum = number[i] - '0' + nTakeOver;

		//4.2 i为最后一位，就该位数值++，前面字符串不变
        if (i == nLength - 1)
            nSum++;

		//4.3 如果这个位置的数值达到了10，说明该进位了
		if (nSum >= 10)
		{
			//4.3.1 如果这个位置刚好是最大位，就不能再进位，就会溢出，设置bool标记为真。这时不再打印。
			if (i == 0)
			{
				isOverflow = true; break;
			}
			//4.3.2 如果这个位置不是最大位，就进一位 
            else
            {
				//4.3.2.1 将数值设为0(nSum-10)
                nSum -= 10;
				//4.3.2.2 将进位设为1，将加到高位上去
                nTakeOver = 1;
				//4.3.2.3 将这一位设为0
                number[i] = '0' + nSum;
            }
        }
		//4.4 如果没有到达10，将数值+'0'并存入数组[i]中，并跳出循环开始打印。
        else
        {
            number[i] = '0' + nSum;
            break;
        }
    }
	//5.返回是否溢出值bool
    return isOverflow;
}

// ====================方法二====================
void Print1ToMaxOfNDigits_2(int n)
{
	//1.如果位数小于等于0，就不打印
	if (n <= 0)
		return;
	//2.分配长度为N+1的字符串数组指针new char[n+1],并将末位赋值'\0'结束符
	char* number = new char[n + 1];
	number[n] = '\0';

	//3.设置index=0是0-9的循环
	for (int i = 0; i < 10; ++i)
	{
		//3.1 数组[0]赋值i+'0'
		number[0] = i + '0';
		//3.2 开始调用递归函数，从index=0开始，依次设置下一位
		Print1ToMaxOfNDigitsRecursively(number, n, 0);
	}
	//4.释放掉数组指针delete[]
	delete[] number;
}

//递归打印函数void，参数：字符串数组指针char*,长度int,设置位数int,动作：打印函数PrintNumber(number);
void Print1ToMaxOfNDigitsRecursively(char* number, int length, int index)
{
	//1.递归结束条件：如果设置到了最后一位，就打印该字符串
	if (index == length - 1)
	{
		//1.1 执行公共函数PrintNumber(number);
		PrintNumber(number);
		//1.2 返回
		return;
	}

	//2. 设置index+1是0-9的循环
	for (int i = 0; i < 10; ++i)
	{
		//2.1 数组[index+1]赋值i+'0'
		number[index + 1] = i + '0';

		//2.2 使用递归设置下一位，参数index+1
		Print1ToMaxOfNDigitsRecursively(number, length, index + 1);
	}
}



// ====================公共函数====================
// 字符串number表示一个数字，数字有若干个0开头
// 打印出这个数字，并忽略开头的0
void PrintNumber(char* number)
{
	//1.bool标记第一个数是否为0，默认为0
    bool isBeginning0 = true;
	//2.数组的长度,即n位数，不含'\0'
    int nLength = strlen(number);
	//3.从数组[0]开始打印，循环
    for (int i = 0; i < nLength; ++i)
    {
		//3.1 判断该位是否为零：如果当前bool标记为true,即上一位为0，判断这一位是否为0，如果不是0，将新bool标记改为false。
        //if (isBeginning0 && number[i] != '0')
        //    isBeginning0 = false;
		if (isBeginning0)
			isBeginning0 = number[i] != '0' ? false:true;
		
		//3.2 如果该位不为0，就开始打印
        if (!isBeginning0)
        {
            printf("%c", number[i]);
        }
    }

    printf("\t");
}

// ====================测试代码====================
void Test(int n)
{
    printf("Test for %d begins:\n", n);
	printf("\n Solution 1:\n", n);
    Print1ToMaxOfNDigits_1(n);
	printf("\n Solution 2:\n", n);
    Print1ToMaxOfNDigits_2(n);

    printf("\nTest for %d ends.\n", n);
}

int main(int argc, char* argv[])
{
    Test(1);
    Test(2);
    Test(3);
    Test(0);
    Test(-1);

	system("pause");
    return 0;
}

