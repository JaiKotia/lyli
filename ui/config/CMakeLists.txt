
include_directories(.. ../ ../../usbpp ${OpenCV_INCLUDE_DIRS})

add_library(lyliuiconfig SHARED
            lyliconfig.cpp)
target_link_libraries(lyliuiconfig lyliuicalibration usbpp lyli Qt5::Core Qt5::Widgets)
install(TARGETS lyliuiconfig LIBRARY DESTINATION lib)
