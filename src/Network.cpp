#include "Network.hpp"
#include "Display.hpp"

void Display::SetTitle(const char* title) const
{
	glfwSetWindowTitle(window, title);
}

inline void Poll()
{
	while (Network.context != NULL)
	{
		lws_service(Network.context, 250);
	}
}

Network::~Network()
{
	offline = true;
	if (thread.joinable()) {
		thread.join();
	};
}

int Callback(struct lws* wsi, enum lws_callback_reasons reason, void* user, void* in, size_t len)
{
	switch (reason)
	{

	case LWS_CALLBACK_CLIENT_ESTABLISHED:
		Network.offline = false;
		Display.SetTitle("WebITG (Online)");
		break;

	case LWS_CALLBACK_CLIENT_RECEIVE:
		// std::cout << "Length: " << len << std::endl;
		if (len < 2)
		{
			std::cout << "Length is too small!" << std::endl;
			break;
		}

		uint16_t packet_type;
		memcpy(&packet_type, in, sizeof(uint16_t));
		static unsigned char* buff;

		if (packet_type == 0x0001)
		{
			buff = (unsigned char*)calloc(1, 2 + 4);
			buff[0] = 0x01;
			lws_write(wsi, buff, 2 + 4, LWS_WRITE_BINARY);
		}

		break;


	case LWS_CALLBACK_CLIENT_CLOSED:
	case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
		std::cout << "Disconnected from server!" << std::endl;
		Network.web_socket = NULL;
		Network.offline = true;
		Display.SetTitle("WebITG (Offline)");
		break;

	default:
		break;
	}
	return 0;
}

enum protocols
{
	PROTOCOL_EXAMPLE = 0,
	PROTOCOL_COUNT
};

static struct lws_protocols protocols[]
{
	{
		.name = "callback",
		.callback = &Callback,
		.per_session_data_size = 0,
		.rx_buffer_size = 0,
		.id = 0,
		.user = nullptr,
		.tx_packet_size = 0
	},
	LWS_PROTOCOL_LIST_TERM
};


void Network::Connect()
{
	struct lws_context_creation_info info;
	memset(&info, 0, sizeof(info));

	info.port = CONTEXT_PORT_NO_LISTEN; /* we do not run any server */
	info.protocols = protocols;
	info.gid = -1;
	info.uid = -1;

	context = lws_create_context(&info);

	/* Connect if we are not connected to the server. */
	if (!web_socket && offline)
	{
		struct lws_client_connect_info ccinfo;
		memset(&ccinfo, 0, sizeof(ccinfo));

		ccinfo.context = context;
		ccinfo.address = "147.185.221.16";
		ccinfo.port = 53060;
		ccinfo.path = "/";
		ccinfo.host = lws_canonical_hostname(context);
		ccinfo.origin = "origin";
		ccinfo.protocol = protocols[PROTOCOL_EXAMPLE].name;

		web_socket = lws_client_connect_via_info(&ccinfo);
	}

	thread = std::thread(Poll);
	thread.detach();
}