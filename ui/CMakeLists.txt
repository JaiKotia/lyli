
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
include_directories(.. ../usbpp ${OpenCV_INCLUDE_DIRS})

add_subdirectory(calibrationwizard)
add_subdirectory(cameraview)
add_subdirectory(config)
add_subdirectory(imageview)

qt5_wrap_ui(LYLI_UI_SRCS mainwindow.ui)
add_executable(lyli-qt main.cpp mainwindow.cpp progressbar.cpp
               ${LYLI_UI_SRCS})
install(TARGETS lyli-qt RUNTIME DESTINATION bin)
target_link_libraries(lyli-qt lyliuicalibration lyliuicamera lyliuiconfig lyliuiimage lyli
                      usbpp ${CMAKE_THREAD_LIBS_INIT}
                      Qt5::Core Qt5::Widgets)
