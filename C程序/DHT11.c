 #include <intrins.h> 

typedef unsigned char  U8;       /* defined for unsigned 8-bits integer variable    无符号8位整型变量  */
typedef signed   char  S8;       /* defined for signed 8-bits integer variable    有符号8位整型变量  */
typedef unsigned int   U16;      /* defined for unsigned 16-bits integer variable    无符号16位整型变量 */


sbit  P2_0  = P2^0 ;

//----------------------------------------------//
//----------------定义区--------------------//
//----------------------------------------------//
U8  U8FLAG;
U8  U8count,U8temp;
U8  U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;
U8  U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;
U8  U8comdata;    
U8  indata[5];
U8  count, count_r=0;
U16 U16temp1,U16temp2;




void Delay2(U16 j)
{   
		 U8 i;
		 for(;j>0;j--)
		 {  
		 		for(i=0;i<27;i++); 
		 }
}  
/*void delay1(unsigned int num)//延时函数
{
 		while( --num );
}	*/
void  Delay_10us(void)
{
		 U8 i;
		 i--;
		 i--;
		 i--;
		 i--;
		 i--;
		 i--;
}
//串行总线  
void COM(void)
{

		 U8 i;
		 for(i=0;i<8;i++)    
		 {
 
				  U8FLAG=2;				  
				  while((!P2_0)&&U8FLAG++);
				  Delay_10us();
				  Delay_10us();
				  // Delay_10us();
				  U8temp=0;
				  if(P2_0)U8temp=1;
				  U8FLAG=2;
				  while((P2_0)&&U8FLAG++);
				  //----------------------
				  //超时则跳出for循环    
				  if(U8FLAG==1)break;
				  //判断数据位是0还是1  
				  
				  // 如果高电平高过预定0高电平值则数据位为 1 
				  
				  U8comdata<<=1;
				  U8comdata|=U8temp;        //0
		 }//rof

}

 //--------------------------------
 //-----湿度读取子程序 ------------
 //--------------------------------
 //----以下变量均为全局变量--------
 //----温度高8位== U8T_data_H------
 //----温度低8位== U8T_data_L------
 //----湿度高8位== U8RH_data_H-----
 //----湿度低8位== U8RH_data_L-----
 //----校验 8位 == U8checkdata-----
 //----调用相关子程序如下----------
 //---- Delay();, Delay_10us();,COM(); 
 //--------------------------------

void RH(void)
{
	  //主机拉低18ms 
	   P2_0=0;
	   Delay2(180);
	   P2_0=1;
	 //总线由上拉电阻拉高 主机延时20us
	   Delay_10us();
	   Delay_10us();
	   Delay_10us();
	   Delay_10us();
	 //主机设为输入 判断从机响应信号 
	   P2_0=1;
	 //判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行   
	   if(!P2_0)   //T !   
	   {
			    U8FLAG=2;////////////////////////////////////////////////////
			  //判断从机是否发出 80us 的低电平响应信号是否结束  
			    while((!P2_0)&&U8FLAG++);
			    U8FLAG=2;
			  //判断从机是否发出 80us 的高电平，如发出则进入数据接收状态
			    while((P2_0)&&U8FLAG++);
			  //数据接收状态   
			    COM();
			    U8RH_data_H_temp=U8comdata;
			    COM();
			    U8RH_data_L_temp=U8comdata;
			    COM();
			    U8T_data_H_temp=U8comdata;
			    COM();
			    U8T_data_L_temp=U8comdata;
			    COM();
			    U8checkdata_temp=U8comdata;
			    P2_0=1;
			  //数据校验 
			  
			    U8temp=(U8T_data_H_temp+U8T_data_L_temp+U8RH_data_H_temp+U8RH_data_L_temp);
			    if(U8temp==U8checkdata_temp)
			    {
					     U8RH_data_H=U8RH_data_H_temp;
					     U8RH_data_L=U8RH_data_L_temp;
					     U8T_data_H=U8T_data_H_temp;
					     U8T_data_L=U8T_data_L_temp;
					     U8checkdata=U8checkdata_temp;
	    		}//fi
	   }//fi

}
