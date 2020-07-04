#pragma once
#include"HuffmanTree.hpp"
#include<stdlib.h>
#include<iostream>
struct  HEAD{
	char type[4];	//文件类型
	int length;		//源文件长度
	int wigth[256];	//权值数组
};
class Compress {
public:
	Compress();
	void CompressFile(char filename[]);		//压缩函数
	void SaveFile(char filename[]);
private:
	void readFileNum(char filename[]);			//读取统计字符数
	void InitHead();
private:
	HuffmanTree hfmTree;
	int wigth[256];		//256个字符的权值
	int n;
	bool isOK;
	char* temp;	//压缩结果
	int NumberOld ;
	int NumberNow;
	HEAD head;
};
void Compress::SaveFile(char filename[]) {
	this->InitHead();
	char path[256] = { 0 };
	strcpy(path, filename);
	strcat(path,".huf");
	//打开文件
	FILE* out = fopen(path, "wb");
	fwrite(&head, sizeof(HEAD), 1, out);
	fwrite(temp, sizeof(char),this->NumberNow, out);
	fclose(out);

	cout << "生成压缩文件：" << path << endl;
	cout << "压缩比：" << 100*double(this->NumberNow + sizeof(HEAD) + strlen(path) + 1) / this->NumberOld <<" %"<< endl;
}
//初始化文件头
void Compress::InitHead() {
	strcat(head.type, "HUF");
	head.length = this->NumberOld;
	for(int i=0;i<this->n;i++)
		head.wigth[i] = this->wigth[i];
}
//构造函数
Compress::Compress() {
	memset(this->wigth,0,sizeof(wigth));
	this->isOK = false;
	this->n = 256;
	this->NumberOld = 0;
	this->NumberNow = 0;
}
//压缩函数
void Compress::CompressFile(char filename[]) {
	//读取数据
	this->readFileNum(filename);
	//源文件大小
	cout << "原文件大小：" << this->NumberOld << endl;

	//构建哈夫曼树
	this->hfmTree.createHFM(this->wigth, this->n);
	
	//生成编码表
	this->hfmTree.createCode();

	//获取大小
	this->NumberNow = this->hfmTree.getSize(this->wigth,this->n);
	
	//压缩数据
	this->temp=this->hfmTree.Encode(filename,this->NumberNow);
	
	//保存
	cout << "输入保存路径：" << endl;
	//cin >> path;
	char path[100] = { "C:\\Users\\HUANGYAOHUI\\Desktop\\Pic.bmp" };
	this->SaveFile(path);
	cout << "压缩成功" << endl;
}
//读取统计字符数
void Compress::readFileNum(char filename[]) {
	//以二进制流的方式打开文件
	int ch;
	FILE* in = fopen(filename, "rb");
	if (in == NULL){
		cout << "打开文件失败" << endl;
	}
	//扫描文件，获得权重
	while ((ch = getc(in) )!= EOF){
		wigth[ch]++;
		this->NumberOld++;
	}
	//关闭文件
	fclose(in);
	/*
	for (int i = 0; i < 256; i++)
		cout <<i<<"  :  "<< wigth[i] << endl;
	*/
}