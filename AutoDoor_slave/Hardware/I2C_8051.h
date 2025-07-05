#ifndef __I2C_8051_H
#define __I2C_8051_H


void scl_w(bit value);
void sda_w(bit value);
bit sda_r(void);
void start();
void send_8bits(unsigned char value);
bit ack_receive(void);
void ack_send(void);
void stop(void);

#endif
