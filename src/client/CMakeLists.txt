aux_source_directory(. SRC_LIST)

add_executable(chatClient ${SRC_LIST} ../../include/server/redis/redis.h)

target_link_libraries(chatClient pthread)