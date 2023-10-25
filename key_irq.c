
#include "interrupt.h"
#include "uart.h"
#include "key_irq.h"

//GPIOA 28 SW6 KEY?
//
void do_gpioa_irq(void)
{
    uart_puts("\n\r do_gpioa_irq \n\r");

    GPIOA_DET |= (1<<28);
}

void key_irq_init(void)
{

    GPIOA_INTENB &= ~(1<<28);
    GPIOA_ALTFN1 &= ~(3<<(24));
    GPIOA_OUTEN &= ~(1<<28);

    //清除检测标志位
    GPIOA_DET |= (1<<28);

    //检测下降沿事件，使能检测
    GPIOA_DETMODE1 = (GPIOA_DETMODE1 & ~(3<<24)) | (2<<24);
    GPIOA_DETMODEEX &=  ~(1<<28);
    GPIOA_DETENB |= (1<<28);




    GPIOA_INTENB |= (1<<28);


}
