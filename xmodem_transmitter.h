#ifndef __XMODEM_TRANSMITTER_H__
#define __XMODEM_TRANSMITTER_H__


#include <stdint.h>

enum {
    XMODEM_TRANSMIT_INITIAL,
    XMODEM_TRANSMIT_WAIT_C,
    XMODEM_TRANSMIT_WAIT_FOR_C_ACK,
    XMODEM_TRANSMIT_WRITE_BLOCK_FAILED,
    XMODEM_TRANSMIT_ABOUT_TRANSFER,
    XMODEM_TRANSMIT_WRITE_BLOCK,
    XMODEM_TRANSMIT_C_ACK_RECEIVED,
    XMODEM_TRANSMIT_COMPLETE,
    XMODEM_TRANSMIT_WRITE_EOT,
    XMODEM_TRANSMIT_WAIT_FOR_EOT_ACK,
    XMODEM_TRANSMIT_TIMEOUT_EOT,
    XMODEM_TRANSMIT_WRITE_BLOCK_TIMEOUT,
    XMODEM_TRANSMIT_WRITE_ETB,
    XMODEM_TRANSMIT_WAIT_FOR_ETB_ACK,
    XMODEM_TRANSMIT_TIMEOUT_ETB,
    XMODEM_TRANSMIT_WAIT_WRITE_BLOCK,
    XMODEM_TRANSMIT_UNKNOWN
} xmodem_transmit_status_t;


uint8_t xmodem_transmit_init(uint32_t size);
uint8_t xmodem_transmit_process(const uint32_t current_time);
uint8_t xmodem_transmitter_cleanup();

typedef uint8_t (*xmodem_transmit_write_cb_t)(const uint32_t requested_size, uint8_t *buffer, uint8_t *write_status);
void xmodem_transmitter_set_callback_write(xmodem_transmit_write_cb_t write_cb);

typedef uint8_t (*xmodem_transmit_read_cb_t)(const uint32_t requested_size, uint8_t *buffer, uint32_t *returned_size);
void xmodem_transmitter_set_callback_read(xmodem_transmit_read_cb_t read_cb);

typedef uint8_t (*is_inbound_empty_cb_t)(void);
void xmodem_transmitter_set_callback_is_outbound_full(void *user_data);
typedef uint8_t (*is_outbound_full_cb_t)(void);
void xmodem_transmitter_set_callback_is_inbound_empty(void *user_data);

typedef uint8_t (*xmodem_transmit_get_cb_t)(const uint32_t position, uint8_t *buffer);
void xmodem_transmitter_set_callback_get_buffer(xmodem_transmit_get_cb_t get_cb);



#endif