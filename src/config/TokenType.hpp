#pragma once

#ifndef __TOKEN_TYPE_HPP__
#define __TOKEN_TYPE_HPP__

enum TokenType {
    SERVER,
    LOCATION,
    LISTEN,
    SERVER_NAME,
    ROOT,
    INDEX,
    CLIENT_MAX_BODY_SIZE,
    ERROR_PAGE,
    AUTOINDEX,
    RETURN,
    ALLOW_METHODS,
    LEFT_BRACE,
    RIGHT_BRACE,
    SEMICOLON,
    PARAMETER,
    END
};

#endif
