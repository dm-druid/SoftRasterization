#pragma once

#include <stdio.h>
#include <malloc.h>

#define BM 19778		// λͼ�ı�־

#define PATH "texture.bmp"  //�򿪵��ļ�·�� 

//�ж��Ƿ���λͼ,��0-1�ֽ� 
int IsBitMap (FILE *fp) {
	unsigned short s;
	fseek (fp, 0, SEEK_SET);
	fread (&s, 1, 2, fp);
	if (s == BM)
		return 1;
	else
		return 0;
}

//���ͼƬ�Ŀ��,��18-21�ֽ� 
long getWidth (FILE *fp) {
	long width;
	fseek (fp, 18L, SEEK_SET);
	fread (&width, 1, 4, fp);
	return width;
}

//���ͼƬ�ĸ߶� ����22-25�ֽ� 
long getHeight (FILE *fp) {
	long height;
	fseek (fp, 22L, SEEK_SET);
	fread (&height, 1, 4, fp);
	return height;
}

//���ÿ�����ص�λ��,��28-29�ֽ� 
unsigned short getBit (FILE *fp) {
	unsigned short bit;
	fseek (fp, 28, SEEK_SET);
	fread (&bit, 1, 2, fp);
	return bit;
}

//������ݵ���ʼλ��
unsigned int getOffSet (FILE *fp) {
	unsigned int OffSet;
	fseek (fp, 10L, SEEK_SET);
	fread (&OffSet, 1, 4, fp);
	return OffSet;
}

//���ͼ�������
void getData (FILE* fp, unsigned char *r, unsigned char *g, unsigned char *b) {
	int i, j = 0;
	int stride;
	unsigned char* pix = NULL;
	long height, width;
	height = getHeight (fp);
	width = getWidth (fp);

	fseek (fp, getOffSet (fp), SEEK_SET);	//�ҵ�λͼ�������� 

	stride = (24 * width) / 8;	//����,����һ��width�ж��ٸ�8λ 
	stride = stride / 4 * 4;		//ȡ�ĵı��� r,g,b,alph 
									//д������ 
	pix = (unsigned char *)malloc (stride);
	for (j = 0; j<height; j++) {
		fread (pix, 1, stride, fp);
		for (i = 0; i<width; i++) {
			*(r + (height - 1 - j) * width + i) = pix[i * 3 + 2];
			*(g + (height - 1 - j) * width + i) = pix[i * 3 + 1];
			*(b + (height - 1 - j) * width + i) = pix[i * 3];
		}
	}

	/*for (j = 0; j<height; j++) {
		for (i = 0; i<width; i++) {
			printf ("%4d-", *(r + i + j));
			printf ("%4d-", *(g + i + j));
			printf ("%4d", *(b + i + j));
			printf ("\t");
		}
	}*/
}