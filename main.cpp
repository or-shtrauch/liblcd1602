#include <string>
#include <iostream>

#include "include/lcd1602.h"

int main(void)
{
	constexpr int i2c_id = 1;
	constexpr int dev_addr = 0x27;

	LCD1602 lcd(i2c_id, dev_addr);

	std::string line;

	while (1) {
		std::getline(std::cin, line);
		lcd.clear();

		if (line.size() > 16) {
			lcd.send_string(line.substr(0, 16).c_str());
			lcd.drop_line();
			lcd.send_string(line.substr(16).c_str());
		} else {
			lcd.send_string(line.c_str());
		}

	}

	return 0;
}