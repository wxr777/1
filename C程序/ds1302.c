sbit RTC_SCLK =P3^5;
sbit RTC_DATA =P3^6;
sbit RTC_nRST =P3^7;

                   
void delay(unsigned int dly);                       //��������  
void write_1byte_to_ds1302(unsigned char da);
unsigned char read_1byte_from_ds1302(void);
void write_data_to_ds1302(unsigned char addr ,unsigned char da);
unsigned char read_data_from_ds1302(unsigned char addr);
void set_time(unsigned char *ti);
void get_time(char *ti);
/*
//��ds1302�ṹ����г�ʼ����֮һ�ṹ���к���֮�еĳ�ʼ����ʽ
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
//   Description :��ds1302д�� 1byte������

void write_1byte_to_ds1302(unsigned char da)
{
    unsigned int i;
    //д���ݵ�ʱ��RTC_DATAΪ�����������Ϊ���
    
    //���²����Ǵ��������ݵľ��䷽����һ��λһ��λ�����ж�
    for(i=8;i>0;i--){
            if(da&0x01)
                RTC_DATA  =1;
             else 
                RTC_DATA  =0;
              //���������ֲᣬ�ʵ��ļ���ʱ������ȷ  
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
 ////////Description : ��ds1302��ȡ1 byte����
 unsigned char read_1byte_from_ds1302(void)
 {
        unsigned char i;
        unsigned char da = 0;
        //�������ݵ�ʱ������Ҫ������IO����Ϊ����
       RTC_DATA=1;
        //�����Ǿ���Ķ�ȡ�������ݵķ���
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
 // Description : ��ds1302д������   
 ///////////////////////////////////////////////////////////
 void write_data_to_ds1302(unsigned char addr ,unsigned char da)
 {
    
    RTC_nRST= 0;//��λ���͵�ƽ��Ч 
    RTC_SCLK =0;

    RTC_nRST  =1;
    //��д��ַ����д���ݣ�ÿ��дһ���ֽ�
    write_1byte_to_ds1302(addr);//��ַ������
    write_1byte_to_ds1302(da);//дһ��byte����
    
    RTC_SCLK =1;
    RTC_SCLK =0;
    delay(1);//delay(40);
 }
 
 ////////////////////////function /////////////////////////
 unsigned char read_data_from_ds1302(unsigned char addr)
 {
        unsigned char da;
        RTC_nRST= 0;//��λ���͵�ƽ��Ч 
        RTC_SCLK =0;

        RTC_nRST  =1;
        //��д��ַ����д���ݣ�ÿ��дһ���ֽ�
        write_1byte_to_ds1302(addr);//��ַ������
        da = read_1byte_from_ds1302();
        
        RTC_SCLK = 1;
        
        RTC_nRST= 0;//��λ���͵�ƽ��Ч 

        return(da);
        
 
 }
 
 
 /////////////////////////////function //////////////////////////////
 /////              Name : set_time
 ////       Description  : ����ʱ�� 
 //////////////////////////////////////////////////////////
 void set_time(unsigned char *ti)
 {
        unsigned char i;
        unsigned char addr =0x80;
        
        write_data_to_ds1302(0x8e,0x00);//�������wp=0������ 
        
        for(i=7;i>0;i--){
              write_data_to_ds1302(addr,*ti);  //�� �� ʱ  �� �� ����  ��
              ti++;
              addr +=2;
                
        }
        
        write_data_to_ds1302(0x8e,0x80);//�������wp=1��д����
        
 }
 
  /////////////////////////////function //////////////////////////////
 /////              Name : get_time
 ////       Description  : ��ȡʱ�䣬��ȡ��ʱ��ΪBCD�룬��Ҫת����ʮ����  
 //////////////////////////////////////////////////////////
 
 void get_time(char *ti)
 {
        unsigned char i;
        unsigned char addr = 0x81;
        char time;
        
        for(i=0;i<7;i++){
                time = read_data_from_ds1302(addr);//��ȡʱ��ΪBCD��
              //  ti[i] =time /16 *10+ time %16;//��ʽΪ ���� �� ʱ �� �� ���� �� 
              ti[i] =(time >>4) *10+ time %16;//��ʽΪ ���� �� ʱ �� �� ���� �� 
                addr +=2;
        }
 }
                                                                  


