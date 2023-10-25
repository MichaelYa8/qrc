
#include "iic.h"

#define MMA8653_ID  (0x1D)

#define MMA8653_RANGE_2G  0
#define MMA8653_RANGE_4G  1
#define MMA8653_RANGE_8G  2


void mma8653_read(unsigned char addr, unsigned char *byte, int len)
{
    /*发送START,设备地址和读写位*/
    iic2_start(MMA8653_ID, 0);
    /*发送片内地址*/
    iic2_tx(&addr, 1);
    /*重发START，设备地址和读写位*/
    iic2_start(MMA8653_ID, 1);
    
    iic2_rx(byte, len);
    iic2_stop();
}
unsigned char id[32];
void mma8653_show_id(void)
{
    int i;
    char buf[16];
    mma8653_read(0xd, id, 1);

    uart_puts("\nMMA8653 ID:");
    for (i=0; i < 1;i++)
    {
        itoa(buf, id[i]);
        uart_puts(buf);
        uart_puts("\n");

    }

}
void mma8653_write(unsigned char addr, unsigned char *byte, int len)
{
    /*发送START和设备地址读写位*/
    iic2_start(MMA8653_ID, 0);
    /*发送片内地址*/
    iic2_tx(&addr, 1);
    iic2_tx(byte, len);
    iic2_stop();
}
void mma8653_active(void)
{
    unsigned char buf[8];
    char ibuf[16];


    /*读取片内寄存器的0x2A的值放到buf[0]中*/
    mma8653_read(0x2A, buf, 1);

    /*设置MMA8653为正常的运行模式,默认为待机*/
    buf[0] |= 1;
    mma8653_write(0x2A, buf, 1);
}

void mma8653_get_xyz(void)
{
    int i;
    int x, y, z;
    unsigned char buf[16];
    char ibuf[16];
    // 1.激活外设
    mma8653_active();

    /*读取坐标从片内寄存器地址1开始读取,连续读6个字节*/
    mma8653_read(1, buf, 6);
    x = ((buf[0] & 0xFF) << 2) | ((buf[1] & 0xFF) >> 6);

    y = ((buf[2] & 0xFF) << 2) | ((buf[3] & 0xFF) >> 6);

    z = ((buf[4] & 0xFF) << 2) | ((buf[5] & 0xFF) >> 6);

    itoa(ibuf, x);
    uart_puts("\n X:");
    uart_puts(ibuf);
    uart_puts("\n");

    itoa(ibuf, y);
    uart_puts("\n Y:");
    uart_puts(ibuf);
    uart_puts("\n");

    itoa(ibuf, z);
    uart_puts("\n Z:");
    uart_puts(ibuf);
    uart_puts("\n");
}







