#include "i2c_device.h"

static constexpr int i2c_device_name_size = 20;

I2CDevice::I2CDevice(int dev_id, int dev_addr)
	: _dev_addr(dev_addr)
{
	_dev_name_size = i2c_device_name_size;
	_dev_name = new char[_dev_name_size];

	snprintf(_dev_name, _dev_name_size, "/dev/i2c-%d", dev_id);

	open_i2c_dev();
}

inline void I2CDevice::i2c_write(int data)
{
	write(_fd, &data, 1);
}

~I2CDevice::I2CDevice();
{
	close(_fd);
	_fd = -1;
	delete _dev_name;
}

void I2CDevice::open_i2c_dev()
{
	_fd = open(_dev_name, O_RDWR);
	if (_fd < 0) {
		throw I2CDeviceException("Failed to open i2c dev");
	}

	if (ioctl(_fd, I2C_SLAVE, _dev_addr) < 0) {
		throw I2CDeviceException("Faied to set i2c dev addr");
	}
}
