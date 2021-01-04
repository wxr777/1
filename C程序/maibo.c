#include<reg52.h>
#define uchar unsigned char
#define uint  unsigned	int

unsigned int s=0;	  //ÏÂ½µÑØÀÛ¼ÓÖĞ¼ä¼ÆÊı±äÁ¿
unsigned int maibo=0;	  //Ò»·ÖÖÓµÄÂö²«ÆµÂÊ
unsigned int num;	  //ÖĞ¼ä¼ÆÊıÃ¿50msÀÛ¼ÓÒ»´Î
unsigned char idata mc_num[6];	//ÓÃÀ´×öÖĞÖµÂË²¨Ëã·¨µÄÖĞ¼ä±äÁ¿
unsigned char t=0;	   //ÖĞ¼ä±äÁ¿ 
sbit P32=P3^2;  
uchar Set_maiboL=50;
uchar Set_maiboH=100;
uchar flag=0;		 //¹¤×÷×´Ì¬±êÖ¾Î»
uchar maobo_key=0;

bit biaozhi=1;	 //±¨¾¯±êÖ¾
sbit FMQ =P1^0;		//·äÃùÆ÷¿ØÖÆÒı½Å

uchar num1;
//°´¼üÉ¨Ãè³ÌĞò ÉèÖÃÉÏÏÂÏŞ
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
		if(flag==1)			  //ÉÏÏŞ
		{	
		    Lcd_ShowSring(4,7,"H"); 
		    biaozhi=0;			   //ÇåÁã
		   	maibo=0; 
		}
 
		if(flag==2) 	   //ÏÂÏŞ
		{
		  Lcd_ShowSring(4,7,"L");

		}
		
	}
	if(flag==1){
		if(!key2&&maobo_key==1){
			//while(!key2);
			Delay1(100);  //Èí¼şÏû³ı°´¼ü¶¶¶¯
			if(!key2&&maobo_key==1){
				
				Set_maiboH++;
				if(Set_maiboH>180){	//³¬¹ıÉÏÏŞ¾Í¸³Öµ
					Set_maiboH=20;

				}
				biaozhi=1;	// ÉÏÏŞ±êÖ¾
			}
		}
		if(!key3&&maobo_key==1){
			Delay1(100); //Èí¼şÏû³ı°´¼ü¶¶¶¯
			if(!key3&&maobo_key==1){
			 
 				 Set_maiboH--;
				if(Set_maiboH<20){	//µÍÓÚÏÂÏŞ¾Í¸³Öµ
					Set_maiboH=180;
				}
					biaozhi=1;	// ÉÏÏŞ±êÖ¾
			
			}
		}	
		//Lcd_Display_3Date(2,6,Set_maiboH);
		  Lcd_Display33data(4,3,Set_maiboH);
	}
////////////////////////////////////////////////////////////////	
	 if(flag==2){
		if(!key2&&maobo_key==1){
			//while(!key2);
			Delay1(100);  //Èí¼şÏû³ı°´¼ü¶¶¶¯
			if(!key2&&maobo_key==1){
				
				Set_maiboL++;
				if(Set_maiboL>180){	//³¬¹ıÉÏÏŞ¾Í¸³Öµ
					Set_maiboL=20;

				}
				biaozhi=1;	// ÏÂÏŞ±êÖ¾
			}
		}
		if(!key3&&maobo_key==1){
			Delay1(100); //Èí¼şÏû³ı°´¼ü¶¶¶¯
			if(!key3&&maobo_key==1){
 				 Set_maiboL--;
				if(Set_maiboL<20){	//µÍÓÚÏÂÏŞ¾Í¸³Öµ
					Set_maiboL=180;
				}
				
				biaozhi=1;	// ÏÂÏŞ±êÖ¾
			}
		}
		//	Lcd_Display_3Date(2,6,Set_maiboL);
		    Lcd_Display33data(4,3,Set_maiboL);
	}


}

//ÖĞ¶Ï³õÊ¼»¯
void init()
  {	  

	//¶¨Ê±Æ÷ÉèÖÃ
    TMOD=0x11; 		//ÉèÖÃ¶¨Ê±Æ÷0£¬·½Ê½1:16Î»¶¨Ê±Æ÷	
	TH0=(65535-50000)/255;	  //¶¨Ê±Æ÷1¸ßÎ»×°³õÖµ
	TL0=(65535-50000)%255;;	  //¶¨Ê±Æ÷1¸ßÎ»×°³õÖµ
	ET0=1;   ////¶¨Ê±Æ÷0	  Ê¹ÄÜÎ»
	TR0=1;

//	TH1=(65535-50000)/255;	  //¶¨Ê±Æ÷1¸ßÎ»×°³õÖµ
//	TL1=(65535-50000)%255;;	  //¶¨Ê±Æ÷1¸ßÎ»×°³õÖµ

//	ET1=1;	//¶¨Ê±Æ÷1	  Ê¹ÄÜÎ»

//	TR1=0;

    IT0=1,//ÏÂ½µÑØ´¥·¢
	EX0=1;//Íâ²¿ÖĞ¶Ï0     Ê¹ÄÜÎ»

	EA=1;//	×ÜÖĞ¶Ï
 }
