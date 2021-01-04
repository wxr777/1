sbit RTC_SCLK =P3^5;
sbit RTC_DATA =P3^6;
sbit RTC_nRST =P3^7;

                   
void delay(unsigned int dly);                       //函数声明  
void write_1byte_to_ds1302(unsigned char da);
unsigned char read_1byte_from_ds1302(void);
void write_data_to_ds1302(unsigned char addr ,unsigned char da);
unsigned char read_data_from_ds1302(unsigned char addr);
void set_time(unsigned char *ti);
void get_time(char *ti);
/*
//对ds1302结构体进行初始化，之一结构体中函数之中的初始化方式
DS1302 ds1302={
        .set_time =set_time,
        .get_time =get_time

}; */
///////////function///////////////////////////////////////
//Name delay  
//description 
///////////////////////////////////////////////////////////////
void delay (unsigned int dly)
{
    for(;dly>0;dly--);
}
///////////function /////////////////////////////////////////
//Name : write_1byte_to_ds1302
//   Description :向ds1302写入 1byte的数据

void write_1byte_to_ds1302(unsigned char da)
{
    unsigned int i;
    //写数据的时候，RTC_DATA为输出，先置其为输出
    
    //以下步骤是处理串行数据的经典方法，一个位一个位的来判断
    for(i=8;i>0;i--){
            if(da&0x01)
                RTC_DATA  =1;
             else 
                RTC_DATA  =0;
              //根据数据手册，适当的加延时，不精确  
            delay(1);// delay(10);
             RTC_SCLK = 1;
            delay(1);// delay(20);
             RTC_SCLK = 0;
           // delay(1);// delay(10);
             da >>= 1;
                
    }
 }
 
 //////////////////function////////////////////////////
 ////////name :read_1byte_from_ds1302
 ////////Description : 从ds1302读取1 byte数据
 unsigned char read_1byte_from_ds1302(void)
 {
        unsigned char i;
        unsigned char da = 0;
        //当读数据的时候，我们要将数据IO设置为输入
       RTC_DATA=1;
        //以下是经典的读取串行数据的方法
        for(i=8;i>0;i--){
                //delay(10);
                delay(1);
                da >>= 1;
                if(RTC_DATA)
                        da +=0x80;
                 RTC_SCLK=1;
                // delay(20);
                delay(1);
                 RTC_SCLK=0;
               //  delay(1);
                // delay(10);
                 
        }
               
        return(da);
 }
 
 ////////////////////////////fonction////////////////////////////
 //Name :write_data_to_Da1302
 // Description : 向ds1302写入数据   
 ///////////////////////////////////////////////////////////
 void write_data_to_ds1302(unsigned char addr ,unsigned char da)
 {
    
    RTC_nRST= 0;//复位，低电平有效 
    RTC_SCLK =0;

    RTC_nRST  =1;
    //先写地址，后写数据，每次写一个字节
    write_1byte_to_ds1302(addr);//地址，命令
    write_1byte_to_ds1302(da);//写一个byte数据
    
    RTC_SCLK =1;
    RTC_SCLK =0;
    delay(1);//delay(40);
 }
 
 ////////////////////////function /////////////////////////
 unsigned char read_data_from_ds1302(unsigned char addr)
 {
        unsigned char da;
        RTC_nRST= 0;//复位，低电平有效 
        RTC_SCLK =0;

        RTC_nRST  =1;
        //先写地址，后写数据，每次写一个字节
        write_1byte_to_ds1302(addr);//地址，命令
        da = read_1byte_from_ds1302();
        
        RTC_SCLK = 1;
        
        RTC_nRST= 0;//复位，低电平有效 

        return(da);
        
 
 }
 
 
 /////////////////////////////function //////////////////////////////
 /////              Name : set_time
 ////       Description  : 设置时间 
 //////////////////////////////////////////////////////////
 void set_time(unsigned char *ti)
 {
        unsigned char i;
        unsigned char addr =0x80;
        
        write_data_to_ds1302(0x8e,0x00);//控制命令，wp=0，操作 
        
        for(i=7;i>0;i--){
              write_data_to_ds1302(addr,*ti);  //秒 分 时  日 月 星期  年
              ti++;
              addr +=2;
                
        }
        
        write_data_to_ds1302(0x8e,0x80);//控制命令，wp=1，写保护
        
 }
 
  /////////////////////////////function //////////////////////////////
 /////              Name : get_time
 ////       Description  : 获取时间，读取得时间为BCD码，需要转换成十进制  
 //////////////////////////////////////////////////////////
 
 void get_time(char *ti)
 {
        unsigned char i;
        unsigned char addr = 0x81;
        char time;
        
        for(i=0;i<7;i++){
                time = read_data_from_ds1302(addr);//读取时间为BCD码
              //  ti[i] =time /16 *10+ time %16;//格式为 ：秒 分 时 日 月 星期 年 
              ti[i] =(time >>4) *10+ time %16;//格式为 ：秒 分 时 日 月 星期 年 
                addr +=2;
        }
 }
                                                                  


