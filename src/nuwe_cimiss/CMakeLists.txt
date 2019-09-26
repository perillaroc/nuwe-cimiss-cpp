project("nuwe_cimiss")

add_library(nuwe_cimiss STATIC)

find_package(protobuf CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

find_path(CPP_HTTPLIB_INCLUDE_PATH httplib.h REQUIRED)

find_path(CPP_INIH_INCLUDE_PATH INIReader.h REQUIRED)
find_library(CPP_INIH_LIBRARY inih REQUIRED)

target_sources(nuwe_cimiss
	PRIVATE
		include/nuwe_cimiss/data.h
		include/nuwe_cimiss/client.h
		src/client.cpp
		src/data.cpp
		src/apiinterface.pb.h
		src/apiinterface.pb.cc
		src/connection.h
		src/connection.cpp
		src/data_convert.h
		src/data_convert.cpp
)

target_include_directories(nuwe_cimiss
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/include/nuwe_cimiss
		${CPP_HTTPLIB_INCLUDE_PATH}
		${CPP_INIH_INCLUDE_PATH}
)

target_link_libraries(nuwe_cimiss
	PRIVATE
		protobuf::libprotobuf 
		fmt::fmt-header-only
		nlohmann_json::nlohmann_json
		${CPP_INIH_LIBRARY}
)

add_library(NuweCimiss::NuweCimiss ALIAS nuwe_cimiss)