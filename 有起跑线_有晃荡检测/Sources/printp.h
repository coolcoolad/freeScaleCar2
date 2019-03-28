#ifndef _PRINTP_H_
#define _PRINTP_H_

extern void uart_init(void);
extern void uart_putchar(unsigned char);
extern unsigned char uart_getkey(void);
extern void scanuf(char *buffer);
extern void scan_count_byte(char *buffer,int count);

unsigned char TERMIO_GetChar(void); 

extern   void test_printp();
extern   void test_print_string();

extern void printp( char * , ...);
extern unsigned char uart_r();          //串口接受函数
extern void uart_t(unsigned char message);//串口发送函数

#endif