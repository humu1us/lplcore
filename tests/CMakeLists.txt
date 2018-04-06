add_executable(header_new header_new.c)
add_executable(search search.c)

target_link_libraries(header_new lplcore)
target_link_libraries(search lplcore)
