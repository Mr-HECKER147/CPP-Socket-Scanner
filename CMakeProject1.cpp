// CMakeProject1.cpp : Defines the entry point for the application.
//

#include "CMakeProject1.h"
#include <string>
#include <chrono>

using namespace std;

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
    #define CLOSE_SOCKET closesocket
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define CLOSE_SOCKET close
#endif

bool isPortOpen(const char* host, int port, int timeout_ms = 1000) {
    #ifdef _WIN32
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
        cerr << "WSAStartup failed" << endl;
        return false;
    }
    #endif

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        cerr << "Socket creation failed" << endl;
        #ifdef _WIN32
        WSACleanup();
        #endif
        return false;
    }

    struct sockaddr_in server_addr {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, host, &server_addr.sin_addr);

    // Set non-blocking mode and timeout
    #ifdef _WIN32
    unsigned long mode = 1;
    ioctlsocket(sock, FIONBIO, &mode);
    #else
    fcntl(sock, F_SETFL, O_NONBLOCK);
    #endif

    int result = connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    bool is_open = (result == 0);

    if (!is_open) {
        #ifdef _WIN32
        int error = WSAGetLastError();
        is_open = (error == WSAEWOULDBLOCK || error == WSAEINPROGRESS);
        #else
        int error = errno;
        is_open = (error == EINPROGRESS || error == EWOULDBLOCK);
        #endif
    }

    CLOSE_SOCKET(sock);

    #ifdef _WIN32
    WSACleanup();
    #endif

    return is_open;
}

int main() {
    cout << "=== Simple Socket Scanner ===" << endl;
    cout << "Scanning localhost (127.0.0.1) for open ports..." << endl << endl;

    const char* host = "127.0.0.1";
    int ports[] = { 80, 443, 22, 3306, 5432, 8080, 8443, 9000 };

    cout << "Port\t| Status" << endl;
    cout << "--------+--------" << endl;

    for (int port : ports) {
        if (isPortOpen(host, port, 500)) {
            cout << port << "\t| OPEN" << endl;
        }
        else {
            cout << port << "\t| CLOSED" << endl;
        }
    }

    cout << "\nScan complete!" << endl;
    return 0;
}
