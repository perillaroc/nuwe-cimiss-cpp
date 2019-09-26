#include "data.h"
#include "data_convert.h"

#include <algorithm>

namespace nuwe_cimiss {



RequestInfoPrivate::RequestInfoPrivate(RequestInfo* request_info):
    p{request_info}
{

}

void RequestInfoPrivate::LoadFromProtobufObject(const cma::music::pb::RequestInfo& pb_request_info) {
    p->error_code = pb_request_info.errorcode();
    p->error_message = pb_request_info.errormessage();
    p->request_elements = pb_request_info.requestelems();
    p->request_params = pb_request_info.requesttime();
    p->request_time = pb_request_info.requesttime();
    p->row_count = pb_request_info.rowcount();
    p->take_time = pb_request_info.taketime();
    p->col_count = pb_request_info.colcount();
}

RequestInfo RequestInfoPrivate::CreateFromProtobufObject(const cma::music::pb::RequestInfo& pb_request_info) {
    RequestInfo request_info;
    request_info.d_->LoadFromProtobufObject(pb_request_info);
    return request_info;
}

Array2DPrivate::Array2DPrivate(Array2D* array_2d):
    p{array_2d}
{
}

void Array2DPrivate::LoadFromProtobufObject(const cma::music::pb::RetArray2D* ret_array_2d)
{
    p->request = RequestInfoPrivate::CreateFromProtobufObject(ret_array_2d->request());
    if (p->request.error_code != 0) {
        return;
    }

    p->row_count = p->request.row_count;
    const auto total_count = ret_array_2d->data().size();
    p->col_count = static_cast<int32_t>(total_count / p->row_count);

    std::copy(std::cbegin(ret_array_2d->data()), std::cend(ret_array_2d->data()), std::back_inserter(p->data));
}


} // namespace nuwe_cimiss