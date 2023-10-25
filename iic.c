
#define GPIOD_ALTFN0 (*((volatile unsigned int *)0xC001D020))
#define I2CCLKENB2 (*((volatile unsigned int *)0xC00B0000))
#define IPRESET0 (*((volatile unsigned int *)0xC0012000))
#define I2CCON     (*((volatile unsigned int *)0xC00A6000))
#define I2CSTAT    (*((volatile unsigned int *)0xC00A6004))
#define I2CADD     (*((volatile unsigned int *)0xC00A6008))
#define I2CDS      (*((volatile unsigned int *)0xC00A600C))
#define I2CLC      (*((volatile unsigned int *)0xC00A6010))

void iic2_init(void)
{
    /*配置GPIOD6 GPIOD7为FUNC1 即I2C_SCL I2C_SDAT*/
    GPIOD_ALTFN0 &= ~(0x3<<12 | 0x03<<14);
    GPIOD_ALTFN0 |= (1<<12 | 1<<14);

    /*使能I2C控制器时钟*/
    I2CCLKENB2 |= (1<<3);

    /*3.I2C控制器复位 P294*/
    IPRESET0 &= ~(1<<22);
    IPRESET0 |= (1<<22);
    
    I2CCON = (1<<8) | (1<<7) | (1 << 6) | (1<<5) | 0xF ;
    I2CLC = (1 << 2) | 1;

}
void iic2_start(unsigned char slave_addr, unsigned int rdwr)
{
    unsigned int stat = 0;
    unsigned int iiccon = 0;

    /*使能发送和接收*/
    stat |=  (1<<4);
    I2CSTAT |= (1<<4);


    /*使能中断,使能ACK*/
    iiccon = I2CCON;
    iiccon |= (1<<5) | (1 << 7) | (1 << 8);
    I2CCON = iiccon;

    /*设置I2C2的接收发送模式*/
    if(rdwr)
    {
         stat |= (2<<6); //接受模式
         slave_addr = (slave_addr << 1) | 1;
    }
    else
    {
        stat |= (3<<6);//发送模式
        slave_addr = (slave_addr<< 1) | 0;
    }

    /*填充要发送的设备地址和读写位*/
    I2CDS = slave_addr;
    I2CCON &= ~(1 << 4 );

    /*START信号，发送从设备地址*/
    stat |= (1<<5);
    I2CSTAT = stat;
    while(!(I2CCON & (1<<4)));
}
void iic2_stop(void)
{

     /*发送STOP信号*/
     I2CSTAT &= ~(1<<5);
}

void iic2_tx(unsigned char *byte, unsigned char len)
{
        int count;

        for (count = 0; count < len; count++)
        {

            //发送数据
            I2CDS = byte[count];
            //清除中断标志
            I2CCON &= ~(1<<4);

            //判断是否发送完毕
            while(!(I2CCON & (1<<4)));
        }
}
void iic2_rx(unsigned char *byte, unsigned char len)
{

    int count = 0;
    unsigned int iicon;
    while(count < len)
    {
        /*接收最后一个字符前 CPU无需回送ACK，禁止自动ACK*/
        if (count == len - 1)
        {
            I2CCON &= ~(1<<7);
        }
        /*清除中断标志位*/
        I2CCON &= ~(1<<4);

        /*判断是否有中断到来,如果有中断到来，说明有数据接受到*/
        while(!(I2CCON & (1<<4)));
        
        /*读取数据*/
        byte[count] = I2CDS;
        count++;

    }

}
