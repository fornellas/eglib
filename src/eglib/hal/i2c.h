#ifndef EGLIB_HAL_I2C_H
#define EGLIB_HAL_I2C_H

#include <stdint.h>

typedef struct {
	void (*power_up)(void *hal_i2c_config);
	void (*power_down)(void *hal_i2c_config);
	void (*delay_ms)(void *hal_i2c_config, uint32_t ms);
	void (*set_reset)(void *hal_i2c_config, uint8_t state);
	void (*send_byte)(void *hal_i2c_config, uint8_t byte);
} eglib_hal_i2c_t;

#endif