#include "RunTimeException.hpp"
#include "ConfigParse.hpp"

RunTimeException::RunTimeException(const Token& token,
                                const std::string& message)
{
    _errMsg = "[line " + ConfigParse::toString(token.getLine()) + "] at '"
            + token.getLexeme() + "': " + message;
}

RunTimeException::~RunTimeException() throw() {}

const char* RunTimeException::what() const throw() { return _errMsg.c_str(); }