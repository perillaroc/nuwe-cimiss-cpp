#include "client.h"
#include "connection.h"

#include <INIReader.h>
#include <fmt/format.h>

#include <filesystem>

namespace nuwe_cimiss {

void CimissClientConfig::LoadConfig(const std::string& config_file) {
    INIReader reader(config_file);
    if (reader.ParseError() < 0) {
        throw std::runtime_error("parser config file has error");
    }

    if (server_ip.empty()) {
        server_ip = reader.GetString("Pb", "music_server", "");
    }

    if (server_port.empty()) {
        server_port = reader.GetString("Pb", "music_port", "");
    }

    if (server_id.empty()) {
        server_id = reader.GetString("Pb", "music_ServiceId", "");
    }

    if (connection_timeout == 0) {
        connection_timeout = reader.GetInteger("Pb", "music_connTimeout", 0);
    }

    if (read_timeout == 0) {
        read_timeout = reader.GetInteger("Pb", "music_readTimeout", 0);
    }
}

CimissClient::CimissClient(const CimissClientConfig& config, const std::string& config_file):
    config_{config} {
    if (!config_file.empty()) {
        config_file_ = config_file;
    }
    LoadConfig();
}

void CimissClient::Connect(const std::string& user, const std::string& password) {
    user_ = user;
    password_ = password;
    connection_ = std::make_unique<Connection>(this);
}

std::unique_ptr<Array2D> CimissClient::callAPI_to_array2D(
    const std::string& interface_id,
    const ApiParams& params,
    const std::string& server_id) {
    auto array_2d = std::make_unique<Array2D>();

    const std::string method = "callAPI_to_array2D";

    auto result = DoRequest(
        interface_id,
        method,
        params,
        server_id,
        Connection::GeneratePackSuccessHandler(array_2d.get()),
        Connection::GeneratePackFailureHandler(array_2d.get()),
        Connection::GenerateExceptionHandler(array_2d.get())
    );

    return array_2d;
}

void CimissClient::LoadConfig() {
    const std::filesystem::path config_file_path{config_file_};
    if (!std::filesystem::exists(config_file_path)) {
        throw std::runtime_error("config file is not available.");
    }
    config_.LoadConfig(config_file_);
}

std::any CimissClient::DoRequest(
    const std::string& interface_id,
    const std::string& method,
    const ApiParams& params,
    const std::string& server_id,
    HandlerFunction&& success_handler,
    HandlerFunction&& failure_handler,
    HandlerFunction&& exception_handler) {
    const auto fetch_url = GetFetchUrl(interface_id, method, params, server_id);
    return connection_->MakeRequest(
        config_.server_ip,
        std::stoi(config_.server_port),
        fetch_url,
        success_handler,
        failure_handler,
        exception_handler);
}

CimissClient::~CimissClient() {
}

std::string CimissClient::GetFetchUrl(
    const std::string& interface_id,
    const std::string& method,
    const ApiParams& params,
    std::string server_id) const {
    if (server_id.empty()) {
        server_id = config_.server_id;
    }

    const auto basic_url = fmt::format(
        basic_url_,
        fmt::arg("server_id", server_id)
    );

    auto fetch_url = fmt::format(
        "{basic_url}method={method}&userId={user}&pwd={password}&interfaceId={interface_id}"
        "&language={client_language}&clientversion={client_version}",
        fmt::arg("basic_url", basic_url),
        fmt::arg("method", method),
        fmt::arg("user", user_),
        fmt::arg("password", password_),
        fmt::arg("interface_id", interface_id),
        fmt::arg("client_language", client_language_),
        fmt::arg("client_version", client_language_)
    );

    for (const auto& [key, value] : params) {
        fetch_url += fmt::format("&{key}={value}", fmt::arg("key", key), fmt::arg("value", value));
    }

    return fetch_url;
}
} // namespace nuwe_cimiss
