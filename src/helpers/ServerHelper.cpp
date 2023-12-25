#include "ServerHelper.hpp"
#include <arpa/inet.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>

const char* ServerHelper::GetIPAddressFromSockAddr(int sockfd) {
    struct sockaddr_storage addr;
    socklen_t               len = sizeof(addr);
    static char             buffer[INET6_ADDRSTRLEN];

    std::memset(&addr, 0, sizeof(addr));
    std::memset(buffer, 0, sizeof(buffer));
    if (getsockname(sockfd, (struct sockaddr*)&addr, &len) == -1) {
        std::perror("getsockname ip");
        return NULL;
    }
    if (addr.ss_family == AF_INET) {
        struct sockaddr_in* s = (struct sockaddr_in*)&addr;
        inet_ntop(AF_INET, &(s->sin_addr), buffer, INET6_ADDRSTRLEN);
    } else { // AF_INET6
        struct sockaddr_in6* s = (struct sockaddr_in6*)&addr;
        inet_ntop(AF_INET6, &(s->sin6_addr), buffer, INET6_ADDRSTRLEN);
    }
    return buffer;
}

const char* ServerHelper::GetPortAddressFromSockAddr(int sockfd) {
    static char             portBuffer[6];
    struct sockaddr_storage addr;
    socklen_t               len = sizeof(addr);

    std::memset(&addr, 0, sizeof(addr));
    std::memset(portBuffer, 0, sizeof(portBuffer));
    if (getsockname(sockfd, (struct sockaddr*)&addr, &len) == -1) {
        std::perror("getsockname port");
        return NULL;
    }
    if (addr.ss_family == AF_INET) {
        struct sockaddr_in* s = (struct sockaddr_in*)&addr;
        snprintf(portBuffer, sizeof(portBuffer), "%d", ntohs(s->sin_port));
    } else { // AF_INET6
        struct sockaddr_in6* s = (struct sockaddr_in6*)&addr;
        snprintf(portBuffer, sizeof(portBuffer), "%d", ntohs(s->sin6_port));
    }
    return portBuffer;
}
