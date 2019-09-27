#pragma once
#include <nuwe_cimiss/data.h>

#include <map>
#include <memory>
#include <functional>
#include <any>

namespace nuwe_cimiss {

struct CimissClientConfig {
    std::string server_ip;
    std::string server_port;
    std::string server_id;
    int connection_timeout = 0;
    int read_timeout = 0;

    void LoadConfig(const std::string& config_file);
};

class Connection;

using ApiParams = std::map<std::string, std::string>;

class CimissClient final {
public:
    using HandlerFunction = std::function<std::any(const std::string&)>;

    explicit CimissClient(const CimissClientConfig& config, const std::string& config_file = "");
    ~CimissClient();

    void Connect(const std::string& user, const std::string& password);

    std::unique_ptr<Array2D> callAPI_to_array2D(
        const std::string& interface_id,
        const ApiParams& params,
        const std::string& server_id = "");


    std::unique_ptr<GridArray2D> callAPI_to_gridArray2D(
        const std::string& interface_id,
        const ApiParams& params,
        const std::string& server_id = "");

private:
    void LoadConfig();

    std::any DoRequest(
        const std::string& interface_id,
        const std::string& method,
        const ApiParams& params,
        const std::string& server_id,
        HandlerFunction&& success_handler,
        HandlerFunction&& failure_handler,
        HandlerFunction&& exception_handler
    );

    std::string GetFetchUrl(
        const std::string& interface_id,
        const std::string& method,
        const ApiParams& params,
        std::string server_id = ""
    ) const;

    CimissClientConfig config_;
    std::string config_file_ = "client.conf";
    std::string user_;
    std::string password_;

    const std::string client_language_ = "Python";
    const std::string client_version_ = "V2.0.0";
    const std::string basic_url_ = "/music-ws/api?serviceNodeId={server_id}&";

    std::unique_ptr<Connection> connection_;
};

} // nuwe_cimiss
