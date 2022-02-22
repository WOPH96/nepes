#include <stdio.h>
#include <rt/rt_api.h>
#include <stdint.h>
#include <stdarg.h>

#define BUFFER_SIZE 32

int __rt_fpga_fc_frequency            = 64000000;  // e.g.
int __rt_fpga_periph_frequency        = 64000000;  // e.g.

//unsigned int __rt_iodev               = 1;
unsigned int __rt_iodev_uart_baudrate = 115200;

typedef struct {
    rt_spim_t *device;
    int *tx_buffer;
    int *rx_buffer;
} spi_flash_t;

rt_spim_conf_t* spi_flash_init_cfg(){
  rt_spim_conf_t *conf = malloc(sizeof(rt_spim_conf_t));
  rt_spim_conf_init(conf);
  conf->max_baudrate = 1000000;
  conf->id = 0;
  conf->cs = 0;
  conf->phase = 1;
  conf->polarity = 1;
  conf->big_endian = 1;
  conf->wordsize = RT_SPIM_WORDSIZE_32;
  return conf;
}

spi_flash_t* spi_flash_open(rt_spim_conf_t *conf) {
  rt_spim_t *device = rt_spim_open(NULL, conf, NULL);
  spi_flash_t *flash = malloc(sizeof(spi_flash_t));
  flash->device = device;
  flash->tx_buffer = rt_alloc(RT_ALLOC_PERIPH, BUFFER_SIZE);
  flash->rx_buffer = rt_alloc(RT_ALLOC_PERIPH, BUFFER_SIZE);
  return flash;
}

void spi_flash_write_enable(spi_flash_t *flash){
  flash->tx_buffer[0] = 0x06;
  rt_spim_send(flash->device, flash->tx_buffer, 8, RT_SPIM_CS_AUTO, NULL);
}

void spi_flash_close(spi_flash_t *flash){
  rt_spim_close(flash->device, NULL);
}

char spi_flash_read_sr1(spi_flash_t *flash){
  flash->tx_buffer[0] = 0x05;
  rt_spim_send(flash->device, flash->tx_buffer, 8, RT_SPIM_CS_KEEP, NULL);
  rt_spim_receive(flash->device, flash->rx_buffer, 8, RT_SPIM_CS_AUTO, NULL);
  return flash->rx_buffer[0];
}

char spi_flash_read_sr2(spi_flash_t *flash){
  flash->tx_buffer[0] = 0x07;
  rt_spim_send(flash->device, flash->tx_buffer, 8, RT_SPIM_CS_KEEP, NULL);
  rt_spim_receive(flash->device, flash->rx_buffer, 8, RT_SPIM_CS_AUTO, NULL);
  return flash->rx_buffer[0];
}

void spi_flash_wait_sr1(spi_flash_t *flash){
  while(spi_flash_read_sr1(flash) & 0x1){
  }
}

void spi_flash_wait_sr2(spi_flash_t *flash){
  while(spi_flash_read_sr2(flash) & 0x1){
  }
}

void spi_flash_bulk_erase(spi_flash_t *flash){
  flash->tx_buffer[0] = 0x60;
  rt_spim_send(flash->device, flash->tx_buffer, 32, RT_SPIM_CS_NONE, NULL);
}

void spi_flash_write_test(spi_flash_t *flash, int* data){
  flash->tx_buffer[0] = 0x02;
  rt_spim_send(flash->device, flash->tx_buffer, 32, RT_SPIM_CS_KEEP, NULL);
  flash->tx_buffer[0] = data[0];
  flash->tx_buffer[1] = data[1];
  flash->tx_buffer[2] = data[2];
  flash->tx_buffer[3] = data[3];
  rt_spim_send(flash->device, flash->tx_buffer, (32*4), RT_SPIM_CS_AUTO, NULL);
}

int main()
{

  int data[] = {0xDEADBEEF, 0x11111111, 0x22222222, 0x33333333};

  rt_spim_conf_t *config = spi_flash_init_cfg();
  spi_flash_t *flash = spi_flash_open(config);

  spi_flash_write_enable(flash);
  spi_flash_bulk_erase(flash);
  spi_flash_wait_sr2(flash);

  spi_flash_write_enable(flash);
  spi_flash_write_test(flash, data);
  spi_flash_wait_sr1(flash);

  spi_flash_close(flash);

  return 0;
}