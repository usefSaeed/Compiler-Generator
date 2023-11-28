project(RulesParser)

set(HEADER_FILES
        regularDefinition.h
        regularExpression.h)

set(SOURCE_FILES
        regularDefinition.cpp
        regularExpression.cpp)

add_library(RulesParser_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})