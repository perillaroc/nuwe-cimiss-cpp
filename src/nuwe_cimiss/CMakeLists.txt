project("nuwe_cimiss")

add_library(nuwe_cimiss STATIC)

set(Protobuf_DEBUG ON)
set(Protobuf_USE_STATIC_LIBS ON)
find_package(protobuf CONFIG REQUIRED)

target_sources(nuwe_cimiss
	PRIVATE
		include/nuwe_cimiss/data.h
		src/data.cpp
		src/apiinterface.pb.h
		src/apiinterface.pb.cc
)

target_include_directories(nuwe_cimiss
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(nuwe_cimiss
	PRIVATE
		protobuf::libprotoc 
		protobuf::libprotobuf 
		protobuf::libprotobuf-lite
)

add_library(NuweCimiss::NuweCimiss ALIAS nuwe_cimiss)