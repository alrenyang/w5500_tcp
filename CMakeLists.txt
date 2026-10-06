cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME GR100)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

#하위 폴더의 모든 *.c를 포함 한다.
file(GLOB_RECURSE SRC_FILES_RECURSE CONFIGURE_DEPENDS
    # Middlewares/lvgl/*.c
    Middlewares/Internet/DNS/*.c
    Middlewares/Internet/Socket/*.c
    Middlewares/Internet/*.c
    Middlewares/Ethernet/*.c
    Middlewares/Ethernet/W5500/*.c
    Middlewares/Internet/httpServer/*.c
    App/driver/src/*.c
    # App/lvgl/src/*.c
    App/*.c

    # src/ap/*.cpp
    # src/ap/*.c
    # src/bsp/*.s
    # src/common/*.c
    # src/hw/*.c
    # src/lib/STM32H7xx_HAL_Driver/Src/*.c
    # src/lib/littlefs/*.c

    # #lvgl
    # src/hw/driver/lvgl/*.c
    # src/lib/lvgl/*.c

    # src/ap/touch-gfx/*.cpp
    # src/lib/touchgfx/framework/source/touchgfx/*.cpp  
)

# 특정 폴더를 빌드에서 제외한다.
# 추가 설정
set(EXCLUDE_PATHS 
    # "src/ap/touch-gfx/build"
    # "src/ap/touch-gfx/simulator"
    # "src/ap/touch-gfx/generated/simulator"
    # "src/lib/touchgfx_backup"
    # "src/ap/touch-gfx"
    "Middlewares/Internet/MQTT"
    "Middlewares/Internet/TFTP"
    "Middlewares/Internet/SNMP"
    "Middlewares/Internet/SNTP"
    # "Middlewares/Internet/httpServer"
    "Middlewares/Internet/DHCP6"
)

#추가 설정
foreach(TMP_PATH ${SRC_FILES_RECURSE}) 
    foreach(EXCLUDE_PATH ${EXCLUDE_PATHS}) 
        string(FIND ${TMP_PATH} ${EXCLUDE_PATH} RESULT) 
        if(NOT ${RESULT} EQUAL -1) 
            list(REMOVE_ITEM SRC_FILES_RECURSE ${TMP_PATH}) 
        endif() 
    endforeach(EXCLUDE_PATH) 
endforeach(TMP_PATH)


# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    ${SRC_FILES_RECURSE}    #반드시 추가 해야함.
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    Core/Inc
    # Middlewares/lvgl
    Middlewares/
    Middlewares/Ethernet/
    Middlewares/Ethernet/W5500/
    Middlewares/Internet/
    Middlewares/Internet/DNS/
    Middlewares/Application/
    Middlewares/Internet/httpServer/
    App/
    # App/Lvgl/Inc/
    App/driver/Inc/
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)

# 경고 메시지를 에러로 처리하지 않고 무시하도록 설정
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wno-format)

#추가 설정
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "================================ BUILD SUCCESS ================================"
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.hex
    COMMAND ${CMAKE_COMMAND} -E echo "HEX : ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.hex"
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin
    COMMAND ${CMAKE_COMMAND} -E echo "BIN : ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin"
    # COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf
    # COMMAND ${CMAKE_COMMAND} -E echo "ELF : ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf"
    COMMAND ${CMAKE_COMMAND} -E echo "=============================================================================="
    COMMENT "Generating hex and bin files"
)