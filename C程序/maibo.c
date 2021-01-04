#include<reg52.h>
#define uchar unsigned char
#define uint  unsigned	int

unsigned int s=0;	  //�½����ۼ��м��������
unsigned int maibo=0;	  //һ���ӵ�����Ƶ��
unsigned int num;	  //�м����ÿ50ms�ۼ�һ��
unsigned char idata mc_num[6];	//��������ֵ�˲��㷨���м����
unsigned char t=0;	   //�м���� 
sbit P32=P3^2;  
uchar Set_maiboL=50;
uchar Set_maiboH=100;
uchar flag=0;		 //����״̬��־λ
uchar maobo_key=0;

bit biaozhi=1;	 //������־
sbit FMQ =P1^0;		//��������������

uchar num1;
//����ɨ����� ����������
void Key_Check()
{
  
	 if(!key4){
		while(!key4);
		flag++;
		FMQ=1;
		maobo_key=1;
		KEY_flag=0;
		biaozhi=1;	
	  if(flag==3){
			flag=0; 
			Lcd_ShowSring(4,7," ");
			    Sector_erase(0x2000);	      
			    Byte_program(0x2000,Set_maiboH);
				Sector_erase(0x2200);
				Byte_program(0x2200,Set_maiboL);
		} 
		if(flag==1)			  //����
		{	
		    Lcd_ShowSring(4,7,"H"); 
		    biaozhi=0;			   //����
		   	maibo=0; 
		}
 
		if(flag==2) 	   //����
		{
		  Lcd_ShowSring(4,7,"L");

		}
		
	}
	if(flag==1){
		if(!key2&&maobo_key==1){
			//while(!key2);
			Delay1(100);  //���������������
			if(!key2&&maobo_key==1){
				
				Set_maiboH++;
				if(Set_maiboH>180){	//�������޾͸�ֵ
					Set_maiboH=20;

				}
				biaozhi=1;	// ���ޱ�־
			}
		}
		if(!key3&&maobo_key==1){
			Delay1(100); //���������������
			if(!key3&&maobo_key==1){
			 
 				 Set_maiboH--;
				if(Set_maiboH<20){	//�������޾͸�ֵ
					Set_maiboH=180;
				}
					biaozhi=1;	// ���ޱ�־
			
			}
		}	
		//Lcd_Display_3Date(2,6,Set_maiboH);
		  Lcd_Display33data(4,3,Set_maiboH);
	}
////////////////////////////////////////////////////////////////	
	 if(flag==2){
		if(!key2&&maobo_key==1){
			//while(!key2);
			Delay1(100);  //���������������
			if(!key2&&maobo_key==1){
				
				Set_maiboL++;
				if(Set_maiboL>180){	//�������޾͸�ֵ
					Set_maiboL=20;

				}
				biaozhi=1;	// ���ޱ�־
			}
		}
		if(!key3&&maobo_key==1){
			Delay1(100); //���������������
			if(!key3&&maobo_key==1){
 				 Set_maiboL--;
				if(Set_maiboL<20){	//�������޾͸�ֵ
					Set_maiboL=180;
				}
				
				biaozhi=1;	// ���ޱ�־
			}
		}
		//	Lcd_Display_3Date(2,6,Set_maiboL);
		    Lcd_Display33data(4,3,Set_maiboL);
	}


}

//�жϳ�ʼ��
void init()
  {	  

	//��ʱ������
    TMOD=0x11; 		//���ö�ʱ��0����ʽ1:16λ��ʱ��	
	TH0=(65535-50000)/255;	  //��ʱ��1��λװ��ֵ
	TL0=(65535-50000)%255;;	  //��ʱ��1��λװ��ֵ
	ET0=1;   ////��ʱ��0	  ʹ��λ
	TR0=1;

//	TH1=(65535-50000)/255;	  //��ʱ��1��λװ��ֵ
//	TL1=(65535-50000)%255;;	  //��ʱ��1��λװ��ֵ

//	ET1=1;	//��ʱ��1	  ʹ��λ

//	TR1=0;

    IT0=1,//�½��ش���
	EX0=1;//�ⲿ�ж�0     ʹ��λ

	EA=1;//	���ж�
 }
/////////////////////////////////////////////////////////////////
   //��ʱ��0 
 void time0()interrupt 1   
 { 	
		 //ÿ50ms����һ���ж�
	 	TH0=(65535-50000)/256;	 //��ʱ��0��λװ��ֵ
		TL0=(65535-50000)%256; //��ʱ��0��λװ��ֵ
	 	num++; //ÿ���ж�num �ۼ�

 }
   /*/��ʱ��0 
 void time1()interrupt 3   
 { 	
		 //ÿ50ms����һ���ж�
	 	TH1=(65535-50000)/256;	 //��ʱ��0��λװ��ֵ
		TL1=(65535-50000)%256; //��ʱ��0��λװ��ֵ
	 	num1++; //ÿ���ж�num �ۼ�
		if(num1==10){
		 num1=0;
		 FMQ=~FMQ;
		}

 }	*/
//�ⲿ�ж�0 �½��ؼ���
void int0() interrupt 0
{	 
		unsigned char temp,p,g;
		unsigned int ii=0;

		ii=0;
		if(P32==0) {

			//	Delay(1);
				if(P32==0) {
	
				s++;
			
				//��һ���½��������ʱ��
				//�򿪶�ʱ��
				//�ȴ��ڶ����жϵ�ʱ�� ���������ж����õ�ʱ��
				//
				if(s==1){
						TR0 = 1;
						//��ʼ����������ֵÿ50ms ��һ���ж�
					 	TH0=(65535-50000)/256;	 //��ʱ��0��λװ��ֵ
						TL0=(65535-50000)%256; //��ʱ��0��λװ���
						num =0;	
				} 
				if(s==2){
						
						s =0;
						TR0 = 0;
		
				//		TH0 =0;
				//		TL0 =0;	
					//	maibo	= 1/ (num *5/1000);
					//һ������Ŀ���� num  �� 50ms  num*50ms ת��һ��  num*50/1000 s	 
					//һ���Ӿ���  1/�� num*50/1000�� ��������
					//һ�����ھ���  60 * 1 /�� num*50 /1000��
					//�����һ�����ڵ�������Ϊ   1200/num 
						temp 	= 1200/ num ;	//�������ȵ�ʱ�� ���������½����жϵ�ʱ�䣩 ��Ӧ��Ƶ�ʸ��м����
						if(  temp >30 && temp <120 )
					   {	
					   		mc_num[t] =temp ;
							t++;	 //һ����6���м����

						    if(t==6){ 
		
								t=0;
								// ��ֵ�˲� 
								//��6�βɼ����������Ƶ�� ��С����� ���� ȡ�м�ֵ
								for(p=0;p<6;p++){
										   for(g=0;g<6-p;g++){
											   if(mc_num[g]>mc_num[g+1] )
												{   temp  = mc_num[g];
												   mc_num[g] =  mc_num[g+1];
												   mc_num[g+1] = temp ;
												}			                                                                                                            		
										   }
								 }	
		
///								maibo =	mc_num[5];	//ȡ�����еĵڸ�����Ϊһ���ӵ�������
							maibo=mc_num[1]+mc_num[2]+mc_num[3] ;
					   			  maibo =maibo/3;  



					    }

							
					   }

					
				} 
			 }  
	   }
		
}

