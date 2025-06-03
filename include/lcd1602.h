#ifndef __LCD1602_H__
#define __LCD1602_H__

#include "i2c_device.h"

static constexpr int lcd_clear_dispaly = 0x01;
static constexpr int lcd_function_set = 0x20;
static constexpr int lcd_return_home = 0x02;
static constexpr int lcd_display_control = 0x08;
static constexpr int lcd_entry_mode_set = 0x04;
static constexpr int lcd_set_ddram_mode_addr = 0x80;

// Flags
static constexpr int lcd_4bit_mode = 0x00;
static constexpr int lcd_2line = 0x08;
static constexpr int lcd_5x8_dots = 0x00;
static constexpr int lcd_display_on = 0x04;
static constexpr int lcd_cursor_off = 0x00;
static constexpr int lcd_cursor_on = 0x02;
static constexpr int lcd_blink_off = 0x00;
static constexpr int lcd_blink_on = 0x01;
static constexpr int lcd_entry_left = 0x02;
static constexpr int lcd_entry_shift_decrement = 0x00;

// Backlight and control bits
static constexpr int lcd_back_light = 0x08;
static constexpr int en_mode = 0x04; // Enable = bit
static constexpr int rs_mode = 0x01; // Register select bit

class LCD1602 {
    public:
	LCD1602(int id, int addr)
		: _id(id)
		, _addr(addr)
		, _dev(id, addr)
	{
		send_init_seq();
	}

	LCD1602(const LCD1602 &other) = delete;

	~LCD1602() = default;

	void send_string(const char *str)
	{
		uint8_t i = 0;
		while (str != NULL && *str && i < 16) {
			send_char(*str++);
			i++;
		}
	}

	void drop_line(void)
	{
		send_command(lcd_set_ddram_mode_addr | 0x40);
	}

	void clear(void)
	{
		send_command(lcd_clear_dispaly);
		send_command(lcd_return_home);
	}

    private:
	int _id;
	int _addr;
	I2CDevice _dev;

	inline void _write(int data)
	{
		_dev.i2c_write(data);
	}

	inline void _pulse(int data)
	{
		_write(data | en_mode);
		usleep(1);
		_write(data & ~en_mode);
		usleep(50);
	}

	inline void write_4_bits(int data)
	{
		_write(data);
		_pulse(data);
	}

	inline void send_byte(int value, int mode)
	{
		int high = value & 0xf0;
		int low = (value << 4) & 0xf0;

		write_4_bits(high | mode | lcd_back_light);
		write_4_bits(low | mode | lcd_back_light);
	}

	inline void send_command(int cmd)
	{
		send_byte(cmd, 0);
	}

	inline void send_char(char c)
	{
		send_byte(c, rs_mode);
	}

	inline void send_init_seq(void)
	{
		usleep(50000);

		write_4_bits(0x30 | lcd_back_light);
		usleep(4500);

		write_4_bits(0x30 | lcd_back_light);
		usleep(4500);

		write_4_bits(0x30 | lcd_back_light);
		usleep(150);

		write_4_bits(0x20 | lcd_back_light);

		send_command(lcd_function_set | lcd_4bit_mode | lcd_2line |
			     lcd_5x8_dots);

		send_command(lcd_display_control | lcd_display_on |
			     lcd_cursor_off | lcd_blink_off);

		send_command(lcd_clear_dispaly);
		usleep(2000);

		send_command(lcd_entry_mode_set | lcd_entry_left |
			     lcd_entry_shift_decrement);
	}
};

#endif /* __LCD1602_H__ */