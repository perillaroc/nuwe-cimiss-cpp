#include "data.h"
#include "data_convert.h"

#include <algorithm>

namespace nuwe_cimiss {


RequestInfoPrivate::RequestInfoPrivate(RequestInfo* request_info):
    p{request_info} {

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
    p{array_2d} {
}

void Array2DPrivate::LoadFromProtobufObject(const cma::music::pb::RetArray2D* ret_array_2d) {
    p->request = RequestInfoPrivate::CreateFromProtobufObject(ret_array_2d->request());
    if (p->request.error_code != 0) {
        return;
    }

    p->row_count = p->request.row_count;
    const auto total_count = ret_array_2d->data().size();
    p->col_count = static_cast<int32_t>(total_count / p->row_count);

    std::copy(std::cbegin(ret_array_2d->data()), std::cend(ret_array_2d->data()), std::back_inserter(p->data));
}

// GridArray2DPrivate

GridArray2DPrivate::GridArray2DPrivate(GridArray2D* grid_array_2d):
    p{ grid_array_2d }
{

}

void GridArray2DPrivate::LoadFromProtobufObject(const cma::music::pb::RetGridArray2D* ret_grid_array_2d) {
    p->request = RequestInfoPrivate::CreateFromProtobufObject(ret_grid_array_2d->request());
    if (p->request.error_code != 0) {
        return;
    }

    p->start_lat = ret_grid_array_2d->startlat();
    p->start_lon = ret_grid_array_2d->startlon();
    p->end_lat = ret_grid_array_2d->endlat();
    p->end_lon = ret_grid_array_2d->endlon();
    p->lat_count = ret_grid_array_2d->latcount();
    p->lon_count = ret_grid_array_2d->loncount();
    p->lon_step = ret_grid_array_2d->lonstep();
    p->lat_step = ret_grid_array_2d->latstep();

    if(ret_grid_array_2d->lons_size() == 0) {
        p->lons.resize(p->lon_count);
        std::generate(
            std::begin(p->lons), std::end(p->lons), 
            [start_lon=p->start_lon, lon_step=p->lon_step, n = 0]() mutable {
            const auto value = start_lon + n * lon_step;
            n++;
            return value;
        });
    } else {
        std::copy(std::cbegin(ret_grid_array_2d->lons()), std::cend(ret_grid_array_2d->lons()), std::back_insert_iterator(p->lons));
    }

    if (ret_grid_array_2d->lats_size() == 0) {
        p->lats.resize(p->lat_count);
        std::generate(
            std::begin(p->lats), std::end(p->lats),
            [start_lat = p->start_lat, lat_step = p->lat_step, n = 0]() mutable {
            const auto value = start_lat + n * lat_step;
            n++;
            return value;
        });
    }
    else {
        std::copy(std::cbegin(ret_grid_array_2d->lats()), std::cend(ret_grid_array_2d->lats()), std::back_insert_iterator(p->lats));
    }

    p->units = ret_grid_array_2d->units();
    p->user_element_name = ret_grid_array_2d->userelename();

    auto row_count = p->request.row_count;
    auto data_count = ret_grid_array_2d->data_size();
    auto col_count = static_cast<int>(data_count / row_count);

    p->data.resize(row_count);
    for(auto row_index=0; row_index<row_count; row_index++) {
        std::copy(
            std::cbegin(ret_grid_array_2d->data()) + row_index * col_count,
            std::cbegin(ret_grid_array_2d->data()) + (row_index+1) * col_count,
            std::back_inserter(p->data[row_index])
        );
    }
}


} // namespace nuwe_cimiss
