cmake_minimum_required(VERSION 3.19)

project( createQtAppImage
    VERSION 0.0.1
    LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable( ${PROJECT_NAME}
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
)

target_link_libraries( ${PROJECT_NAME}
    PRIVATE
        Qt::Core
        Qt::Widgets
)

target_compile_definitions( ${PROJECT_NAME}
    PRIVATE
        VERSION=${PROJECT_VERSION}
        PROGRAM=${PROJECT_NAME}
)

install( TARGETS ${PROJECT_NAME}
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install( FILES ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.png
         DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/256x256/apps )
install( FILES ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.desktop
         DESTINATION ${CMAKE_INSTALL_DATADIR}/applications )

qt_generate_deploy_app_script(
    TARGET ${PROJECT_NAME}
    OUTPUT_SCRIPT deploy_script
    INCLUDE_PLUGINS xcb wayland
    NO_UNSUPPORTED_PLATFORM_ERROR
    NO_TRANSLATIONS
)
install( SCRIPT ${deploy_script} )

install( CODE
  "include(${CMAKE_SOURCE_DIR}/cmake/CreateAppImage.cmake)
   create_appimage(
        EXE \"${PROJECT_NAME}\"
        ICON \"${PROJECT_NAME}.png\"
        DESKTOP \"${PROJECT_NAME}.desktop\"
        WORKDIR \"${CMAKE_BINARY_DIR}\"
        APPDIR \"${PROJECT_NAME}-v${PROJECT_VERSION}-${CMAKE_SYSTEM_PROCESSOR}.AppDir\"
        ARCH \"${CMAKE_SYSTEM_PROCESSOR}\"
   )"
)

if (DEFINED ENV{GITHUB_OUTPUT})
    file(APPEND
        "$ENV{GITHUB_OUTPUT}"
        "config_version=${PROJECT_VERSION}\n"
    )
endif()
