#include "hal.h"

void eglib_CommBegin(eglib_t *eglib) {
	eglib->hal_comm_active = true;
	eglib->hal_i2c_send_slave_addr++;
	eglib->hal->comm_begin(eglib);
}

void eglib_Send(
	eglib_t *eglib,
	hal_dc_t dc,
	uint8_t *bytes,
	uint32_t length
) {
	uint8_t prev_hal_i2c_send_slave_addr;

	prev_hal_i2c_send_slave_addr = eglib->hal_i2c_send_slave_addr;

	eglib->hal->send(eglib, dc, bytes, length);
	if(eglib->hal_i2c_send_slave_addr == prev_hal_i2c_send_slave_addr) {
		if(eglib->hal_i2c_send_slave_addr)
			eglib->hal_i2c_send_slave_addr--;
	} else {
		if(eglib->hal_i2c_send_slave_addr)
			eglib->hal_i2c_send_slave_addr--;
		// I2C ReStart
		if(!eglib->hal_i2c_send_slave_addr)
			eglib->hal_i2c_send_slave_addr++;
	}
}

void eglib_CommEnd(eglib_t *eglib) {
	// Send pending I2C Slave address
	if(eglib->hal_i2c_send_slave_addr)
		eglib->hal->send(eglib, 0, NULL, 0);
	eglib->hal->comm_end(eglib);
	eglib->hal_comm_active = false;
	eglib->hal_i2c_send_slave_addr = 0;
}
