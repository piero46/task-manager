cmake_minimum_required(VERSION 3.16)

project(PR VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

if(ANDROID)
    set(QT_ANDROID_APP ON)
endif()

qt_standard_project_setup(REQUIRES 6.8)

# Добавляем исполняемый файл
qt_add_executable(cardan
    main.cpp
    authmanager.cpp
    authmanager.h
)

# Явно добавляем ресурсы
qt_add_resources(cardan "AppResources" PREFIX "/" FILES
    Avto.qml
    Main.qml
    Reg.qml
    16.png
    24.png
)

# Настройки для Android
if(ANDROID)
    message(STATUS "✅ ANDROID detected. Setting up APK build...")

    # Указываем путь к Android-ресурсам
    set_target_properties(cardan PROPERTIES
        ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android"
    )

    # В Qt 6.10.1 не используется qt_add_apk()
    # APK создаётся автоматически при сборке исполняемого файла

else()
    message(STATUS "⚠️ NOT building for Android. Skip APK creation.")
endif()

# Связываем с Qt (после Android-настроек)
target_link_libraries(cardan PRIVATE Qt6::Quick)

# Установка (для Linux/macOS/Windows)
include(GNUInstallDirs)
install(TARGETS cardan
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)