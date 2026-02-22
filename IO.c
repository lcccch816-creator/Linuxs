/*






*/



/*

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include "time.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <sys/wait.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
// int main(int argc, char *argv[])
// {
//     //1.要求计算大小的文件的路径需要通过命令行传递给main（），并且需要判断命令行参数的个数是否正确
//     if(argc !=2 )
//     {
//         printf("argument is invalid\n");
//         exit(1);
//     }
//     //2.利用fopen（）以只读方式打开需要计算大小的文件“r”
//     FILE *fp = fopen(argv[1], "ab");
//     if(fp == NULL)
//     {
//         printf("file open failed\n");
//         exit(1);
//     }
//     //3.计算文本数据大小，采用通过循环计数的方式进行，直到文件结束
//     // int cnt = 0;
//     // while(fgetc(fp) != EOF)
//     // {
//     //     cnt++;
//     // }
    
//     // fclose(fp);
//     printf("file[%s]:size is %ld\n",argv[1],ftell(fp));
//     fclose(fp);
//     return 0;
// }


//利用IO函数接口实现文件拷贝，把本地磁盘的文件A中的数据完整的拷贝到另一个文本B中
// #define BUFFERSIZE 512
// int main(int argc, char *argv[])
// {
//     if(argc != 3)
//     {
//         printf("argument is invalid\n");
//         exit(1);
//     }
//     FILE *fp1 = fopen(argv[1], "rb");
//     FILE *fp2 = fopen(argv[2], "wb");
//     if(fp1 == NULL || fp2 == NULL)
//     {
//         printf("file open failed\n");
//         exit(1);
//     }
//     char buffer[BUFFERSIZE];
//     int cnt = 0;//记录待拷贝文件的字节大小
//     fseek(fp1, 0, SEEK_END);//将文件指针移动到文件末尾
//     cnt = ftell(fp1);//获取文件字节大小
//     fseek(fp1, 0, SEEK_SET);//将文件指针移动到文件开头
//     printf("file[%s]:size is %d\n",argv[1],cnt);
//     //计算需要读取数据的次数，循坏写入到目标文件中即可
//     int loop_cnt = 0;
//     loop_cnt = cnt / BUFFERSIZE;
//     int reminder = 0;
//     reminder = cnt % BUFFERSIZE;

//     while(loop_cnt--)
//     {
//         //从待拷贝文件中读取数据到缓冲区
//         fread(buffer, BUFFERSIZE, 1, fp1);
//         //将缓冲区中的数据写入到目标文件中
//         fwrite(buffer, BUFFERSIZE, 1, fp2);
//     }
//     if(reminder > 0)
//     {
//         //需要提前清空数据缓冲区
//         bzero(buffer, BUFFERSIZE);
//         //从待拷贝文件中读取剩余的数据到缓冲区
//         fread(buffer, reminder, 1, fp1);
//         //将缓冲区中的数据写入到目标文件中
//         fwrite(buffer, reminder, 1, fp2);
//     }
//     //验证拷贝是否成功，统计目标文件的数据量
//     printf("file[%s]:size is %ld\n",argv[2],ftell(fp2));
//     //完成拷贝动作，需要分别关闭两个文件
//     fclose(fp1);
//     fclose(fp2);

//     return 0;
// }


// //利用IO函数接口实现获取当前系统时间，把时间转换为特定的格式，年月日星期时分秒，并每隔一秒写入到本地磁盘中一个叫做log.txt的文件中

// int main(int argc, char *argv[])
// {
//     FILE *fp = fopen("log.txt", "ab");
//     if(fp == NULL)
//     {
//         printf("file open failed\n");
//         exit(1);
//     }
//     while(1)
//     {
//         //给结构体指针变量申请一个堆内存空间
//         struct tm *p = localtime( time(NULL));
//         //将时间转换为特定的格式，年月日星期时分秒
//         fprintf(fp, "%d-%d-%d %d %d:%d:%d\n", p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_wday, p->tm_hour, p->tm_min, p->tm_sec);
//         //每隔一秒写入一次
//         sleep(1);
//     }
//     return 0;
// }



//测试open函数接口能打开多少个文件
// int main(int argc, char *argv[])
// {
//     int cnt = 0;
//     while(open("./IO.c", O_RDONLY) != -1)
//     {
//         cnt++;
//     }
//     printf("cnt = %d\n", cnt+3);//+3是因为文件打开之前会打开标准输入，标准输出和标准错误输出
//     return 0;
// }

// int main(int argc, char *argv[])
// {
//     int fb = open("/dev/stdin",O_RDWR);
//     if(-1 == fb)
//     {
//         printf("open failed\n");
//         exit(-1);
//     }

//     int buffer[800*480] = {0};
//     int i = 0;
//     for(;i<800*480;i++)
//     {
//         buffer[i]=0x00FF0000;
//     }
//     write(fb,buffer,800*480*4);
//     close(fb);
//     return 0;

// }

//在屏幕中心画一个圆（800*480）
// int main(int argc, char *argv[])
// {
//     int fb = open("/dev/stdin",O_RDWR);
//     if(-1 == fb)
//     {
//         printf("open failed\n");
//         exit(-1);
//     }

//     int buffer[800*480] = {0};
//     for(int y=240-10;y<240+10;y++)
//     {
//         for(int x=400-10;x<400+10;x++)
//         {
//             if((x-400)*(x-400)+(y-240)*(y-240)<10*10)
//             {
//                 buffer[y*800+x] = 0x00FF0000;
//             }
//         }
//     }
//     write(fb,buffer,800*480*4);
//     close(fb);
//     return 0;

// }


//查看屏幕的参数
// int main(int argc, char *argv[])
// {
//     int fb = open("/dev/fb0",O_RDWR);//打开屏幕设备
//     //定义一个结构体变量，用于存储屏幕参数信息
//     struct fb_var_screeninfo vinfo;
//     if(-1 == fb)
//     {
//         printf("open failed\n");
//         exit(-1);
//     }
//     ioctl(fb, FBIOGET_VSCREENINFO, &vinfo);//获取屏幕参数
//     printf("xres = %d\n",vinfo.xres);
//     printf("yres = %d\n",vinfo.yres);
//     close(fb);
//     return 0;
// }


//使用内存映射的方法，将屏幕设置为红色
// int main(int argc, char *argv[])
// {
//     int fb = open("/dev/fb0",O_RDWR);//打开屏幕设备
//     if(-1 == fb)
//     {
//         printf("open failed\n");
//         exit(-1);
//     }
//     //对lcd进行内存映射， mmap函数，接收返回值
//     int *p = mmap(NULL, 800*480*4, PROT_READ|PROT_WRITE, MAP_SHARED, fb, 0);
//     if(p == MAP_FAILED)
//     {
//         printf("mmap failed\n");
//         exit(-1);
//     }
//     //将颜色分量写入到申请的映射内存空间中，通过地址偏移实现访问。
//     for(int i=0;i<800*480;i++)
//     {
//         p[i] = 0x00FF0000;
//     }
//     //解除内存映射
//     munmap(p, 800*480*4);
//     close(fb);
//     return 0;
//     }


//使用系统IO读取指定的BMP格式图片，以及图片的大小，宽度，并且输出到终端，要求图片名称通过命令行传递
// int main(int argc, const char *argv[])
// {
//     int bmp_size = 0;
//     int bmp_height = 0;
//     int bmp_width =0;
//     if(argc !=2)
//     {
//         printf("argument is invalid\n");
//         exit(-1);
//     }
//     int p = open(argv[1],O_RDWR);
//     if(p == -1)
//     {
//         printf("open %s is error\n",argv[1]);
//         exit(-1);
//     }
//     lseek(p,2,SEEK_SET);
//     read(p,&bmp_size,4);

//     lseek(p,18,SEEK_SET);
//     read(p,&bmp_width,4);

//     lseek(p,22,SEEK_SET);
//     read(p,&bmp_width,4);
//     printf("bmp name is %s,size is %d,height is %d,\n",argv[1],bmp_size,bmp_height);
// }


//显示Bmp图像
#pragma pack(1)
//定义一个结构体，用于存储BMP格式图片的文件头信息
typedef struct {
    unsigned short bfType; //文件类型，0x4D42
    unsigned int bfSize; //文件大小
    unsigned short bfReserved1; //保留字
    unsigned short bfReserved2; //保留字
    unsigned int bfOffBits; //从文件头到像素数据的偏移字节数
} BITMAPFILEHEADER;

//定义一个结构体，用于存储BMP格式图片的信息头信息
typedef struct {
    unsigned int biSize; //信息头大小
    int biWidth; //图像宽度
    int biHeight; //图像高度
    unsigned short biPlanes; //位平面数，必须为1
    unsigned short biBitCount; //每个像素的位数
    unsigned int biCompression; //压缩类型
    unsigned int biSizeImage; //图像数据大小
    int biXPelsPerMeter; //水平分辨率
    int biYPelsPerMeter; //垂直分辨率
    unsigned int biClrUsed; //实际使用的颜色表中的颜色索引数
    unsigned int biClrImportant; //重要的颜色索引数
}   BITMAPINFOHEADER;
#pragma pack()

// int main(int argc, const char *argv[])
// {
//     FILE *bmp_fp = fopen("1.bmp","rb");
//     if(bmp_fp == NULL)
//     {
//         printf("open bmp file failed\n");
//         exit(-1);
//     }
//     //2.读取BMP文件的图像信息，获取BMP的宽和高
//     BITMAPINFOHEADER headerinfo;
//     fseek(bmp_fp,14,SEEK_SET);
//     fread(&headerinfo,1,40,bmp_fp);
//     printf("bmp width = %d\n",headerinfo.biWidth);
//     printf("bmp height = %d\n",headerinfo.biHeight); 

//     char bmp_buffer[800*480*4] = {0};
//     fread(bmp_buffer,1,800*480*4,bmp_fp);

//     fclose(bmp_fp);

//     //3.打开LCD设备，将BMP图像数据写入LCD设备
//     int fb = open("/dev/fb0",O_RDWR);
//     if(-1 == fb)
//     {
//         printf("open failed\n");
//         exit(-1);
//     }

//     //4.对LCD进行内存映射， mmap函数，接收返回值
//     int *p =(int *) mmap(NULL, 800*480*4, PROT_READ|PROT_WRITE, MAP_SHARED, fb, 0);
//     if(p == MAP_FAILED)
//     {
//         printf("mmap failed\n");
//         exit(-1);
//     }
//     //5.将颜色分量依次写入到LCD的像素点中 ARGB<-BGR
//     int i =0;
//     int data = 0;
//     for(int y =480-1;y>=0;y--)
//     {
//         for(int x=0;x<800;x++)
//         {
//             //把BMP图片的一个像素点的颜色分量转换为LCD屏幕的一个像素点的颜色分量格式 3字节的数据放入到4字节的空间
//             data |= bmp_buffer[i+2]<<16;//R
//             data |= bmp_buffer[i+1]<<8;//G
//             data |= bmp_buffer[i];//B

//             p[y*800+x] = data;
//             i+=3;
//             data = 0;
//         }
//     }
//     //6.解除内存映射
//     munmap(p, 800*480*4);
//     close(fb);
//     return 0;

// }

// 设计程序，实现在LCD上任意位置显示一张任意大小的色深为24bit的bmp图片，要求图像不失真可以在开发板的LCD上显示。
int show_bmp(const char *bmp_name,int start_x,int start_y)
{
    FILE *bmp_fp = fopen("1.bmp","rb");
    if(bmp_fp == NULL)
    {
        printf("open bmp file failed\n");
        exit(-1);
    }
    //2.读取BMP文件的图像信息，获取BMP的宽和高
    BITMAPINFOHEADER headerinfo;
    fseek(bmp_fp,14,SEEK_SET);
    fread(&headerinfo,1,40,bmp_fp);
    printf("bmp width = %d\n",headerinfo.biWidth);
    printf("bmp height = %d\n",headerinfo.biHeight);
    //3.读取BMP图像数据

    char bmp_buffer[headerinfo.biWidth*headerinfo.biHeight*3];
    memset(bmp_buffer,0,sizeof(bmp_buffer));//手动清零
    fread(bmp_buffer,1,sizeof(bmp_buffer),bmp_fp);
    fclose(bmp_fp);
    //3.打开LCD设备，将BMP图像数据写入LCD设备
    int fb = open("/dev/fb0",O_RDWR);
    if(-1 == fb)
    {
        printf("open failed\n");
        exit(-1);
    }

    //4.对LCD进行内存映射， mmap函数，接收返回值
    int *p =(int *) mmap(NULL, 800*480*4, PROT_READ|PROT_WRITE, MAP_SHARED, fb, 0);
    if(p == MAP_FAILED)
    {
        printf("mmap failed\n");
        exit(-1);
    }
    //5.将颜色分量依次写入到LCD的像素点中 ARGB<-BGR
    int i =0;
    for(int y = 0 ; y<headerinfo.biHeight;y++)
    {
        for(int x=0;x<headerinfo.biWidth;x++)
        {
            unsigned char b = bmp_buffer[i++];
            unsigned char g = bmp_buffer[i++];
            unsigned char r = bmp_buffer[i++];
            int color = (r<<16)|(g<<8)|b;
            if((start_x + x) < 800 && (start_y + y) < 480)
            {
                p[(start_y+headerinfo.biHeight -1-y) + (start_x+x)] = color;
            }
            }
    }
    //6.解除内存映射
    munmap(p, 800*480*4);
    fclose(fb);
    return 0;
}


//把一张任意尺寸的BMP图片等比例且不失真的缩小为原来的1/2，并生成一张新的BMP图片，要求BMP图片的路径都需要通过命令行进行传递。
// int main(int argc, const char *argv[])
// {
//     if(argc != 3)
//     {
//         printf("usage:./a.out bmp_name bmp_save_name\n");
//         exit(-1);
//     }
//     //1.打开BMP图片
//     FILE *bmp_fp = fopen(argv[1],"rb");
//     if(bmp_fp == NULL)
//     {
//         printf("open bmp file failed\n");
//         exit(-1);
//     }
//     //2.读取BMP文件的图像信息，获取BMP的宽和高
//     BITMAPINFOHEADER headerinfo;
//     fseek(bmp_fp,14,SEEK_SET);
//     fread(&headerinfo,1,40,bmp_fp);
//     printf("bmp width = %d\n,bmp height = %d\n",headerinfo.biWidth,headerinfo.biHeight);
//     //3.读取BMP图像数据
//     char bmp_buffer[headerinfo.biWidth*headerinfo.biHeight*3];
//     memset(bmp_buffer,0,sizeof(bmp_buffer));//手动清零
//     fread(bmp_buffer,1,sizeof(bmp_buffer),bmp_fp);
//     fclose(bmp_fp);

//     //4.创建一张新的BMP图片，宽高为原来的一半
//     FILE *new_bmp_fp = fopen(argv[2],"wb");
//     if(new_bmp_fp == NULL)
//     {
//         printf("open new bmp file failed\n");
//         exit(-1);
//     }
//     //5.写入BMP文件头
//     fwrite("BM",1,2,new_bmp_fp);
//     int file_size = 54 + headerinfo.biWidth/2 * headerinfo.biHeight/2 * 3;
//     fwrite(&file_size,1,4,new_bmp_fp);

// }