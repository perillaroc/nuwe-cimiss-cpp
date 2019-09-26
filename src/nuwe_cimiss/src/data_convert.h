#pragma once
#include "apiinterface.pb.h"

namespace nuwe_cimiss {

struct RequestInfo;

struct RequestInfoPrivate {
    explicit RequestInfoPrivate(RequestInfo* request_info);

    void LoadFromProtobufObject(const cma::music::pb::RequestInfo& pb_request_info);

    static RequestInfo CreateFromProtobufObject(const cma::music::pb::RequestInfo& pb_request_info);

    RequestInfo* p;
};

struct Array2D;

struct Array2DPrivate {
    explicit Array2DPrivate(Array2D* array_2d);

    void LoadFromProtobufObject(const cma::music::pb::RetArray2D* ret_array_2d);

    Array2D* p;
};


} // namespace
