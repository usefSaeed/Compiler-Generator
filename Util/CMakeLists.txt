project(Util)

set(HEADER_FILES
        util.h)

set(SOURCE_FILES
        util.cpp)

add_library(Util_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})