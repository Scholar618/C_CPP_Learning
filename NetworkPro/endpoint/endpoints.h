#pragma once
/* client_end_point
 * 客户端连接服务器端
 * 已知服务器端的IP、port转换成端点
 */
extern int client_end_point();

extern int server_end_point();

// 创建客户端socket
extern int create_tcp_socket();

// 创建服务器socket
extern int create_acceptor_socket();

// 服务器bind（socket绑定port/ip）
extern int bind_acceptor_socket();

// 客户端connect操作
extern int connect_to_end();

// 解析域名
extern int dns_connect_to_end();

// 服务器接收连接
extern int accept_int_connection();