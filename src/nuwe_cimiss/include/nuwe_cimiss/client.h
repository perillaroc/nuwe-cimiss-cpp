#pragma once
#include <nuwe_cimiss/data.h>

namespace nuwe_cimiss {

using ApiParams = std::map<std::string, std::string>;

struct CimissClientConfig {
    std::string server_ip;
    std::string server_port;
    std::string server_id;
    int connection_timeout = 0;
    int read_timeout = 0;

    void LoadConfig(const std::string &config_file);
};

class CimissClient final{
public:
    explicit CimissClient(const CimissClientConfig &config, const std::string& config_file = "");

    void connect(const std::string& user, const std::string& password);

    Array2D callAPI_to_array2D(const std::string &interface_id, const ApiParams& params, const std::string &server_id="");

private:
    void LoadConfig();

    CimissClientConfig config_;
    std::string config_file_ = "client.conf";
    std::string user_ ;
    std::string password_;
};

} // nuwe_cimiss