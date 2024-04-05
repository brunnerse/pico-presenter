set(PROJECT_NAME pico-presenter)
#Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)


set(BUILD_BT_VERSION false)
set(BT_USE_BLE false)

set(PICO_BOARD "pico_w")

#include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)


# Set name of project (as PROJECT_NAME) and C/C++ Standards
project(${PROJECT_NAME} C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()


# Create presenter-usb executable
add_executable(presenter-usb
	src/presenter.hpp
        src/usb/presenter-usb.cpp
	src/usb/usb_descriptors.c
)

target_include_directories(presenter-usb PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/src/usb #For tinyusb config
)
target_link_libraries(presenter-usb
        pico_stdlib
	pico_unique_id
	tinyusb_device
	tinyusb_board
)

pico_add_extra_outputs(presenter-usb)


if (${BUILD_BT_VERSION})
if(${PICO_BOARD} STREQUAL "pico_w")
	message("Board supports bluetooth: Creating presenter-bt")
	# Create presenter-usb executable
	add_executable(presenter-bt
		src/presenter.hpp
        	src/bt/presenter-bt.cpp
	)
	
	# Not a must 
	pico_enable_stdio_usb(presenter-bt 1)
	
	target_include_directories(presenter-bt PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/src/bt # For btstack config
	)
	if (${BT_USE_BLE})
		target_link_libraries(presenter-bt
	        	pico_stdlib
			pico_btstack_ble
			#pico_cyw43_arch_none
		)
	else()
		target_link_libraries(presenter-bt
	        	pico_stdlib
		 	pico_btstack_cyw43
			#pico_cyw43_arch_none
		)
	endif()
	
	pico_add_extra_outputs(presenter-bt)
else()
	message("Board does not supports bluetooth: Not creating presenter-bt")
endif()
endif()
