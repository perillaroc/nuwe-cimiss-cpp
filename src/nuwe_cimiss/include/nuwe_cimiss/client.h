#pragma once
#include <nuwe_cimiss/data.h>

#include <memory>
#include <functional>
#include <any>

#include "nuwe_cimiss/connection.h"

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

    std::unique_ptr<Array2D> callAPI_to_array2D(const std::string &interface_id, const ApiParams& params, const std::string &server_id="");

private:
    void LoadConfig();

    std::any DoRequest(
        const std::string& interface_id,
        const std::string& method,
        const ApiParams& params,
        const std::string& server_id,
        Connection::HandlerFunction&& success_handler,
        Connection::HandlerFunction&& failure_handler,
        Connection::HandlerFunction&& exception_handler
    );

    std::string GetFetchUrl(
        const std::string& interface_id,
        const std::string& method,
        const ApiParams& params,
        std::string server_id=""
    ) const;

    CimissClientConfig config_;
    std::string config_file_ = "client.conf";
    std::string user_ ;
    std::string password_;

    const std::string client_language_ = "Python";
    const std::string client_version_ = "V2.0.0";
    const std::string basic_url_ = "/music-ws/api?serviceNodeId={server_id}&";

    std::unique_ptr<Connection> connection_;
};

} // nuwe_cimiss