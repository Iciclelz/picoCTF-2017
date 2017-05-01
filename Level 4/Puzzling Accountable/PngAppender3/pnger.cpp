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


std::vector<byte> get_stream(const std::string &s = "a.txt")
{
	std::vector<byte> stream;
	std::ifstream infile(s);
	std::string line;
	while (std::getline(infile, line))
	{
		std::vector<byte> temp = string_to_bytes(line);
		stream.insert(stream.end(), temp.begin() + 66, temp.end());
	}

	return stream;
}

int main()
{
	std::vector<byte> stream = get_stream();
	
	/*for (byte b : stream)
	{
		printf("%.02x ", b);
	}*/

	std::ofstream outfile("flag.png", std::ios::out | std::ios::binary);
	outfile.write((char*)stream.data(), stream.size());
	outfile.close();

	getchar();
	return 0;
}

