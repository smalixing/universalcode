#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "xmodem.h"
#include "xmodem_transmitter.h"

static xmodem_transmit_status_t transmit_state;
static const uint32_t transfer_ack_timeout = 60000;
static const uint32_t transfer_eot_timeout = 10000;
static const uint32_t transfer_etb_timeout = 10000;
static const uint8_t transfer_write_block_timeout = 60000;
static const uint8_t write_block_max_retries = 10;
static const uint8_t write_etb_max_retries = 5;             // max 5 retries for ETB ACK

static uint8_t control_character = 0;
static uint8_t write_success = false;
static uint32_t returned_size = 0;
static uint8_t inbound = 0;
static uint8_t payload_buffer_postion = 0;
static uint8_t payload_size = 0;
static uint8_t current_packet_id = 0;
static uint8_t write_block_retries = 0;
static uint32_t write_block_timer = 0;
static uint8_t write_etb_retries = 0;
static xmodem_packet_t current_packet;

static uint8_t internal_buffer[XMODEM_BLOCK_SIZE] = {0};

static xmodem_transmit_write_cb_t xmodem_write_cb = NULL;
static xmodem_transmit_read_cb_t xmodem_read_cb = NULL;
static xmodem_transmit_get_cb_t xmodem_get_cb = NULL;
static is_inbound_empty_cb_t xmodem_is_innbound_empty_cb = NULL;
static is_outbound_full_cb_t xmodem_is_outbound_full_cb = NULL;

xmodem_transmit_state_t xmodem_trannsmit_state()
{
    return transmit_state;
}

uint8_t xmodem_transmit_init(uint32_t size)
{
    uint8_t result = false;
    transmit_state = XMODEM_TRANSMIT_UNKNOWN;

    if (!xmodem_write_cb && !xmodem_read_cb && !xmodem_get_cb &&
        !xmodem_is_innbound_empty_cb && !xmodem_is_outbound_full_cb && 
        size % XMODEM_BLOCK_SIZE == 0) {
            transmit_state = XMODEM_TRANNSMIT_INITIAL;
        }
}
uint8_t xmodem_transmit_process(const uint32_t current_time);
uint8_t xmodem_transmitter_cleanup();

void xmodem_transmitter_set_callback_write(xmodem_transmit_write_cb_t write_cb);


void xmodem_transmitter_set_callback_read(xmodem_transmit_read_cb_t read_cb);

void xmodem_transmitter_set_callback_is_outbound_full(void *user_data);
void xmodem_transmitter_set_callback_is_inbound_empty(void *user_data);


void xmodem_transmitter_set_callback_get_buffer(xmodem_transmit_get_cb_t get_cb);