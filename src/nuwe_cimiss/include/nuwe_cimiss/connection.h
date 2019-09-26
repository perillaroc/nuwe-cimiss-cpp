#pragma once
#include <string>
#include <any>
#include <functional>

namespace nuwe_cimiss {

struct ResponseData;

class CimissClient;

class Connection final
{
public:
    using HandlerFunction = std::function<std::any(const std::string&)>;

    static const std::string kGetWayFlag;
    static const int kOtherError = -10001;

    explicit Connection(CimissClient* client);

    std::any MakeRequest(
        const std::string& host,
        int port,
        const std::string& url,
        const HandlerFunction& success_handler,
        const HandlerFunction& failure_handler,
        const HandlerFunction& exception_handler
    ) const;

    static HandlerFunction GeneratePackFailureHandler(ResponseData* response_data);

    static HandlerFunction GeneratePackSuccessHandler(ResponseData* response_data);

    static HandlerFunction GenerateExceptionHandler(ResponseData* response_data);

private:
    static bool CheckGetwayFlag(const std::string& content);

    CimissClient* client_;
};

} // namespace nuwe_cimiss