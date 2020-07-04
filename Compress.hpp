#pragma once
#include"HuffmanTree.hpp"
#include<stdlib.h>
#include<iostream>
struct  HEAD{
	char type[4];	//�ļ�����
	int length;		//Դ�ļ�����
	int wigth[256];	//Ȩֵ����
};
class Compress {
public:
	Compress();
	void CompressFile(char filename[]);		//ѹ������
	void SaveFile(char filename[]);
private:
	void readFileNum(char filename[]);			//��ȡͳ���ַ���
	void InitHead();
private:
	HuffmanTree hfmTree;
	int wigth[256];		//256���ַ���Ȩֵ
	int n;
	bool isOK;
	char* temp;	//ѹ�����
	int NumberOld ;
	int NumberNow;
	HEAD head;
};
void Compress::SaveFile(char filename[]) {
	this->InitHead();
	char path[256] = { 0 };
	strcpy(path, filename);
	strcat(path,".huf");
	//���ļ�
	FILE* out = fopen(path, "wb");
	fwrite(&head, sizeof(HEAD), 1, out);
	fwrite(temp, sizeof(char),this->NumberNow, out);
	fclose(out);

	cout << "����ѹ���ļ���" << path << endl;
	cout << "ѹ���ȣ�" << 100*double(this->NumberNow + sizeof(HEAD) + strlen(path) + 1) / this->NumberOld <<" %"<< endl;
}
//��ʼ���ļ�ͷ
void Compress::InitHead() {
	strcat(head.type, "HUF");
	head.length = this->NumberOld;
	for(int i=0;i<this->n;i++)
		head.wigth[i] = this->wigth[i];
}
//���캯��
Compress::Compress() {
	memset(this->wigth,0,sizeof(wigth));
	this->isOK = false;
	this->n = 256;
	this->NumberOld = 0;
	this->NumberNow = 0;
}
//ѹ������
void Compress::CompressFile(char filename[]) {
	//��ȡ����
	this->readFileNum(filename);
	//Դ�ļ���С
	cout << "ԭ�ļ���С��" << this->NumberOld << endl;

	//������������
	this->hfmTree.createHFM(this->wigth, this->n);
	
	//���ɱ����
	this->hfmTree.createCode();

	//��ȡ��С
	this->NumberNow = this->hfmTree.getSize(this->wigth,this->n);
	
	//ѹ������
	this->temp=this->hfmTree.Encode(filename,this->NumberNow);
	
	//����
	cout << "���뱣��·����" << endl;
	//cin >> path;
	char path[100] = { "C:\\Users\\HUANGYAOHUI\\Desktop\\Pic.bmp" };
	this->SaveFile(path);
	cout << "ѹ���ɹ�" << endl;
}
//��ȡͳ���ַ���
void Compress::readFileNum(char filename[]) {
	//�Զ��������ķ�ʽ���ļ�
	int ch;
	FILE* in = fopen(filename, "rb");
	if (in == NULL){
		cout << "���ļ�ʧ��" << endl;
	}
	//ɨ���ļ������Ȩ��
	while ((ch = getc(in) )!= EOF){
		wigth[ch]++;
		this->NumberOld++;
	}
	//�ر��ļ�
	fclose(in);
	/*
	for (int i = 0; i < 256; i++)
		cout <<i<<"  :  "<< wigth[i] << endl;
	*/
}