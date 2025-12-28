cmake_minimum_required(VERSION 3.16)

project(PR VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

# Добавляем исполняемый файл
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
    message(STATUS "✅ ANDROID detected. Setting up APK build...")

    # Указываем путь к Android-ресурсам
    set_target_properties(appPR PROPERTIES
        ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android"
    )

    # Создаём APK
    qt_add_apk(appPR)

    # Диагностика: проверяем, создан ли таргет apk
    if(TARGET appPR_apk)
        message(STATUS "✅ Target 'appPR_apk' created successfully!")
    else()
        message(FATAL_ERROR "❌ Target 'appPR_apk' not created! Check Qt Android setup.")
    endif()

else()
    message(STATUS "⚠️ NOT building for Android. Skip APK creation.")
endif()

# Установка (для Linux/macOS/Windows)
include(GNUInstallDirs)
install(TARGETS appPR
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)