#include "data.h"
#include "data_convert.h"


namespace nuwe_cimiss {

RequestInfo::RequestInfo() {
    d_ = std::make_unique<RequestInfoPrivate>(this);
}

RequestInfo::RequestInfo(
    int32_t error_code,
    std::string& error_message,
    std::string& request_elements,
    std::string& request_params,
    std::string& request_time,
    std::string& response_time,
    int32_t row_count,
    int32_t take_time,
    int32_t col_count):
    error_code(error_code),
    error_message(error_message),
    request_elements(request_elements),
    request_params(request_params),
    request_time(request_time),
    response_time(response_time),
    row_count(row_count),
    take_time(take_time),
    col_count(col_count) {

}


Array2D::Array2D() {
    d_ = std::make_unique<Array2DPrivate>(this);
}

void Array2D::LoadFromProtobufContent(const std::string& content) {
    cma::music::pb::RetArray2D ret_array_2d;
    auto result = ret_array_2d.ParseFromString(content);
    if (!result) {
        return;
    }
    d_->LoadFromProtobufObject(&ret_array_2d);
}

} // namespace nuwe_cimiss
