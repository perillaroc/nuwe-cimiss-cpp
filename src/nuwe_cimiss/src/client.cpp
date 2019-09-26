#include "nuwe_cimiss/client.h"

#include "INIReader.h"

namespace nuwe_cimiss {

void CimissClientConfig::LoadConfig(const std::string &config_file)
{
    INIReader reader(config_file);
    if (reader.ParseError() < 0)
    {
        throw std::runtime_error("parser config file has error");
    }

    if(server_ip.empty())
    {
        server_ip = reader.GetString("Pb", "music_server", "");
    }

    if (server_port.empty())
    {
        server_port = reader.GetString("Pb", "music_port", "");
    }

    if (server_id.empty())
    {
        server_id = reader.GetString("Pb", "music_ServiceId", "");
    }

    if (connection_timeout == 0)
    {
        connection_timeout = reader.GetInteger("Pb", "music_connTimeout", 0);
    }

    if (read_timeout == 0)
    {
        read_timeout = reader.GetInteger("Pb", "music_readTimeout", 0);
    }
}

CimissClient::CimissClient(const CimissClientConfig& config, const std::string& config_file):
config_{config}
{
    if(!config_file.empty())
    {
        config_file_ = config_file;
    }
    LoadConfig();
}

void CimissClient::connect(const std::string& user, const std::string& password)
{
    user_ = user;
    password_ = password;
}

Array2D CimissClient::callAPI_to_array2D(
    const std::string &interface_id, 
    const ApiParams& params,
    const std::string& server_id)
{
    Array2D array_2d{};

    return array_2d;
}

void CimissClient::LoadConfig()
{
    config_.LoadConfig(config_file_);
}
} // namespace nuwe_cimiss