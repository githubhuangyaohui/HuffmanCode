#pragma once
#include<iostream>
#include<cstdio>
#define MAX 1000
#define SIZE 256
using namespace std;
//���������ڵ��
struct HFNode {
	int wight;	//Ȩֵ
	int parent;	//���ڵ�
	int Lchild;	//����
	int Rchild;	//�Һ���
};
//��������
class HuffmanTree {
public:
	void createHFM(int wight[],int n);		//������������
	void createCode();						//���ɱ����
	int getSize(int wigth[], int n);		//�õ�ѹ�������ֽ���
	char* Encode(char filename[], int nSize);			//ѹ������
private:
	int selectMin(int n);					//�ҵ���СȨֵ��λ��
	char str2byte(char *s);				//�ַ���ת��
private:
	int n;	//wight��
	HFNode hfTree[MAX];
	string code[MAX];
};
//�õ�ѹ�������ֽ���
char* HuffmanTree::Encode(char filename[],int nSize) {
	//����ռ�
	char *out =(char*)malloc(nSize*sizeof(char));
	//��������
	char temp[SIZE] = {0};
	int pos = 0;
	int ch;
	FILE* in = fopen(filename, "rb");
	if (in == NULL) {
		cout << "���ļ�ʧ��" << endl;
	}
	//ɨ���ļ�����ñ���
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
	//�ر��ļ�
	fclose(in);
	return out;
}
//�ַ���ת�룬ÿ�˸��ֽ�
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
//�õ�ѹ�������ֽ���
int HuffmanTree::getSize(int wigth[], int Number) {
	int nSize = 0;
	for (int i = 0; i < Number; i++) {
		nSize += wigth[i] * code[i].length();
	}
	nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;
	return nSize;
}
//��������
void HuffmanTree::createCode() {
	//�ɵ�������
//	cout << "�������\t�����" << endl;
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
//������������
void HuffmanTree::createHFM(int wight[], int Number) {
	//����������ʼ����n��Ҷ�ӽڵ��� 2n-1���ڵ�
	//�����С��n�Ľ��(Ҷ�ӽ��),���ÿ���ֽڵ��ظ�������ΪȨֵ������Щ�ý��
	//������Ҷ�ӽ��Ȩֵ��Ϊ0
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
	//������������ķ�Ҷ�ӽڵ�
	for (int i = 0; i < n-1 ; i++) {
		//�ҵ���һ�ڶ�С��Ȩֵ
		int minF = this->selectMin(n+i);
		this->hfTree[minF].parent = n+i;	//�����½ڵ���
		int minS = this->selectMin(n+i);
		this->hfTree[minS].parent = n+i;	//�����½ڵ���
		//�ϲ����������µĽڵ�
		this->hfTree[n + i].wight = this->hfTree[minF].wight + this->hfTree[minS].wight;
		this->hfTree[n + i].Lchild = minF;
		this->hfTree[n + i].Rchild = minS;
	}
	//�������
	/*
	cout <<  "Ȩֵ\t"  << "������\t"  << "������\t" << "���׽ڵ�"<< endl;
	for (int i = 0; i < 2*n-1; i++) {
		cout << this->hfTree[i].wight << "\t" << this->hfTree[i].Lchild << "\t" << this->hfTree[i].Rchild << "\t" << this->hfTree[i].parent << endl;
	}
	*/
}
//�ҵ�Ȩֵ��С��λ��
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
