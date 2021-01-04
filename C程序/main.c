#include <reg52.h>
#define uchar unsigned char
#define uint  unsigned	int


sbit key1 = P1^2;	   //按键输入
sbit key2 = P1^3;
sbit key3 = P1^4;

sbit LED  = P1^0;	   //光强度报警指示灯
sbit FENG = P1^1;	   //风扇去湿
sbit FMQ  = P1^5;	   //蜂鸣器

sbit JDQ_S = P1^7;	  //加湿继电器

sbit JDQ_R = P3^7;	  // 加热继电器
sbit JDQ_L = P3^6;	  //制冷继电器

unsigned char key_mode=0;
unsigned char Set_mode=0;   //设置模式

uint wendu;	 //	温度数值
uchar light;
bit baojing=1;	//报警标志
int set_w_num_H=38,set_w_num_L=10;   //设置的上下限数值
int set_s_num_H=80,set_s_num_L=0;
int set_g_num_H=50,set_g_num_L=0;

#include<Lcd12864.h>		   //头文件
#include<dht11.c>
#include<adc0832.c>
#include<eeprom.c>

void Delay(uchar t)				//延时程序
{
    uint i,j;  
	for(i=t;i>0;i--)   
	for(j=110;j>0;j--); 	

} 
//按键扫面
 void scant()
  {
  		if(!key1){
		
					while(!key1);
					if(key_mode<6){
							key_mode++;
							
					}
					else{ 					       
							key_mode=0;
							Set_mode=0;
							Lcd_ShowSring(4,6," ");
						//	Lcd_ShowSring(2,0,"             ");
						  	ISP_ERASE(0x2c00);		//注意：字节编程时必须要先要擦除整个扇区	
							ISP_PROGRAM(0x2c00, set_w_num_H/256);
							ISP_PROGRAM(0x2c01, set_w_num_H);
							/////////////////////////////////////
							ISP_PROGRAM(0x2c02, set_w_num_L/256);
							ISP_PROGRAM(0x2c03, set_w_num_L);
						  /////////////////////////////////////////
							ISP_PROGRAM(0x2c04, set_s_num_H/256);
							ISP_PROGRAM(0x2c05, set_s_num_H);
						   /////////////////////////////////////////
							ISP_PROGRAM(0x2c06, set_s_num_L/256);
							ISP_PROGRAM(0x2c07, set_s_num_L);
						 /////////////////////////////////////////

							ISP_PROGRAM(0x2c08, set_g_num_H/256);
							ISP_PROGRAM(0x2c09, set_g_num_H);
						   /////////////////////////////////////////
							ISP_PROGRAM(0x2c0a, set_g_num_L/256);
							ISP_PROGRAM(0x2c0b, set_g_num_L);


					}
				
			}
			switch(key_mode){
					case 0: Lcd_ShowSring(1,7," "); break;
					       
			 /////////////==========温度通道========////////////////////////////////
					case 1: Lcd_ShowSring(1,7,"1");FMQ=1;FENG=1;Set_mode=1;Lcd_ShowSring(2,6,"H");
					        JDQ_R=1;JDQ_L=1;JDQ_S=1;Lcd_ShowSring(2,7,"  ");Lcd_ShowSring(3,7,"  ");
							Lcd_ShowSring(4,7,"  ");break;
					case 2: Lcd_ShowSring(1,7,"1");Lcd_ShowSring(2,6,"L");break;
			 /////////////==========湿度通道========////////////////////////////////
					case 3: Lcd_ShowSring(1,7,"2");Lcd_ShowSring(3,6,"H");Lcd_ShowSring(2,6,"  ");break;
					case 4: Lcd_ShowSring(1,7,"2");Lcd_ShowSring(3,6,"L");break;
			 /////////////==========光度通道========////////////////////////////////
					case 5: Lcd_ShowSring(1,7,"3");Lcd_ShowSring(4,6,"H");Lcd_ShowSring(3,6,"  ");break;
					case 6: Lcd_ShowSring(1,7,"3");Lcd_ShowSring(4,6,"L");break;
					default :break;
			     }
		
///////////////////////////////////////////////////////////////////////////////////////////////////
		 //模式a，通道温度进行设置加减	  //温度上限
		if(key_mode==1){
				 if(!key2){
					Delay(10);
					if(!key2){
					///		while(!key2);
							if(set_w_num_H<99) {

								set_w_num_H++;
							}
							else {
								set_w_num_H=0;
							}							
						 
					}
					
				}
				 if(!key3){
					Delay(10);
					if(!key3){
					//		while(!key3);
							if(set_w_num_H>0) {

									set_w_num_H--;
							}
							else {
								   set_w_num_H=99;
							}

					}
					
				}
					 Lcd_Display22data(2,3,set_w_num_H);

		}
  	if(key_mode==2){						  //下限
				 if(!key2){
					Delay(10);
					if(!key2){
					///		while(!key2);
							if(set_w_num_L<99) {

								set_w_num_L++;
							}
							else {
								set_w_num_L=0;
							}							
					
					}
					
				}
				 if(!key3){
					Delay(10);
					if(!key3){
					//		while(!key3);
							if(set_w_num_L>0) {

									set_w_num_L--;
							}
							else {
								   set_w_num_L=99;
							}
						
					}
					
				}
				  Lcd_Display22data(2,3,set_w_num_L);

		}
//////////////////////模式b，湿度进行设置加减/////////////////////////////////////湿度上限
        if(key_mode==3){
				 if(!key2){
					Delay(10);
					if(!key2){
			
							if(set_s_num_H<99) {

									set_s_num_H++;
							}
							else {
									set_s_num_H=0;
							}	
		
					}
					
				}
				 if(!key3){
					Delay(10);
					if(!key3){
			
							if(set_s_num_H>0) {

									set_s_num_H--;
							}
							else {
									set_s_num_H=99;
							}
					
					}
					
				}
			     Lcd_Display2data(3,3,set_s_num_H);	  
		}
		if(key_mode==4){							 //湿度下限
				 if(!key2){
					Delay(100);
					if(!key2){
				//			while(!key2);
							if(set_s_num_L<99) {

									set_s_num_L++;
							}
							else {
									set_s_num_L=0;
							}	
						  
					}
					
				}
				 if(!key3){
					Delay(10);
					if(!key3){
				//			while(!key3);
							if(set_s_num_L>0) {

									set_s_num_L--;
							}
							else {
									set_s_num_L=99;
							}
						  
					}
					
				}
			     Lcd_Display2data(3,3,set_s_num_L);	  
		}

//////////////////////模式c，光度进行设置加减/////////////////////////////////////光度上限
			 if(key_mode==5){							 //guang度shang限
				 if(!key2){
					Delay(10);
					if(!key2){
				//			while(!key2);
							if(set_g_num_H<100) {

									set_g_num_H++;
							}
							else {
									set_g_num_H=0;
							}	
						 
					}
					
				}
				 if(!key3){
					Delay(10);
					if(!key3){
				//			while(!key3);
							if(set_g_num_H>0) {

									set_g_num_H--;
							}
							else {
									set_g_num_H=100;
							}
						 
					}
					
				}
			    Lcd_Display3data(4,3,set_g_num_H);	  
		}
				   	
		if(key_mode==6){							 //GUang度下限
				 if(!key2){
					Delay(10);
					if(!key2){
				//			while(!key2);
							if(set_g_num_L<99) {

									set_g_num_L++;
							}
							else {
									set_g_num_L=0;
							}	
						 
					}
					
				}
				 if(!key3){
					Delay(10);
					if(!key3){
				//			while(!key3);
							if(set_g_num_L>0) {

									set_g_num_L--;
							}
							else {
									set_g_num_L=99;
							}
					
					}
					
				}
			     Lcd_Display3data(4,3,set_g_num_L);	  
		}
	/////////////////////////////////////////////////////////////////////////////
			
		
}
void campare_wendu()	//比较 报警
{
      

	if(baojing==1){

	    if( (U8T_data_H>set_w_num_H||U8T_data_H<set_w_num_L) || (U8RH_data_H>set_s_num_H||U8RH_data_H<set_s_num_L)||
		     (light>set_g_num_H||light<set_g_num_L) ) {
						FMQ =~	FMQ; //报警
					if( U8T_data_H>set_w_num_H||U8T_data_H<set_w_num_L ){

							Lcd_ShowSring(2,7,"W");		
					}
					else{
						   Lcd_ShowSring(2,7," ");	
					}
					if(U8RH_data_H>set_s_num_H||U8RH_data_H<set_s_num_L){
	
							Lcd_ShowSring(3,7,"S");		
					} else{
					   		Lcd_ShowSring(3,7," ");	
					}
					if(light>set_g_num_H||light<set_g_num_L){
	
	                      if(light>set_g_num_H){
							Lcd_ShowSring(4,7,"^G");
						    }
					      else if(light<set_g_num_L){
						    Lcd_ShowSring(4,7,"vG");
						  }			
					} else{
					   		Lcd_ShowSring(4,7,"  ");	
					}			
				}else{
						Lcd_ShowSring(2,7," ");	Lcd_ShowSring(3,7," ");Lcd_ShowSring(4,7,"  ");
						FMQ=1;//解除报警
				}
			 }
    
		
}
void ctrl()	   //控制
{
	 if(baojing==1){

			if( U8T_data_H>set_w_num_H)		//温度大于上限 说明温度高了 要制冷
			{
			    	JDQ_L=0;				       //制冷继电器启动
					JDQ_R=1;
			}
			else if(U8T_data_H<set_w_num_L){		 //温度小于下限 说明温度低了 要加热
	
					JDQ_R=0;						 //制加热继电器启动
					JDQ_L=1;	
			}
			else{
					JDQ_L=1;						 //继电器都不工作
					JDQ_R=1;
			}

		  if(U8RH_data_H>set_s_num_H){			//湿度大于上限 说明湿度大 要去湿  — 

					FENG=0;
				//	TR0=1;						
					JDQ_S=1;					// 风扇转动
		   }
		  else if(U8RH_data_H<set_s_num_L){		////湿度小于下限 说明湿度小 要加湿  — 

				    JDQ_S=0;
				    FENG=1;						  // 加湿继电器工作
		  }
		  else{
					JDQ_S=1;					  //都不工作
					FENG=1;
		     }
	 //////////////////////////////////////////////////////////////////////// 
		   if(light>set_g_num_H){				   //光线充足	
				    LED=0;
				
		   }
	      else if(light<set_g_num_L){			 //光线不充

				    LED=0;
		  }
		  else {
		  		    LED=1;
		       }  

	  }


}
void us_delay(uchar t) 
{  
	while(t--); 
}  
//*********主函数*****************

