#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <memory>


namespace nuwe_cimiss {

struct RequestInfoPrivate;

struct RequestInfo {
    RequestInfo();
    RequestInfo(
        int32_t error_code,
        std::string &error_message,
        std::string &request_elements,
        std::string &request_params,
        std::string &request_time,
        std::string &response_time,
        int32_t row_count,
        int32_t take_time,
        int32_t col_count
    );

    int32_t error_code = 0;
    std::string error_message;
    std::string request_elements;
    std::string request_params;
    std::string request_time;
    std::string response_time;
    int32_t row_count = 0;
    int32_t take_time = 0;
    int32_t col_count = 0;

private:
    std::unique_ptr<RequestInfoPrivate> d_;
    friend struct RequestInfoPrivate;
};


struct ResponseData{
    ResponseData() = default;
    virtual ~ResponseData() = default;

    virtual void LoadFromProtobufContent(const std::string& content) = 0;

    RequestInfo request;
};

struct Array2DPrivate;

struct Array2D: public ResponseData {
    Array2D();

    void LoadFromProtobufContent(const std::string& content) override;

    std::vector<std::string> data;
    std::vector<std::string> element_names;
    int32_t row_count;
    int32_t col_count;

private:
    std::unique_ptr<Array2DPrivate> d_;
};


struct GridArray2D {
    std::vector<float> data;
    RequestInfo request;
    float start_lat = 0.0f;
    float start_lon = 0.0f;
    float end_lat = 0.0f;
    float end_lon = 0.0f;
    int32_t lat_count = 0;
    int32_t lon_count = 0;
    float lon_step = 0.0f;
    float lat_step = 0.0f;
    std::vector<float> lats;
    std::vector<float> lons;
    std::string units;
    std::string user_element_name;
};

} // namespace nuwe_cimiss