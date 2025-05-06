cmake_minimum_required(VERSION 3.16)

project(Convenient_Anime_Manager VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Sql)
find_package(Qt6 REQUIRED COMPONENTS Multimedia)
find_package(Qt6 REQUIRED COMPONENTS MultimediaWidgets)
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)

set(PROJECT_SOURCES
        main.cpp
        anime_management_homepage.cpp
        anime_management_homepage.h
)
# Cards_Page
file(GLOB CAPA_H  ${CMAKE_CURRENT_SOURCE_DIR}/Cards_Page Cards_Page/*.h)
set(FILE_H_A ${CAPA_H})

file(GLOB CAPA_CPP  ${CMAKE_CURRENT_SOURCE_DIR}/Cards_Page Cards_Page/*.cpp)
set(FILE_CPP_A ${CAPA_CPP})

# Cards_Page/Menu_Set
file(GLOB CAPAMESE_H  ${CMAKE_CURRENT_SOURCE_DIR}/Cards_Page/Menu_Set Cards_Page/Menu_Set/*.h)
set(FILE_H_E ${CAPAMESE_H})

file(GLOB CAPAMESE_CPP  ${CMAKE_CURRENT_SOURCE_DIR}/Cards_Page/Menu_Set Cards_Page/Menu_Set/*.cpp)
set(FILE_CPP_E ${CAPAMESE_CPP})

# Horizontal_Navigation_Page
file(GLOB HONAPA_H  ${CMAKE_CURRENT_SOURCE_DIR}/Horizontal_Navigation_Page Horizontal_Navigation_Page/*.h)
set(FILE_H_B ${HONAPA_H})

file(GLOB HONAPA_CPP  ${CMAKE_CURRENT_SOURCE_DIR}/Horizontal_Navigation_Page Horizontal_Navigation_Page/*.cpp)
set(FILE_CPP_B ${HONAPA_CPP})

# Playback_Page
file(GLOB PLPA_H  ${CMAKE_CURRENT_SOURCE_DIR}/Playback_Page Playback_Page/*.h)
set(FILE_H_C ${PLPA_H})

file(GLOB PLPA_CPP  ${CMAKE_CURRENT_SOURCE_DIR}/Playback_Page Playback_Page/*.cpp)
set(FILE_CPP_C ${PLPA_CPP})


# Cards_Page/Menu_Set/New_Menu_Component
file(GLOB CAPAMESENEMECO_H  ${CMAKE_CURRENT_SOURCE_DIR}/Cards_Page/Menu_Set/New_Menu_Component Cards_Page/Menu_Set/New_Menu_Component/*.h)
set(FILE_H_F ${CAPAMESENEMECO_H})

file(GLOB CAPAMESENEMECO_CPP  ${CMAKE_CURRENT_SOURCE_DIR}/Cards_Page/Menu_Set/New_Menu_Component Cards_Page/Menu_Set/New_Menu_Component/*.cpp)
set(FILE_CPP_F ${CAPAMESENEMECO_CPP})

# Playback_Page
file(GLOB SISE_H  ${CMAKE_CURRENT_SOURCE_DIR}/Singleton_Set Singleton_Set/*.h)
set(FILE_H_G ${SISE_H})

file(GLOB SISE_CPP  ${CMAKE_CURRENT_SOURCE_DIR}/Singleton_Set Singleton_Set/*.cpp)
set(FILE_CPP_G ${SISE_CPP})

# Playback_Page/Video_Components
file(GLOB PLPAVICO_H  ${CMAKE_CURRENT_SOURCE_DIR}/Playback_Page/Video_Components Playback_Page/Video_Components/*.h)
set(FILE_H_H ${PLPAVICO_H})

file(GLOB PLPAVICO_CPP  ${CMAKE_CURRENT_SOURCE_DIR}/Playback_Page/Video_Components Playback_Page/Video_Components/*.cpp)
set(FILE_CPP_H ${PLPAVICO_CPP})

file(GLOB LEWUBTUAR_H  ${CMAKE_CURRENT_SOURCE_DIR}/Left_Window_Tip_Area Left_Window_Tip_Area/*.h)
set(FILE_H_I ${LEWUBTUAR_H})

file(GLOB LEWUBTUAR_CPP  ${CMAKE_CURRENT_SOURCE_DIR}/Left_Window_Tip_Area Left_Window_Tip_Area/*.cpp)
set(FILE_CPP_I ${LEWUBTUAR_CPP})

# main
file(GLOB IMA_H  ${CMAKE_CURRENT_SOURCE_DIR} *.h)
set(FILE_H_D ${IMA_H})

file(GLOB IMA_CPP  ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
set(FILE_CPP_D ${IMA_CPP})

#.h文件
source_group(Header\\Cards_Page FILES ${FILE_H_A})
source_group(Header\\Horizontal_Navigation_Page FILES ${FILE_H_B})
source_group(Header\\Playback_Page FILES ${FILE_H_C})
source_group(Header FILES ${FILE_H_D})
source_group(Header\\Cards_Page\\Menu_Set FILES ${FILE_H_E})
source_group(Header\\Cards_Page\\Menu_Set\\New_Menu_Component FILES ${FILE_H_F})
source_group(Header\\Singleton_Set FILES ${FILE_H_G})
source_group(Header\\Playback_Page\\Video_Components FILES ${FILE_H_H})
source_group(Header\\Left_Window_Tip_Area FILES ${FILE_H_I})

#.cpp文件
source_group(Source\\Cards_Page FILES ${FILE_CPP_A})
source_group(Source\\Horizontal_Navigation_Page FILES ${FILE_CPP_B})
source_group(Source\\Playback_Page FILES ${FILE_CPP_C})
source_group(Source FILES ${FILE_CPP_D})
source_group(Source\\Cards_Page\\Menu_Set FILES ${FILE_CPP_E})
source_group(Source\\Cards_Page\\Menu_Set\\New_Menu_Component FILES ${FILE_CPP_F})
source_group(Source\\Singleton_Set FILES ${FILE_CPP_G})
source_group(Source\\Playback_Page\\Video_Components FILES ${FILE_CPP_H})
source_group(Source\\Left_Window_Tip_Area FILES  ${FILE_CPP_I})


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Convenient_Anime_Manager
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Cards_Page/cards_page.h Cards_Page/cards_page.cpp
        Horizontal_Navigation_Page/horizontal_navigation_page.h Horizontal_Navigation_Page/horizontal_navigation_page.cpp
        Playback_Page/playback_page.h Playback_Page/playback_page.cpp
        Horizontal_Navigation_Page/horizontal_button.h Horizontal_Navigation_Page/horizontal_button.cpp
        Horizontal_Navigation_Page/button_slider_component.h Horizontal_Navigation_Page/button_slider_component.cpp
        Cards_Page/cardlayoutmanager.h Cards_Page/cardlayoutmanager.cpp
        Cards_Page/anime_card.h Cards_Page/anime_card.cpp
        img.qrc
        Cards_Page/Menu_Set/right_click_menu_set.h Cards_Page/Menu_Set/right_click_menu_set.cpp
        Cards_Page/Menu_Set/new_menu_set.h Cards_Page/Menu_Set/new_menu_set.cpp
        Cards_Page/Menu_Set/right_click_menu_button.h Cards_Page/Menu_Set/right_click_menu_button.cpp
        Cards_Page/Menu_Set/New_Menu_Component/input_box.h Cards_Page/Menu_Set/New_Menu_Component/input_box.cpp
        Cards_Page/Menu_Set/New_Menu_Component/Time_Button_Module.h Cards_Page/Menu_Set/New_Menu_Component/Time_Button_Module.cpp
        Cards_Page/Menu_Set/New_Menu_Component/Time_Selection_Module.h Cards_Page/Menu_Set/New_Menu_Component/Time_Selection_Module.cpp
        Cards_Page/Menu_Set/New_Menu_Component/function_button.h Cards_Page/Menu_Set/New_Menu_Component/function_button.cpp
        Singleton_Set/file_related.h Singleton_Set/file_related.cpp
        Singleton_Set/database_related.h Singleton_Set/database_related.cpp
        Singleton_Set/image_processing.h Singleton_Set/image_processing.cpp
        Playback_Page/video_playback_area.h Playback_Page/video_playback_area.cpp
        Playback_Page/video_control_area.h Playback_Page/video_control_area.cpp
        Playback_Page/video_episode_bar.h Playback_Page/video_episode_bar.cpp
        Playback_Page/video_info_bar.h Playback_Page/video_info_bar.cpp
        Cards_Page/ratio_slider.h Cards_Page/ratio_slider.cpp
        Playback_Page/Video_Components/episode_button.h Playback_Page/Video_Components/episode_button.cpp
        Singleton_Set/central_bundle_bridge.h Singleton_Set/central_bundle_bridge.cpp
        Singleton_Set/status_group.h Singleton_Set/status_group.cpp
        Playback_Page/Video_Components/back_button.h Playback_Page/Video_Components/back_button.cpp
        Cards_Page/customscrollbar.h Cards_Page/customscrollbar.cpp
        Playback_Page/video_episode_bar_shell.h Playback_Page/video_episode_bar_shell.cpp
        Playback_Page/Video_Components/progress_bar.h Playback_Page/Video_Components/progress_bar.cpp
        Playback_Page/Video_Components/control_area.h Playback_Page/Video_Components/control_area.cpp
        Playback_Page/Video_Components/control_button.h Playback_Page/Video_Components/control_button.cpp

        Playback_Page/Video_Components/playback_status_button.h Playback_Page/Video_Components/playback_status_button.cpp
        Horizontal_Navigation_Page/show_all.h Horizontal_Navigation_Page/show_all.cpp
        Left_Window_Tip_Area/left_window_tip.h Left_Window_Tip_Area/left_window_tip.cpp






    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Convenient_Anime_Manager APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Convenient_Anime_Manager SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Convenient_Anime_Manager
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Convenient_Anime_Manager PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Convenient_Anime_Manager PRIVATE Qt6::Sql)
target_link_libraries(Convenient_Anime_Manager PRIVATE Qt6::MultimediaWidgets)
target_link_libraries(Convenient_Anime_Manager PRIVATE Qt6::Multimedia)
target_link_libraries(Convenient_Anime_Manager PRIVATE Qt6::OpenGLWidgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Convenient_Anime_Manager)
endif()
set_target_properties(Convenient_Anime_Manager PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Convenient_Anime_Manager
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Convenient_Anime_Manager)
endif()
