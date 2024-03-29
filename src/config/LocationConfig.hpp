#pragma once

#ifndef __LOCATION_CONFIG_HPP__
#define __LOCATION_CONFIG_HPP__

#include "ConfigInfo.hpp"

class LocationConfig : public ConfigInfo {
  public:
    LocationConfig();
    LocationConfig(const std::set<std::string>& paths, const std::string& ip,
                   const std::string& port, const std::set<std::string>& name,
                   const size_t& size, const std::set<std::string>& indx,
                   const std::set<std::string>&         root_dir,
                   const std::map<size_t, std::string>& error_page,
                   const std::map<size_t, std::string>& return_page,
                   const std::set<std::string>& methods, bool auto_index);
    LocationConfig(const LocationConfig& svconfig);
    virtual ~LocationConfig();

    LocationConfig& operator=(const LocationConfig& svconfig);

    const std::set<std::string>& getPaths() const;
    void                         addPath(const std::string& path);
    void                         addPath(const std::vector<std::string>& paths);

  private:
    std::set<std::string> _paths;
};

#endif
