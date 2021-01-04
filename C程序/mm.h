								 //  *********STC89C52**********
/**********12MHz晶振********/
#include "reg51.h"
#define uint8 unsigned char
#define uint16 unsigned int
#define uchar unsigned char
#define uint unsigned int
uint16 cnt2ms;	//10ms计数器
uint8 cnt1s;	//1秒计数器
//电阻--------------------------------//
#define        Z1 14050053.00  //电阻校正值
 float RZ=0;
unsigned long   RX=0;
unsigned long   RX2=0;
unsigned long   RX3=0;
unsigned long   RX4=0;
unsigned long   RX5=0;
unsigned long   RX6=0;
unsigned long   RX7=0;
unsigned long   RX8=0;
unsigned long   RX9=0;
//电感--------------------------------
 float LZ=0;
#define        C1 0.045//电感校正值
//电容--------------------------------
 float CZ=0;
 float CX=0;
uint8 KL=0;	//
unsigned int Pulsecnt=0;	//脉冲个数
unsigned int Pulsenum;	//脉冲个数
uint8 start=0;	//
uint16 PulseTime;	//10ms计数器
uint16 Pulse;	//10ms计数器
bit flag=0;
uint8 CH=0;	//
unsigned long x;
void Init_Extint(void);
void TimerInitProc();
void Init_System(void);
void Display(uint8 chose_dat, uint8 dat);
void ShowDisp(uint8 tPulsenum, uint8 tPulsecnt, uint8 tcnt1s);
void DelayMs(uint8 Ms);
uint8 Pulse_FLAG=0;
uint8 Pulse_5=0;
/********************************按键*****************************************/
sbit    K1=P1^0;
sbit    K2=P1^1;
sbit    K3=P1^2;
sbit    A0=P2^0;
sbit    A1=P2^1;
sbit    RED=P1^5;
sbit    GRE=P1^4;
sbit    YEW=P1^3;
/********************************LCD液晶**************************************/
sbit CS=P0^0; //RS
sbit SID=P0^1; //R/W
sbit LCD_SCLK=P0^2; //E
void delay_1ms(uint x) 
{ 
uint j; 
uchar i; 
for(j=0;j<x;j++) 
{ 
for(i=0;i<120;i++); 
} 
}
/***********************液晶驱动程序********************/
//------------------写指令----------------------
void send_command(uchar command_data) 
{ 
uchar i; 
uchar i_data,temp_data1,temp_data2; 
i_data=0xf8; 
delay_1ms(10); 
CS=1; 
LCD_SCLK=0; 
for(i=0;i<8;i++) 
{ 
SID=(bit)(i_data&0x80); 
LCD_SCLK=0; 
LCD_SCLK=1; 
i_data=i_data<<1; 
} 
i_data=command_data; 
i_data&=0xf0; 
for(i=0;i<8;i++) 
{ 
SID=(bit)(i_data&0x80); 
LCD_SCLK=0; 
LCD_SCLK=1; 
i_data=i_data<<1; 
} 
i_data=command_data; 
temp_data1=i_data&0xf0; 
temp_data2=i_data&0x0f; 
temp_data1>>=4; 
temp_data2<<=4; 
i_data=temp_data1|temp_data2; 
i_data&=0xf0; 
for(i=0;i<8;i++) 
{ 
SID=(bit)(i_data&0x80); 
LCD_SCLK=0; 
LCD_SCLK=1; 
i_data=i_data<<1; 
} 
CS=0; 
} 
//-----------写数据-------------------
void send_data(uchar command_data) 
{ 
uchar i; 
uchar i_data,temp_data1,temp_data2; 
i_data=0xfa; 
delay_1ms(10); 
CS=1; 
for(i=0;i<8;i++) 
{ 
SID=(bit)(i_data&0x80); 
LCD_SCLK=0; 
LCD_SCLK=1; 
i_data=i_data<<1; 
} 
i_data=command_data; 
i_data&=0xf0; 
for(i=0;i<8;i++) 
{ 
SID=(bit)(i_data&0x80); 
LCD_SCLK=0; 
LCD_SCLK=1; 
i_data=i_data<<1; 
} 
i_data=command_data; 
temp_data1=i_data&0xf0; 
temp_data2=i_data&0x0f; 
temp_data1>>=4; 
temp_data2<<=4; 
i_data=temp_data1|temp_data2; 
i_data&=0xf0; 
for(i=0;i<8;i++) 
{ 
SID=(bit)(i_data&0x80); 
LCD_SCLK=0; 
LCD_SCLK=1; 
i_data=i_data<<1; 
} 
CS=0; 
}
//----------显示字符串------------
void ShowMessage(uchar addr,uchar num,uchar  *ptr)
{
 uchar i;
    send_command(addr);
 for (i=0;i<num;i++) 
 {
 send_data(*ptr);
 *ptr++;
}
}
void lcd_init() 
{ 
delay_1ms(100); 
   send_command(0X30);
   send_command(0X3C);
   send_command(0X38);
   send_command(0X01);
   send_command(0X80);
} 
void Key_SM(void){

        if(K1==0){
             delay_1ms(5);//延时
            if(K1==0){ 
                YEW=1;RED=1; //指示灯转换
                GRE=0;                  
                 
                ShowMessage(0x80,16,"  电感档 Lx   ");
                //----电感档-------
                A0=0; //CD4052选择
                A1=0; 
                CH=2;//电感档

                while(K1==0){}//等待按键释放
                             }
  }
        if(K2==0){
             delay_1ms(5);
            if(K2==0){ 
                GRE=1;YEW=1; 
                RED=0;                  
                ShowMessage(0x80,16,"  电阻档 Rx   ");
               //----电阻档-------
                A0=1; //CD4052选择
                A1=0; 
                CH=1;//电阻档     
                while(K2==0){}//等待按键释放
                     }
                }
       if(K3==0){
             delay_1ms(5);
            if(K3==0){
               YEW=0;GRE=1;RED=1;
               ShowMessage(0x80,16,"  电容档 Cx   "); 
               //----电容档-------
                A0=0; //CD4052选择
                A1=1; 
                CH=3;//电容挡                     
               while(K3==0){}//等待按键释放
                       }
                }
}
void  Value_to_ASCII1(unsigned long value,uchar add)  //欧姆级
{
    unsigned char temp[] = "0000.0欧   ";
    temp[0] = value/1000000 + 0x30;
    value = value%1000000;
    temp[0] = value/100000 + 0x30;
    value = value%100000;
    temp[0] = value/10000 + 0x30;
    value = value%10000;
    temp[1] = value/1000 + 0x30;
    value = value%1000;
    temp[2] = value/100 + 0x30;
    value = value%100;
    temp[3] = value/10 + 0x30;
    value = value%10;
    temp[5] = value + 0x30;
    ShowMessage(add,9,temp);
}
void  Value_to_ASCII2(unsigned long value,uchar add)
{
    unsigned char temp[] = "0.00K    ";		  //K欧姆级别，显示两位小数点
    temp[0] = value/1000000 + 0x30;
    value = value%1000000;
    temp[0] = value/100000 + 0x30;
    value = value%100000;
    temp[0] = value/10000 + 0x30;
    value = value%10000;
    temp[2] = value/1000 + 0x30;
    value = value%1000;
    temp[3] = value/100 + 0x30;  
    ShowMessage(add,9,temp);
}
void  Value_to_ASCII4(unsigned long value,uchar add)
{
    unsigned char temp[] = "000.0K   ";
    temp[0] = value/1000000 + 0x30;//把数字转换成字符
    value = value%1000000;
    temp[1] = value/100000 + 0x30;
    value = value%100000;
    temp[2] = value/10000 + 0x30;
    value = value%10000;
    temp[4] = value/1000 + 0x30;    
    ShowMessage(add,9,temp);
}
void  Value_to_ASCIIL(unsigned long value,uchar add)
{
    unsigned char temp[] = "000000uH  ";
    temp[0] = value/100000 + 0x30;
    value = value%100000;
    temp[1] = value/10000 + 0x30;
    value = value%10000;
    temp[2] = value/1000 + 0x30;
    value = value%1000;
    temp[3] = value/100 + 0x30;
    value = value%100;
    temp[4] = value/10 + 0x30;
    value = value%10;
    temp[5] = value + 0x30;  
    ShowMessage(add,9,temp); 
}
void  Value_to_ASCIIC(unsigned long value,uchar add)
{
    unsigned char temp[] = "00000.0pF ";
    temp[0] = value/100000 + 0x30;
    value = value%100000;
    temp[1] = value/10000 + 0x30;
    value = value%10000;
    temp[2] = value/1000 + 0x30;
    value = value%1000;
    temp[3] = value/100 + 0x30;
    value = value%100;
    temp[4] = value/10 + 0x30;
    value = value%10;
    temp[6] = value + 0x30;   
    ShowMessage(add,9,temp);
}
//--------------------主程序--------------------------------
void main()
{
   //定时器设置
      TMOD=0x51; 		//设置定时器0，方式1:16位定时器
      TH1=0; 
      TL1=0; 
      TH0=(65536-2000)/256; //设定定时周期
      TL0=(65536-2000)%256; 
      TR0=1; 
      TR1=1; 
      ET1=1; 
      ET0=1;
      EA=1;
//----电阻档-------
      A0=1; 
      A1=0;
    lcd_init(); //液晶初始化
 	ShowMessage(0x80,16,"  电阻档 Rx   ");              
    RED=0; 
    CH=1;  
	while(1)
	{
     Key_SM(); //按键检测
    if(flag==1){ //1秒定时标记查询
        flag=0;

        x=Pulsenum*65536+TH1*256+TL1;//计算1s内的脉冲个数，频率=脉冲个数


if(CH==1){//电阻档开启 
        RZ=(Z1/x);//测量1K到1000K
        RX=RZ-1000;
        RX=RX>>1;//RX/2 
        RX=RX*10;//数值扩大10倍
   if(RX>=10040){//减去1K阻值
        RX=RX-10040;
}else{RX=0;}
 if(x==0){RX=0;RX2=0;RX3=0;RX4=0;RX5=0;RX6=0;RX7=0;RX8=0;RX9=0;}//无脉冲后所有的数//字归零
  if(RX>9999999){RX=9999999; }//RX大于9999999，则RX=9999999            
              RX2=(RX+RX3+RX4+RX5+RX6+RX7+RX8+RX9)>>3;//求平均提高精度
RX9=RX8;RX8=RX7;RX7=RX6;RX6=RX5;RX5=RX4;RX4=RX3;RX3=RX;//数值往后移动 保存上一次的阻值     
//单位换算及显示刷新//         
if(RX2<=9999)Value_to_ASCII1(RX2,0x92);//小于999.9Ω用此显示  
if(RX2>9999&&RX2<=99999)Value_to_ASCII2(RX2,0x92); //大于999.9Ω小于9999.9Ω用此显示
if(RX2>99999&&RX2<=9999999)Value_to_ASCII4(RX2,0x92);  
}
if(CH==2){//电感挡      
        LZ=(x*39*C1)/1000000;//电感计算
        LZ=LZ*x;
        LZ=1000000/LZ;
    if(x==0)LZ=0; 
  if(LZ>999999)LZ=999999; //限制最高值
         Value_to_ASCIIL(LZ,0x92);//更新电感值显示
}
if(CH==3){//电容档位
       CZ=6600000/x;//电容挡计算
    if(x==0||x>30500)CZ=0;    
  if(CZ>999999)CZ=999999;  //限制最高值
         Value_to_ASCIIC(CZ,0x92);//更新电容值显示
}
         cnt2ms=0;//定时器清0
         Pulsenum=0;//脉冲个数清0
         TH1=0;
         TL1=0;
         TR1=1; 
    }	
	}
}

