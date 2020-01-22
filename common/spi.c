#include "spi.h"

void spi_init(void) {
  ANSEL &= 0xc9;
  PORTB &= 0xc9;
  TRISB &= 0xcb;
  TRISB |= 0x02;

  SSPSTAT = 0x00;
  SSPCON  = 0x30;
}

uint8_t spi_xfer(uint8_t data) {
  SSPBUF = data;
  while(!SSPSTATbits.BF);
  return SSPBUF;
}
