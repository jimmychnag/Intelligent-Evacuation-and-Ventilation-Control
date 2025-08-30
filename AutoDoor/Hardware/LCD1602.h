#ifndef __LCD1602_H
#define __LCD1602_H

void WriteInst4bits(unsigned char inst_4b);
void WriteInst(unsigned char inst);
void WriteData(unsigned char data_);
void WriteString(unsigned char* string);
void initial(void);
void CG_RAM_write(unsigned char* ptr);
void dis_p(char row,column);
void WriteNum(unsigned char Num);
void WriteFloat(float T,unsigned char row,unsigned char column);


#endif
