#include "connection.h"
#include "client.h"

#include <httplib.h>
#include <nlohmann/json.hpp>
#include <fmt/format.h>

namespace nuwe_cimiss {

const std::string Connection::kGetWayFlag = R"("flag":"slb")";

Connection::Connection(CimissClient* client):
client_{client}
{
}

std::any Connection::MakeRequest(
    const std::string& host,
    int port,
    const std::string& url, 
    const HandlerFunction& success_handler,
    const HandlerFunction& failure_handler,
    const HandlerFunction& exception_handler) const
{
    httplib::Client cli(host.c_str(), port);
    const auto response = cli.Get(url.c_str());

    if(response == nullptr)
    {
        return exception_handler("");
    }

    const auto content = response->body;

    if(CheckGetwayFlag(content))
    {
        return failure_handler(content);
;   }

    return success_handler(content);
}

Connection::HandlerFunction Connection::GeneratePackSuccessHandler(ResponseData* response_data)
{
    return [response_data](const std::string& content) {
        response_data->LoadFromProtobufContent(content);
        return true;
    };
}

Connection::HandlerFunction Connection::GeneratePackFailureHandler(ResponseData* response_data)
{
    return [response_data](const std::string& content) {
        auto getway_info = nlohmann::json::parse(content);
        if(getway_info.empty())
        {
            response_data->request.error_code = kOtherError;
            response_data->request.error_message = fmt::format("parse getway return string error: {}", content);
        }
        else
        {
            response_data->request.error_code = getway_info["returnCode"];
            response_data->request.error_message = getway_info["returnMessage"];
        }
        return true;
    };
}

Connection::HandlerFunction Connection::GenerateExceptionHandler(ResponseData* response_data)
{
    return [response_data](const std::string&) {
        response_data->request.error_code = kOtherError;
        response_data->request.error_message = "Error retrieving data";
        return true;
    };
}

bool Connection::CheckGetwayFlag(const std::string& content)
{
    return content.find(kGetWayFlag) != std::string::npos;
}
} // namespace nuwe_cimiss