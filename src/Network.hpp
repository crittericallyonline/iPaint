#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <libwebsockets.h>
#include <iostream>
#include <string>
#include <thread>

struct Network {
	~Network();
	bool offline = true;
	std::thread thread;
	struct lws* web_socket = NULL;
	struct lws_context* context = NULL;
	void Connect();
} Network;

#endif //NETWORK_HPP