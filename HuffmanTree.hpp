#pragma once
#include<iostream>
#include<cstdio>
#define MAX 1000
#define SIZE 256
using namespace std;
//哈夫曼树节点表
struct HFNode {
	int wight;	//权值
	int parent;	//父节点
	int Lchild;	//左孩子
	int Rchild;	//右孩子
};
//哈夫曼树
class HuffmanTree {
public:
	void createHFM(int wight[],int n);		//构建哈夫曼树
	void createCode();						//生成编码表
	int getSize(int wigth[], int n);		//得到压缩数据字节数
	char* Encode(char filename[], int nSize);			//压缩编码
private:
	int selectMin(int n);					//找到最小权值的位置
	char str2byte(char *s);				//字符串转码
private:
	int n;	//wight数
	HFNode hfTree[MAX];
	string code[MAX];
};
//得到压缩数据字节数
char* HuffmanTree::Encode(char filename[],int nSize) {
	//分配空间
	char *out =(char*)malloc(nSize*sizeof(char));
	//缓存区域
	char temp[SIZE] = {0};
	int pos = 0;
	int ch;
	FILE* in = fopen(filename, "rb");
	if (in == NULL) {
		cout << "打开文件失败" << endl;
	}
	//扫描文件，获得编码
	while ((ch = fgetc(in)) != EOF) {
		strcat(temp, this->code[ch].c_str());
		while (strlen(temp) >= 8) {
			out[pos++] = str2byte(temp);
			for (int i = 0; i < SIZE - 8; i++) {
				temp[i] = temp[i + 8];
			}
		}
	}
	if (strlen(temp) > 0)
		out[pos++]= str2byte(temp);
	//关闭文件
	fclose(in);
	return out;
}
//字符串转码，每八个字节
char HuffmanTree::str2byte(char *s) {
	char b = 0x00;
	for (int i = 0; i <  8; i++) {
		b = b << 1;
		if (s[i] =='1') {
			b = b | 0x01;
		}
	}
	return b;
}
//得到压缩数据字节数
int HuffmanTree::getSize(int wigth[], int Number) {
	int nSize = 0;
	for (int i = 0; i < Number; i++) {
		nSize += wigth[i] * code[i].length();
	}
	nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;
	return nSize;
}
//构造编码表
void HuffmanTree::createCode() {
	//由底向上找
//	cout << "编码序号\t编码表" << endl;
	for (int i = 0; i < this->n; i++) {
		string s;
		int temp=i;
		while (this->hfTree[temp].parent != -1) {
			if (this->hfTree[this->hfTree[temp].parent].Lchild == temp)
				s += '0';
			else
				s += '1';
			temp = this->hfTree[temp].parent;
		}
		reverse(s.begin(), s.end());
		//cout <<i<<"\t"<< s << endl;
		this->code[i] = s;
	}
}
//创建哈夫曼树
void HuffmanTree::createHFM(int wight[], int Number) {
	//哈夫曼树初始化，n个叶子节点有 2n-1个节点
	//如果是小于n的结点(叶子结点),则把每个字节的重复次数作为权值赋给这些该结点
	//其他非叶子结点权值设为0
	this->n = Number;
	for (int i = 0; i < 2 * n - 1; i++){
		if (i < n)	
			this->hfTree[i].wight = wight[i];
		else
			this->hfTree[i].wight = 0;	
		hfTree[i].parent = -1;
		hfTree[i].Lchild = -1;
		hfTree[i].Rchild = -1;
	}
	//构造哈夫曼树的非叶子节点
	for (int i = 0; i < n-1 ; i++) {
		//找到第一第二小的权值
		int minF = this->selectMin(n+i);
		this->hfTree[minF].parent = n+i;	//挂在新节点上
		int minS = this->selectMin(n+i);
		this->hfTree[minS].parent = n+i;	//挂在新节点上
		//合并两个生成新的节点
		this->hfTree[n + i].wight = this->hfTree[minF].wight + this->hfTree[minS].wight;
		this->hfTree[n + i].Lchild = minF;
		this->hfTree[n + i].Rchild = minS;
	}
	//测试输出
	/*
	cout <<  "权值\t"  << "左子树\t"  << "右子树\t" << "父亲节点"<< endl;
	for (int i = 0; i < 2*n-1; i++) {
		cout << this->hfTree[i].wight << "\t" << this->hfTree[i].Lchild << "\t" << this->hfTree[i].Rchild << "\t" << this->hfTree[i].parent << endl;
	}
	*/
}
//找到权值最小的位置
int HuffmanTree::selectMin(int n) {
	int minValue = INT_MAX;
	int minIndex = -1;
	for (int i = 0; i < n; i++) {
		if (this->hfTree[i].wight < minValue && this->hfTree[i].parent == -1) {
			minIndex = i;
			minValue = this->hfTree[i].wight;
		}
	}
	return minIndex;
}
