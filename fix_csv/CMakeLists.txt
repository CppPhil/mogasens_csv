# STATIC LIBRARY
set(LIB_NAME fix_mogasens_csv_lib)

set(LIB_HEADERS
    include/adjust_hardware_timestamp.hpp
    include/convert_to_unix_line_endings.hpp
    include/create_backup_file.hpp
    include/delete_non_bosch_sensors.hpp
    include/delete_out_of_bounds_values.hpp
    include/remove_zeros_from_field.hpp
    include/restore_from_backup.hpp
    include/write_file.hpp)

set(LIB_SOURCES
    src/adjust_hardware_timestamp.cpp
    src/convert_to_unix_line_endings.cpp
    src/create_backup_file.cpp
    src/delete_non_bosch_sensors.cpp
    src/delete_out_of_bounds_values.cpp
    src/remove_zeros_from_field.cpp
    src/restore_from_backup.cpp
    src/write_file.cpp)

add_library(${LIB_NAME} STATIC ${LIB_HEADERS} ${LIB_SOURCES})

target_link_libraries(${LIB_NAME} PUBLIC csv_lib)

target_include_directories(${LIB_NAME}
                           PUBLIC ${mogasens_csv_SOURCE_DIR}/fix_csv/include)

# APPLICATION
set(APP_NAME fix_mogasens_csv_app)

add_executable(${APP_NAME} src/main.cpp)

target_link_libraries(${APP_NAME} PRIVATE ${LIB_NAME})

add_subdirectory(test)
