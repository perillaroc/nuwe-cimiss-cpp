project("example_grid_array_2d")

add_executable(example_grid_array_2d)

target_sources(example_grid_array_2d
	PRIVATE
	main.cpp
)

target_link_libraries(example_grid_array_2d 
	PRIVATE 
	NuweCimiss::NuweCimiss
	CLI11::CLI11)