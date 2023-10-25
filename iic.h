
#ifndef __I2C_H__
#define __I2C_H__


extern void iic2_init(void);
extern void iic2_start(unsigned char, unsigned int rdwr);
extern void iic2_stop(void);
extern void iic2_tx(unsigned char *, unsigned char);
extern void iic2_rx(unsigned char *, unsigned char);



#endif 


