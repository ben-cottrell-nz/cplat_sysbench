cmake_minimum_required(VERSION 3.21)
project(cplat_sysbench)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
#if (${CMAKE_BUILD_TYPE} STREQUAL "MinSizeRel")
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    add_compile_options(-ffunction-sections -fdata-sections)
    add_link_options(-Wl,--gc-sections)
endif()
include_directories(../libpciutils)
include_directories(../include)
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
add_executable(cplat_sysbench main.cpp ../include/mainwindow.h mainwindow.cpp)
add_library(libpciutils STATIC
        ${CMAKE_SOURCE_DIR}/../libpciutils/init.c
        ${CMAKE_SOURCE_DIR}/../libpciutils/access.c
        ${CMAKE_SOURCE_DIR}/../libpciutils/params.c
        ${CMAKE_SOURCE_DIR}/../libpciutils/caps.c
        ${CMAKE_SOURCE_DIR}/../libpciutils/i386-ports.c
        ${CMAKE_SOURCE_DIR}/../libpciutils/proc.c
        ${CMAKE_SOURCE_DIR}/../libpciutils/sysfs.c
        ${CMAKE_SOURCE_DIR}/../libpciutils/generic.c
        ${CMAKE_SOURCE_DIR}/../libpciutils/dump.c
        ${CMAKE_SOURCE_DIR}/../libpciutils/names.c
        ${CMAKE_SOURCE_DIR}/../libpciutils/names-cache.c
        ${CMAKE_SOURCE_DIR}/../libpciutils/names-hash.c
        ${CMAKE_SOURCE_DIR}/../libpciutils/names-parse.c
        ${CMAKE_SOURCE_DIR}/../libpciutils/names-net.c
        ${CMAKE_SOURCE_DIR}/../libpciutils/names-hwdb.c
        ${CMAKE_SOURCE_DIR}/../libpciutils/filter.c)
set(PCI_IDS "pci.ids")

if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    target_compile_definitions(libpciutils PUBLIC
            LINUX
#            PCI_HAVE_PM_LINUX_SYSFS
#            PCI_HAVE_PM_LINUX_PROC
#            PCI_HAVE_LINUX_BYTEORDER_H
#            PCI_PATH_PROC_BUS_PCI=\"/proc/bus/pci\"
#            PCI_PATH_SYS_BUS_PCI=\"/sys/bus/pci\"
    )
    target_link_libraries(libpciutils udev)
#    set(CPU X86_64)
    execute_process(COMMAND uname -m
            COMMAND tr '[a-z' '[A-Z]'
            OUTPUT_VARIABLE
            CPU)
    configure_file(${CMAKE_SOURCE_DIR}/../libpciutils/config.h.in
            ${CMAKE_SOURCE_DIR}/../libpciutils/config.h)
endif()
target_link_libraries(cplat_sysbench
        libpciutils
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

