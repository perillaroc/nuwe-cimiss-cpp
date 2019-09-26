#include "nuwe_cimiss/data.h"

#include <algorithm>

namespace nuwe_cimiss {

RequestInfo::RequestInfo(
    int32_t error_code, 
    std::string &error_message, 
    std::string &request_elements,
    std::string &request_params, 
    std::string &request_time, 
    std::string &response_time, 
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
col_count(col_count)
{

}

void RequestInfo::LoadFromProtobufObject(const cma::music::pb::RequestInfo & pb_request_info) {
    error_code = pb_request_info.errorcode();
    error_message = pb_request_info.errormessage();
    request_elements = pb_request_info.requestelems();
    request_params = pb_request_info.requesttime();
    request_time = pb_request_info.requesttime();
    row_count = pb_request_info.rowcount();
    take_time = pb_request_info.taketime();
    col_count = pb_request_info.colcount();
}

RequestInfo RequestInfo::CreateFromProtobufObject(const cma::music::pb::RequestInfo &pb_request_info)
{
    RequestInfo request_info;
    request_info.LoadFromProtobufObject(pb_request_info);
    return request_info;
}

ResponseData::ResponseData(RequestInfo& request_info):
request(request_info)
{
}

void Array2D::LoadFromProtobufContent(const std::string& content)
{
    cma::music::pb::RetArray2D ret_array_2d;
    auto result = ret_array_2d.ParseFromString(content);
    if(!result)
    {
        return;
    }
    LoadFromProtobufObject(&ret_array_2d);
}

void Array2D::LoadFromProtobufObject(cma::music::pb::RetArray2D* ret_array_2d)
{
    request = RequestInfo::CreateFromProtobufObject(ret_array_2d->request());
    if(request.error_code != 0){
        return;
    }

    row_count = request.row_count;
    const auto total_count = ret_array_2d->data().size();
    col_count = static_cast<int32_t>(total_count / row_count);

    std::copy(std::cbegin(ret_array_2d->data()), std::cend(ret_array_2d->data()), std::back_inserter(data));

}

} // namespace nuwe_cimiss