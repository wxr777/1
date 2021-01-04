#include <reg52.h>
#define uchar unsigned char
#define uint  unsigned	int


sbit key1 = P1^2;	   //��������
sbit key2 = P1^3;
sbit key3 = P1^4;

sbit LED  = P1^0;	   //��ǿ�ȱ���ָʾ��
sbit FENG = P1^1;	   //����ȥʪ
sbit FMQ  = P1^5;	   //������

sbit JDQ_S = P1^7;	  //��ʪ�̵���

sbit JDQ_R = P3^7;	  // ���ȼ̵���
sbit JDQ_L = P3^6;	  //����̵���

unsigned char key_mode=0;
unsigned char Set_mode=0;   //����ģʽ

uint wendu;	 //	�¶���ֵ
uchar light;
bit baojing=1;	//������־
int set_w_num_H=38,set_w_num_L=10;   //���õ���������ֵ
int set_s_num_H=80,set_s_num_L=0;
int set_g_num_H=50,set_g_num_L=0;

#include<Lcd12864.h>		   //ͷ�ļ�
#include<dht11.c>
#include<adc0832.c>
#include<eeprom.c>

void Delay(uchar t)				//��ʱ����
{
    uint i,j;  
	for(i=t;i>0;i--)   
	for(j=110;j>0;j--); 	

} 
//����ɨ��
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
						  	ISP_ERASE(0x2c00);		//ע�⣺�ֽڱ��ʱ����Ҫ��Ҫ������������	
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
					       
			 /////////////==========�¶�ͨ��========////////////////////////////////
					case 1: Lcd_ShowSring(1,7,"1");FMQ=1;FENG=1;Set_mode=1;Lcd_ShowSring(2,6,"H");
					        JDQ_R=1;JDQ_L=1;JDQ_S=1;Lcd_ShowSring(2,7,"  ");Lcd_ShowSring(3,7,"  ");
							Lcd_ShowSring(4,7,"  ");break;
					case 2: Lcd_ShowSring(1,7,"1");Lcd_ShowSring(2,6,"L");break;
			 /////////////==========ʪ��ͨ��========////////////////////////////////
					case 3: Lcd_ShowSring(1,7,"2");Lcd_ShowSring(3,6,"H");Lcd_ShowSring(2,6,"  ");break;
					case 4: Lcd_ShowSring(1,7,"2");Lcd_ShowSring(3,6,"L");break;
			 /////////////==========���ͨ��========////////////////////////////////
					case 5: Lcd_ShowSring(1,7,"3");Lcd_ShowSring(4,6,"H");Lcd_ShowSring(3,6,"  ");break;
					case 6: Lcd_ShowSring(1,7,"3");Lcd_ShowSring(4,6,"L");break;
					default :break;
			     }
		
