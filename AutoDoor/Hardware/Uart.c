#include <REGX51.H>


void UART_Init(void) {
    TMOD |= 0x20; // Timer1 模式 2 (自動重載)
    TH1 = 243; // 波特率 4800 
		PCON = 0x80;
		TR1 = 1; // 啟動 Timer1
		SCON = 0x40;
}
void UART_Transmit(unsigned char data_) {
	
    SBUF = data_; // 載入 UART 資料寄存器
    while (TI == 0); // 等待傳送完成
    TI = 0; // 清除傳送標誌
	
}