void Uart_Init()				//使用定时器1作为波特率发生器（STC89C52、STC89C51、AT89C51等均可） 
{  
    TMOD = 0x21;
    SCON = 0x50;		 		//设置串行方式
    TH1 = 0xFD;			 		//波特率9600
    TL1 = TH1;
    PCON = 0x00;
    EA = 1;						//总中断打开 
    ES = 1;						//开串口中断  
    TR1 = 1;					//启动定时器1
} 
/******************************************************************** 
名称：串口发送函数  功能：MCU向无线WIFI模块ESP8266发送数据  
********************************************************************/ 
void Send_Uart(uchar value) 
{  
	ES=0;  						//关闭串口中断  
	TI=0;   					//清发送完毕中断请求标志位   
	SBUF=value; 				//发送  
	while(TI==0); 				//等待发送完毕   
	TI=0;   					//清发送完毕中断请求标志位   
	ES=1;  						//允许串口中断
	TH0=0;
	TL0=0;  
}  

/******************************************************************** 
名称：WIFI模块设置函数  作用: 启动模块，以便可以实现无线接入和控制  
********************************************************************/ 

void ESP8266_Set(uchar *puf) 	// 数组指针*puf指向字符串数组                
{    
	while(*puf!='\0')    		//遇到空格跳出循环  
	{   
		Send_Uart(*puf);  		//向WIFI模块发送控制指令。   
		us_delay(5);   
		puf++;    
	}  
	us_delay(5);  
	Send_Uart('\r'); 			//回车  
	us_delay(5);  
	Send_Uart('\n');   			//换行  
} 

