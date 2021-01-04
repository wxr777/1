					  /********************************************
Description:  LCD12864 驱动 ,采用串行方式,
********************************************/ 

//******12864**************
//#define CS =    ;   //RS  接高电平//RW//EN


sbit Lcd_Rw	=	 P2^4;
sbit Lcd_En	=	 P2^5;

#define BIT(n)	(1<<(n))
#define SID_0   Lcd_Rw=0;
#define SID_1   Lcd_Rw=1; 
#define SCLK_0  Lcd_En=0;
#define SCLK_1  Lcd_En=1; 
//15脚 PSB 接低电平



void SendByte(uchar bye)
{
	uchar i;
	for(i=0;i<8;i++)
	{
		if((bye<<i)&0x80){SID_1;}
		else {SID_0;}
		SCLK_1;
	//	delay1us(1);//没有延时不行
	     Delay(2);

		SCLK_0;

	}
}

void Lcd_WriteCom(uchar CMD)
{
	SendByte(0xf8);
	SendByte(CMD&0xf0);
	SendByte((CMD<<4)&0xf0);
//	delay1us(90);//8155来模拟串行通信,所以,加上8155的延时,//8M
//	delay1us(250);//16M时，延时90us已经不够！！！
      Delay(250);
	  Delay(250);
	  Delay(250);
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
//	DDRB|=(1 << 1)|(1<< 2);
    Lcd_WriteCom(0x34);//功能设置，一次送8位数据，基本指令集
    Lcd_WriteCom(0x30);//0000,1100  整体显示，游标off，游标位置off
    Lcd_WriteCom(0x01);//0000,0001 清DDRAM
    Lcd_WriteCom(0x06);//0000,0010 DDRAM地址归位
    Lcd_WriteCom(0x0c);//1000,0000 设定DDRAM 7位地址000，0000到地址计数器AC//     
}

/*****************************
发送字符串
*****************************/
//void show_str(uchar const *s)//改AVR去掉const

void  Lcd_String(const uchar  *str)
{ while(*str !='\0')
   { 
   		Lcd_WriteDate(*str++);
     // 	s++;
    //	delay1ms(1);
	//	_delay_ms(2);
	    Delay(2);
   }
}

//***************************************
 /*void desplay1(uint temp,uchar dizhi)
{	
 	 uchar i; 
	 uchar ta[]={0,0,0,0,0,'\0'};	  //用一个数组来装数
	 for(i=5;i>0;i--)
	 {							  //循环四次把四个数从高到低装入ta
	 	ta[i-1]=temp%10+48;
		temp=temp/10;
	 }

	Lcd_WriteCom(dizhi);			  
	show_str(ta);	 //送出将要显示的首地址
}*/
 
 
 /*void change ( uint ta)
{	
	uchar g,s,b,q;               //g 位的是数 s位的数 
		
	q=  ta /4096;
    b = ta /256%16;
    s = ta /16%16;
	g = ta %16;
	if(q >9) q += 7;
	if(b >9) b += 7;
    if(s >9) s += 7;
    if(g >9) g += 7;
	
}   */
void display(uchar dz,uint temp)
{

	//change(temp); //显示地址码
	uchar g,s,b,q;               //g 位的是数 s位的数 
		
	q=  temp/4096;
    b = temp /256%16;
    s = temp /16%16;
	g = temp %16;

	if(q >9) q += 7;
	if(b >9) b += 7;
    if(s >9) s += 7;
    if(g >9) g += 7;

 	Lcd_WriteCom( dz);
 	Lcd_WriteDate(q+48);
	Lcd_WriteDate(b+48);
 	Lcd_WriteDate(s+48);
 	Lcd_WriteDate(g+48);
}

void display1(uchar dz,const uchar *p)
{
	Lcd_WriteCom( dz);
	 Lcd_String(p);
		
}


void display2(uchar dizhi,uint temp)
{	
 	 uchar i; 
	 uchar ta[]={0,0,0,0,0,'\0'};	  //用一个数组来装数
	 for(i=5;i>0;i--)
	 {							  //循环四次把四个数从高到低装入ta
	 	ta[i-1]=temp%10+48;
		temp=temp/10;
	 }

	Lcd_WriteCom(dizhi);			  
	 Lcd_String(ta);	 //送出将要显示的首地址
}

