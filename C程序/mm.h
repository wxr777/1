								 //  *********STC89C52**********
/**********12MHz����********/
#include "reg51.h"
#define uint8 unsigned char
#define uint16 unsigned int
#define uchar unsigned char
#define uint unsigned int
uint16 cnt2ms;	//10ms������
uint8 cnt1s;	//1�������
//����--------------------------------//
#define        Z1 14050053.00  //����У��ֵ
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
//���--------------------------------
 float LZ=0;
#define        C1 0.045//���У��ֵ
//����--------------------------------
 float CZ=0;
 float CX=0;
uint8 KL=0;	//
unsigned int Pulsecnt=0;	//�������
unsigned int Pulsenum;	//�������
uint8 start=0;	//
uint16 PulseTime;	//10ms������
uint16 Pulse;	//10ms������
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
/********************************����*****************************************/
sbit    K1=P1^0;
sbit    K2=P1^1;
sbit    K3=P1^2;
sbit    A0=P2^0;
sbit    A1=P2^1;
sbit    RED=P1^5;
sbit    GRE=P1^4;
sbit    YEW=P1^3;
/********************************LCDҺ��**************************************/
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
/***********************Һ����������********************/
//------------------дָ��----------------------
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
//-----------д����-------------------
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
//----------��ʾ�ַ���------------
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
             delay_1ms(5);//��ʱ
            if(K1==0){ 
                YEW=1;RED=1; //ָʾ��ת��
                GRE=0;                  
                 
                ShowMessage(0x80,16,"  ��е� Lx   ");
                //----��е�-------
                A0=0; //CD4052ѡ��
                A1=0; 
                CH=2;//��е�

                while(K1==0){}//�ȴ������ͷ�
                             }
  }
        if(K2==0){
             delay_1ms(5);
            if(K2==0){ 
                GRE=1;YEW=1; 
                RED=0;                  
                ShowMessage(0x80,16,"  ���赵 Rx   ");
               //----���赵-------
                A0=1; //CD4052ѡ��
                A1=0; 
                CH=1;//���赵     
                while(K2==0){}//�ȴ������ͷ�
                     }
                }
       if(K3==0){
             delay_1ms(5);
            if(K3==0){
               YEW=0;GRE=1;RED=1;
               ShowMessage(0x80,16,"  ���ݵ� Cx   "); 
               //----���ݵ�-------
                A0=0; //CD4052ѡ��
                A1=1; 
                CH=3;//���ݵ�                     
               while(K3==0){}//�ȴ������ͷ�
                       }
                }
}
void  Value_to_ASCII1(unsigned long value,uchar add)  //ŷķ��
{
    unsigned char temp[] = "0000.0ŷ   ";
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
    unsigned char temp[] = "0.00K    ";		  //Kŷķ������ʾ��λС����
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
    temp[0] = value/1000000 + 0x30;//������ת�����ַ�
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
//--------------------������--------------------------------
void main()
{
   //��ʱ������
      TMOD=0x51; 		//���ö�ʱ��0����ʽ1:16λ��ʱ��
      TH1=0; 
      TL1=0; 
      TH0=(65536-2000)/256; //�趨��ʱ����
      TL0=(65536-2000)%256; 
      TR0=1; 
      TR1=1; 
      ET1=1; 
      ET0=1;
      EA=1;
//----���赵-------
      A0=1; 
      A1=0;
    lcd_init(); //Һ����ʼ��
 	ShowMessage(0x80,16,"  ���赵 Rx   ");              
    RED=0; 
    CH=1;  
	while(1)
	{
     Key_SM(); //�������
    if(flag==1){ //1�붨ʱ��ǲ�ѯ
        flag=0;

        x=Pulsenum*65536+TH1*256+TL1;//����1s�ڵ����������Ƶ��=�������


if(CH==1){//���赵���� 
        RZ=(Z1/x);//����1K��1000K
        RX=RZ-1000;
        RX=RX>>1;//RX/2 
        RX=RX*10;//��ֵ����10��
   if(RX>=10040){//��ȥ1K��ֵ
        RX=RX-10040;
}else{RX=0;}
 if(x==0){RX=0;RX2=0;RX3=0;RX4=0;RX5=0;RX6=0;RX7=0;RX8=0;RX9=0;}//����������е���//�ֹ���
  if(RX>9999999){RX=9999999; }//RX����9999999����RX=9999999            
              RX2=(RX+RX3+RX4+RX5+RX6+RX7+RX8+RX9)>>3;//��ƽ����߾���
RX9=RX8;RX8=RX7;RX7=RX6;RX6=RX5;RX5=RX4;RX4=RX3;RX3=RX;//��ֵ�����ƶ� ������һ�ε���ֵ     
//��λ���㼰��ʾˢ��//         
if(RX2<=9999)Value_to_ASCII1(RX2,0x92);//С��999.9���ô���ʾ  
if(RX2>9999&&RX2<=99999)Value_to_ASCII2(RX2,0x92); //����999.9��С��9999.9���ô���ʾ
if(RX2>99999&&RX2<=9999999)Value_to_ASCII4(RX2,0x92);  
}
if(CH==2){//��е�      
        LZ=(x*39*C1)/1000000;//��м���
        LZ=LZ*x;
        LZ=1000000/LZ;
    if(x==0)LZ=0; 
  if(LZ>999999)LZ=999999; //�������ֵ
         Value_to_ASCIIL(LZ,0x92);//���µ��ֵ��ʾ
}
if(CH==3){//���ݵ�λ
       CZ=6600000/x;//���ݵ�����
    if(x==0||x>30500)CZ=0;    
  if(CZ>999999)CZ=999999;  //�������ֵ
         Value_to_ASCIIC(CZ,0x92);//���µ���ֵ��ʾ
}
         cnt2ms=0;//��ʱ����0
         Pulsenum=0;//���������0
         TH1=0;
         TL1=0;
         TR1=1; 
    }	
	}
}

