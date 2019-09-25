add_library(vendor INTERFACE)

target_include_directories(vendor
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
    )

add_library(NuweCimiss::vendor ALIAS vendor)

install(TARGETS vendor EXPORT NwpcCodesCppTargets
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
)