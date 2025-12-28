cmake_minimum_required(VERSION 3.16)

project(PR VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

# Добавляем исполняемый файл
qt_add_executable(appPR
    main.cpp
    authmanager.cpp
    qml.qrc
)

# Явно добавляем ресурсы (без модуля)
qt_add_resources(appPR "AppResources" PREFIX "/" FILES
    Avto.qml
    Main.qml
    Reg.qml
    16.png
    24.png
)

# Связываем с Qt
target_link_libraries(appPR PRIVATE Qt6::Quick)

# Установка
include(GNUInstallDirs)
install(TARGETS appPR
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
