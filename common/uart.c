#include "uart.h"

void uart_init(void) {
  ANSEL &= 0xdb;
  PORTB &= 0xdb;
  TRISB &= 0xdf;
  TRISB |= 0x04;

  SPBRG = SPBRG_DATA;

  TXSTAbits.TXEN = 1;
  TXSTAbits.SYNC = SYNC_BIT;
  TXSTAbits.BRGH = BRGH_BIT;
  RCSTAbits.CREN = 1;
  RCSTAbits.SPEN = 1;
}

void uart_disable(void) {
  TXSTAbits.TXEN = 0;
  RCSTAbits.CREN = 0;
  RCSTAbits.SPEN = 0;
}

void uart_putc(const char data) {
  while(!PIR1bits.TXIF);
  TXREG = data;
}

uint8_t uart_puts(const char *buf) {
  uint8_t len = 0;

  while(buf[len])
    uart_putc(buf[len++]);
  return len;
}

uint8_t uart_getc(void) {
  while(!PIR1bits.RCIF);
  return RCREG;
}
