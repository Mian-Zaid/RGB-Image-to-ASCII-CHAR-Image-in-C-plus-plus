//============================================================================
// Name        : ascii-art.cpp
// Author      : Sibt ul Hussain    Muhammad Zaid Ali   i160042
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <cmath>
#include "CImg.h"
using namespace std;
using namespace cimg_library;

#define WIDTH 960
#define HEIGHT 960
double array[10][10]={};
const int divide=8;
void ReadAsciiCharactersImage(double array[250][230])
{

	CImg<unsigned char> img("ascii-char-set-25*23-95.png");
	int k = 0;
	for (int i = 0; i < 250; ++i)
		for (int j = 0; j < 230; ++j)
			array[i][j] = img[k++];

}


void ReadImage(string imgname, double imgArray[HEIGHT][WIDTH])
{
	CImg<unsigned char> img(imgname.c_str());
	int k = 0;
	for (int i = 0; i < img.height(); ++i)
		for (int j = 0; j < img.width();++j)
			imgArray[i][j] = img[k++];
}

//================================================Calculating mean of Ascii Art Image===========================================================//

void mean(double array[250][230],double average[10][10])
{
	double summ=0;

	int m=0,n=25,o=0,p=23;
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			for(int k=m;k<n;k++)
			{
				for(int l=o;l<p;l++)
				{
					summ=summ+array[k][l];
				}
			}
			o=p;
			p=p+23;

			average[i][j]=summ/(25*23);
			summ=0;
		}
		m=n;
		n=n+25;
		o=0,p=23;
	}
	double min=average[0][0];
	double max=average[0][0];
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			if (average[i][j]<min)
			{
				min=average[i][j];
			}
			if (average[i][j]>max)
			{
				max=average[i][j];
			}
		}
	}

	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			average[i][j]=(average[i][j]-min)/(max-min);
		}
	}
}

//==================================================Calculating mean of New  Image===========================================================//

void mean2(double array[HEIGHT][WIDTH],double average[HEIGHT/divide][WIDTH/divide])
{
	double summ=0;

	int m=0,n=divide,o=0,p=divide;
	for(int i=0;i<HEIGHT/divide;i++)
	{
		for(int j=0;j<WIDTH/divide;j++)
		{
			for(int k=m;k<n;k++)
			{
				for(int l=o;l<p;l++)
				{
					summ=summ+array[k][l];
				}
			}
			o=p;
			p=p+divide;

			average[i][j]=summ/(divide*divide);
			summ=0;
		}
		m=n;
		n=n+divide;
		o=0,p=divide;
	}
	double min=average[0][0];
	double max=average[0][0];
	for(int i=0;i<HEIGHT/divide;i++)
	{
		for(int j=0;j<WIDTH/divide;j++)
		{
			if (average[i][j]<min)
			{
				min=average[i][j];
			}
			if (average[i][j]>max)
			{
				max=average[i][j];
			}
		}
	}

	for(int i=0;i<HEIGHT/divide;i++)
	{
		for(int j=0;j<WIDTH/divide;j++)
		{
			average[i][j]=(average[i][j]-min)/(max-min);
		}
	}

}

//============================================Producing New Char Image=================================================================//

void charImage(double average[10][10],double average2[HEIGHT/divide][WIDTH/divide])
{
	double min=0;
	int index=0;
	char image[HEIGHT/divide][WIDTH/divide]={};
	double diff[100]={};
	for(int i=0;i<HEIGHT/divide;i++)
	{
		for(int j=0;j<WIDTH/divide;j++)
		{
				int m=0;
				for(int k=0;k<10;k++)
				{
					for(int l=0;l<10;l++,m++)
					{
						diff[m]=average2[i][j]-average[k][l];
						if(diff[m]<0)
						{
							diff[m]*=-1;
						}
					}
				}
				min=diff[0];
				for(int o=0;o<95;o++)
				{
					if (diff[o]<min)
					{
						min=diff[o];
						index=o;
					}
				}

			image[i][j]=index+32;
		}
	}
	for(int i=0;i<HEIGHT/divide;i++)
	{
		for(int j=0;j<WIDTH/divide;j++)
		{
				cout<<image[i][j];
		}
		cout<<endl;
	}
}


//=============================================================================================================================================//


int main()
{
	double average[10][10];
	double average2[HEIGHT/divide][WIDTH/divide];
	double array[250][230]={};
	ReadAsciiCharactersImage(array);
	mean(array,average);
	double imgArray[HEIGHT][WIDTH]={};
	string imgname;
	cout<<"Please Enter image name\n";
	cin>>imgname;
	ReadImage(imgname,imgArray);
	mean2(imgArray, average2);
	charImage(average,average2);
}
