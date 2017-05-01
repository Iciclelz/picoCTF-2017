#include <vector>
#include <string>
#include <windows.h>
#include <random>
#include <chrono>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <unordered_map>

const std::vector<byte> string_to_bytes(const std::string & array_of_bytes)
{
	std::vector<byte> data;
	std::string array_data(array_of_bytes);

	array_data.erase(std::remove(array_data.begin(), array_data.end(), ' '), array_data.end());
	if ((array_data.size() % 2) || !array_data.size())
	{
		return data;
	}

	data.reserve(array_data.size() / 2);

	std::mt19937 mt(static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count()));
	std::uniform_int_distribution<int32_t> dist(0, 15);
	char hexadecimal_character[] = "0123456789ABCDEF";

	for (size_t n = 0; n < array_data.size(); ++n)
	{
		if (!isxdigit(array_data.at(n)))
		{
			array_data.at(n) = hexadecimal_character[dist(mt)];
		}
	}

	for (size_t i = 0; i < array_data.size(); i += 2)
	{
		std::stringstream ss;
		ss << std::hex << array_data.at(i) << array_data.at(i + 1);
		data.push_back(static_cast<uint8_t>(std::stoi(ss.str(), nullptr, 16)));
	}

	return data;
}

void print_vector(const std::vector<std::vector<byte>> &data)
{
	for (auto &n : data)
	{
		for (auto b : n)
		{
			printf("%.02X ", b);
		}
		printf("\n");
	}
}

void print_vector_(const std::vector<byte> &data)
{
	for (auto b : data)
	{
		printf("%.02X ", b);
	}
	printf("\n");
}

std::unordered_map<byte, char> bytecode;
void print_bcvector_(const std::vector<byte> &data)
{
	for (auto b : data)
	{
		printf("%c ", bytecode[b]);
	}
	printf("\n");
}

std::vector<byte> get_truncated_vector(const std::vector<byte> &data)
{
	std::vector<byte> truncated;

	for (size_t n = 27; n < data.size(); ++n)
	{
		truncated.push_back(data.at(n));
	}

	return truncated;
}

int main()
{
	std::vector<std::vector<byte>> data;

	std::ifstream infile("keyptrying.txt");
	std::string line;
	while (std::getline(infile, line))
	{
		data.push_back(string_to_bytes(line));
	}

	for (auto v : data)
	{
		print_vector_(get_truncated_vector(v));
	}
	printf("\n");

	
	char temp = 'a';
	for (byte b = 0x04; temp <= 'z'; ++b, ++temp)
	{
		bytecode[b] = temp;
	}

	bytecode[0x1E] = '1';
	bytecode[0x1F] = '2';
	bytecode[0x20] = '3';
	bytecode[0x21] = '4';
	bytecode[0x22] = '5';
	bytecode[0x23] = '6';
	bytecode[0x24] = '7';
	bytecode[0x25] = '8';
	bytecode[0x26] = '9';
	bytecode[0x27] = '0';

	bytecode[0x2F] = '{';
	bytecode[0x30] = '}';

	bytecode[0x2D] = '_';

	bytecode[0] = ' ';

	for (auto v : data)
	{
		print_bcvector_(get_truncated_vector(v));
	}

	printf("\n");

	for (auto v : data)
	{
		char c = bytecode[get_truncated_vector(v).at(2)];
		if (c != ' ')
		{
			printf("%c", c);
		}
		
	}

	printf("\n");

	getchar();
	return 0;
}