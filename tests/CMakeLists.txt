find_package(Qt6 REQUIRED COMPONENTS Test)

macro(add_qt_test NAME SOURCES)
    add_executable(${NAME} ${SOURCES}
        models/test_models.cpp
        ../model/character.cpp
        ../model/character.h
        ../model/episode.cpp
        ../model/episode.h
    )

    target_link_libraries(${NAME} PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Network
        Qt${QT_VERSION_MAJOR}::Test
    )

    target_include_directories(${NAME} PRIVATE ${CMAKE_SOURCE_DIR})
    target_include_directories(${NAME} PRIVATE ../${CMAKE_SOURCE_DIR})

    add_test(NAME ${NAME} COMMAND ${NAME})
endmacro()

add_qt_test(test_models
    ../model/character.h
    ../model/episode.h
    ../model/character.cpp
    ../model/episode.cpp
)


# add_qt_test(test_apiclient services/test_apiclient.cpp)
