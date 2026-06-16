cmake_minimum_required(VERSION 3.16)

project(AlocadoraDeFilmes VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontre a versão correta do Qt (Qt6 ou Qt5)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
        main.cpp
        login.cpp
        login.h
        login.ui
)

# Condicional para versão do Qt (Qt6 ou Qt5)
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(AlocadoraDeFilmes
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        moviesys.h moviesys.cpp moviesys.ui
        cadastro.h cadastro.cpp cadastro.ui
        acervo.h acervo.cpp acervo.ui
        aluguel.h aluguel.cpp aluguel.ui
        Images.qrc
        signup.h signup.cpp signup.ui
        cliente.h cliente.cpp cliente.ui
        ingresso.h ingresso.cpp ingresso.ui
        perfil.h perfil.cpp perfil.ui
        filme.h filme.cpp filme.ui
    )
else()
    if(ANDROID)
        add_library(AlocadoraDeFilmes SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(AlocadoraDeFilmes
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Vinculação das bibliotecas Qt necessárias, incluindo QtSql
target_link_libraries(AlocadoraDeFilmes PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui)

# Configurações de bundle para macOS (se necessário)
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.AlocadoraDeFilmes)
endif()

# Definindo propriedades do alvo
set_target_properties(AlocadoraDeFilmes PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Instalar o projeto
include(GNUInstallDirs)
install(TARGETS AlocadoraDeFilmes
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalizar o CMake no Qt6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(AlocadoraDeFilmes)
endif()
find_package(Qt6 REQUIRED COMPONENTS Core Sql)
