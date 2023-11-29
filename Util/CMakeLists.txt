project(Util)

set(HEADER_FILES
        Util.h)

set(SOURCE_FILES
        Util.cpp)

add_library(Util_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})