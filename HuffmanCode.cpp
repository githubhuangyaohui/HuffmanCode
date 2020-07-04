// HuffmanCode.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
/*
创建工程。
2、读取源文件。
3、生成哈夫曼树。
4、生成哈夫曼编码。
5、压缩原文件。
6、保存压缩文件。
7、扩展功能。
*/
#include <iostream>
#include<string>
#include"Compress.hpp"
using namespace std;
int main(){
    int sign = 0;
    Compress *compress=new Compress();
    cout << "-----------------------哈夫曼图片压缩实现-----------------------"<<endl;
    cout << "输入文件名（路径）：" << endl;
    char path[100] = { "C:\\Users\\HUANGYAOHUI\\Desktop\\Pic.bmp" };
    cout << path << endl;
    //cin >> path;
    compress->CompressFile(path);
    return 0;
}