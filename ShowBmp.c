#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#pragma pack(1)

// 定义BMP文件头部结构
typedef struct{
	unsigned short bfType;
	unsigned int   bfSize;
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned int   bfOffBits;
}BITMAPFILEHEADER;

typedef struct{
	unsigned int biSize;
	int biWidth;				//宽
	int biHeight;				//高
	unsigned short biPlanes;
	unsigned short biBitCount;	//色深
	unsigned int biCompression;
	unsigned int biSizeImage;
	int biXPelsPerMeter;
	int biYPelsPerMeter;
	unsigned int biClrUsed;
	unsigned int biClrImportant;
}BITMAPINFOHEADER;


#pragma pack()


int main(int argc, char const *argv[])
{
	//1.打开待显示的BMP图像  fopen
	FILE * bmp_fp = fopen("demo.bmp","rb");
	if (NULL == bmp_fp)
	{
		return -1;
	}

	//2.读取BMP文件的图像信息，获取BMP的宽和高
	BITMAPINFOHEADER headerinfo;
	fseek(bmp_fp,14,SEEK_SET);
	fread(&headerinfo,1,40,bmp_fp); //读取40字节
	printf("bmp width = %d,height = %d\n",headerinfo.biWidth,headerinfo.biHeight);

	//3.读取BMP图*片的颜色分量  800*480*3
	char bmp_buf[800*480*3] = {0};
	fread(bmp_buf,1,800*480*3,bmp_fp);

	//4.关闭BMP
	fclose(bmp_fp);

	//5.打开LCD   open  
	int lcd_fd = open("/dev/fb0",O_RDWR);


	//6.对LCD进行内存映射  mmap
	int * lcd_mp = (int *)mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,lcd_fd,0);

	//7.循环的把BMP图像的颜色分量依次写入到LCD的像素点中 
	int i = 0;
	int data = 0;

	for (int y = 480-1; y >= 0; y--)
	{
		for (int x = 0; x < 800 ; ++x)
		{
			//把BMP图片的一个像素点的颜色分量转换为LCD屏幕的一个像素点的颜色分量格式  ARGB <--- BGR
			data |= bmp_buf[i];			//B
			data |= bmp_buf[i+1]<<8;	//G
			data |= bmp_buf[i+2]<<16;  	//R

			lcd_mp[800*y + x] = data;  //BGR BGR BGR .... 

			i+=3;  
			data = 0;
		}
	}
	
	//8.关闭LCD
	close(lcd_fd);
	munmap(lcd_mp,800*480*4);

	return 0;
}