cmake_minimum_required(VERSION 3.19)
project(Casino LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets StateMachine Gui)

qt_standard_project_setup()

qt_add_executable(Casino
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    icons/apple.png icons/banana.png icons/pineapple.png icons/watermelon.png
    reel.h reel.cpp

)

target_link_libraries(Casino
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::StateMachine
        Qt::Gui
)

include(GNUInstallDirs)

install(TARGETS Casino
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Casino
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