uchar table[]="温度:25℃   湿度:25%      光度:030";
uchar code ta[]="0123456789- ";  
uchar xm0,xm1,xm2;

void main ()
{
	 
	set_w_num_H = ISP_READ(0x2c00)*256+ISP_READ(0x2c01);
	set_w_num_L = ISP_READ(0x2c02)*256+ISP_READ(0x2c03);
	set_s_num_H = ISP_READ(0x2c04)*256+ISP_READ(0x2c05);
	set_s_num_L = ISP_READ(0x2c06)*256+ISP_READ(0x2c07);
	set_g_num_H = ISP_READ(0x2c08)*256+ISP_READ(0x2c09);
	set_g_num_L = ISP_READ(0x2c0a)*256+ISP_READ(0x2c0b);
	Uart_Init();											//波特率发生器 
	Delay(500);
	ESP8266_Set("AT+CWMODE=2"); 							//设置路由器模式1 station,模式2 AP,模式3 station+AP混合模式   设置前wifi的波特率设置成9600
	Delay(500);
	ESP8266_Set("AT+RST"); 									//重新启动wifi模块            
    Delay(500);
	ESP8266_Set("AT+CWSAP=\"wifi\",\"12345678\",11,4");  	//AT+CWSAP="wifi_yuan","12345678",11,4  设置模块SSID:WIFI, PWD:密码 及安全类型加密模式（WPA2-PSK） 
	Delay(500);
	ESP8266_Set("AT+CIPMUX=1");								//开启多连接模式，允许多个各客户端接入 
	Delay(500);
	ESP8266_Set("AT+CIPSERVER=1,5000");  					//启动TCP/IP 实现基于网络//控制 	ESP8266_Set("AT+CIPSERVER=1,5000");  
	Delay(500);
	ESP8266_Set("AT+CIPSTO=0"); 							//永远不超时
	Delay(500);
   	LCDInit();	//lcd12864初始化
	//Lcd_ShowSring(1,1,"温室大棚监控");
    Lcd_ShowSring(2,0,"温度:");
	Lcd_ShowSring(3,0,"湿度:");
	Lcd_ShowSring(4,0,"光度:");
	while(1){

			   scant();	  //按键扫描
			  if(Set_mode==0){	 //模式
				  
			      RH();
			      Lcd_Display2data(3,3,U8RH_data_H);   //显示湿度
				  Lcd_WriteDate('%');	
				  Lcd_Display2data(2,3,U8T_data_H);  //显示温度
				  Lcd_WriteDate('C');
				 // Delay(2000);
			  ////////////////////////////////////////////////////
				  //采集光度
	              light=adc0832();
		          light=255-light;
				  light=light/2.55;		 //转换成100
		          Lcd_Display3data(4,3,light);		 //显示光度

				  campare_wendu();	//比较 报警
				  ctrl();		   //控制继电器跟风扇

			  }			
		///////////////////////////////////////////////////////////////////
				xm0=U8RH_data_H/10;//存放十位数据		  湿度
  		        xm1=U8RH_data_H%10;  //存放个位数据		 
				table[17]=ta[xm0];
		  		table[18]=ta[xm1]; 
				xm0=U8T_data_H/10;//存放十位数据
		  		xm1=U8T_data_H%10;  //存放个位数据
				table[5]=ta[xm0];
		  		table[6]=ta[xm1]; 
				xm0= light/100;//存放bai位数据
		  		xm1= light%100/10;  //存放shi位数据
				xm2= light%10;
				table[31]=ta[xm0];
				table[32]=ta[xm1];
				table[33]=ta[xm2];					  
				ESP8266_Set("AT+CIPSEND=0,34");	   ////发送字符长度  
	            Delay(100);	
		        ESP8266_Set(table);		 	 //发送数值 数组
		        Delay(100);
		  
	      }
			
			
				
}
