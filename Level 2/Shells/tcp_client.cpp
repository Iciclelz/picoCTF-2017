#include "tcp_client.hpp"
#include <ws2tcpip.h>
#include <memory>

#pragma comment (lib, "Ws2_32.lib")

tcp_client::tcp_client(int32_t af, int32_t type, int32_t protocol)
{
	WSAStartup(MAKEWORD(2, 2), &wsadata);

	this->af = af;
	this->sock = socket(af, type, protocol);
}

tcp_client::~tcp_client() noexcept
{
	closesocket(this->sock);

	WSACleanup();
}

bool tcp_client::try_connect(const std::pair<std::string, uint16_t>& address)
{
	sockaddr_in sockaddress;
	sockaddress.sin_family = af;
	sockaddress.sin_port = htons(address.second);
	//sockaddress.sin_addr.S_un.S_addr = inet_addr(address.first.c_str());

	inet_pton(this->af, address.first.c_str(), reinterpret_cast<void*>(&sockaddress.sin_addr.S_un.S_addr));

	return connect(this->sock, reinterpret_cast<sockaddr*>(&sockaddress), sizeof(sockaddr)) == 0;
}

bool tcp_client::send_data(const std::vector<byte>& data)
{
	return send(this->sock, reinterpret_cast<const char*>(data.data()), data.size(), 0) > 0;
}

bool tcp_client::send_data(const std::string & data)
{
	return send(this->sock, data.c_str(), data.size(), 0) > 0;
}

bool tcp_client::receive_data(std::vector<byte> &data, size_t size)
{
	std::unique_ptr<byte[]> buffer = std::make_unique<byte[]>(size);
	int32_t size_received = recv(this->sock, reinterpret_cast<char*>(buffer.get()), size, 0);
	std::copy(buffer.get(), buffer.get() + size_received, std::back_inserter(data));

	return size_received > 0;
}

bool tcp_client::receive_data(std::string &data, size_t size)
{
	std::unique_ptr<char[]> buffer = std::make_unique<char[]>(size);
	int32_t size_received = recv(this->sock, reinterpret_cast<char*>(buffer.get()), size, 0);
	//std::copy(buffer.get(), buffer.get() + size_received, std::back_inserter(data));
	data = buffer.get();

	return size_received > 0;
}

std::vector<byte> tcp_client::get_data(size_t size)
{
	std::vector<byte> data;
	this->receive_data(data, size);
	return data;
}

std::string tcp_client::get_string(size_t size)
{
	std::string data;
	this->receive_data(data, size);
	return data;
}
