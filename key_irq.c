
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
    //GPIO ����
    //  1��GPIO����Ϊ����
    //  2����ֹ�ڲ��ϡ���������
    //  3��GPIO���ʹ��
    //  4��GPIO����½����¼�
    //  5��GPIO�ж�ʹ��
    //  FUNC 0  
    //  ����ڣ���ֹ�ڲ�����������
    GPIOA_ALTFN1 &= ~(3<<(24));
    GPIOA_OUTEN &= ~(1<<28);

    //�������־λ
    GPIOA_DET |= (1<<28);

    //����½����¼���ʹ�ܼ��
    GPIOA_DETMODE1 = (GPIOA_DETMODE1 & ~(3<<24)) | (2<<24);
    GPIOA_DETMODEEX &=  ~(1<<28);
    GPIOA_DETENB |= (1<<28);




    GPIOA_INTENB |= (1<<28);


}