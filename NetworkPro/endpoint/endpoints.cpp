#include "endpoints.h"
#include <boost/asio.hpp>
#include <iostream>
using namespace boost;

int client_end_point() {
	std::string raw_ip_address = "127.0.0.1";
	unsigned short port_num = 3333;
	boost:system::error_code ec; // 错误码
	// asio提供转换地址
	asio::ip::address ip_address = asio::ip::address::from_string(raw_ip_address, ec);
	if (ec.value() != 0) {
		std::cout 
			<< "Failed to parse the IP Address. Error code = " 
			<< ec.value() << ". Message is " << ec.message();
		return ec.value();
	}

	// bind（ip+address）
	asio::ip::tcp::endpoint ep(ip_address, port_num);
	return 0;
}

int server_end_point()
{
	unsigned short port_num = 3333;
	// 监听任何可用的IPv6地址 
	asio::ip::address ip_address = asio::ip::address_v6::any();
	asio::ip::tcp::endpoint ep(ip_address, port_num);
	return 0;
}

int create_tcp_socket()
{
	// 上下文告诉socket，此socket为ioc服务
	asio::io_context ioc;
	// IPV4协议
	asio::ip::tcp protocol = asio::ip::tcp::v4();
	asio::ip::tcp::socket socket(ioc);
	boost::system::error_code ec;

	socket.open(protocol, ec);
	if (ec.value() != 0) {
		std::cout 
			<< "Failed to open the socket. Error code = " 
			<< ec.value() << ". Message is " << ec.message();
	}

	return 0;
}

int create_acceptor_socket()
{
	asio::io_context ioc;
	asio::ip::tcp::acceptor a(ioc, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 3333));
	return 0;
}

int bind_acceptor_socket()
{
	unsigned short port_num = 3333;
	asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(), port_num);
	asio::io_context ioc;
	asio::ip::tcp::acceptor acceptor(ioc, ep.protocol());
	boost::system::error_code ec;
	acceptor.bind(ep, ec);
	if (ec.value() != 0) {
		std::cout
			<< "Failed to bind the acceptor socket. Error code = "
			<< ec.value() << ". Message is " << ec.message();
	}
	return 0;
}

int connect_to_end()
{
	std::string raw_ip_address = "192.168.1.124";
	unsigned short port_num = 3333;
	try
	{
		asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address), port_num);
		asio::io_context ioc;
		asio::ip::tcp::socket socket(ioc, ep.protocol());
		socket.connect(ep);
	}
	catch (system::system_error &e)
	{
		std::cout << "Error connect! Error code = " << e.code()
			<< ". Message: " << e.what();
		return e.code().value();
	}
	return 0;
}

int dns_connect_to_end()
{
	std::string host = "scholar618.com";
	std::string port_num = "3333";
	asio::io_context ioc;
	// DNS解析器
	asio::ip::tcp::resolver::query resolver_query(host, port_num, asio::ip::tcp::resolver::query::numeric_service);
	asio::ip::tcp::resolver resolver(ioc);
	try
	{
		asio::ip::tcp::resolver::iterator it = resolver.resolve(resolver_query);
		asio::ip::tcp::socket socket(ioc);
		asio::connect(socket, it);
	}
	catch (system::system_error& e)
	{
		std::cout << "Error DNS! Error code = " << e.code()
			<< ". Message: " << e.what();
		return e.code().value();
	}
	return 0;
}

int accept_int_connection()
{
	// 缓冲来不及接收的信息
	const int BACKLOG_SIZE = 30;
	unsigned short port_num = 3333;
	asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(), port_num);
	asio::io_context ioc;
	try
	{
		asio::ip::tcp::acceptor acceptor(ioc, ep.protocol());
		acceptor.bind(ep);
		acceptor.listen(BACKLOG_SIZE);
		asio::ip::tcp::socket socket(ioc);
		acceptor.accept(socket);
	}
	catch (system::system_error& e)
	{
		std::cout << "Error accept! Error code = " << e.code()
			<< ". Message: " << e.what();
		return e.code().value();
	}
	return 0;
}
