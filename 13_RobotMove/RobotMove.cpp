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

// 面试题13：机器人的运动范围
// 题目：地上有一个m行n列的方格。一个机器人从坐标(0, 0)的格子开始移动，它
// 每一次可以向左、右、上、下移动一格，但不能进入行坐标和列坐标的数位之和
// 大于k的格子。例如，当k为18时，机器人能够进入方格(35, 37)，因为3+5+3+7=18。
// 但它不能进入方格(35, 38)，因为3+5+3+8=19。请问该机器人能够到达多少个格子？

#include <cstdio>
#include <stdlib.h>
#include <string.h>

int movingCountCore(int threshold, int rows, int cols, int row, int col, bool* visited);
bool check(int threshold, int rows, int cols, int row, int col, bool* visited);
int getDigitSum(int number);

//int movingCount(int threshold, int rows, int cols)
//{
//    if(threshold < 0 || rows <= 0 || cols <= 0)
//        return 0;
//
//    bool *visited = new bool[rows * cols];
//    for(int i = 0; i < rows * cols; ++i)
//        visited[i] = false;
//
//    int count = movingCountCore(threshold, rows, cols,
//        0, 0, visited);
//
//    delete[] visited;
//
//    return count;
//}
//
//int movingCountCore(int threshold, int rows, int cols, int row,
//    int col, bool* visited)
//{
//    int count = 0;
//    if(check(threshold, rows, cols, row, col, visited))
//    {
//        visited[row * cols + col] = true;
//
//        count = 1 + movingCountCore(threshold, rows, cols,
//            row - 1, col, visited)
//            + movingCountCore(threshold, rows, cols,
//                row, col - 1, visited)
//            + movingCountCore(threshold, rows, cols,
//                row + 1, col, visited)
//            + movingCountCore(threshold, rows, cols,
//                row, col + 1, visited);
//    }
//
//    return count;
//}
//
//bool check(int threshold, int rows, int cols, int row, int col,
//    bool* visited)
//{
//    if(row >= 0 && row < rows && col >= 0 && col < cols
//        && getDigitSum(row) + getDigitSum(col) <= threshold
//        && !visited[row* cols + col])
//        return true;
//
//    return false;
//}
//
//int getDigitSum(int number)
//{
//    int sum = 0;
//    while(number > 0)
//    {
//        sum += number % 10;
//        number /= 10;
//    }
//
//    return sum;
//}


 
	//1.计数函数int，参数：阈值int,矩阵行数int,矩阵列数int，返回值：计数int
	int movingCount(int threshold, int rows, int cols)
	{
		//1.1如果阈值为负，矩阵不存在，返回0
		if (threshold<0 || rows<0 || cols<0)
			return 0;

		//1.2分配访问矩阵bool并初始化
		bool* visited = new bool[rows*cols];
		memset(visited, 0, rows*cols);

		//1.3初始化计数为0
		int count = 0;
		//1.4 从(0,0)开始计数
		count = movingCountCore(threshold, rows, cols, 0, 0, visited);


		//返回计数
		return count;
	}


	//2.搜索函数int ,参数：阈值int,矩阵行数int,矩阵列数int，当前行数int,当前列数int,访问矩阵数组bool*,返回值：计数int
	int movingCountCore(int threshold, int rows, int cols, int row, int col, bool* visited)
	{
		//2.1 初始计数为0
		int count = 0;

		//2.2 如果该位置满足条件
		if (check(threshold, rows, cols, row, col, visited))
		{
			//2.2.1 更新访问矩阵
			visited[row*cols + col] = true;

			//2.2.2 从该位置的上下左右开始作为起点依次行递归调用,这里是计数，所以用＋，如果是找存在路径就用或
			count = 1 + movingCountCore(threshold, rows, cols, row - 1, col, visited) +//上
				movingCountCore(threshold, rows, cols, row + 1, col, visited) +//下
				movingCountCore(threshold, rows, cols, row, col - 1, visited) +//左
				movingCountCore(threshold, rows, cols, row, col + 1, visited);//右


		}
		//2.3 返回计数
		return count;
	}

	//3.匹配函数bool,参数：：阈值int,矩阵行数int,矩阵列数int，当前行数int,当前列数int,访问矩阵数组bool*,返回值：是否满足条件 bool
	bool check(int threshold, int rows, int cols, int row, int col, bool* visited)
	{
		//3.1 如果该位置满足条件：1.不越界。2.不超过阈值。3.未曾访问过。则返回真。
		if (row<rows&&col<cols&&col>=0 && row>=0 && !visited[col + cols*row] && getDigitSum(row) + getDigitSum(col) <= threshold)
			return true;
		//3.2 否则返回假。
		return false;
	}

	//4. 计算数位之和函数int,参数：数字int,返回值：数位之和int。
	int getDigitSum(int num)
	{
		//4.1 初始化数为之和为0
		int sum = 0;

		//4.2 循环
		while (num>0)
		{
			//4.2.1 取余，先加个位数
			sum += num % 10;
			//4.2.2 除以10，降一位
			num /= 10;
		}

		//4.3 返回sum
		return sum;
	}

	 

// ====================测试代码====================
void test(char* testName, int threshold, int rows, int cols, int expected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    if(movingCount(threshold, rows, cols) == expected)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}


// 方格多行多列
void test0()
{
	test("Test0", 1, 2, 2, 3);
}

// 方格多行多列
void test1()
{
    test("Test1", 5, 10, 10, 21);
}

// 方格多行多列
void test2()
{
    test("Test2", 15, 20, 20, 359);
}

// 方格只有一行，机器人只能到达部分方格
void test3()
{
    test("Test3", 10, 1, 100, 29);
}

// 方格只有一行，机器人能到达所有方格
void test4()
{
    test("Test4", 10, 1, 10, 10);
}

// 方格只有一列，机器人只能到达部分方格
void test5()
{
    test("Test5", 15, 100, 1, 79);
}

// 方格只有一列，机器人能到达所有方格
void test6()
{
    test("Test6", 15, 10, 1, 10);
}

// 方格只有一行一列
void test7()
{
    test("Test7", 15, 1, 1, 1);
}

// 方格只有一行一列
void test8()
{
    test("Test8", 0, 1, 1, 1);
}

// 机器人不能进入任意一个方格
void test9()
{
    test("Test9", -10, 10, 10, 0);
}

int main(int agrc, char* argv[])
{
	test0();
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();
	test9();
	system("pause");
    return 0;
}
