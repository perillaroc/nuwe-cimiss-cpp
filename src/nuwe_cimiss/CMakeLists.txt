project("nuwe_cimiss")

add_library(nuwe_cimiss STATIC)

# set(Protobuf_DEBUG ON)
# set(Protobuf_USE_STATIC_LIBS ON)
find_package(protobuf CONFIG REQUIRED)

find_path(CPP_HTTPLIB_INCLUDE_PATH httplib.h REQUIRED)

target_sources(nuwe_cimiss
	PRIVATE
		include/nuwe_cimiss/data.h
		include/nuwe_cimiss/client.h
		include/nuwe_cimiss/apiinterface.pb.h
		src/client.cpp
		src/data.cpp
		src/apiinterface.pb.cc
)

target_include_directories(nuwe_cimiss
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/include/nuwe_cimiss
		${CPP_HTTPLIB_INCLUDE_PATH}
)

target_link_libraries(nuwe_cimiss
	PRIVATE
		protobuf::libprotobuf 
)

add_library(NuweCimiss::NuweCimiss ALIAS nuwe_cimiss)