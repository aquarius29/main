
#ifndef PROTO_USART_ISR_MEGA_H
#define PROTO_USART_ISR_MEGA_H

#include <stdint.h>

uint8_t proto_usartInitMega(void);
uint8_t *proto_getRxMsg(void);

#endif /* PROTO_USART_ISR_MEGA_H */