///////////////////////////////////////////////////////////////////////////////////////////////////
		 //ģʽa��ͨ���¶Ƚ������üӼ�	  //�¶�����
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
  	if(key_mode==2){						  //����
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
//////////////////////ģʽb��ʪ�Ƚ������üӼ�/////////////////////////////////////ʪ������
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
		if(key_mode==4){							 //ʪ������
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

//////////////////////ģʽc����Ƚ������üӼ�/////////////////////////////////////�������
			 if(key_mode==5){							 //guang��shang��
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
				   	
		if(key_mode==6){							 //GUang������
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
void campare_wendu()	//�Ƚ� ����
{
      

	if(baojing==1){

	    if( (U8T_data_H>set_w_num_H||U8T_data_H<set_w_num_L) || (U8RH_data_H>set_s_num_H||U8RH_data_H<set_s_num_L)||
		     (light>set_g_num_H||light<set_g_num_L) ) {
						FMQ =~	FMQ; //����
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
						FMQ=1;//�������
				}
			 }
    
		
}
void ctrl()	   //����
{
	 if(baojing==1){

			if( U8T_data_H>set_w_num_H)		//�¶ȴ������� ˵���¶ȸ��� Ҫ����
			{
			    	JDQ_L=0;				       //����̵�������
					JDQ_R=1;
			}
			else if(U8T_data_H<set_w_num_L){		 //�¶�С������ ˵���¶ȵ��� Ҫ����
	
					JDQ_R=0;						 //�Ƽ��ȼ̵�������
					JDQ_L=1;	
			}
			else{
					JDQ_L=1;						 //�̵�����������
					JDQ_R=1;
			}

		  if(U8RH_data_H>set_s_num_H){			//ʪ�ȴ������� ˵��ʪ�ȴ� Ҫȥʪ  �� 

					FENG=0;
				//	TR0=1;						
					JDQ_S=1;					// ����ת��
		   }
		  else if(U8RH_data_H<set_s_num_L){		////ʪ��С������ ˵��ʪ��С Ҫ��ʪ  �� 

				    JDQ_S=0;
				    FENG=1;						  // ��ʪ�̵�������
		  }
		  else{
					JDQ_S=1;					  //��������
					FENG=1;
		     }
	 //////////////////////////////////////////////////////////////////////// 
		   if(light>set_g_num_H){				   //���߳���	
				    LED=0;
				
		   }
	      else if(light<set_g_num_L){			 //���߲���

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
//*********������*****************

void Uart_Init()				//ʹ�ö�ʱ��1��Ϊ�����ʷ�������STC89C52��STC89C51��AT89C51�Ⱦ��ɣ� 
{  
    TMOD = 0x21;
    SCON = 0x50;		 		//���ô��з�ʽ
    TH1 = 0xFD;			 		//������9600
    TL1 = TH1;
    PCON = 0x00;
    EA = 1;						//���жϴ� 
    ES = 1;						//�������ж�  
    TR1 = 1;					//������ʱ��1
} 
/******************************************************************** 
���ƣ����ڷ��ͺ���  ���ܣ�MCU������WIFIģ��ESP8266��������  
********************************************************************/ 
void Send_Uart(uchar value) 
{  
	ES=0;  						//�رմ����ж�  
	TI=0;   					//�巢������ж������־λ   
	SBUF=value; 				//����  
	while(TI==0); 				//�ȴ��������   
	TI=0;   					//�巢������ж������־λ   
	ES=1;  						//�������ж�
	TH0=0;
	TL0=0;  
}  

/******************************************************************** 
���ƣ�WIFIģ�����ú���  ����: ����ģ�飬�Ա����ʵ�����߽���Ϳ���  
********************************************************************/ 

void ESP8266_Set(uchar *puf) 	// ����ָ��*pufָ���ַ�������                
{    
	while(*puf!='\0')    		//�����ո�����ѭ��  
	{   
		Send_Uart(*puf);  		//��WIFIģ�鷢�Ϳ���ָ�   
		us_delay(5);   
		puf++;    
	}  
	us_delay(5);  
	Send_Uart('\r'); 			//�س�  
	us_delay(5);  
	Send_Uart('\n');   			//����  
} 

uchar table[]="�¶�:25��   ʪ��:25%      ���:030";
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
	Uart_Init();											//�����ʷ����� 
	Delay(500);
	ESP8266_Set("AT+CWMODE=2"); 							//����·����ģʽ1 station,ģʽ2 AP,ģʽ3 station+AP���ģʽ   ����ǰwifi�Ĳ��������ó�9600
	Delay(500);
	ESP8266_Set("AT+RST"); 									//��������wifiģ��            
    Delay(500);
	ESP8266_Set("AT+CWSAP=\"wifi\",\"12345678\",11,4");  	//AT+CWSAP="wifi_yuan","12345678",11,4  ����ģ��SSID:WIFI, PWD:���� ����ȫ���ͼ���ģʽ��WPA2-PSK�� 
	Delay(500);
	ESP8266_Set("AT+CIPMUX=1");								//����������ģʽ�����������ͻ��˽��� 
	Delay(500);
	ESP8266_Set("AT+CIPSERVER=1,5000");  					//����TCP/IP ʵ�ֻ�������//���� 	ESP8266_Set("AT+CIPSERVER=1,5000");  
	Delay(500);
	ESP8266_Set("AT+CIPSTO=0"); 							//��Զ����ʱ
	Delay(500);
   	LCDInit();	//lcd12864��ʼ��
	//Lcd_ShowSring(1,1,"���Ҵ�����");
    Lcd_ShowSring(2,0,"�¶�:");
	Lcd_ShowSring(3,0,"ʪ��:");
	Lcd_ShowSring(4,0,"���:");
	while(1){

			   scant();	  //����ɨ��
			  if(Set_mode==0){	 //ģʽ
				  
			      RH();
			      Lcd_Display2data(3,3,U8RH_data_H);   //��ʾʪ��
				  Lcd_WriteDate('%');	
				  Lcd_Display2data(2,3,U8T_data_H);  //��ʾ�¶�
				  Lcd_WriteDate('C');
				 // Delay(2000);
			  ////////////////////////////////////////////////////
				  //�ɼ����
	              light=adc0832();
		          light=255-light;
				  light=light/2.55;		 //ת����100
		          Lcd_Display3data(4,3,light);		 //��ʾ���

				  campare_wendu();	//�Ƚ� ����
				  ctrl();		   //���Ƽ̵���������

			  }			
		///////////////////////////////////////////////////////////////////
				xm0=U8RH_data_H/10;//���ʮλ����		  ʪ��
  		        xm1=U8RH_data_H%10;  //��Ÿ�λ����		 
				table[17]=ta[xm0];
		  		table[18]=ta[xm1]; 
				xm0=U8T_data_H/10;//���ʮλ����
		  		xm1=U8T_data_H%10;  //��Ÿ�λ����
				table[5]=ta[xm0];
		  		table[6]=ta[xm1]; 
				xm0= light/100;//���baiλ����
		  		xm1= light%100/10;  //���shiλ����
				xm2= light%10;
				table[31]=ta[xm0];
				table[32]=ta[xm1];
				table[33]=ta[xm2];					  
				ESP8266_Set("AT+CIPSEND=0,34");	   ////�����ַ�����  
	            Delay(100);	
		        ESP8266_Set(table);		 	 //������ֵ ����
		        Delay(100);
		  
	      }
			
			
				
}
