
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
include_directories(.. ../ ${OpenCV_INCLUDE_DIRS})

qt5_wrap_ui(LYLI_UI_IMAGE_SRCS viewerform.ui)
add_library(lyliuiimage SHARED
               viewerform.cpp lytroimage.cpp
               ${LYLI_UI_IMAGE_SRCS})
target_link_libraries(lyliuiimage lyli Qt5::Core Qt5::Widgets)
install(TARGETS lyliuiimage LIBRARY DESTINATION lib)
