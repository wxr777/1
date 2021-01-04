/********************************************
Description:  LCD12864 ���� ,���ô��з�ʽ,
********************************************/ 
sbit lcd_RS =    P2^5; 
sbit Lcd_Rw	=	 P2^6;
sbit Lcd_En	=	 P2^7;

#define BIT(n)	(1<<(n))
#define SID_0   Lcd_Rw=0;
#define SID_1   Lcd_Rw=1; 
#define SCLK_0  Lcd_En=0;
#define SCLK_1  Lcd_En=1; 
//15�� PSB �ӵ͵�ƽ

//����  delay(uchar z)
//������  ��ʱ

void Delay1(uchar z)
{
	uchar a,b;
	for(a=z;a>0;a--)
	 for(b=200;b>0;b--);	
} 

void SendByte(uchar bye)
{
	uchar i;
	for(i=0;i<8;i++)
	{
		if((bye<<i)&0x80){SID_1;}
		else {SID_0;}
		SCLK_1;
	//	delay1us(1);//û����ʱ����
	//     Delay(2);

		SCLK_0;

	}
}

void Lcd_WriteCom(uchar CMD)
{
	SendByte(0xf8);
	SendByte(CMD&0xf0);
	SendByte((CMD<<4)&0xf0);
//	delay1us(90);//8155��ģ�⴮��ͨ��,����,����8155����ʱ,//8M
//	delay1us(250);//16Mʱ����ʱ90us�Ѿ�����������
      Delay1(20);
	  Delay1(20);
	  Delay1(20);
}

void Lcd_WriteDate(uchar Data)
{	SendByte(0xf8+2);
	SendByte(Data&0xf0);
	SendByte((Data<<4)&0xf0);
}

void LCDInit()
{/*	RST=0;
	delay1MS(50);
	RST=1;          */
	lcd_RS=1;
//	DDRB|=(1 << 1)|(1<< 2);
    Lcd_WriteCom(0x34);//�������ã�һ����8λ���ݣ�����ָ�
    Lcd_WriteCom(0x30);//0000,1100  ������ʾ���α�off���α�λ��off
    Lcd_WriteCom(0x01);//0000,0001 ��DDRAM
    Lcd_WriteCom(0x06);//0000,0010 DDRAM��ַ��λ
    Lcd_WriteCom(0x0c);//1000,0000 �趨DDRAM 7λ��ַ000��0000����ַ������AC//     
}

/*****************************
�����ַ���
*****************************/
//void show_str(uchar const *s)//��AVRȥ��const
void  Lcd_String(const uchar  *str)
{ while(*str !='\0')
   { 
   		Lcd_WriteDate(*str++);
     // 	s++;
    //	delay1ms(1);
	//	_delay_ms(2);
	//    Delay(2);
   }
}

void Lcd_Display2data(uchar line,uchar list,uint Date)
{
		uchar i;
		 uchar ta[]={0,0,'\0'};	  //��һ��������װ��
	   list=list &0x07;			       //������ 0-7��
	   switch(line){
				case 1:   Lcd_WriteCom(0x80+list);break;	//��һ��
				case 2:   Lcd_WriteCom(0x90+list);break;	//�ڶ���
				case 3:   Lcd_WriteCom(0x88+list);break;	//������
				case 4:   Lcd_WriteCom(0x98+list);break;	//������
				default : break;
	
	   }
	 for(i=2;i>0;i--)
	 {							  //ѭ���Ĵΰ��ĸ����Ӹߵ���װ��ta
	 	ta[i-1]=Date%10+48;
		Date=Date/10;
	 }
	  Lcd_String(ta);
} 
void Lcd_Display3data(uchar line,uchar list,uint Date)
{
		uchar i;
		 uchar ta[]={0,0,0,0,'\0'};	  //��һ��������װ��
	   list=list &0x07;			       //������ 0-7��
	   switch(line){
				case 1:   Lcd_WriteCom(0x80+list);break;	//��һ��
				case 2:   Lcd_WriteCom(0x90+list);break;	//�ڶ���
				case 3:   Lcd_WriteCom(0x88+list);break;	//������
				case 4:   Lcd_WriteCom(0x98+list);break;	//������
				default : break;
	
	   }
	 for(i=3;i>0;i--)
	 {							  //ѭ���Ĵΰ��ĸ����Ӹߵ���װ��ta
	 	ta[i-1]=Date%10+48;
		Date=Date/10;
	 }
	  Lcd_String(ta);
} 

 ////////////////////////////////////////////////////////////////////
//����	  Lcd_init(uchar com)
//����    ��ȷ��Ļ��ʾ����
//����    line  Һ�����ĵڼ���  list  �ڼ���λ�ÿ�ʼд �����8���У�  DateҪд������

void Lcd_Display22data(uchar line,uchar list,uint Date)
{
	
	  uchar ta[]={0,0,0,'\0'};	  //��һ��������װ��
	   list=list &0x07;			       //������ 0-7��
	   switch(line){
				case 1:   Lcd_WriteCom(0x80+list);break;	//��һ��
				case 2:   Lcd_WriteCom(0x90+list);break;	//�ڶ���
				case 3:   Lcd_WriteCom(0x88+list);break;	//������
				case 4:   Lcd_WriteCom(0x98+list);break;	//������
				default : break;
	
	   }
						  //ѭ���Ĵΰ��ĸ����Ӹߵ���װ��ta
	 	ta[0]=Date/10+48;
		ta[1]=Date%10+48;
		ta[2]= 'C';
	    Lcd_String(ta);
}
 

 ////////////////////////////////////////////////////////////////////
//����	  Lcd_init(uchar com)
//����    ��ȷ��Ļ��ʾ�ַ���
//����    line  Һ�����ĵڼ���  list  �ڼ���λ�ÿ�ʼд �����8���У�  *pҪд���ַ���
void  Lcd_ShowSring(uchar line,uchar list,uchar*p)
{
	 switch(line){
				case 1:   Lcd_WriteCom(0x80+list);break;	//��һ��
				case 2:   Lcd_WriteCom(0x90+list);break;	//�ڶ���
				case 3:   Lcd_WriteCom(0x88+list);break;	//������
				case 4:   Lcd_WriteCom(0x98+list);break;	//������
				default : break;
	
	   }

	    Lcd_String(p);

}

