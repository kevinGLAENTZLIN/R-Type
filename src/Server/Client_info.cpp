/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client_info
*/

#include "Client_info.hh"

Rtype::client_info::client_info():
	_id(-1), _x(0), _y(0), _AckExpected(0), _AckToSend(0), _gameRoom(false),
	_inGame(false), _port(-1), _addr("")
{
}

Rtype::client_info::client_info(int id, int port, std::string addr):
	_id(id), _x(0), _y(0), _AckExpected(0), _AckToSend(0), _gameRoom(false),
	_inGame(false), _port(port), _addr(addr)
{
}

Rtype::client_info::~client_info()
{
}

int Rtype::client_info::getId() const
{
	return _id;
}

void Rtype::client_info::setId(int id)
{
	_id = id;
}

int Rtype::client_info::getX() const
{
	return _x;
}

void Rtype::client_info::setX(int x)
{
	_x = x;
}

int Rtype::client_info::getY() const
{
	return _y;
}

void Rtype::client_info::setY(int y)
{
	_y = y;
}

int Rtype::client_info::getAckToExpect() const
{
	return _AckExpected;
}

void Rtype::client_info::setAckToExpect()
{
	_AckExpected++;
}

int Rtype::client_info::getAckToSend() const
{
	return _AckToSend;
}

void Rtype::client_info::setAckToSend()
{
	_AckToSend++;
}

int Rtype::client_info::getRoom() const
{
	return _gameRoom;
}

void Rtype::client_info::setRoom(int room)
{
	_gameRoom = room;
}

int Rtype::client_info::getPort() const
{
	return _port;
}

void Rtype::client_info::setPort(int port)
{
	_port = port;
}

std::string Rtype::client_info::getAddr() const
{
	return _addr;
}

void Rtype::client_info::setAddr(std::string address)
{
	_addr = address;
}

void Rtype::client_info::pushCmdToHistory(int function_type, int function_index,  std::va_list params)
{
	int nb_params = Utils::ParametersMap::getNbParameterPerFunctionClient(function_type, function_index);
	std::string params_type = Utils::ParametersMap::getParameterTypePerFunctionClient(function_type, function_index);
	std::vector<std::string> vector_params;

	for (int i = 0; i < nb_params; i++) {
		switch (params_type[i]) {
			case 'b':
				vector_params.push_back(std::to_string(va_arg(params, int)));
				break;
			case 'c':
				vector_params.push_back(std::to_string(va_arg(params, int)));
				break;
			case 'i':
				vector_params.push_back(std::to_string(va_arg(params, int)));
				break;
			case 'f':
				vector_params.push_back(std::to_string(va_arg(params, double)));
				break;
			default:
				std::cerr << "Unsupported type" << std::endl;
				break;
		}
	}
	_history[_AckToSend] = std::make_tuple(function_type, function_index, vector_params);
	setAckToSend();
}
