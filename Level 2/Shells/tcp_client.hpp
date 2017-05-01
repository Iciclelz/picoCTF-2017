#pragma once
#include <WinSock2.h>
#include <string>
#include <vector>
#include <cstdint>

class tcp_client
{
private:
	SOCKET sock;
	WSADATA wsadata;
	int32_t af;

public:
	tcp_client(
		_In_ int32_t af = AF_INET,
		_In_ int32_t type = SOCK_STREAM,
		_In_ int32_t protocol = 0);

	~tcp_client() noexcept;

	bool try_connect(_In_ const std::pair<std::string, uint16_t> &address);

	bool send_data(_In_ const std::vector<byte> &data);
	bool send_data(_In_ const std::string &data);

	bool receive_data(
		_Inout_ std::vector<byte> &data, 
		_In_ size_t size = 1024);

	bool receive_data(
		_Inout_ std::string &data,
		_In_ size_t size = 1024);

	std::vector<byte> get_data(_In_ size_t size = 1024);
	std::string	get_string(_In_ size_t size = 1024);

};
