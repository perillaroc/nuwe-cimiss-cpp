#pragma once
#include <string>
#include <any>
#include <functional>

#include "nuwe_cimiss/client.h"

namespace nuwe_cimiss {

struct ResponseData;

class Connection final {
public:
    static const std::string kGetWayFlag;
    static const int kOtherError = -10001;

    explicit Connection(CimissClient* client);

    std::any MakeRequest(
        const std::string& host,
        int port,
        const std::string& url,
        const CimissClient::HandlerFunction& success_handler,
        const CimissClient::HandlerFunction& failure_handler,
        const CimissClient::HandlerFunction& exception_handler
    ) const;

    static CimissClient::HandlerFunction GeneratePackFailureHandler(ResponseData* response_data);

    static CimissClient::HandlerFunction GeneratePackSuccessHandler(ResponseData* response_data);

    static CimissClient::HandlerFunction GenerateExceptionHandler(ResponseData* response_data);

private:
    static bool CheckGetwayFlag(const std::string& content);

    CimissClient* client_;
};

} // namespace nuwe_cimiss
