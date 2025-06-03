#ifndef __I2C_DEVICE_H__
#define __I2C_DEVICE_H__

#include <cstddef>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "exceptions.h"

class I2CDevice {
    public:
	I2CDevice(int dev_id, int dev_addr);
	// 	: _dev_addr(dev_addr)
	// {
	// 	_dev_name_size = 20;
	// 	_dev_name = new char[_dev_name_size];

	// 	snprintf(_dev_name, _dev_name_size, "/dev/i2c-%d", dev_id);

	// 	open_i2c_dev();
	// }

	I2CDevice(const I2CDevice &) = delete;
	I2CDevice(I2CDevice &&other)
		: _fd(other._fd)
		, _dev_name(other._dev_name)
		, _dev_name_size(other._dev_addr)
		, _dev_addr(other._dev_addr)

	{
		other._fd = -1;
		other._dev_name = nullptr;
		other._dev_name_size = 0;
		other._dev_addr = 0;
	};

	I2CDevice &operator=(I2CDevice &&other)
	{
		if (this != &other) {
			_fd = other._fd;
			_dev_name = other._dev_name;
			_dev_name_size = other._dev_name_size;
			_dev_addr = other._dev_addr;

			other._fd = -1;
			other._dev_name = nullptr;
			other._dev_name_size = 0;
			other._dev_addr = 0;
		}

		return *this;
	}

	inline void i2c_write(int data);
	// {
	// 	write(_fd, &data, 1);
	// }

	~I2CDevice();
	// {
	// 	close(_fd);
	// 	_fd = -1;
	// 	delete _dev_name;
	// }

    private:
	int _fd;
	char *_dev_name;
	uint8_t _dev_name_size;
	int _dev_addr;

	void open_i2c_dev();
	// {
	// 	_fd = open(_dev_name, O_RDWR);
	// 	if (_fd < 0) {
	// 		throw I2CDeviceException("Failed to open i2c dev");
	// 	}

	// 	if (ioctl(_fd, I2C_SLAVE, _dev_addr) < 0) {
	// 		throw I2CDeviceException("Faied to set i2c dev addr");
	// 	}
	// }
};

#endif /* __I2C_DEVICE_H__ */