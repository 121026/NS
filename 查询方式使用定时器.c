#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char

//定义控制LED灯的端口
#define LED1 P1_0	//定义LED1为P10口控制

//函数声明
void Delayms(uint xms);		//延时函数
void InitLed(void);		//初始化P1口
void InitT1();                  //初始化定时器T1

/****************************
//延时函数
*****************************/
void Delayms(uint xms)   //i=xms 即延时i毫秒
{
 uint i,j;
 for(i=xms;i>0;i--)
   for(j=587;j>0;j--);
} 

/****************************
//初始化程序
*****************************/
void InitLed(void)
{
    P1DIR |= 0x03; //P1_0定义为输出
    LED1 = 1;       //LED1灯初始化熄灭
    
}
//定时器初始化
void InitT1() //系统不配置工作时钟时默认是2分频，即16MHz
{
  T1CTL = 0x0d;          //128分频，自动重装 0X0000-0XFFFF 
  T1STAT= 0x21;          //通道0, 中断有效   
}

/***************************
//主函数
***************************/
void main(void)
{
        uchar count = 0;
	InitLed();		//调用初始化函数
        InitT1();
	while(1)
	{
          if(IRCON>0)
          { IRCON=0;
            if(++count>=1)      //约1s周期性闪烁
            {
              count=0;
              LED1 = !LED1;        //LED1闪烁        
            }
           } 
	}
}
