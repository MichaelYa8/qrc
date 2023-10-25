
#define UART0CLKENB         *((volatile unsigned int *)0xC00A9000)
#define UART0CLKGEN0L       *((volatile unsigned int *)0xC00A9004)

#define GPIOD_ALTFN0        *((volatile unsigned int *)0xC001D020)
#define GPIOD_ALTFN1        *((volatile unsigned int *)0xC001D024)
#define GPIOD_PULLENB       *((volatile unsigned int *)0xC001D060)

#define ULCON0              *((volatile unsigned int *)0xC00A1000)
#define UCON0               *((volatile unsigned int *)0xC00A1004)
#define UTRSTAT0            *((volatile unsigned int *)0xC00A1010)
#define UTXH0               *((volatile unsigned int *)0xC00A1020)
#define URXH0               *((volatile unsigned int *)0xC00A1024)
#define UBRDIV0             *((volatile unsigned int *)0xC00A1028)
#define UFRACVAL0           *((volatile unsigned int *)0xC00A102C)

void uart_init(void)
{
    /*UART0 CLK Disable*/
    UART0CLKENB &= ~(1<<2);

    /*TX--->GPIOD18  RX----->GPIOD14*/
    GPIOD_ALTFN0 = (GPIOD_ALTFN0 & ~(3<<28)) | (1 << 28);
    GPIOD_ALTFN1 = (GPIOD_ALTFN1 & ~(3<<4)) | (1 << 4);
    /*禁止两个管脚的上下拉电阻*/
    GPIOD_PULLENB &= ~((1<<14) | (1<<18));

    /*时钟配置*/
    /*选择PLL1 800MHz*/
    UART0CLKGEN0L &= ~(7<<2);
    UART0CLKGEN0L |= 1<<2;
    /*分频系数 800MHz/(0x0f+1) = 50MHz*/
    UART0CLKGEN0L &= ~(0xff<<5);
    UART0CLKGEN0L |= (0x0f<<5);

    ULCON0 = 3;
    UCON0 = 5;
    UBRDIV0 = 26;//50000000/115200*16-1取整   
    UFRACVAL0 = 2;//(26.12-26)*16=2.02取整

     /*UART0 CLK ENABLE*/
     UART0CLKENB |= (1<<2);
}

void uart_putc(char c)
{
    while(!(UTRSTAT0 & 0x02)) ;

    UTXH0 = c;
    if(c == '\n')
        uart_putc('\r');
}
void uart_puts(char *str)
{
    if(!str)
        return ;
    while(*str)
    {
        uart_putc(*str);
        str++;
    }
}

char uart_getc(void)
{
    while(!(UTRSTAT0 & 1));

    return (URXH0 & 0xff);
}
void uart_gets(char *buf, int len)
{
    int i = 0 ;
    char tmp = 0;

    while(i<(len-1))
    {
        tmp = uart_getc();
        uart_putc(tmp);

        buf[i] = tmp;
        if(tmp == '\r')
            break;
        i++;
    }
    buf[i] = 0;
}













