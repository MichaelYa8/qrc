

#define GPIOC_OUT       (*(volatile unsigned long *)0xC001C000)
#define GPIOC_OUTENB    (*(volatile unsigned long *)0xC001C004)
#define GPIOC_ALTFN0    (*(volatile unsigned long *)0xC001C020)


void led_init(void)
{
    /*配置为输出功能管脚*/
    GPIOC_ALTFN0 &= ~(0x3 << 24);
    GPIOC_ALTFN0 |= 1 << 24;
    GPIOC_OUTENB |= 1 << 12;
}
void led1_on(void)
{
    /*输出低电平 亮灯*/
    GPIOC_OUT &= ~(1 << 12);
}
void led1_off(void)
{
    /*输出高电平 灭灯*/
    GPIOC_OUT |= (1 << 12);
}


