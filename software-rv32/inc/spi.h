#ifndef __SPI_H
#define __SPI_H

#include "systick.h"
#include "gd32vf103.h"

void spi_config(void);
void gpio_config(void);
void rcu_config(void);
uint8_t spi_send(uint8_t data);
uint8_t stb_high(void);
uint8_t stb_low(void);

#endif /* __SPI_H */
