#ifndef __HTTP_HPP__
#define __HTTP_HPP__

#define CRLF "\r\n"
#include <iostream>

namespace HTTP {
enum METHOD { GET, POST, PUT, DELETE };

enum VERSION { HTTP_1_0, HTTP_1_1, HTTP_2_0 };

enum STATUS_CODE {
    OK = 200,
    CREATED = 201,
    ACCEPTED = 202,
    NO_CONTENT = 203,
    BAD_REQUEST = 400,
    FORBIDDEN = 403,
    NOT_FOUND = 404,
    REQUEST_TIMEOUT = 408,
    REQUEST_ENTITY_TOO_LARGE = 413,
    REQUEST_URI_TOO_LONG = 414,
    INTERNAL_SERVER_ERROR = 500,
    NOT_IMPLEMENTED = 501,
    BAD_GATEWAY = 502,
    SERVICE_UNAVAILABLE = 503,
};

std::string toString(VERSION version);
VERSION     toVersion(const std::string& version);
std::string toString(METHOD method);
METHOD      toMethod(const std::string& method);

} // namespace HTTP

#endif
