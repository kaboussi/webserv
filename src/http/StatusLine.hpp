#ifndef __STATUS_LINE_HPP__
#define __STATUS_LINE_HPP__

#include "HTTP.hpp"
#include <iostream>

// Method "" uri "" version CRLF
// GET /index.html HTTP/1.1
class StatusLine {
  public:
    StatusLine();
    StatusLine(HTTP::METHOD, const std::string&, HTTP::VERSION);
    std::string serliaze() const;
    static StatusLine deserialize(const std::string& status_line);

  private:
    HTTP::METHOD _method;
    std::string _uri;
    HTTP::VERSION _version;

};

#endif // __STATUS_LINE_HPP__
