cmake_minimum_required(VERSION 3.16)

project(PR VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

# Добавляем исполняемый файл (ТОЛЬКО .cpp и .h)
qt_add_executable(appPR
    main.cpp
    authmanager.cpp
)

# Явно добавляем ресурсы
qt_add_resources(appPR "AppResources" PREFIX "/" FILES
    Avto.qml
    Main.qml
    Reg.qml
    16.png
    24.png
)

# Связываем с Qt
target_link_libraries(appPR PRIVATE Qt6::Quick)

# Настройки для Android
if(ANDROID)
    set_target_properties(appPR PROPERTIES
        ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android"
    )
    qt_add_apk(appPR)  # ← ЭТО ОБЯЗАТЕЛЬНО!
endif()

# Установка
include(GNUInstallDirs)
# Диагностика: проверяем, определён ли ANDROID
message(STATUS "=== BUILD TARGET DIAGNOSTICS ===")
message(STATUS "CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
message(STATUS "ANDROID: ${ANDROID}")
message(STATUS "Qt6_ANDROID_ENABLED: ${Qt6_ANDROID_ENABLED}")
install(TARGETS appPR
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
