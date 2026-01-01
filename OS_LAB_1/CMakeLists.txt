cmake_minimum_required(VERSION 3.15)
project(OS_LAB_1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Устанавливаем общую выходную директорию для всех исполняемых файлов
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

# Создаем заголовочный файл employee.h в папке common, если его нет
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/common)
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/common/employee.h)
    file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/common/employee.h
"#ifndef EMPLOYEE_H
#define EMPLOYEE_H

const int NAME_LENGTH = 10;

struct employee
{
    int num;
    char name[NAME_LENGTH];
    double hours;
};

#endif // EMPLOYEE_H
")
endif()

# Creator программа
add_executable(Creator creator/creator.cpp)
target_include_directories(Creator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/common)

# Reporter программа
add_executable(Reporter reporter/reporter.cpp)
target_include_directories(Reporter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/common)

# Основная программа
add_executable(OSLab1 OsLab1/OsLab1.cpp)
target_include_directories(OSLab1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/common)

# Для Windows API
if (WIN32)
    target_link_libraries(OSLab1 kernel32 user32)
endif()

# После сборки копируем необходимые файлы
add_custom_command(TARGET OSLab1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Creator>
        $<TARGET_FILE_DIR:OSLab1>/
    COMMENT "Copying Creator.exe to OSLab1 directory"
)

add_custom_command(TARGET OSLab1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Reporter>
        $<TARGET_FILE_DIR:OSLab1>/
    COMMENT "Copying Reporter.exe to OSLab1 directory"
)

# Создаем удобную цель для запуска
add_custom_target(run
    COMMAND $<TARGET_FILE:OSLab1>
    DEPENDS OSLab1 Creator Reporter
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMENT "Running OSLab1 program"
)