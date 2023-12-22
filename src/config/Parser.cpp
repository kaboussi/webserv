#include "Parser.hpp"

Parser::Parser(const std::string& source) : _lexer(source) {
    _token = _lexer.scan();
    _prev = _token;
}

void    Parser::parse() {
    statement();
}

void    Parser::statement() {
    serverContext();

    while (!isAtEnd()) {
        serverContext();
    }
}

void    Parser::serverContext() {
    consume(SERVER_CONTEXT, "Expect a server context.");
    block();
}

void    Parser::block() {
    consume(LEFT_BRACE, "Expect a left brace after the server context.");
    while (!isAtEnd() && !check(RIGHT_BRACE)) {
        if (matchServerDirective()) {
            parameter();
            if (peek().getLine() != previous().getLine() || !match(SEMICOLON))
                throw ParseException(peek(), "Expect a ';' after statement.");
        } else if (match(LOCATION_CONTEXT)) {
            locationContext();
        } else {
            throw ParseException(peek(), "Invalid statement.");
        }
    }
    consume(RIGHT_BRACE, "Expect end brace '}' after expression.");
}

void    Parser::locationContext() {
    consume(PARAMETER, "Expect a path.");
    std::vector<std::string>    params;

    do {
        params.push_back(previous().getLexeme());
    }   while (match(PARAMETER));
    consume(LEFT_BRACE, "Expect a left brace '{' after statement.");
    if (!matchLocationDirective())
        throw ParseException(peek(), "Expect statement.");
    Token   token;
    do {
        parameter();
        if (peek().getLine() != previous().getLine() || !match(SEMICOLON))
            throw ParseException(peek(), "Expect a ';' after statement.");
    }   while (matchLocationDirective());
    consume(RIGHT_BRACE, "Expect end brace '}' after statement.");
}

void    Parser::parameter() {
    Token   prev = previous();

    if (!check(PARAMETER))
        throw ParseException(peek(), "Expect parameter for the directive.");

    std::vector<std::string>    params;

    while (match(PARAMETER))
        params.push_back(previous().getLexeme());
}

bool    Parser::matchServerDirective() {
    switch (peek().getType()) {
        case LISTEN:
        case SERVER_NAME:
        case CLIENT_MAX_BODY_SIZE:
        case ROOT:
        case INDEX:
        case ERROR_PAGE:
            advance();
            return true;
        default:
            break;
    }
    return false;
}

bool    Parser::matchLocationDirective() {
    switch (peek().getType()) {
        case AUTOINDEX:
        case RETURN:
        case ALLOW_METHODS:
        case ROOT:
        case ERROR_PAGE:
        case CLIENT_MAX_BODY_SIZE:
            advance();
            return true;
        default:
            break;
    }
    return false;
}

void    Parser::consume(TokenType type, const std::string& message) {
    if (match(type))
        return;
    throw ParseException(_prev, message);
}

bool    Parser::match(TokenType type) {
    if (!check(type))
        return false;
    advance();
    return true;
}

Token&  Parser::previous() { return _prev; }

void    Parser::advance() {
    if (isAtEnd())
        return;
    _prev = _token;
    _token = _lexer.scan();
}

bool    Parser::check(TokenType type) {
    return peek().getType() == type;
}

Token&  Parser::peek() {
    return _token;
}

bool    Parser::isAtEnd() const {
    return _token.getType() == END;
}