void display3(uchar dz,uint temp ,uchar num)
{	
 	 uchar i; 
	 uchar ta[]={0,0,0,0};	  //用一个数组来装数
	 for(i=4;i>0;i--)
	 {							  //循环四次把四个数从高到低装入ta
	 	ta[i-1]=temp%10+48;
		temp=temp/10;
	 }

     Lcd_WriteCom( dz);
/*	 if(num==4)
	 {		
	 		
	       Lcd_WriteDate(ta[0]);
		   Lcd_WriteDate(' '); 
		   Lcd_WriteDate(ta[1]);	
		   Lcd_WriteDate(' '); 	    
		   Lcd_WriteDate(ta[2]);
		   Lcd_WriteDate(' '); 
		    Lcd_WriteDate(0x2e);
		   Lcd_WriteDate(ta[3]);
	 }
	 else
	 {  
	  
		 
		   Lcd_WriteDate(ta[1]);	
		   Lcd_WriteDate(' '); 	    
		   Lcd_WriteDate(ta[2]);
		   Lcd_WriteDate(' '); 
		   Lcd_WriteDate(0x2e);
		   Lcd_WriteDate(ta[3]);
		  	
   
	  }*/
      switch(num)
	  {
		case 0: if(ta[0]==48)
		        {
					for(i=1;i<4;i++)
					{    
					     Lcd_WriteDate(ta[i]);
					     Lcd_WriteDate(' ');
					}
				}
				else
				{
					for(i=0;i<4;i++)
					{    
					     Lcd_WriteDate(ta[i]);
					     Lcd_WriteDate(' ');
					}
				}break;
		case 1:  if(ta[0]==48)				  	   
		         {     Lcd_WriteDate(ta[1]);	
					   Lcd_WriteDate(' '); 	    
					   Lcd_WriteDate(ta[2]);
					   Lcd_WriteDate(' '); 
					   Lcd_WriteDate(0x2e);
					   Lcd_WriteDate(ta[3]);
					   
			      }
				  else
				  {
				  	   Lcd_WriteDate(ta[0]);
					   Lcd_WriteDate(' '); 
					   Lcd_WriteDate(ta[1]);	
					   Lcd_WriteDate(' '); 	    
					   Lcd_WriteDate(ta[2]);
					   Lcd_WriteDate(' '); 
					    Lcd_WriteDate(0x2e);
					   Lcd_WriteDate(ta[3]);
				  }break;
		default :break;


	  }
	  


}


 ////////////////////////////////////////////////////////////////////
//函数	  Lcd_init(uchar com)
//功能    精确屏幕显示数据
//参数    line  液晶屏的第几行  list  第几个位置开始写 （最多8个列）  Date要写的数据

void Lcd_Display(uchar line,uchar list,uint Date)
{
		uchar i;
		 uchar ta[]={0,0,0,0,'\0'};	  //用一个数组来装数
	   list=list &0x07;			       //限制在 0-7列
	   switch(line){
				case 1:   Lcd_WriteCom(0x80+list);break;	//第一行
				case 2:   Lcd_WriteCom(0x90+list);break;	//第二行
				case 3:   Lcd_WriteCom(0x88+list);break;	//第三行
				case 4:   Lcd_WriteCom(0x98+list);break;	//第四行
				default : break;
	
	   }
	 for(i=4;i>0;i--)
	 {							  //循环四次把四个数从高到低装入ta
	 	ta[i-1]=Date%10+48;
		Date=Date/10;
	 }
	  Lcd_String(ta);
}

 ////////////////////////////////////////////////////////////////////
//函数	  Lcd_init(uchar com)
//功能    精确屏幕显示字符串
//参数    line  液晶屏的第几行  list  第几个位置开始写 （最多8个列）  *p要写的字符串

void  Lcd_ShowSring(uchar line,uchar list,uchar*p)
{
	 switch(line){
				case 1:   Lcd_WriteCom(0x80+list);break;	//第一行
				case 2:   Lcd_WriteCom(0x90+list);break;	//第二行
				case 3:   Lcd_WriteCom(0x88+list);break;	//第三行
				case 4:   Lcd_WriteCom(0x98+list);break;	//第四行
				default : break;
	
	   }

	    Lcd_String(p);

}

