add_executable(header_new header_new.c)
add_executable(search search.c)
add_executable(append append.c)
add_executable(delete delete.c)

target_link_libraries(header_new lplcore)
target_link_libraries(search lplcore)
target_link_libraries(append lplcore)
target_link_libraries(delete lplcore)
