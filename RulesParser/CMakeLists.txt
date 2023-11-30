project(RulesParser)

set(HEADER_FILES
        RegularDefinition.h
        RegularExpression.h
        RulesConverter.h)

set(SOURCE_FILES
        RegularDefinition.cpp
        RegularExpression.cpp
        RulesConverter.cpp)


add_library(RulesParser_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(RulesParser_lib PUBLIC Util_lib)