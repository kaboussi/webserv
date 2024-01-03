#include "Socket.hpp"
#include "AddressResolver.hpp"
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fcntl.h>
#include <iostream>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

Socket::Socket() : _addresses(NULL, NULL) {}

Socket::Socket(const char* ip, const char* port)
    : _sockfd(-1), _ip(ip), _port(port), _addresses(ip, port) {
    initializeSocket();
    _addresses.~AddressResolver();
    _ip = const_cast<char*>(ServerHelper::GetIPAddressFromSockAddr(_sockfd));
    _port =
        const_cast<char*>(ServerHelper::GetPortAddressFromSockAddr(_sockfd));
    std::cout << "Successfully listening on " << _ip << ":" << _port << "\n";
}

const char* Socket::getIP() const {
    return _ip;
}

const char* Socket::getPort() const {
    return _port;
}

void Socket::initializeSocket() {
    struct addrinfo* addresses =
        const_cast<struct addrinfo*>(_addresses.getAddresses());
    for (struct addrinfo* address = addresses; address;
         address = address->ai_next) {
        if ((_sockfd = socket(address->ai_family, address->ai_socktype,
                              address->ai_protocol)) == -1) {
            std::perror("server socket");
            continue;
        }
        try {
            configureSocket();
            bindSocket(*address);
        } catch (const std::exception& ex) {
            std::cout << ex.what() << std::endl;
            close(_sockfd);
            continue;
        }
        return;
    }
    std::cerr << "Error: could not bind address for " << std::string(_ip) + ":"
              << std::string(_port) << ".\n";
    std::exit(EXIT_FAILURE);
}

Socket::~Socket() {
    close(_sockfd);
}

int Socket::getSocketfd() const {
    return _sockfd;
}

void Socket::configureSocket() {
    if (fcntl(_sockfd, F_SETFL, O_NONBLOCK, FD_CLOEXEC) < 0) {
        throw std::runtime_error("Failed to configure socket");
    }
    int option = 1;
    if (setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &option,
                   sizeof(option)) == -1) {
        throw std::runtime_error("Failed to set socket option");
    }
}

void Socket::bindSocket(const struct addrinfo address) {
    const int bret = bind(_sockfd, address.ai_addr, address.ai_addrlen);
    if (bret < 0) {
        throw std::runtime_error("Failed to bind on socket: " +
                                 std::string(strerror(errno)));
    }
    const int lret = listen(_sockfd, BACKLOG);
    if (lret < 0) {
        throw std::runtime_error("Failed to listen on socket: " +
                                 std::string(strerror(errno)));
    }
}
