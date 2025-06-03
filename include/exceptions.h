#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <exception>
#include <string>

class I2CDeviceException : public std::exception {
    private:
	std::string _msg;

    public:
	I2CDeviceException(const std::string &&msg)
		: _msg(std::move(msg))
	{
	}

	const char *what()
	{
		return _msg.c_str();
	}
};

class LCD1602Exception : public std::exception {
    private:
	std::string _msg;

    public:
	LCD1602Exception(const std::string &&msg)
		: _msg(std::move(msg))
	{
	}

	const char *what()
	{
		return _msg.c_str();
	}
};

#endif /* __EXCEPTIONS_H__ */