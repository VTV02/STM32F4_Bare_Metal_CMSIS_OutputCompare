
#ifndef UART_H_
#define UART_H_

void uart2_txrx_init(void);
void uart2_write(int ch);
void write_string(int wordlength,char* word);
char uart2_read(void);


#endif /* UART_H_ */