/////////////////////////////////////////////////////////////////
   //¶¨Ê±Æ÷0 
 void time0()interrupt 1   
 { 	
		 //Ã¿50ms½øĞĞÒ»´ÎÖĞ¶Ï
	 	TH0=(65535-50000)/256;	 //¶¨Ê±Æ÷0¸ßÎ»×°³õÖµ
		TL0=(65535-50000)%256; //¶¨Ê±Æ÷0µÍÎ»×°³õÖµ
	 	num++; //Ã¿´ÎÖĞ¶Ïnum ÀÛ¼Ó

 }
   /*/¶¨Ê±Æ÷0 
 void time1()interrupt 3   
 { 	
		 //Ã¿50ms½øĞĞÒ»´ÎÖĞ¶Ï
	 	TH1=(65535-50000)/256;	 //¶¨Ê±Æ÷0¸ßÎ»×°³õÖµ
		TL1=(65535-50000)%256; //¶¨Ê±Æ÷0µÍÎ»×°³õÖµ
	 	num1++; //Ã¿´ÎÖĞ¶Ïnum ÀÛ¼Ó
		if(num1==10){
		 num1=0;
		 FMQ=~FMQ;
		}

 }	*/
//Íâ²¿ÖĞ¶Ï0 ÏÂ½µÑØ¼ÆÊı
void int0() interrupt 0
{	 
		unsigned char temp,p,g;
		unsigned int ii=0;

		ii=0;
		if(P32==0) {

			//	Delay(1);
				if(P32==0) {
	
				s++;
			
				//µÚÒ»¸öÏÂ½µÑØÇå³ş¶¨Ê±Æ÷
				//´ò¿ª¶¨Ê±Æ÷
				//µÈ´ıµÚ¶ş´ÎÖĞ¶ÏµÄÊ±ºò ¼ÆËãÁ©´ÎÖĞ¶ÏËùÓÃµÄÊ±¼ä
				//
				if(s==1){
						TR0 = 1;
						//³õÊ¼»¯¼ÆÊıÆ÷µÄÖµÃ¿50ms ½øÒ»´ÎÖĞ¶Ï
					 	TH0=(65535-50000)/256;	 //¶¨Ê±Æ÷0¸ßÎ»×°³õÖµ
						TL0=(65535-50000)%256; //¶¨Ê±Æ÷0µÍÎ»×°³õµ
						num =0;	
				} 
				if(s==2){
						
						s =0;
						TR0 = 0;
		
				//		TH0 =0;
				//		TL0 =0;	
					//	maibo	= 1/ (num *5/1000);
					//Ò»´ÎÂö³åµÄ¿í¶ÈÓĞ num  ¸ö 50ms  num*50ms ×ª»¯Ò»ÏÂ  num*50/1000 s	 
					//Ò»ÃëÖÓ¾ÍÓĞ  1/£¨ num*50/1000£© ¸öÂö³åÊı
					//Ò»·ÖÖÓÄÚ¾ÍÓĞ  60 * 1 /£¨ num*50 /1000£©
					//»¯¼òµÃÒ»·ÖÖÓÄÚµÄÂö³åÊıÎª   1200/num 
						temp 	= 1200/ num ;	//½«Âö³å¿í¶ÈµÄÊ±¼ä £¨¼´Á©´ÎÏÂ½µÑØÖĞ¶ÏµÄÊ±¼ä£© ¶ÔÓ¦µÄÆµÂÊ¸øÖĞ¼ä±äÁ¿
						if(  temp >30 && temp <120 )
					   {	
					   		mc_num[t] =temp ;
							t++;	 //Ò»¹²ÓĞ6¸öÖĞ¼ä±äÁ¿

						    if(t==6){ 
		
								t=0;
								// ÖĞÖµÂË²¨ 
								//½«6´Î²É¼¯µ½µÄÂö³åµÄÆµÂÊ ´ÓĞ¡µ½´óµÄ ÅÅÁĞ È¡ÖĞ¼äÖµ
								for(p=0;p<6;p++){
										   for(g=0;g<6-p;g++){
											   if(mc_num[g]>mc_num[g+1] )
												{   temp  = mc_num[g];
												   mc_num[g] =  mc_num[g+1];
												   mc_num[g+1] = temp ;
												}			                                                                                                            		
										   }
								 }	
		
///								maibo =	mc_num[5];	//È¡Êı×éÖĞµÄµÚ¸öÊı×÷ÎªÒ»·ÖÖÓµÄÂö²«Êı
							maibo=mc_num[1]+mc_num[2]+mc_num[3] ;
					   			  maibo =maibo/3;  



					    }

							
					   }

					
				} 
			 }  
	   }
		
}

