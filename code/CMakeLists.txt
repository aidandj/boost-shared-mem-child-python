cmake_minimum_required(VERSION 3.13)

include_directories(/usr/local/include /usr/include/python3.7m)
link_directories(/usr/local/lib)

add_link_options(-Wl,--unresolved-symbols=report-all)

add_library(python_shared_mem SHARED python_shared_mem.cpp)
set_target_properties(python_shared_mem PROPERTIES PREFIX "")

target_link_libraries(python_shared_mem boost_python37 python3.7m pthread rt)